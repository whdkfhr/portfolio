#include "TwistedBackDetection.h"

#include <iostream>
#include <fstream>

TwistedBackDetection::TwistedBackDetection()
{
	FaceClassifier.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml");

	rgb_frame = NULL;
	ir_frame = NULL;
	depth_frame = NULL;

	processed_frame = NULL;

	//---------- 1.

	CornerRange = 0;
	startLeftX = 0;
	startRightX = 0;
	startY = 0;

	LeftTop = 0;
	RightTop = 0;

	ShoulderHeightTolerance = 0;
	HeightGapValue = 0;
	isShoulderSymmetry = true;

	//---------- 2.

	CenterOfForeheadX = 0;
	CenterOfForeheadY = 0;

	CenterOfUpperbodyX = 0;
	CenterOfUpperbodyY = 0;

	ubMLX = 0;
	ubMRX = 0;
	ubMidX = 0;
	ubPointCnt = 0;

	CenterAlignTolerance = 0;
	SineValue = 0.0;
	isCenterAligned = true;

	//----------
	SkewnessValue = 0.0;
	isWrongPosture = false;

	fontColor = cv::Scalar(255, 255, 255);

	regionL = 0;
	regionR = 0;

	FaceIndex = -1;

	FaceClassifier.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml");
}

bool TwistedBackDetection::detect()
{
	try {
		// convert captured frame to gray scale & equalize
		// cv::cvtColor(ir_frame, grayframe, CV_BGR2GRAY);

		if (body_index_frame.empty()) {
			ir_frame.convertTo(grayframe, -1, 2.5, 0);
			//cv::threshold(processed_frame, grayframe, 5, 255, 0);
			cv::Canny(grayframe, cannyframe, 100, 300);
		}
		else {
			cv::cvtColor(body_index_frame, grayframe, CV_BGR2GRAY);
			cv::equalizeHist(grayframe, grayframe);
			cv::Canny(grayframe, cannyframe, 200, 600);
		}

		// threshold(grayframe, grayframe, 200, 255, THRESH_BINARY_INV);
		// bitwise_and(grayframe, depth_frame, grayframe

		// find index of largest face
		FaceIndex = faceDetection();

		if (FaceIndex > -1)   // 얼굴을 찾았을 때
		{
			//cout << "The index of face is " << FaceIndex << "." << endl;

			cv::Point lb(faces[FaceIndex].x + faces[FaceIndex].width,
				faces[FaceIndex].y + faces[FaceIndex].height);
			cv::Point tr(faces[FaceIndex].x, faces[FaceIndex].y);

			// 얼굴에 사각형 그리기
			cv::rectangle(processed_frame, lb, tr, cv::Scalar(0, 255, 0), 3, 4, 0);

			isShoulderSymmetry = checkShoulderSymmetry2(FaceIndex);
			isCenterAligned = checkCenterAligned2(FaceIndex);
			HeightGapValue = (HeightGapValue == 0) ? 1 : HeightGapValue;
			SkewnessValue = SineValue * HeightGapValue * (CenterOfUpperbodyY - CenterOfForeheadY) / (ubMRX - ubMLX);

			if (SkewnessValue < 3.0) {
				fontColor = cv::Scalar(255, 255, 255);
				isWrongPosture = false;
			} else {
				fontColor = cv::Scalar(255, 0, 0);
				isWrongPosture = true;
			}

			stringstream ssSkewnessValue, ssWrongPosture;
			ssSkewnessValue << "Skewness Value: " << SkewnessValue;
			cv::putText(processed_frame, ssSkewnessValue.str(), cv::Point(10, 105), cv::FONT_HERSHEY_DUPLEX, 0.7f, fontColor, 1, CV_AA);
		}
		else {   // 얼굴을 찾지 못했을 때
			//cout << "Cannot find any face." << endl;
		}

		/*if (isWrongPosture)
		{
			stringstream ssWrongPosture;
			ssWrongPosture << "Wrong Posture!";
			cv::putText(processed_frame, ssWrongPosture.str(), cv::Point(365, 20), cv::FONT_HERSHEY_DUPLEX, 0.7f, cv::Scalar(255, 255, 255), 1, CV_AA);
		}*/

		processed_frame = grayframe;
	}
	catch (cv::Exception& e) {
		//   return true;
		cerr << "Exception occurred. Ignoring frame... " << e.err
			<< endl;
	}

	//   cannyframe.release();

	return isWrongPosture;
}

