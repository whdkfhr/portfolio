#include "player.h"
#include <windows.h>	/* WinAPI */
#include <qmessagebox.h>	// for debug

/* Windows sleep in 100ns(10^-7 seconds) units */
BOOLEAN nanosleep(LONGLONG ns){
	/* Declarations */
	HANDLE timer;	/* Timer handle */
	LARGE_INTEGER li;	/* Time defintion */
	/* Create timer */
	if (!(timer = CreateWaitableTimer(NULL, TRUE, NULL)))
		return FALSE;
	/* Set timer properties */
	li.QuadPart = -ns;
	if (!SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE)){
		CloseHandle(timer);
		return FALSE;
	}
	/* Start & wait for timer */
	WaitForSingleObject(timer, INFINITE);
	/* Clean resources */
	CloseHandle(timer);
	/* Slept without problems */
	return TRUE;
}


// just for optimization

const __int16 MIN_DEPTH_VALUE = 223;	// 100cm, 3.1 cm / 1 depth
const float AVERAGE_DEPTH_SCALE = 0.02;

uchar get_median(vector<uchar>& val)
{
	uchar median;
	size_t size = val.size();
	sort(val.begin(), val.end());
	if (size % 2 == 0)  {
		median = val[size / 2 - 1];
	}
	else {
		median = val[size / 2];
	}
	return median;
}

uchar Player::get_median_depthvalue_at(const Point& point, const Rect& upper_body)
{
	Mat gray_scale;
	cvtColor(depth_mat, gray_scale, CV_BGR2GRAY);

	int x_start = point.x - static_cast<int>(ceil(upper_body.width * AVERAGE_DEPTH_SCALE));
	int x_end = point.x + static_cast<int>(floor(upper_body.width * AVERAGE_DEPTH_SCALE));

	int y_start = point.y - static_cast<int>(ceil(upper_body.height * AVERAGE_DEPTH_SCALE));
	int y_end = point.y + static_cast<int>(floor(upper_body.height * AVERAGE_DEPTH_SCALE));

	int num_of_depth = (y_end - y_start) * (x_end - x_start);

	vector<uchar> depths(num_of_depth);
	int index = 0;

	for (int x = x_start; x < x_end; x++) {
		for (int y = y_start; y < y_end; y++) {
			//	ellipse(ir_frame, Point(x, y), Size(0.1, 0.1), 0, 0, 360, Scalar(255, 0, 125), 3, 8, 0);
			uchar current_depth = gray_scale.at<uchar>(Point(x, y));
			depths[index] = current_depth;
			index++;
		}
	}

	return get_median(depths);
	//	return gray_scale.at<uchar>(point);
}

bool Player::is_right_upperbody(const Rect& upperbody)
{
	Point upperbody_center(upperbody.x + upperbody.width * 0.5, upperbody.y + upperbody.height * 0.5);
	if (get_median_depthvalue_at(upperbody_center, upperbody) < MIN_DEPTH_VALUE) return false;
	return true;
}

Rect Player::opti_get_upperbody(CascadeClassifier& classifier, const Mat& frame)
{
	// convert to gray scale	
	Mat grayframe;
	cvtColor(frame, grayframe, CV_BGR2GRAY);
	equalizeHist(grayframe, grayframe);

	vector<Rect> upperbodys;
	classifier.detectMultiScale(grayframe, upperbodys,
		1.1,
		3,
		CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE,
		Size(80, 80));

	if (upperbodys.size() == 0) throw NoDetectedUpperbodyException("Error:no detected upperbody");

	// find the maximum size of detected upper bodys
	int index = 0;
	for (int i = 1; i < upperbodys.size(); i++) {
		if (upperbodys[i].width > upperbodys[index].width) index = i;
	}

	if (!is_right_upperbody(upperbodys[index])) throw NoDetectedUpperbodyException("Error:no detected upperbody");

	return upperbodys[index];
}




// public

