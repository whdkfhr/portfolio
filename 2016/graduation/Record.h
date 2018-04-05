#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>

using namespace cv;
using namespace std;

class Record
{
public:
	static const int FOURCC = 1; //CV_FOURCC();

	Record();
	~Record();
	bool open(const string& file_name, const double fps, const double width, const double height);
	void release();
	void write(const Mat& frame);

private:
	VideoWriter* video_writer;
};