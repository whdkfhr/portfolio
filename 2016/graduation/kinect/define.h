#pragma once

//////////////////////////////////////////////////////////////////////////
// Kinect Header files
//////////////////////////////////////////////////////////////////////////
#include <Kinect.h>
#pragma comment(lib, "kinect20.lib")

//////////////////////////////////////////////////////////////////////////
//		Opencv
//////////////////////////////////////////////////////////////////////////
//OpenCV headers
#include <QtWidgets/QMainWindow>
#include "opencv2/opencv.hpp"

/*
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
*/

#ifdef DEBUG
// //OpenCV Lib - for debug mode
#pragma comment(lib, "opencv_core242d.lib")
#pragma comment(lib, "opencv_highgui242d.lib")
#pragma comment(lib, "opencv_calib3d242d.lib")
#pragma comment(lib, "opencv_imgproc242d.lib")
#pragma comment(lib, "opencv_flann242d.lib")
#pragma comment(lib, "opencv_features2d242d.lib")
#else
//OpenCV Lib - for release mode
#pragma comment(lib, "opencv_core2413.lib")
#pragma comment(lib, "opencv_highgui2413.lib")
#pragma comment(lib, "opencv_calib3d2413.lib")
#pragma comment(lib, "opencv_imgproc2413.lib")
#pragma comment(lib, "opencv_flann2413.lib")
#pragma comment(lib, "opencv_features2d2413.lib")
#endif

using namespace cv;
using namespace std;

// Safe release for interfaces
template<class Interface>
inline void SafeRelease(Interface *& pInterfaceToRelease)
{
	if (pInterfaceToRelease != NULL)
	{
		pInterfaceToRelease->Release();
		pInterfaceToRelease = NULL;
	}
}


#define		_Color_Width_			1920
#define		_Color_Height_			1080
#define		_WndTitle_Color_		"Window_for_RGB"

#define		_IR_Width_			512
#define		_IR_Height_			424
#define		_WndTitle_IR_		"Window_for_InfraRed(IR)"
#define		_WndTitle_Depth_		"Window_for_Depth"

#define		_BodyIndex_Width_			512
#define		_BodyIndex_Height_			424
#define		_WndTitle_Body_		"Window_for_Body"

// InfraredSourceValueMaximum is the highest value that can be returned in the InfraredFrame.
// It is cast to a float for readability in the visualization code.
#define InfraredSourceValueMaximum static_cast<float>(USHRT_MAX)

// The InfraredOutputValueMinimum value is used to set the lower limit, post processing, of the
// infrared data that we will render.
// Increasing or decreasing this value sets a brightness "wall" either closer or further away.
#define InfraredOutputValueMinimum 0.01f 

// The InfraredOutputValueMaximum value is the upper limit, post processing, of the
// infrared data that we will render.
#define InfraredOutputValueMaximum 1.0f

// The InfraredSceneValueAverage value specifies the average infrared value of the scene.
// This value was selected by analyzing the average pixel intensity for a given scene.
// Depending on the visualization requirements for a given application, this value can be
// hard coded, as was done here, or calculated by averaging the intensity for each pixel prior
// to rendering.
#define InfraredSceneValueAverage 0.08f

/// The InfraredSceneStandardDeviations value specifies the number of standard deviations
/// to apply to InfraredSceneValueAverage. This value was selected by analyzing data
/// from a given scene.
/// Depending on the visualization requirements for a given application, this value can be
/// hard coded, as was done here, or calculated at runtime.
#define InfraredSceneStandardDeviations 3.0f