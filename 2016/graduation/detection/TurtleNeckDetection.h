#pragma once

#include "Detection.h"

class TurtleNeckDetection :
	public Detection
{
public:
	TurtleNeckDetection();
	virtual bool detect();
	~TurtleNeckDetection();

	int get_degree() const { return degree; }

	// just for optimization of the system 
	void set_upperbody_ir_space(const Rect& upperbody) { this->upperbody_ir_space = upperbody; }

private:
	// main module
	Rect get_upperbody(const Mat& frame);

	// sub modules
	uchar get_median_depthvalue_at(const Point& point, const Rect& upper_body);
	uchar get_median(vector<uchar>& val);
	bool is_right_upperbody(const Rect& upperbody);

	// fields for detection
	CascadeClassifier upperbody_classifier;
	Rect upperbody_ir_space;

	// If depth diff is 1 ~ 5, degree == depth diff; else if more than 5, degree = 5; else 0
	int degree;
};

