#ifndef PLAYER_H
#define PLAYER_H
#define NOMINMAX	// for kinect, for no error

/*
	thanks to http://codingexodus.blogspot.kr/2012/12/working-with-video-using-opencv-and-qt.html
*/

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <string>

// For OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

// For Detection
#include "detection/Detection.h"
#include "detection/HandOnFaceDetection.h"
#include "detection/TurtleNeckDetection.h"
#include "detection/TwistedBackDetection.h"

// for recording
#include "Record.h"

// for kinect
#include "kinect/KinectManager.h"

// multi-thread
#include <thread>
#include <mutex>

// for chart
#include <QtCore/QTimer>

using namespace cv;

const string RGB_FILE = "C:/Users/Tae-Ik/Desktop/rgb6.avi";
const string IR_FILE = "C:/Users/Tae-Ik/Desktop/ir6.avi";
const string DEPTH_FILE = "C:/Users/Tae-Ik/Desktop/depth6.avi";
const int TIMER_INTERVAL = 500;	// 500ms

class Player : public QThread
{
	Q_OBJECT

signals:
	// signal to output frame to be displayed
	void set1stWidget(const QImage &image);
	void set2ndWidget(const QImage &image);
	void set3rdWidget(const QImage &image);
	
	// signals for each summary
	void setForwardHeadProgressBar(const int);
	void setTwistedBackProgressBar(const qreal);
	void setHandOnFaceCount(const int);
	
	// signals for each charts
	void update_forward_head_chart_signal(const qreal time, const qint16 grade);
	void update_slant_posture_chart_signal(const qreal time, const qreal value);
	void update_hand_on_face_chart_signal(const qreal time, const bool is_detected);
	void whether_to_scroll_signal(const qreal time);

	// Signal to MainWindow for alert
	void handOnFaceSignal();
	void turtleNeckSignal();
	void twistedBackSignal();

	// for debug in local video playing
	void player_echo(const QString& message);

private slots:
	void onTimeout();

protected:
	void processBasicCamImage();
	void processLocalVideo();
	void processKinectImage();

	void run();
	void msleep(int ms);

	void turtle_neck_thread_function();
	void twisted_back_thread_function();
	void hand_on_face_thread_function();

public:
	static const __int64 FRAME_FATE = 30 / 2;
	static const __int64 SLEEP_PERIOD = 50000;

	Player(QObject *parent = 0);
	~Player();

//	bool loadLocalVideo(std::string filename);
	bool loadLocalVideos();
	bool loadBasicCam();
	bool loadKinectCam();

	// for recording
	bool getIsRecording() const;
	void startRecording();
	void stopRecording();

	void disConnect();
	bool isConnected() const;

	void setKinectConnect();

	void Play();
	void Stop();
	bool isStopped() const;

	void set_whether_turtle_neck(const bool setting) { detect_turtle_neck = setting; }
	void set_whether_twisted_back(const bool setting) { detect_twisted_back = setting; }
	void set_whether_hand_on_face(const bool setting) { detect_hand_on_face = setting; }

	// detection thread start, stop
	void start_turtle_neck_detect();
	void start_twisted_back_detect();
	void start_hand_on_face_detect();

	void stop_turtle_neck_detect();
	void stop_twisted_back_detect();
	void stop_hand_on_face_detect();

private:

	// thread
	bool stop;
	QMutex mutex;
	QWaitCondition condition;

	// for saving origin frame
	Mat rgb_origin_mat;
	Mat ir_origin_mat;
	Mat depth_origin_mat;
	Mat bodyIndex_origin_mat;

	// for saving each frame
	Mat rgb_mat;
	Mat ir_mat;
	Mat depth_mat;
	Mat bodyIndex_mat;

	// for saving body joints
	vector<Joint> rgb_joints;
	vector<Joint> ir_joints;

	// for saving detected?? frame
	Mat one_mat;
	Mat two_mat;
	Mat three_mat;

	// after converted from Mat to QImage
	QImage one_Qimage;
	QImage two_Qimage;
	QImage three_Qimage;

	// for recording
	Record* rgb_record;
	Record* ir_record;
	Record* depth_record;
	bool isRecording;

	// for local video loading
	VideoCapture rgb_capture;
	VideoCapture ir_capture;
	VideoCapture depth_capture;
	__int64 rgb_framerate;
	__int64 ir_framerate;
	__int64 depth_framerate;

	int delay;

	// three detection as multi-thread
	std::thread *turtle_neck_thread;
	std::thread *twisted_back_thread;
	std::thread *hand_on_face_thread;

	std::mutex kinect_process_mutex;

	// stop flags for each multi-thread
	bool turtle_neck_detection_stop;
	bool twisted_back_detection_stop;
	bool hand_on_face_detection_stop;

	TurtleNeckDetection turtleNeckDetection;
	TwistedBackDetection twistedBackDetection;
	HandOnFaceDetection handOnFaceDetection;

	// q chart time 
	qreal elapsed_time;
	QTimer timer;

	// whether to detect
	bool detect_turtle_neck;
	bool detect_twisted_back;
	bool detect_hand_on_face;

	// flags
	bool isLocalVideoConnection;
	bool isBasicCamConnection;
	bool isKinnectConnection;

//	KinectCamData *kinect_cam_data;
	KinectManager *kinect_manager;

	// just for system optimization
	CascadeClassifier upperbody_classifier;
	Rect upperbody;

	uchar get_median_depthvalue_at(const Point& point, const Rect& upper_body);
	bool is_right_upperbody(const Rect& upperbody);
	Rect opti_get_upperbody(CascadeClassifier& classifier, const Mat& frame);
};

#endif // VIDEOPLAYER_H