TwistedBackDetection::~TwistedBackDetection()
{
}

int TwistedBackDetection::faceDetection() {
	int faceIndex = -1;
	int faceWidth = 0;
	FaceClassifier.detectMultiScale(ir_frame, faces,
		1.1, // increase search scale by 10% each pass
		3,   // merge groups of three detections
		CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE,
		cv::Size(30, 30));

	// find index of largest face
	for (int i = 0; i < faces.size(); i++) {
		if (faces[i].width >= faceWidth) {
			faceWidth = faces[i].width;
			faceIndex = i;
		}
	}
	return faceIndex;
}

bool TwistedBackDetection::checkShoulderSymmetry(int fi) {
	CornerRange = faces[fi].width / 2;
	startLeftX = faces[fi].x - faces[fi].width / 2;
	startLeftX = startLeftX < 0 ? 0 : startLeftX;
	startRightX = faces[fi].x + faces[fi].width * 3 / 2;
	startRightX = startRightX > cannyframe.cols ? (cannyframe.cols - 1) : startRightX;
	startY = faces[fi].y + faces[fi].height * 3 / 2;
	startY = startY > cannyframe.rows ? (cannyframe.rows - 1) : startY;
	LeftTop = startY;
	RightTop = startY;

	ShoulderHeightTolerance = cannyframe.rows / 10;

	for (int i = 0; i < CornerRange; i++) {
		if (cannyframe.at<uchar>(startY, startLeftX + i) > 250) {
			cv::circle(processed_frame, cv::Point(startLeftX + i, startY), 1, cv::Scalar(255, 0, 0), 2, 4, 0);
		}
		if (cannyframe.at<uchar>(startY, startRightX - i) > 250) {
			cv::circle(processed_frame, cv::Point(startRightX - i, startY), 1, cv::Scalar(255, 0, 0), 2, 4, 0);
		}
		if (cannyframe.at<uchar>(startY - i, startLeftX) > 250) {
			cv::circle(processed_frame, cv::Point(startLeftX, startY - i), 1, cv::Scalar(255, 0, 0), 2, 4, 0);
			LeftTop = LeftTop > (startY - i) ? (startY - i) : LeftTop;
		}
		if (cannyframe.at<uchar>(startY - i, startRightX) > 250) {
			cv::circle(processed_frame, cv::Point(startRightX, startY - i), 1, cv::Scalar(255, 0, 0), 2, 4, 0);
			RightTop = RightTop > (startY - i) ? (startY - i) : RightTop;
		}
	}

	int HeightGap = LeftTop - RightTop;
	HeightGap = HeightGap < 0 ? (-1) * HeightGap : HeightGap;
	HeightGapValue = HeightGap;

	stringstream ssHeightGap;
	ssHeightGap << "Height Gap(pixel): " << HeightGap;
	cv::putText(processed_frame, ssHeightGap.str(), cv::Point(10, 85), cv::FONT_HERSHEY_DUPLEX, 0.7f, cv::Scalar(255, 255, 255), 1, CV_AA);

	if (HeightGap < ShoulderHeightTolerance) {
		return true;
	}
	else {
		return false;
	}
}

