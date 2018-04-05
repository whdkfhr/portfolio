#pragma once

#include "Detection.h"
#include <cmath>

using namespace std;

class TwistedBackDetection :
	public Detection
{
public:
	TwistedBackDetection();
	virtual bool detect();
	~TwistedBackDetection();

	const Mat& get_body_index_processed() const { return body_index_frame; }
	void set_body_index_frame(const Mat& body_index_frame) { this->body_index_frame = body_index_frame.clone(); }
	double getSkewnessValue();

private:
	cv::Mat frame_original;
	cv::Mat frame_gradient;
	//cv::Mat ir_frame;

	cv::Mat grayframe;
	cv::Mat cannyframe;

	//---------- 1.

	int CornerRange;
	int startLeftX;
	int startRightX;
	int startY;

	int LeftTop;
	int RightTop;

	int ShoulderHeightTolerance;
	int HeightGapValue;
	bool isShoulderSymmetry;

	//---------- 2.

	int CenterOfForeheadX;
	int CenterOfForeheadY;

	int CenterOfUpperbodyX;
	int CenterOfUpperbodyY;

	int ubMLX;
	int ubMRX;
	int ubMidX;
	int ubPointCnt;

	int CenterAlignTolerance;
	double SineValue;
	bool isCenterAligned;

	// synthesis
	double SkewnessValue;
	bool isWrongPosture;

	cv::Scalar fontColor;

	int regionL;
	int regionR;

	// face detection configuration
	cv::CascadeClassifier FaceClassifier;
	int FaceIndex;
	vector<cv::Rect> faces; // a vector array to store the face found

	Mat body_index_frame;

	int faceDetection();

	bool checkShoulderSymmetry(int fi);
	bool checkShoulderSymmetry2(int fi);
	bool checkCenterAligned(int fi);
	bool checkCenterAligned2(int fi);
};