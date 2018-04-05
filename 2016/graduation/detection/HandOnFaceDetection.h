#pragma once
#include "Detection.h"

class HandOnFaceDetection :
	public Detection
{
public:
	HandOnFaceDetection();
	virtual bool detect();
	~HandOnFaceDetection();

	const bool is_detected() const { return detected; }
	const int get_cumulative_count() const { return cumulative_count; }

	bool is_rising_edge() const { return is_hand_rising; }

	// just for optimization of the system 
	void set_upperbody_ir_space(const Rect& upperbody) { this->upperbody_ir_space = upperbody; }

private:

	Rect get_upperbody(const Mat& frame);
	Rect get_face_by_upperbody(const Rect& upperbody);

	bool is_in_upperbody(const Rect& rect, int row, int col);
	
	void delete_background(const Rect& upperbody, Mat& depth_frame);
	void delete_face(const Rect& face, Mat& frame);
	void get_hand_by_depth(Mat& depth_image);

	bool is_in_face_rect(const Rect& face_rect, const Point& point);

	double radius;
	bool detected;
	bool is_hand_rising;
	int cumulative_count;

	// fields for detection
	CascadeClassifier upperbody_classifier;
	Rect upperbody_ir_space;
	
	/* 
		not used
	*/
	Rect get_face(const Mat& frame);
	Point get_hand_center(const Mat& hand_by_binary, double& radius);
	void draw_hand_center(Mat& hand_by_binary, const Point& center);

	Rect ir_space_rect_to_rgb_space(const Rect& rect_ir_space);
	void ir_space_mat_to_rgb_space(const Mat& mat_ir_space, Mat& mat_rgb_space);
	void get_skin_by_binary(const Rect& upperbody, const Mat& rgb_frame, Mat& binaryed_frame);

	CascadeClassifier face_classifier;
};
