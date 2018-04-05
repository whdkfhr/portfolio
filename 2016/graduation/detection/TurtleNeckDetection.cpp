#include "TurtleNeckDetection.h"


const __int16 MIN_DEPTH_VALUE = 223;	// 100cm, 3.1 cm / 1 depth
const int TURTLENECK_THRESHOLD = 3;
const float AVERAGE_DEPTH_SCALE = 0.02;

const float IR_Height = 424;
const float EAR_TRAGUS_RATE_FROM_UPPERBODY_RECT = 0.38f;
const float NECK_RATE_FROM_UPPERBODY_RECT = 0.65f;
const float CHEST_RATE_FROM_UPPERBODY_RECT = 0.9f;

const Scalar EAR_TRAGUS_DEPTH_DISPLAY_COLOR = Scalar(0, 0, 255);
const Scalar CHEST_DEPTH_DISPLAY_COLOR = Scalar(200, 100, 75);


//float f(const Rect& upperbody_ir_space) {
//	return (static_cast<float>(upperbody_ir_space.height) / IR_Height) * (NECK_RATE_FROM_UPPERBODY_RECT - EAR_TRAGUS_RATE_FROM_UPPERBODY_RECT) * 100;
//}



////////////////////////////////////////////////////////////////////////////
//////////////////////////// public members ////////////////////////////////
////////////////////////////////////////////////////////////////////////////

TurtleNeckDetection::TurtleNeckDetection()
{
	rgb_frame = NULL;
	ir_frame = NULL;
	depth_frame = NULL;

	processed_frame = NULL;

	upperbody_classifier.load("C:/opencv/sources/data/haarcascades/haarcascade_mcs_upperbody.xml");
	
	degree = 0;
}


