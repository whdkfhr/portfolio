#include "HandOnFaceDetection.h"

const float WIDTH_RATIO = 3.75f;
const float HEIGHT_RATIO = 2.547170f;// *1.2f; // for rgb

const float FACE_BASE_X_RATIO = 0.32f;
const float FACE_BASE_Y_RATIO = 0.1f;
const float FACE_WIDTH = 0.4;
const float FACE_HEIGHT = 0.5;

const int DEPTH_THRESHOLD = 1;
const int DEPTH_MINUS = 5;
const int DEPTH_HAND_RADIUS = 15;


HandOnFaceDetection::HandOnFaceDetection()
{
	rgb_frame = NULL;
	ir_frame = NULL;
	depth_frame = NULL;

	processed_frame = NULL;

//	face_classifier.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml");
	upperbody_classifier.load("C:/opencv/sources/data/haarcascades/haarcascade_mcs_upperbody.xml");
//	upperbody_classifier.load("C:/opencv/sources/data/haarcascades/haarcascade_upperbody.xml");

	radius = 0;
	detected = false;
	cumulative_count = 0;
	is_hand_rising = false;
}

bool HandOnFaceDetection::detect()
{
//	processed_frame = get_skin_by_binary(rgb_frame);

	try {
		// find upperbody and face
	//	upperbody_ir_space = get_upperbody(ir_frame);

		// just for optimization part
		if ( upperbody_ir_space.x == 0 && upperbody_ir_space.y == 0 && 
				upperbody_ir_space.width == 0 && upperbody_ir_space.height == 0 ) return false;

		Rect face_ir_space = get_face_by_upperbody(upperbody_ir_space);


		/* depth part */

		// convert to gray scale
		cvtColor(depth_frame, depth_frame, CV_BGR2GRAY);
		equalizeHist(depth_frame, depth_frame);

		// process depth frame
		delete_background(upperbody_ir_space, depth_frame);
		delete_face(face_ir_space, depth_frame);

		get_hand_by_depth(depth_frame);

		Point depth_hand_center = get_hand_center(depth_frame, radius);

		if (radius > DEPTH_HAND_RADIUS && !is_in_face_rect(face_ir_space, depth_hand_center)) {
			// drar hand position
			ellipse(ir_frame, depth_hand_center, Size(20, 20), 0, 0, 360, Scalar(255, 125, 125), 4, 8, 0);

			if (detected == false) is_hand_rising = true;
			else is_hand_rising = false;
			
			if (is_hand_rising) {
				cumulative_count++;
			}
			detected = true;
		}
		else {
			detected = false;
		}
			


		/* rgb part */

		//Rect upperbody_rgb_space = ir_space_rect_to_rgb_space(upperbody_ir_space);
		//Rect face_rgb_space = ir_space_rect_to_rgb_space(face_ir_space);

		//get_skin_by_binary(upperbody_rgb_space, rgb_frame, processed_frame);
	
		//delete_face(face_rgb_space, processed_frame);

		//Point rgb_hand_center = get_hand_center(processed_frame, radius);

		//if (radius > DEPTH_HAND_RADIUS && !is_in_face_rect(face_rgb_space, rgb_hand_center)) {
		//	// draw hand position
		//	ellipse(rgb_frame, rgb_hand_center, Size(80, 80), 0, 0, 360, Scalar(255, 125, 125), 15, 8, 0);

		//	if (detected == false) is_hand_rising = true;
		//	else is_hand_rising = false;
		//	
		//	if (is_hand_rising) {
		//		cumulative_count++;
		//	}
		//	detected = true;
		//}
		//else {
		//	detected = false;
		//}
			


	//	if ( radius > 10 )
	//		ellipse(rgb_frame, rgb_hand_center, Size(15, 15), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);


	//	Point depth_hand_center = get_hand_center(depth_processed, radius);
	//	draw_hand_center(depth_processed, depth_hand_center);

		// bitwise_and of rgb_processed & depth_processed
	//	ir_space_mat_to_rgb_space(depth_processed, depth_processed);
	//	bitwise_and(processed_frame, rgb_space_depth, processed_frame);

		// just for test
	//	bitwise_or(rgb_frame, rgb_space_depth, rgb_frame);
		
	}
	catch (const NoDetectedFaceException& e)
	{
		detected = false;
	}
	catch (const NoDetectedUpperbodyException& e)
	{
		detected = false;
	}

	return detected;
}

