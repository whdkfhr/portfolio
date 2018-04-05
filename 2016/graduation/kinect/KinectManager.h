#pragma once

#include "define.h"
#include "KinectCamData.h"

class KinectManager
{
public:
	static const int NUM_OF_FRAME = 5;

	KinectManager(void)
		: m_pKinectSensor(NULL)
		, m_pCoordinateMapper(NULL)
		, m_pColorFrameReader(NULL)
		, m_pInfraredFrameReader(NULL)
		, m_pDepthFrameReader(NULL)
		, m_pBodyIndexReader(NULL)
		, m_pBodyFrameReader(NULL)
		, m_pColorRGBX(NULL)
		, cam_data(NULL)
	{
		Init_Kin2Mgr();
		cam_data = new KinectCamData;
	}

	~KinectManager(void)
	{
	//	setKinectCamData(NULL);
		Destroy_Kin2Mgr();
		delete cam_data;
	}

	//////////////////////////////////////////////////////////////////////////
	//Var
	//////////////////////////////////////////////////////////////////////////
	// Current Kinect
	IKinectSensor *m_pKinectSensor;

	// Kinect, for body?
	ICoordinateMapper*      m_pCoordinateMapper;

	// Color reader
	IColorFrameReader *m_pColorFrameReader;

	// Infrared reader
	IInfraredFrameReader *m_pInfraredFrameReader;

	// Depth reader
	IDepthFrameReader *m_pDepthFrameReader;

	// BodyIndex reader
	IBodyIndexFrameReader *m_pBodyIndexReader;

	// Body reader
	IBodyFrameReader *m_pBodyFrameReader;

	RGBQUAD *m_pColorRGBX;

	//FPS
	INT64 m_nStartTime[NUM_OF_FRAME];
	INT64 m_nLastCounter[NUM_OF_FRAME];
	double m_fFreq[NUM_OF_FRAME];
	INT64 m_nNextStatusTime[NUM_OF_FRAME];
	DWORD m_nFramesSinceUpdate[NUM_OF_FRAME];
	double m_fFPS[NUM_OF_FRAME];
	INT64 m_nProcTime[NUM_OF_FRAME];

	//////////////////////////////////////////////////////////////////////////
	//Func
	//////////////////////////////////////////////////////////////////////////
	void Init_Kin2Mgr();
	void Destroy_Kin2Mgr();

	/// <summary>
	/// Initializes the default Kinect sensor
	/// </summary>
	/// <returns>S_OK on success, otherwise failure code</returns>
	HRESULT InitializeDefaultSensor();

	/// <summary>
	/// Main processing function
	/// </summary>
	IColorFrame* pColorFrame = NULL;
	IInfraredFrame* pInfraredFrame = NULL;
	IDepthFrame* pDepthFrame = NULL;
	IBodyIndexFrame * pBodyIndexFrame = NULL;
	IBodyFrame* pBodyFrame = NULL;

	void Update_Color();
	void Update_IR();
	void Update_Depth();
	void Update_BodyIndex();
	void Update_Body();

	/// <summary>
	/// Handle new color data
	/// <param name="nTime">timestamp of frame</param>
	/// <param name="pBuffer">pointer to frame data</param>
	/// <param name="nWidth">width (in pixels) of input image dat</param>
	/// <param name="nHeight">height (in pixels) of input image data</param>
	/// </summary>
	void ProcessColor(INT64 nTime, RGBQUAD* pBuffer, int nWidth, int nHeight);

	/// <summary>
	/// Handle new infrared data
	/// <param name="nTime">timestamp of frame</param>
	/// <param name="pBuffer">pointer to frame data</param>
	/// <param name="nWidth">width (in pixels) of input image data</param>
	/// <param name="nHeight">height (in pixels) of input image data</param>
	/// </summary>
	void ProcessInfrared(INT64 nTime, const UINT16* pBuffer, int nWidth, int nHeight);

	/// <summary>
	/// Handle new depth data
	/// <param name="nTime">timestamp of frame</param>
	/// <param name="pBuffer">pointer to frame data</param>
	/// <param name="nWidth">width (in pixels) of input image data</param>
	/// <param name="nHeight">height (in pixels) of input image data</param>
	/// <param name="nMinDepth">minimum reliable depth</param>
	/// <param name="nMaxDepth">maximum reliable depth</param>
	/// </summary>
	void ProcessDepth(INT64 nTime, const UINT16* pBuffer, int nWidth, int nHeight, USHORT nMinDepth, USHORT nMaxDepth);

	/// <summary>
	/// Handle new bodyIndex data
	/// <param name="nTime">timestamp of frame</param>
	/// <param name="pBuffer">pointer to frame data</param>
	/// <param name="nWidth">width (in pixels) of input image data</param>
	/// <param name="nHeight">height (in pixels) of input image data</param>
	/// </summary>
	void ProcessBodyIndex(INT64 nTime, const UCHAR* pBuffer, int nWidth, int nHeight);

	/// <summary>
	/// Handle new body data
	/// <param name="nTime">timestamp of frame</param>
	/// <param name="nBodyCount">body data count</param>
	/// <param name="ppBodies">body data in frame</param>
	/// </summary>
	void ProcessBody(INT64 nTime, int nBodyCount, IBody** ppBodies);

	//FPS
	/// <summary>
	/// Set the status bar message
	/// </summary>
	/// <param name="nShowTimeMsec">time in milliseconds for which to ignore future status messages</param>
	/// <param name="bForce">force status update</param>
	/// <param name="index">update FPS</param>
	bool SetStatusMessage(DWORD nShowTimeMsec, bool bForce, int index);
	void FPS_Check(int index, INT64 nTime);
	void FPS_Render();

	//////////////////////////////////////////////////////////////////////////
	//CVMgr
	//////////////////////////////////////////////////////////////////////////
	

	void setKinectCamData(KinectCamData* cam_data)	{	this->cam_data = cam_data;		}

	const IplImage& getRGBIplImage() const { return *cam_data->get_pRGB_IplImage(); }
	const IplImage& getIRIplImage() const { return *cam_data->get_pIR_IplImage(); }
	const IplImage& getDepthIplImage() const { return *cam_data->get_pDepth_IplImage(); }

	const Mat& getBodyIndexMat() const { return *cam_data->get_pBodyIndex_Mat();  }

	// get rgb point of joints by vector
	const vector<Joint>& get_rgb_joints() const { return rgb_joints;  }

	// get ir joints by vector
	const vector<Joint>& get_ir_joints() const { return ir_joints;  }

private:
	// for Saving Body Joint
	vector<Joint> rgb_joints;
	vector<Joint> ir_joints;

	KinectCamData *cam_data;
};

