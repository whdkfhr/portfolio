#pragma once

#include <opencv2\opencv.hpp>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "NoDetectedFaceException.h"
#include "NoDetectedUpperbodyException.h"

#include <iostream>	// for stringstream

using namespace cv;

class Detection
{
public:
	void set_rgb_frame(const Mat& rgb_frame) { this->rgb_frame = rgb_frame.clone(); }
	void set_ir_frame(const Mat& ir_frame) { this->ir_frame = ir_frame.clone(); }
	void set_depth_frame(const Mat& depth_frame) { this->depth_frame = depth_frame.clone(); }

	const Mat& get_rgb_frame() const { return rgb_frame; }
	const Mat& get_ir_frame() const { return ir_frame; }
	const Mat& get_depth_frame() const { return depth_frame; }

	const Mat& get_processed_frame() const { return processed_frame; }

	virtual bool detect() = 0;

protected:
	Mat rgb_frame;
	Mat ir_frame;
	Mat depth_frame;

	Mat processed_frame;
};

