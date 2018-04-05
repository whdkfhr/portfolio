#pragma once

#include "define.h"

class KinectCamData
{
public:
	KinectCamData(void);	
	~KinectCamData(void);

	const IplImage* get_pRGB_IplImage() const { return m_pImg_3_RGB; }
	const IplImage* get_pIR_IplImage() const { return m_pImg_3_IR; }
	const IplImage* get_pDepth_IplImage() const { return m_pImg_3_Depth; }

	Mat* get_pBodyIndex_Mat() { return m_pImg_3_BodyIndex; }

	BOOL Render(); // not used

private:
	IplImage *m_pImg_3_RGB;
	IplImage *m_pImg_3_IR;
	IplImage *m_pImg_3_Depth;

	Mat *m_pImg_3_BodyIndex; 

//	void Init_CVMgr();
	void init_IplImages();
	void destory_IplImages();
};