bool TwistedBackDetection::checkShoulderSymmetry2(int fi) {
	bool LeftDetected = false;
	bool RightDetected = false;
	int i = 0;

	CornerRange = faces[fi].width / 2;
	startLeftX = faces[fi].x - faces[fi].width / 2;
	startLeftX = startLeftX < 0 ? 0 : startLeftX;
	startRightX = faces[fi].x + faces[fi].width * 3 / 2;
	startRightX = startRightX > cannyframe.cols ? (cannyframe.cols - 1) : startRightX;
	startY = faces[fi].y + faces[fi].height * 3 / 2;
	startY = startY > cannyframe.rows ? (cannyframe.rows - 1) : startY;
	LeftTop = startY;
	RightTop = startY;

	ShoulderHeightTolerance = cannyframe.rows / 10;

	while (!LeftDetected) // for finding Left shoulder edge
	{
		if (cannyframe.at<uchar>(startY - i, startLeftX) > 250) {
			cv::circle(processed_frame, cv::Point(startLeftX, startY - i), 1, cv::Scalar(255, 0, 0), 2, 4, 0);
			LeftTop = startY - i;
			LeftDetected = true;
			regionL = 1;
		}
		if (i++ > CornerRange)
			break;
	}

	i = 0;

	while (!LeftDetected) // if Left shoulder edge was not detected yet (just for drawing position)
	{
		if (cannyframe.at<uchar>(startY, startLeftX + i) > 250) {
			cv::circle(processed_frame, cv::Point(startLeftX + i, startY), 1, cv::Scalar(255, 0, 0), 2, 4, 0);
			LeftDetected = true;
			regionL = 2;
			ubMLX = startLeftX + i;
		}
		if (i++ > CornerRange)
			break;
	}

	i = 0;

	while (!RightDetected) // for finding Right shoulder edge
	{
		if (cannyframe.at<uchar>(startY - i, startRightX) > 250) {
			cv::circle(processed_frame, cv::Point(startRightX, startY - i), 1, cv::Scalar(255, 0, 0), 2, 4, 0);
			RightTop = startY - i;
			RightDetected = true;
			regionR = 3;
		}
		if (i++ > CornerRange)
			break;
	}

	i = 0;

	while (!RightDetected) // if Right shoulder edge was not detected yet (just for drawing position)
	{
		if (cannyframe.at<uchar>(startY, startRightX - i) > 250) {
			cv::circle(processed_frame, cv::Point(startRightX - i, startY), 1, cv::Scalar(255, 0, 0), 2, 4, 0);
			RightDetected = true;
			regionR = 4;
			ubMRX = startRightX - i;
		}
		if (i++ > CornerRange)
			break;
	}

	while (!LeftDetected)
	{
		LeftTop = faces[fi].y + faces[fi].height;
		LeftDetected = true;
	}

	while (!RightDetected)
	{
		RightTop = faces[fi].y + faces[fi].height;
		RightDetected = true;
	}

	int HeightGap = LeftTop - RightTop;
	HeightGap = HeightGap < 0 ? (-1) * HeightGap : HeightGap;
	HeightGapValue = HeightGap;

	stringstream ssHeightGap;
	ssHeightGap << "Height Gap(pixel): " << HeightGap;
	cv::putText(processed_frame, ssHeightGap.str(), cv::Point(10, 85), cv::FONT_HERSHEY_DUPLEX, 0.7f, cv::Scalar(255, 255, 255), 1, CV_AA);

	if (HeightGap < ShoulderHeightTolerance) {
		return true;
	}
	else {
		return false;
	}
}