HandOnFaceDetection::~HandOnFaceDetection()
{

}



////////////////////////////////////////////////////////////////////////////
//////////////////////////// private members ///////////////////////////////
////////////////////////////////////////////////////////////////////////////

bool HandOnFaceDetection::is_in_face_rect(const Rect& face_rect, const Point& point)
{
	return (face_rect.y <= point.y && point.y < face_rect.y + face_rect.height) &&
		(face_rect.x <= point.x && point.x < face_rect.x + face_rect.width);
}

bool HandOnFaceDetection::is_in_upperbody(const Rect& rect, int row, int col)
{
	return (rect.y <= row && row < rect.y + rect.height) &&
		(rect.x <= col && col < rect.x + rect.width);
}

Rect HandOnFaceDetection::get_upperbody(const Mat& frame)
{
	// convert to gray scale	
	Mat grayframe;
	cvtColor(frame, grayframe, CV_BGR2GRAY);
	equalizeHist(grayframe, grayframe);

	vector<Rect> upperbodys;
	upperbody_classifier.detectMultiScale(grayframe, upperbodys,
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

//	if (!is_right_upperbody(upperbodys[index])) throw NoDetectedUpperbodyException("Error:no detected upperbody");

	return upperbodys[index];
}

Rect HandOnFaceDetection::get_face_by_upperbody(const Rect& upperbody)
{
	int x_base = upperbody.x + upperbody.width * FACE_BASE_X_RATIO;
	int y_base = upperbody.y + upperbody.height * FACE_BASE_Y_RATIO;

	Rect face = Rect(x_base, y_base, upperbody.width * FACE_WIDTH, upperbody.height * FACE_HEIGHT);

//	Point test = Point(x_base, y_base);
//	ellipse(ir_frame, test, Size(7, 7), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);

//	rectangle(ir_frame, face, Scalar(0, 0, 255), 3, 4, 0);

	return face;
}

void HandOnFaceDetection::delete_face(const Rect& face, Mat& frame) {
	Scalar scalar;
	if (frame.channels() == 3) {
		scalar = Scalar(0, 0, 0);
	}
	else {
		scalar = Scalar(0);
	}

	int x = face.x;
	int h_temp = face.height;    // storing original height
	int y = face.y - h_temp*0.5; // y is reduced by 0.3*h
	int w = face.width;
	int h = h_temp * 1.6;

	Rect new_face = Rect(x, y, w, h);

	rectangle(frame, new_face, scalar, CV_FILLED, 8, 0);

	//	cv::cvtColor(frame, frame, CV_BGR2GRAY);
	//for (int i = face.x; i < face.x + face.width; i++) {
	//	for (int j = face.y; j < face.y + face.height; j++) {
	//		//	ellipse(frame, Point(i, j), Size(10, 10), 0, 0, 360, Scalar(255, 0, 125), 4, 8, 0);
	//		if (frame.channels() == 3) {
	//			frame.at<Vec3b>(j, i) = Vec3b(0, 0, 0);
	//		}
	//		else {
	//			frame.at<uchar>(j, i) = 0;
	//		}
	//		/*frame.at<Vec3b>(j, i)[0] = 255;
	//		frame.at<Vec3b>(j, i)[1] = 255;
	//		frame.at<Vec3b>(j, i)[2] = 255;*/
	//	}
	//}
}

Point HandOnFaceDetection::get_hand_center(const Mat& hand_by_binary, double& radius) {
	Mat dst;
	distanceTransform(hand_by_binary, dst, CV_DIST_L2, CV_DIST_MASK_5);  //결과는 CV_32SC1 타입

	//거리 변환 행렬에서 값(거리)이 가장 큰 픽셀의 좌표와, 값을 얻어온다.
	int maxIdx[2];
	minMaxIdx(dst, NULL, &radius, NULL, maxIdx, hand_by_binary);

	return Point(maxIdx[1], maxIdx[0]);
}

void HandOnFaceDetection::draw_hand_center(Mat& hand_by_binary, const Point& center) {
	erode(hand_by_binary, hand_by_binary, Mat(3, 3, CV_8U, Scalar(1)), Point(-1, -1), 2);

	//	Point center = get_hand_center(hand_by_binary, radius);

	//중심점
	circle(hand_by_binary, center, 2, Scalar(125), -1);

	//손바닥 
	circle(hand_by_binary, center, (int)(radius + 0.5), Scalar(125), 2);
}

void HandOnFaceDetection::get_hand_by_depth(Mat& depth_image)
{
	//Mat gray_image;
	//cvtColor(depth_image, gray_image, CV_BGR2GRAY);
	//equalizeHist(gray_image, gray_image);

	int frequency[256] = { 0 };

	for (int i = 0; i < depth_image.rows; i++) {
		for (int j = 0; j < depth_image.cols; j++) {
			int index = depth_image.at<uchar>(i, j);
			frequency[index]++;
		}
	}

	//int max_depth = 200;
	//for (int depth = 200; depth < 256; depth++) {
	//	if (max_depth < frequency[depth]) max_depth = depth;
	//}

	int max_depth = 0;
	for (int depth = 200; depth < 256; depth++) {
		if (DEPTH_THRESHOLD < frequency[depth]) max_depth = depth;
	}

	threshold(depth_image, depth_image, max_depth - DEPTH_MINUS, 255, THRESH_BINARY);
}

void HandOnFaceDetection::delete_background(const Rect& upperbody, Mat& depth_frame)
{
	for (int i = 0; i < depth_frame.rows; i++) {
		for (int j = 0; j < depth_frame.cols; j++) {

			if (!is_in_upperbody(upperbody, i, j))
				depth_frame.at<uchar>(Point(j, i)) = 0;
		}
	}
}




////////////////////////////////////////////////////////
////////////////////// not used/////////////////////////

Rect HandOnFaceDetection::get_face(const Mat& frame) {
	// convert to gray scale	
	Mat grayframe;
	cvtColor(frame, grayframe, CV_BGR2GRAY);
	equalizeHist(grayframe, grayframe);

	vector<Rect> faces;

	face_classifier.detectMultiScale(grayframe, faces,
		1.1, // increase search scale by 10% each pass
		4,   // merge groups of three detections
		CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE,
		Size(25, 25));


	if (faces.size() == 0) throw NoDetectedFaceException("Error:no detected face");

	// find the maximum size of detected faces
	int index = 0;
	for (int i = 1; i < faces.size(); i++) {
		if (faces[i].width > faces[index].width) index = i;
	}

	return faces[index];
}


void HandOnFaceDetection::get_skin_by_binary(const Rect& upperbody, const Mat& rgb_frame, Mat& binaryed_frame)
{
	binaryed_frame = Mat(rgb_frame.size(), CV_8U, Scalar(0));

	rectangle(binaryed_frame, upperbody, Scalar(125), 3, 4, 0);

	for (int i = 0; i < rgb_frame.rows; i++) {
		const Vec3b* ith_row = rgb_frame.ptr<Vec3b>(i);

		for (int j = 0; j < rgb_frame.cols; j++) {

			if (!is_in_upperbody(upperbody, i, j)) continue;

			uchar R = ith_row[j][0];
			uchar G = ith_row[j][1];
			uchar B = ith_row[j][2];


			if (R > 95 && G > 40 && B > 20 && max(R, max(G, B)) - min(R, min(G, B)) > 15 && abs(R - G) > 15 && R > G && R > B)
				binaryed_frame.at<uchar>(i, j) = 255;
		}
	}
}

Rect HandOnFaceDetection::ir_space_rect_to_rgb_space(const Rect& rect_ir_space) {
	int rgb_x = rect_ir_space.x * WIDTH_RATIO + 50;
	int rgb_y = rect_ir_space.y * HEIGHT_RATIO;
	int rgb_width = rect_ir_space.width * WIDTH_RATIO;
	int rgb_height = rect_ir_space.height * HEIGHT_RATIO;

	return Rect(rgb_x, rgb_y, rgb_width, rgb_height);
}

void HandOnFaceDetection::ir_space_mat_to_rgb_space(const Mat& mat_ir_space, Mat& mat_rgb_space) {
	//cv::Mat(ir->height, ir->width, CV_32FC1, ir->data).copyTo(irmat);
	//irmat.convertTo(irmat, CV_8U, 1, 0);
	//resize(irmat, irmat, cvSize(1920, 1080);
	//cv::Mat(depth->height, depth->width, CV_32FC1, depth->data).copyTo(depthmat);
	//cv::Mat(rgb->height, rgb->width, CV_8UC4, rgb->data).copyTo(rgbmat, irmat);

	//	resize(mat_ir_space, mat_rgb_space, cvSize(1920, 1080));
	resize(mat_ir_space, mat_rgb_space, cvSize(1920, 1080));
}
