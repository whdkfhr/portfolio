#include "KinectCamData.h"

KinectCamData::KinectCamData()
	: m_pImg_3_RGB(NULL)
	, m_pImg_3_IR(NULL)
	, m_pImg_3_Depth(NULL)
	, m_pImg_3_BodyIndex(NULL)
{
	destory_IplImages();
	init_IplImages();

//	printf_s("Initialize the CVMgr\n");
}

KinectCamData::~KinectCamData()
{
	destory_IplImages();
}

void KinectCamData::destory_IplImages()
{
	if(m_pImg_3_RGB)
	{
		cvReleaseImage(&m_pImg_3_RGB);
		m_pImg_3_RGB = NULL;
	}

	if(m_pImg_3_IR)
	{
		cvReleaseImage(&m_pImg_3_IR);
		m_pImg_3_IR = NULL;
	}

	if(m_pImg_3_Depth)
	{
		cvReleaseImage(&m_pImg_3_Depth);
		m_pImg_3_Depth = NULL;
	}

	delete m_pImg_3_BodyIndex;

	/*
	if (m_pImg_3_BodyIndex)
	{
		cvReleaseImage(&m_pImg_3_BodyIndex);
		m_pImg_3_BodyIndex = NULL;
	}
	*/


//	cvDestroyWindow(_WndTitle_Color_);
//	cvDestroyWindow(_WndTitle_IR_);
//	cvDestroyWindow(_WndTitle_Depth_);
//	cvDestroyWindow(_WndTitle_Body_);

	printf_s("Destroy the CVMgr\n");
}

void KinectCamData::init_IplImages()
{
	if(m_pImg_3_RGB)
	{
		cvReleaseImage(&m_pImg_3_RGB);
		m_pImg_3_RGB = NULL;
	}
	m_pImg_3_RGB = cvCreateImage(cvSize(_Color_Width_, _Color_Height_), IPL_DEPTH_8U, 3);

	if(m_pImg_3_IR)
	{
		cvReleaseImage(&m_pImg_3_IR);
		m_pImg_3_IR = NULL;
	}
	m_pImg_3_IR = cvCreateImage(cvSize(_IR_Width_, _IR_Height_), IPL_DEPTH_8U, 3);

	if(m_pImg_3_Depth)
	{
		cvReleaseImage(&m_pImg_3_Depth);
		m_pImg_3_Depth = NULL;
	}
	m_pImg_3_Depth = cvCreateImage(cvSize(_IR_Width_, _IR_Height_), IPL_DEPTH_8U, 3);

	m_pImg_3_BodyIndex = new Mat(_BodyIndex_Height_, _BodyIndex_Width_, CV_8UC3);
	/*
	if (m_pImg_3_BodyIndex)
	{
		cvReleaseImage(&m_pImg_3_BodyIndex);
		m_pImg_3_BodyIndex = NULL;
	}
	m_pImg_3_BodyIndex = cvCreateImage(cvSize(_Body_Width_, _Body_Height_), IPL_DEPTH_8U, 3); // is it right?
	*/
//	cvNamedWindow(_WndTitle_Color_);
//	cvNamedWindow(_WndTitle_IR_);
//	cvNamedWindow(_WndTitle_Depth_);
//	cvNamedWindow(_WndTitle_Body_);

	printf_s("Initialize the CVMgr's variables\n");
}

BOOL KinectCamData::Render()	// not used
{
//	cvShowImage(_WndTitle_Color_, m_pImg_3_RGB);
//	cvShowImage(_WndTitle_IR_, m_pImg_3_IR);
//	cvShowImage(_WndTitle_Depth_, m_pImg_3_Depth);
//	cvShowImage(_WndTitle_Body_, m_pImg_3_BodyIndex);

	//ESC key
	if(cvWaitKey(10) == 27)
	{
		return FALSE;
	}
	
	return TRUE;
}