bool TwistedBackDetection::checkCenterAligned(int fi) {
	CenterOfForeheadX = faces[fi].x + faces[fi].width / 2;
	CenterOfForeheadY = faces[fi].y;

	cv::circle(processed_frame, cv::Point(CenterOfForeheadX, CenterOfForeheadY),
		4, cv::Scalar(255, 0, 0), 2, 4, 0); // pointing on center of forehead
	/*cv::line(processed_frame, cv::Point(CenterOfForeheadX, CenterOfForeheadY), cv::Point(CenterOfForeheadX, CenterOfForeheadY + faces[fi].height),
	cv::Scalar(255, 255, 255));*/

	int ubStartX = faces[fi].x - faces[fi].width;
	ubStartX = ubStartX < 0 ? 0 : ubStartX;
	int ubEndX = faces[fi].x + 2 * faces[fi].width;
	//cout << "x : " << faces[fi].x << ", width" << faces[fi].width; // test
	ubEndX = ubEndX > cannyframe.cols ? (cannyframe.cols - 1) : ubEndX;
	int ubY = faces[fi].y + faces[fi].height * 3 / 2;
	ubY = ubY > cannyframe.rows ? (cannyframe.rows - 1) : ubY;
	CenterOfUpperbodyY = ubY;
	//cout << cannyframe.cols << ", " << cannyframe.rows << endl;

	/*cv::circle(processed_frame, cv::Point(ubStartX, ubY), 2, cv::Scalar(0, 255, 0), 2, 4, 0);
	cv::circle(processed_frame, cv::Point(ubEndX, ubY), 2, cv::Scalar(0, 255, 0), 2, 4, 0);*/

	ubMLX = 0;
	ubMRX = 0;
	ubMidX = 0;
	ubPointCnt = 0;

	for (int i = ubStartX; i < ubEndX; i++)
	{
		if (cannyframe.at<uchar>(ubY, i) > 250) {
			if (ubPointCnt == 0) ubMLX = i;
			ubMRX = i;
			//cv::circle(processed_frame, cv::Point(i, ubY), 2, cv::Scalar(0, 0, 255), 2, 4, 0);
			ubPointCnt++;
		}
	}

	ubMidX = (ubMLX + ubMRX) / 2;

	cv::circle(processed_frame, cv::Point(ubMLX, ubY), 4, cv::Scalar(255, 0, 0), 2, 4, 0);
	cv::circle(processed_frame, cv::Point(ubMRX, ubY), 4, cv::Scalar(255, 0, 0), 2, 4, 0);
	cv::circle(processed_frame, cv::Point(ubMidX, ubY), 4, cv::Scalar(255, 0, 0), 2, 4, 0);

	stringstream ubMidPoint, centerOfFacePoint;
	centerOfFacePoint << "Center of Face: " << CenterOfForeheadX << ", " << CenterOfForeheadY;
	ubMidPoint << "Center of Body: " << ubMidX << ", " << ubY;
	cv::putText(processed_frame, centerOfFacePoint.str(), cv::Point(10, 25), cv::FONT_HERSHEY_DUPLEX, 0.7f, cv::Scalar(255, 255, 255), 1, CV_AA);
	cv::putText(processed_frame, ubMidPoint.str(), cv::Point(10, 45), cv::FONT_HERSHEY_DUPLEX, 0.7f, cv::Scalar(255, 255, 255), 1, CV_AA);

	int gap = (CenterOfForeheadX - ubMidX) < 0 ? (ubMidX - CenterOfForeheadX) : (CenterOfForeheadX - ubMidX);
	SineValue = gap / sqrt(pow(gap, 2) + pow(CenterOfForeheadY - ubY, 2));
	CenterAlignTolerance = faces[fi].width / 5;

	stringstream ssSineValue;
	ssSineValue << "Sine Value: " << SineValue;
	cv::putText(processed_frame, ssSineValue.str(), cv::Point(10, 65), cv::FONT_HERSHEY_DUPLEX, 0.7f, cv::Scalar(255, 255, 255), 1, CV_AA);

	if (gap < CenterAlignTolerance) {
		return true;
	}
	else {
		return false;
	}
}