bool TurtleNeckDetection::detect()
{
	uchar ear_tragus_depth = 0;
	uchar chest_depth = 0;
	
	try
	{
	//	upperbody_ir_space = get_upperbody(ir_frame);

		// just for optimization part
		if (upperbody_ir_space.x == 0 && upperbody_ir_space.y == 0 &&
				upperbody_ir_space.width == 0 && upperbody_ir_space.height == 0) return false;

	//	if (!is_right_upperbody(upperbody_ir_space)) throw NoDetectedUpperbodyException("Error:no detected upperbody");

		rectangle(depth_frame, upperbody_ir_space, Scalar(0, 0, 255), 3, 4, 0);
	//	rectangle(ir_frame, upperbody_ir_space, Scalar(0, 0, 255), 3, 4, 0);
		//
		//for (float i = 0.1; i < 1.0; i += 0.1) {
		//	Point point = Point(upperbody_ir_space.x + upperbody_ir_space.width * 0.5, upperbody_ir_space.y + upperbody_ir_space.height * i);
		////	ellipse(ir_frame, point, Size(5, 5), 0, 0, 360, Scalar(255, 100, 255), 4, 8, 0);
		////	ellipse(depth_frame, point, Size(5, 5), 0, 0, 360, Scalar(255, 100, 255), 4, 8, 0);

		//	std::stringstream ss;
		//	ss << (int)get_median_depthvalue_at(point, upperbody_ir_space);

		//	string text = ss.str();
		//	putText(ir_frame, text, Point(point.x + 20, point.y), FONT_HERSHEY_SIMPLEX, 0.65, Scalar(34, 116, 28), 3);
		////	putText(depth_frame, text, Point(point.x + 20, point.y), FONT_HERSHEY_SIMPLEX, 0.65, Scalar(34, 116, 28), 3);
		//}

		Point ear_tragus = Point(upperbody_ir_space.x + upperbody_ir_space.width * 0.5, upperbody_ir_space.y + upperbody_ir_space.height * EAR_TRAGUS_RATE_FROM_UPPERBODY_RECT);
	//	ellipse(ir_frame, ear_tragus, Size(5, 5), 0, 0, 360, Scalar(255, 100, 255), 4, 8, 0);

	//	Point neck = Point(upperbody_ir_space.x + upperbody_ir_space.width * 0.5, upperbody_ir_space.y + upperbody_ir_space.height * NECK_RATE_FROM_UPPERBODY_RECT);
	//	ellipse(ir_frame, neck, Size(5, 5), 0, 0, 360, Scalar(255, 100, 255), 4, 8, 0);

		Point chest = Point(upperbody_ir_space.x + upperbody_ir_space.width * 0.5, upperbody_ir_space.y + upperbody_ir_space.height * CHEST_RATE_FROM_UPPERBODY_RECT);
	//	ellipse(ir_frame, chest, Size(7, 7), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
		
		ear_tragus_depth = get_median_depthvalue_at(ear_tragus, upperbody_ir_space);
		chest_depth = get_median_depthvalue_at(chest, upperbody_ir_space);
		
		// displaying text
		std::stringstream ss;

		ss << (int)ear_tragus_depth;
		string head_depth_text = ss.str();

		ss.str("");	// clear buffer

		ss << (int)chest_depth;
		string chest_depth_text = ss.str();

		// display
		ellipse(depth_frame, ear_tragus, Size(5, 5), 0, 0, 360, EAR_TRAGUS_DEPTH_DISPLAY_COLOR, 4, 8, 0);
		ellipse(depth_frame, chest, Size(5, 5), 0, 0, 360, CHEST_DEPTH_DISPLAY_COLOR, 4, 8, 0);

		putText(depth_frame, head_depth_text, Point(ear_tragus.x + 20, ear_tragus.y), FONT_HERSHEY_SIMPLEX, 1., EAR_TRAGUS_DEPTH_DISPLAY_COLOR, 3);
		putText(depth_frame, chest_depth_text, Point(chest.x + 20, chest.y), FONT_HERSHEY_SIMPLEX, 1., CHEST_DEPTH_DISPLAY_COLOR, 3);

		// get depth difference
		int depth_diff = ear_tragus_depth - chest_depth;

		// 1 ~ 5 degree based on depth diff
		if (depth_diff > 5) degree = 5;
		else if (depth_diff <= 0) degree = 0;
		else degree = depth_diff;


		processed_frame = depth_frame;

		if (depth_diff >= TURTLENECK_THRESHOLD)
		{
		//	putText(depth_frame, "detected!!", Point(depth_frame.cols - 150, 30), FONT_HERSHEY_SIMPLEX, 1., Scalar(255, 10, 10), 3);
			return true;
		}
		else
		{
			return false;
		}
	}
	catch (const NoDetectedUpperbodyException& e)
	{
		// rendered image
		processed_frame = depth_frame;

		return false;
	}

	/*

	Point center = Point(0 + ir_frame.cols * 0.5, 0 + ir_frame.rows * 0.5);
	ellipse(ir_frame, center, Size(10, 10), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
	ellipse(depth_frame, center, Size(10, 10), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);

	int center_depth = get_median_depthvalue_at(center);

	std::stringstream ss;
	ss << center_depth;

	string text = ss.str();

	putText(depth_frame, text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1., Scalar(100, 255, 125), 3);

	*/
	return false;
}

TurtleNeckDetection::~TurtleNeckDetection()
{
	// God God mat class automatically deallocate memory
}






////////////////////////////////////////////////////////////////////////////
//////////////////////////// private members ///////////////////////////////
////////////////////////////////////////////////////////////////////////////

Rect TurtleNeckDetection::get_upperbody(const Mat& frame) 
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

	return upperbodys[index];
}



// sub functions

uchar TurtleNeckDetection::get_median_depthvalue_at(const Point& point, const Rect& upper_body) 
{
	Mat gray_scale;
	cvtColor(depth_frame, gray_scale, CV_BGR2GRAY);

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

uchar TurtleNeckDetection::get_median(vector<uchar>& val)
{
	uchar median;
	size_t size = val.size();
	sort(val.begin(), val.end());
	if (size % 2 == 0)  {
		median = val[size / 2 - 1];
	} else {
		median = val[size / 2];
	}
	return median;
}

bool TurtleNeckDetection::is_right_upperbody(const Rect& upperbody) 
{
	Point upperbody_center(upperbody.x + upperbody.width * 0.5, upperbody.y + upperbody.height * 0.5);
	if (get_median_depthvalue_at(upperbody_center, upperbody) < MIN_DEPTH_VALUE) return false;
	return true;
}