Player::Player(QObject *parent)
	: QThread(parent)
{
	isLocalVideoConnection = false;
	isBasicCamConnection = false;
	isKinnectConnection = false;

	stop = true;

	kinect_manager = NULL;

	turtle_neck_thread = NULL;
	twisted_back_thread = NULL;
	hand_on_face_thread = NULL;

	turtle_neck_detection_stop = true;
	twisted_back_detection_stop = true;
	hand_on_face_detection_stop = true;

	// default : false
	detect_turtle_neck = false;
	detect_twisted_back = false;
	detect_hand_on_face = false;

	rgb_record = new Record();
	ir_record = new Record();
	depth_record = new Record();

	isRecording = false;

	delay = 0;

	elapsed_time = 0.0;
	timer.setInterval(TIMER_INTERVAL);

	connect(&timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
	
	// just for optimization
	upperbody_classifier.load("C:/opencv/sources/data/haarcascades/haarcascade_mcs_upperbody.xml");
}

// bool Player::loadLocalVideo(std::string filename) {
bool Player::loadLocalVideos() {
	rgb_capture.open(RGB_FILE);
	ir_capture.open(IR_FILE);
	depth_capture.open(DEPTH_FILE);

	isLocalVideoConnection = true;
	isBasicCamConnection = false;
	isKinnectConnection = false;

	if (rgb_capture.isOpened())
	{
		rgb_framerate = (int)rgb_capture.get(CV_CAP_PROP_FPS);
		return true;
	}
	return false;
}

bool Player::loadBasicCam() {
	rgb_capture.open(0);

	isLocalVideoConnection = false;
	isBasicCamConnection = true;
	isKinnectConnection = false;

	if (rgb_capture.isOpened())
	{
		rgb_framerate = (int)rgb_capture.get(CV_CAP_PROP_FPS);
		return true;
	}
	return false;
}

bool Player::loadKinectCam() {
	isLocalVideoConnection = false;
	isBasicCamConnection = false;
	isKinnectConnection = true;

//	kinect_cam_data = new KinectCamData;
	kinect_manager = new KinectManager;

//	kinect_manager->setKinectCamData(kinect_cam_data);
//	kinect_manager->setKinectCamData();

	if (kinect_manager == NULL) {
		return false;
	} 

//	return !(kinect_manager->m_pKinectSensor);
	return true;
}

void Player::disConnect() {
	rgb_capture.release();

	isLocalVideoConnection = false;
	isBasicCamConnection = false;
	isKinnectConnection = false;

	delete kinect_manager;
//	delete kinect_cam_data;

	kinect_manager = NULL;
//	kinect_cam_data = NULL;
}

bool Player::isConnected() const {
	if (isKinnectConnection)
	{
		if (kinect_manager == NULL) {
			return false;
		}
	//	BOOLEAN isOpened = false;
	//	return SUCCEEDED(kinect_manager->m_pKinectSensor->get_IsOpen(&isOpened));

	//	return kinect_manager->m_pKinectSensor;
		return true;
	}
	else
	{
		return rgb_capture.isOpened();
	}
}

void Player::setKinectConnect() {
	isKinnectConnection = true;
}

void Player::Play()
{
	if (!isRunning()) {
		if (isStopped()){
			stop = false;
		}
		
		start(LowPriority);
	//	start(HighPriority);

		//while (!isRunning())
		//	; // do nothing


	//	kinect_manager->Update_Color();
	//	kinect_manager->Update_IR();
	//	kinect_manager->Update_Depth();
	////	kinect_manager->Update_BodyIndex();
	//	//	kinect_manager->Update_Body();
	//	//	kinect_manager->FPS_Render();

	//	// get frames from kinect_manager
	//	rgb_origin_mat = cvarrToMat(&kinect_manager->getRGBIplImage());
	//	ir_origin_mat = cvarrToMat(&kinect_manager->getIRIplImage());
	//	depth_origin_mat = cvarrToMat(&kinect_manager->getDepthIplImage());
	//	bodyIndex_origin_mat = kinect_manager->getBodyIndexMat();


		if (detect_turtle_neck)
			start_turtle_neck_detect();
		
		if (detect_twisted_back)
			start_twisted_back_detect();

		if (detect_hand_on_face)
			start_hand_on_face_detect();


		//turtle_neck_detection_stop = false;
		//twisted_back_detection_stop = false;
		//hand_on_face_detection_stop = false;

		timer.start();
	}

}

void Player::run()
{
	if (isKinnectConnection)
	{
		processKinectImage();
	}
	else if (isBasicCamConnection)
	{
		processBasicCamImage();
	}
	else if (isLocalVideoConnection)
	{
		processLocalVideo();
	}
	else
	{
		// do nothing
	}
}

void Player::Stop()
{
	//turtle_neck_detection_stop = true;
	//twisted_back_detection_stop = true;
	//hand_on_face_detection_stop = true;

	//delete turtle_neck_thread;
	//delete twisted_back_thread;
	//delete hand_on_face_thread;


	stop_turtle_neck_detect();
	stop_twisted_back_detect();
	stop_hand_on_face_detect();

	stop = true;

	timer.stop();
}


void Player::processKinectImage() {

	while (!stop){
		
		kinect_process_mutex.lock();

		// process kinect
		kinect_manager->Update_Color();
		kinect_manager->Update_IR();
		kinect_manager->Update_Depth();
	//	kinect_manager->Update_BodyIndex();
	//	kinect_manager->Update_Body();
	//	kinect_manager->FPS_Render();

		// get frames from kinect_manager
		rgb_origin_mat = cvarrToMat(&kinect_manager->getRGBIplImage());
		ir_origin_mat = cvarrToMat(&kinect_manager->getIRIplImage());
		depth_origin_mat = cvarrToMat(&kinect_manager->getDepthIplImage());
	//	bodyIndex_origin_mat = kinect_manager->getBodyIndexMat();
	//	rgb_joints = kinect_manager->get_rgb_joints();
	//	ir_joints = kinect_manager->get_ir_joints();

		// convert BGR to RGB
		cvtColor(rgb_origin_mat, rgb_mat, CV_BGR2RGB);
		cvtColor(ir_origin_mat, ir_mat, CV_BGR2RGB);
		cvtColor(depth_origin_mat, depth_mat, CV_BGR2RGB);
	//	cvtColor(bodyIndex_origin_mat, bodyIndex_mat, CV_BGR2RGB);
		
		// just for optimiation
		try {
			upperbody = opti_get_upperbody(upperbody_classifier, ir_mat);
		}
		catch (const NoDetectedUpperbodyException& e) {
			upperbody = Rect(0, 0, 0, 0);
		}

		kinect_process_mutex.unlock();


		if (!detect_turtle_neck)
			emit set1stWidget(QImage((const unsigned char*)(depth_mat.data),
			depth_mat.cols, depth_mat.rows, QImage::Format_RGB888));

		if (!detect_twisted_back)
			emit set2ndWidget(QImage((const unsigned char*)(ir_mat.data),
			ir_mat.cols, ir_mat.rows, QImage::Format_RGB888));

		if (!detect_hand_on_face)
			emit set3rdWidget(QImage((const unsigned char*)(rgb_mat.data),
			rgb_mat.cols, rgb_mat.rows, QImage::Format_RGB888));

		//if (!detect_hand_on_face)
		//	emit set3rdWidget(QImage((const unsigned char*)(ir_mat.data),
		//	ir_mat.cols, ir_mat.rows, QImage::Format_RGB888));


		//// testing code, present body joints
		//for (int i = 0; i < rgb_joints.size(); i++) {
		//	Point point(rgb_joints[i].Position.X, rgb_joints[i].Position.Y);
		//	ellipse(rgb_mat, point, Size(15, 15), 0, 0, 360, Scalar(255, 0, 0), 4, 8, 0);
		//}


		//for (int i = 0; i < ir_joints.size(); i++) {
		//	Point point(ir_joints[i].Position.X, ir_joints[i].Position.Y);
		//	ellipse(ir_mat, point, Size(15, 15), 0, 0, 360, Scalar(255, 0, 0), 4, 8, 0);
		//}

		//stringstream ss;
		//ss << ir_joints.size();

		//QString fuck = QString::fromStdString(ss.str());

		//emit processedStatusBar(fuck);

		//stringstream ss;
		//ss << joints.size();
		//ellipse(rgb_mat, joints[JointType_WristRight], Size(15, 15), 0, 0, 360, Scalar(255, 0, 0), 4, 8, 0);
		//ss << joints[JointType_WristRight].x << ", " << joints[JointType_WristRight].y << " ";

		//QString fuck = QString::fromStdString(ss.str());

		//emit processedStatusBar(fuck);


		// in case of recording
		if (isRecording) {
			rgb_record->write(rgb_origin_mat);
			ir_record->write(ir_origin_mat);
			depth_record->write(depth_origin_mat);
		}

	//	nanosleep(SLEEP_PERIOD);
	}
}

void Player::processBasicCamImage() {
	
	while (!stop){
		if (!rgb_capture.read(rgb_mat))
		{
			stop = true;
		}

		if (rgb_mat.channels() == 3){
			cv::cvtColor(rgb_mat, rgb_mat, CV_BGR2RGB);
			one_Qimage = QImage((const unsigned char*)(rgb_mat.data), 
				rgb_mat.cols, rgb_mat.rows, QImage::Format_RGB888);
		}
		else
		{
			one_Qimage = QImage((const unsigned char*)(rgb_mat.data),
				rgb_mat.cols, rgb_mat.rows, QImage::Format_Indexed8);
		}

		emit set1stWidget(one_Qimage);
	//	emit set2ndWidget(two_Qimage);
	//	emit set3rdWidget(three_Qimage);

		if (isRecording) {
			rgb_record->write(rgb_mat);
		//	ir_record->write(ir_bgr_mat);
		//	depth_record->write(depth_bgr_mat);
		}

		nanosleep(SLEEP_PERIOD);
	}
}

void Player::processLocalVideo()
{
	delay = (10000000 / rgb_framerate);	// never change it..

	while (!stop){

		kinect_process_mutex.lock();

		if (!rgb_capture.read(rgb_origin_mat) || !ir_capture.read(ir_origin_mat) || !depth_capture.read(depth_origin_mat))
		{
			stop = true;
		}

		// convert BGR to RGB
		cvtColor(rgb_origin_mat, rgb_mat, CV_BGR2RGB);
		cvtColor(ir_origin_mat, ir_mat, CV_BGR2RGB);
		cvtColor(depth_origin_mat, depth_mat, CV_BGR2RGB);

		// just for optimiation
		try {
			upperbody = opti_get_upperbody(upperbody_classifier, ir_mat);
		}
		catch (Exception& e) {
			upperbody = Rect(0, 0, 0, 0);
		}

		kinect_process_mutex.unlock();


		if (!detect_turtle_neck)
			emit set1stWidget(QImage((const unsigned char*)(depth_mat.data),
			depth_mat.cols, depth_mat.rows, QImage::Format_RGB888));

		if (!detect_twisted_back)
			emit set2ndWidget(QImage((const unsigned char*)(ir_mat.data),
			ir_mat.cols, ir_mat.rows, QImage::Format_RGB888));

		if (!detect_hand_on_face)
			emit set3rdWidget(QImage((const unsigned char*)(rgb_mat.data),
			rgb_mat.cols, rgb_mat.rows, QImage::Format_RGB888));

		nanosleep(delay);
	}
}

void Player::msleep(int ms){	// not used
//	struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
//	nanosleep(&ts, NULL);

	nanosleep(ms);

//	Sleep(ms);
}

bool Player::isStopped() const{
	return this->stop;
}

bool Player::getIsRecording() const {
	return isRecording;
}

void Player::startRecording()
{
	rgb_record->open("record/rgb.avi", FRAME_FATE, rgb_mat.cols, rgb_mat.rows);
	ir_record->open("record/ir.avi", FRAME_FATE, ir_mat.cols, ir_mat.rows);
	depth_record->open("record/depth.avi", FRAME_FATE, depth_mat.cols, depth_mat.rows);

	isRecording = true;
}

void Player::stopRecording()
{
	mutex.lock();

	rgb_record->release();
	ir_record->release();
	depth_record->release();

	isRecording = false;

	condition.wakeOne();
	mutex.unlock();
}

Player::~Player()
{
	mutex.lock();
	stop = true;
	
	isLocalVideoConnection = false;
	isBasicCamConnection = false;
	isKinnectConnection = false;

	stop_turtle_neck_detect();
	stop_twisted_back_detect();
	stop_hand_on_face_detect();

	delete kinect_manager;
//	delete kinect_cam_data;
	
	delete rgb_record;
	delete ir_record;
	delete depth_record;

	rgb_capture.release();
	ir_capture.release();
	depth_capture.release();

	condition.wakeOne();
	mutex.unlock();
	wait();
}


////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// private slots /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

void Player::onTimeout()
{
	elapsed_time += 0.5;
	if (!turtle_neck_detection_stop) {
		emit update_forward_head_chart_signal(elapsed_time, turtleNeckDetection.get_degree());
	}

	if (!twisted_back_detection_stop) {
		emit update_slant_posture_chart_signal(elapsed_time, twistedBackDetection.getSkewnessValue());
	}

	if (!hand_on_face_detection_stop) {
		emit update_hand_on_face_chart_signal(elapsed_time, handOnFaceDetection.is_detected());
	}

	emit whether_to_scroll_signal(elapsed_time);
}


////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// detection thread functions ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

void Player::start_turtle_neck_detect()
{
	turtle_neck_detection_stop = false;
	turtle_neck_thread = new std::thread(&Player::turtle_neck_thread_function, this);
	turtle_neck_thread->detach();
}

void Player::start_twisted_back_detect()
{
	twisted_back_detection_stop = false;
	twisted_back_thread = new std::thread(&Player::twisted_back_thread_function, this);
	twisted_back_thread->detach();
}

void Player::start_hand_on_face_detect()
{
	hand_on_face_detection_stop = false;
	hand_on_face_thread = new std::thread(&Player::hand_on_face_thread_function, this);
	hand_on_face_thread->detach();
}



void Player::stop_turtle_neck_detect()
{
	if (!turtle_neck_detection_stop) {
		turtle_neck_detection_stop = true;
		delete turtle_neck_thread;
	}
	
	/*if (turtle_neck_thread->joinable() && !turtle_neck_detection_stop)
	{
		turtle_neck_detection_stop = true;
		turtle_neck_thread->join();
		emit processedStatusBar(QString::fromStdString("turtle neck join"));
		delete turtle_neck_thread;
	}*/
}

void Player::stop_twisted_back_detect()
{
	if (!twisted_back_detection_stop) {
		twisted_back_detection_stop = true;
		delete twisted_back_thread;
	}

	/*if (twisted_back_thread->joinable() && !twisted_back_detection_stop)
	{
		twisted_back_detection_stop = true;
		twisted_back_thread->join();
		emit processedStatusBar(QString::fromStdString("twisted back join"));
		delete twisted_back_thread;
	}*/
	
}

void Player::stop_hand_on_face_detect()
{
	if (!hand_on_face_detection_stop) {
		hand_on_face_detection_stop = true;
		delete hand_on_face_thread;
	}
	
	/*if (hand_on_face_thread->joinable() && !hand_on_face_detection_stop
	{
		hand_on_face_detection_stop = true;
		hand_on_face_thread->join();
		emit processedStatusBar(QString::fromStdString("hand on face join"));
		delete hand_on_face_thread;
	}*/
}



void Player::turtle_neck_thread_function()
{
//	TurtleNeckDetection turtleNeckDetection;

	while (!turtle_neck_detection_stop) {
		kinect_process_mutex.lock();
		turtleNeckDetection.set_ir_frame(ir_mat);
		turtleNeckDetection.set_depth_frame(depth_mat);
		turtleNeckDetection.set_upperbody_ir_space(upperbody);	// just for optimization
		kinect_process_mutex.unlock();

		if (turtleNeckDetection.detect()) {
			emit turtleNeckSignal();
		}

		one_mat = turtleNeckDetection.get_depth_frame();
		one_Qimage = QImage((const unsigned char*)(one_mat.data),
				one_mat.cols, one_mat.rows, QImage::Format_RGB888);

		emit set1stWidget(one_Qimage);
		emit setForwardHeadProgressBar(turtleNeckDetection.get_degree());

	//	qreal current_time = time.elapsed() / 1000.0;

	//	if (current_time - floor(current_time) < 0.1)
		//	emit update_forward_head_chart_signal(current_time, turtleNeckDetection.get_degree());

		nanosleep(delay);
	}
}

void Player::twisted_back_thread_function()
{
//	TwistedBackDetection twistedBackDetection;

	while (!twisted_back_detection_stop) {
		kinect_process_mutex.lock();
	//	twistedBackDetection.set_rgb_frame(rgb_mat);
		twistedBackDetection.set_ir_frame(ir_mat);
	//	twistedBackDetection.set_depth_frame(depth_mat);
	//	twistedBackDetection.set_body_index_frame(bodyIndex_mat);
		kinect_process_mutex.unlock();
		
		if (twistedBackDetection.detect()) {
			emit twistedBackSignal();
		}
		

		//one_mat = twistedBackDetection.get_body_index_processed();	
		//if (one_mat.channels() == 3)
		//{
		//	one_Qimage = QImage((const unsigned char*)(one_mat.data),
		//		one_mat.cols, one_mat.rows, QImage::Format_RGB888);
		//}
		//else
		//{
		//	one_Qimage = QImage((const unsigned char*)(one_mat.data),
		//		one_mat.cols, one_mat.rows, QImage::Format_Indexed8);
		//}

		//emit set1stWidget(one_Qimage);

		two_mat = twistedBackDetection.get_processed_frame();
		if (two_mat.channels() == 3)
		{
			two_Qimage = QImage((const unsigned char*)(two_mat.data),
				two_mat.cols, two_mat.rows, QImage::Format_RGB888);
		}
		else
		{
			two_Qimage = QImage((const unsigned char*)(two_mat.data),
				two_mat.cols, two_mat.rows, QImage::Format_Indexed8);
		}

		emit set2ndWidget(two_Qimage);
		emit setTwistedBackProgressBar(twistedBackDetection.getSkewnessValue());

		//three_mat = twistedBackDetection.get_ir_frame();
		//if (three_mat.channels() == 3)
		//{
		//	three_Qimage = QImage((const unsigned char*)(three_mat.data),
		//		three_mat.cols, three_mat.rows, QImage::Format_RGB888);
		//}
		//else
		//{
		//	three_Qimage = QImage((const unsigned char*)(three_mat.data),
		//		three_mat.cols, three_mat.rows, QImage::Format_Indexed8);
		//}
		//emit set3rdWidget(three_Qimage);
	}
}

void Player::hand_on_face_thread_function()
{
//	HandOnFaceDetection handOnFaceDetection;

	while (!hand_on_face_detection_stop) {
		kinect_process_mutex.lock();
	//	handOnFaceDetection.set_rgb_frame(rgb_mat);
		handOnFaceDetection.set_ir_frame(ir_mat);
		handOnFaceDetection.set_depth_frame(depth_mat);
		handOnFaceDetection.set_upperbody_ir_space(upperbody);	// just for optimization
		kinect_process_mutex.unlock();

		if (handOnFaceDetection.detect()) {
			emit handOnFaceSignal();
		}


		//two_mat = handOnFaceDetection.get_depth_processed();
		//emit set2ndWidget(QImage((const unsigned char*)(two_mat.data),
		//	two_mat.cols, two_mat.rows, QImage::Format_Indexed8));

		//two_mat = handOnFaceDetection.get_ir_frame();
		//emit set2ndWidget(QImage((const unsigned char*)(two_mat.data),
		//	two_mat.cols, two_mat.rows, QImage::Format_RGB888));

	//	three_mat = handOnFaceDetection.get_rgb_frame();
		three_mat = handOnFaceDetection.get_ir_frame();
	//	three_mat = handOnFaceDetection.get_processed_frame();
	//	three_mat = handOnFaceDetection.get_depth_frame();

		if (three_mat.channels() == 3)
		{
			three_Qimage = QImage((const unsigned char*)(three_mat.data),
				three_mat.cols, three_mat.rows, QImage::Format_RGB888);
		}
		else
		{
			three_Qimage = QImage((const unsigned char*)(three_mat.data),
				three_mat.cols, three_mat.rows, QImage::Format_Indexed8);
		}

		emit set3rdWidget(three_Qimage);
		emit setHandOnFaceCount(handOnFaceDetection.get_cumulative_count());

		//emit update_hand_on_face_chart_signal(time.elapsed() / 1000.0, handOnFaceDetection.is_detected());

		//if (handOnFaceDetection.is_rising_edge()) {
		//	emit update_hand_on_face_chart_signal(time.elapsed() / 1000.0, handOnFaceDetection.is_detected());

		//}
	}
}