bool TwistedBackDetection::checkCenterAligned2(int fi) {
	CenterOfForeheadX = faces[fi].x + faces[fi].width / 2;
	CenterOfForeheadY = faces[fi].y;

	cv::circle(processed_frame, cv::Point(CenterOfForeheadX, CenterOfForeheadY),
		4, cv::Scalar(255, 0, 0), 2, 4, 0);
	/*cv::line(processed_frame, cv::Point(CenterOfForeheadX, CenterOfForeheadY), cv::Point(CenterOfForeheadX, CenterOfForeheadY + faces[fi].height),
	cv::Scalar(255, 255, 255));*/

	// set X range for detection
	int ubMinX = faces[fi].x - faces[fi].width;
	ubMinX = ubMinX < 0 ? 0 : ubMinX;
	int ubMaxX = faces[fi].x + 2 * faces[fi].width;
	//cout << "x : " << faces[fi].x << ", width" << faces[fi].width; // test
	ubMaxX = ubMaxX >(cannyframe.cols - 1) ? (cannyframe.cols - 1) : ubMaxX;

	int ubY = faces[fi].y + faces[fi].height * 3 / 2;
	ubY = ubY > cannyframe.rows ? (cannyframe.rows - 1) : ubY;
	CenterOfUpperbodyY = ubY;
	//cout << cannyframe.cols << ", " << cannyframe.rows << endl;

	/*cv::circle(processed_frame, cv::Point(ubMinX, ubY), 2, cv::Scalar(0, 255, 0), 2, 4, 0);
	cv::circle(processed_frame, cv::Point(ubMaxX, ubY), 2, cv::Scalar(0, 255, 0), 2, 4, 0);*/

	if (regionL != 2) {
		ubMLX = ubMinX;
		for (int i = faces[fi].x; i > ubMinX; i--)
		{
			if (cannyframe.at<uchar>(ubY, i) > 250) {
				ubMLX = i;
				break;
			}
		}
	}

	if (regionR != 4) {
		ubMRX = ubMaxX;
		for (int i = (faces[fi].x + faces[fi].width); i < ubMaxX; i++)
		{
			if (cannyframe.at<uchar>(ubY, i) > 250) {
				ubMRX = i;
				break;
			}
		}
	}

	ubMidX = (ubMLX + ubMRX) / 2;

	cv::circle(processed_frame, cv::Point(ubMLX, ubY), 4, cv::Scalar(255, 0, 0), 2, 4, 0);
	cv::circle(processed_frame, cv::Point(ubMRX, ubY), 4, cv::Scalar(255, 0, 0), 2, 4, 0);
	cv::circle(processed_frame, cv::Point(ubMidX, ubY), 4, cv::Scalar(255, 0, 0), 2, 4, 0);

	stringstream ubMidPoint, centerOfFacePoint;
	centerOfFacePoint << "Center of Face: " << CenterOfForeheadX << ", " << CenterOfForeheadY;
	ubMidPoint << "Center of Body: " << ubMidX << ", " << ubY;
	cv::putText(processed_frame, centerOfFacePoint.str(), cv::Point(10, 25), cv::FONT_HERSHEY_DUPLEX, 0.7f, cv::Scalar(255, 255, 255), 1, CV_AA);
	cv::putText(processed_frame, ubMidPoint.str(), cv::Point(10, 45), cv::FONT_HERSHEY_DUPLEX, 0.7f, cv::Scalar(255, 255, 255), 1, CV_AA);

	int gap = (CenterOfForeheadX - ubMidX) < 0 ? (ubMidX - CenterOfForeheadX) : (CenterOfForeheadX - ubMidX);
	SineValue = gap / sqrt(pow(gap, 2) + pow(CenterOfForeheadY - ubY, 2));
	CenterAlignTolerance = faces[fi].width / 5;

	stringstream ssSineValue;
	ssSineValue << "Sine Value: " << SineValue;
	cv::putText(processed_frame, ssSineValue.str(), cv::Point(10, 65), cv::FONT_HERSHEY_DUPLEX, 0.7f, cv::Scalar(255, 255, 255), 1, CV_AA);

	if (gap < CenterAlignTolerance) {
		return true;
	}
	else {
		return false;
	}
}

double TwistedBackDetection::getSkewnessValue() {
	if (SkewnessValue < 10) {
		return SkewnessValue;
	}
	else {
		return 10;
	}
}