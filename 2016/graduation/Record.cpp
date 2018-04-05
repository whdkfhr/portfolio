#include "Record.h"


Record::Record()
{
	video_writer = new VideoWriter();
}


Record::~Record()
{
	release();
	delete video_writer;
}

bool Record::open(const string& file_name, const double fps, const double width, const double height)
{
	Size framesize(width, height);// = Size(width, height);
	return video_writer->open(file_name, FOURCC, fps, framesize, true);
}

void Record::release()
{
	video_writer->release();
}

void Record::write(const Mat& frame)
{
	video_writer->write(frame);
}