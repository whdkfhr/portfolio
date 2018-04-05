#include "KinectManager.h"
#include <qmessagebox.h>	// for debug

void KinectManager::Init_Kin2Mgr()
{
	Destroy_Kin2Mgr();

	for(int i = 0; i < 3; i++)
	{
		m_nStartTime[i] = 0;
		m_nLastCounter[i] = 0;
		m_fFreq[i] = 0;
		m_nFramesSinceUpdate[i] = 0;
		m_nNextStatusTime[i] = 0;
		m_fFPS[i] = 0;
		m_nProcTime[i] = 0;
	}

	//FPS
	LARGE_INTEGER qpf = {0};
	if (QueryPerformanceFrequency(&qpf))
	{
		m_fFreq[0] = m_fFreq[1] = m_fFreq[2] = double(qpf.QuadPart);
	}

	// create heap storage for color pixel data in RGBX format
	m_pColorRGBX = new RGBQUAD[_Color_Width_ * _Color_Height_];

	// Get and initialize the default Kinect sensor
	InitializeDefaultSensor();

//	printf_s("Initialize the Kinect 2.0 manager\n");
}

void KinectManager::Destroy_Kin2Mgr()
{
	if (m_pColorRGBX)
	{
		delete [] m_pColorRGBX;
		m_pColorRGBX = NULL;
	}

	// done with color frame reader
	SafeRelease(m_pColorFrameReader);

	// done with infrared frame reader
	SafeRelease(m_pInfraredFrameReader);

	// done with depth frame reader
	SafeRelease(m_pDepthFrameReader);

	// done with body frame reader
	SafeRelease(m_pBodyFrameReader);

	// done with coordinate mapper
	SafeRelease(m_pCoordinateMapper);

	// close the Kinect Sensor
	if (m_pKinectSensor)
	{
		m_pKinectSensor->Close();
	}
	SafeRelease(m_pKinectSensor);

//	printf_s("Destroy the Kinect 2.0 manager\n");
}


/// <summary>
/// Initializes the default Kinect sensor
/// </summary>
/// <returns>indicates success or failure</returns>
HRESULT KinectManager::InitializeDefaultSensor()
{
	HRESULT hr;

	hr = GetDefaultKinectSensor(&m_pKinectSensor);
	if (FAILED(hr))
	{
		return hr;
	}

	if (m_pKinectSensor)
	{
		// Initialize the Kinect and get the color reader
		IColorFrameSource* pColorFrameSource = NULL;

		// Initialize the Kinect and get the infrared reader
		IInfraredFrameSource* pInfraredFrameSource = NULL;

		// Initialize the Kinect and get the depth reader
		IDepthFrameSource* pDepthFrameSource = NULL;

		// Initialize the Kinect and get coordinate mapper and the bodyIndex reader
		IBodyIndexFrameSource* pBodyIndexSource = NULL;

		// Initialize the Kinect and get coordinate mapper and the body reader
		IBodyFrameSource* pBodyFrameSource = NULL;

		hr = m_pKinectSensor->Open();

		// RGB
		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_ColorFrameSource(&pColorFrameSource);
		}

		if (SUCCEEDED(hr))
		{
			hr = pColorFrameSource->OpenReader(&m_pColorFrameReader);
		}

		SafeRelease(pColorFrameSource);

		// IR
		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_InfraredFrameSource(&pInfraredFrameSource);
		}

		if (SUCCEEDED(hr))
		{
			hr = pInfraredFrameSource->OpenReader(&m_pInfraredFrameReader);
		}

		SafeRelease(pInfraredFrameSource);

		// Depth
		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_DepthFrameSource(&pDepthFrameSource);
		}

		if (SUCCEEDED(hr))
		{
			hr = pDepthFrameSource->OpenReader(&m_pDepthFrameReader);
		}

		SafeRelease(pDepthFrameSource);

		// BodyIndex
		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_BodyIndexFrameSource(&pBodyIndexSource);
		}

		if (SUCCEEDED(hr))
		{
			hr = pBodyIndexSource->OpenReader(&m_pBodyIndexReader);
		}

		SafeRelease(pBodyIndexSource);

		// Body
		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_CoordinateMapper(&m_pCoordinateMapper);
		}

		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_BodyFrameSource(&pBodyFrameSource);
		}

		if (SUCCEEDED(hr))
		{
			hr = pBodyFrameSource->OpenReader(&m_pBodyFrameReader);
		}

		SafeRelease(pBodyFrameSource);
	}

	if (!m_pKinectSensor || FAILED(hr))
	{
	//	printf_s("No ready Kinect found!");
		return E_FAIL;
	}

//	printf_s("Ready to use the Kinect 2.0\n");

	return hr;
}

/// <summary>
/// Main processing function
/// </summary>
void KinectManager::Update_Color()
{
	if (!m_pColorFrameReader)
	{
		return;
	}

//	IColorFrame* pColorFrame = NULL;
	pColorFrame = NULL;

	HRESULT hr = m_pColorFrameReader->AcquireLatestFrame(&pColorFrame);	

	if (SUCCEEDED(hr))
	{
		INT64 nTime = 0;
		IFrameDescription* pFrameDescription = NULL;
		int nWidth = 0;
		int nHeight = 0;
		ColorImageFormat imageFormat = ColorImageFormat_None;
		UINT nBufferSize = 0;
		RGBQUAD *pBuffer = NULL;

		hr = pColorFrame->get_RelativeTime(&nTime);

		if (SUCCEEDED(hr))
		{
			hr = pColorFrame->get_FrameDescription(&pFrameDescription);
		}

		if (SUCCEEDED(hr))
		{
			hr = pFrameDescription->get_Width(&nWidth);
		}

		if (SUCCEEDED(hr))
		{
			hr = pFrameDescription->get_Height(&nHeight);
		}

		if (SUCCEEDED(hr))
		{
			hr = pColorFrame->get_RawColorImageFormat(&imageFormat);
		}

		if (SUCCEEDED(hr))
		{
			if (imageFormat == ColorImageFormat_Bgra)
			{
				hr = pColorFrame->AccessRawUnderlyingBuffer(&nBufferSize, reinterpret_cast<BYTE**>(&pBuffer));
			}
			else if (m_pColorRGBX)
			{
				pBuffer = m_pColorRGBX;
				nBufferSize = _Color_Width_ * _Color_Height_ * sizeof(RGBQUAD);
				hr = pColorFrame->CopyConvertedFrameDataToArray(nBufferSize, reinterpret_cast<BYTE*>(pBuffer), ColorImageFormat_Bgra);            
			}
			else
			{
				hr = E_FAIL;
			}
		}

		if (SUCCEEDED(hr))
		{
			ProcessColor(nTime, pBuffer, nWidth, nHeight);
		}

		SafeRelease(pFrameDescription);
	}

	
	SafeRelease(pColorFrame);
}

void KinectManager::Update_IR()
{
	if (!m_pInfraredFrameReader)
	{
		return;
	}

//	IInfraredFrame* pInfraredFrame = NULL;
	pInfraredFrame = NULL;

	HRESULT hr = m_pInfraredFrameReader->AcquireLatestFrame(&pInfraredFrame);

	if (SUCCEEDED(hr))
	{
		INT64 nTime = 0;
		IFrameDescription* pFrameDescription = NULL;
		int nWidth = 0;
		int nHeight = 0;
		UINT nBufferSize = 0;
		UINT16 *pBuffer = NULL;

		hr = pInfraredFrame->get_RelativeTime(&nTime);

		if (SUCCEEDED(hr))
		{
			hr = pInfraredFrame->get_FrameDescription(&pFrameDescription);
		}

		if (SUCCEEDED(hr))
		{
			hr = pFrameDescription->get_Width(&nWidth);
		}

		if (SUCCEEDED(hr))
		{
			hr = pFrameDescription->get_Height(&nHeight);
		}

		if (SUCCEEDED(hr))
		{
			hr = pInfraredFrame->AccessUnderlyingBuffer(&nBufferSize, &pBuffer);            
		}

		if (SUCCEEDED(hr))
		{
			ProcessInfrared(nTime, pBuffer, nWidth, nHeight);
		}

		SafeRelease(pFrameDescription);
	}

	SafeRelease(pInfraredFrame);
}

void KinectManager::Update_Depth()
{
	if (!m_pDepthFrameReader)
	{
		return;
	}

//	IDepthFrame* pDepthFrame = NULL;
	pDepthFrame = NULL;

	HRESULT hr = m_pDepthFrameReader->AcquireLatestFrame(&pDepthFrame);

	if (SUCCEEDED(hr))
	{
		INT64 nTime = 0;
		IFrameDescription* pFrameDescription = NULL;
		int nWidth = 0;
		int nHeight = 0;
		USHORT nDepthMinReliableDistance = 0;
		USHORT nDepthMaxDistance = 0;
		UINT nBufferSize = 0;
		UINT16 *pBuffer = NULL;

		hr = pDepthFrame->get_RelativeTime(&nTime);

		if (SUCCEEDED(hr))
		{
			hr = pDepthFrame->get_FrameDescription(&pFrameDescription);
		}

		if (SUCCEEDED(hr))
		{
			hr = pFrameDescription->get_Width(&nWidth);
		}

		if (SUCCEEDED(hr))
		{
			hr = pFrameDescription->get_Height(&nHeight);
		}

		if (SUCCEEDED(hr))
		{
			hr = pDepthFrame->get_DepthMinReliableDistance(&nDepthMinReliableDistance);
		}

		if (SUCCEEDED(hr))
		{
			// In order to see the full range of depth (including the less reliable far field depth)
			// we are setting nDepthMaxDistance to the extreme potential depth threshold
			nDepthMaxDistance = USHRT_MAX;

			// Note:  If you wish to filter by reliable depth distance, uncomment the following line.
			//// hr = pDepthFrame->get_DepthMaxReliableDistance(&nDepthMaxDistance);
		}

		if (SUCCEEDED(hr))
		{
			hr = pDepthFrame->AccessUnderlyingBuffer(&nBufferSize, &pBuffer);            
		}

		if (SUCCEEDED(hr))
		{
			ProcessDepth(nTime, pBuffer, nWidth, nHeight, nDepthMinReliableDistance, nDepthMaxDistance);
		}

		SafeRelease(pFrameDescription);
	}

	SafeRelease(pDepthFrame);
}

void KinectManager::Update_BodyIndex()
{
	if (!m_pBodyIndexReader)
	{
		return;
	}

//	IBodyIndexFrame * pBodyIndexFrame = nullptr;
	pBodyIndexFrame = NULL;
	
	HRESULT hr = m_pBodyIndexReader->AcquireLatestFrame(&pBodyIndexFrame);

	if (SUCCEEDED(hr))
	{
		INT64 nTime = 0;
		IFrameDescription* pFrameDescription = NULL;
		int nWidth = 0;
		int nHeight = 0;
		UINT nBufferSize = 0;
		UCHAR *pBuffer = nullptr;

		hr = pBodyIndexFrame->get_RelativeTime(&nTime);

		if (SUCCEEDED(hr))
		{
			hr = pBodyIndexFrame->get_FrameDescription(&pFrameDescription);
		}

		if (SUCCEEDED(hr))
		{
			hr = pFrameDescription->get_Width(&nWidth);
		}

		if (SUCCEEDED(hr))
		{
			hr = pFrameDescription->get_Height(&nHeight);
		}

		if (SUCCEEDED(hr))
		{
			hr = pBodyIndexFrame->AccessUnderlyingBuffer(&nBufferSize, &pBuffer);
		}

		if (SUCCEEDED(hr))
		{
			ProcessBodyIndex(nTime, pBuffer, nWidth, nHeight);
		}
	}

	SafeRelease(pBodyIndexFrame);
}


// not done
void KinectManager::Update_Body()
{
	if (!m_pBodyFrameReader)
	{
		return;
	}

//	IBodyFrame* pBodyFrame = NULL;
	pBodyFrame = NULL;

	HRESULT hr = m_pBodyFrameReader->AcquireLatestFrame(&pBodyFrame);

	if (SUCCEEDED(hr))
	{
		INT64 nTime = 0;
		IBody* ppBodies[BODY_COUNT] = { 0 };

		hr = pBodyFrame->get_RelativeTime(&nTime);

		if (SUCCEEDED(hr))
		{
			hr = pBodyFrame->GetAndRefreshBodyData(_countof(ppBodies), ppBodies);
		}

		if (SUCCEEDED(hr))
		{
			ProcessBody(nTime, BODY_COUNT, ppBodies);
		}

		for (int i = 0; i < _countof(ppBodies); ++i)
		{
			SafeRelease(ppBodies[i]);
		}
	}

	SafeRelease(pBodyFrame);
}


/// <summary>
/// Handle new color data
/// <param name="nTime">timestamp of frame</param>
/// <param name="pBuffer">pointer to frame data</param>
/// <param name="nWidth">width (in pixels) of input image data</param>
/// <param name="nHeight">height (in pixels) of input image data</param>
/// </summary>
void KinectManager::ProcessColor(INT64 nTime, RGBQUAD* pBuffer, int nWidth, int nHeight)
{
	if(!cam_data)	return;

	FPS_Check(0, nTime);

	// Make sure we've received valid data
	if (pBuffer && (nWidth == _Color_Width_) && (nHeight == _Color_Height_))
	{
		BYTE* pBufferRun = (BYTE*) pBuffer;
		int _nWidthStep =cam_data->get_pRGB_IplImage()->widthStep;
		int _nCn = cam_data->get_pRGB_IplImage()->nChannels;
		int index_RGB = 0;

		for(int h = 0; h < nHeight; h++)
		{
			for(int w = 0; w < nWidth; w++)
			{
				if(!cam_data)	return;

				index_RGB = h*_nWidthStep+w*_nCn;
				cam_data->get_pRGB_IplImage()->imageData[index_RGB] = *pBufferRun++;
				cam_data->get_pRGB_IplImage()->imageData[index_RGB + 1] = *pBufferRun++;
				cam_data->get_pRGB_IplImage()->imageData[index_RGB + 2] = *pBufferRun++;
				*pBufferRun++;
			}
		}
	}
}

/// <summary>
/// Handle new infrared data
/// <param name="nTime">timestamp of frame</param>
/// <param name="pBuffer">pointer to frame data</param>
/// <param name="nWidth">width (in pixels) of input image data</param>
/// <param name="nHeight">height (in pixels) of input image data</param>
/// </summary>
void KinectManager::ProcessInfrared(INT64 nTime, const UINT16* pBuffer, int nWidth, int nHeight)
{
	FPS_Check(1, nTime);

	// Make sure we've received valid data
	if (pBuffer && (nWidth == _IR_Width_) && (nHeight == _IR_Height_))
	{
		const UINT16* pBufferEnd = pBuffer + (nWidth * nHeight);
		int index_IR = 0;

		while (pBuffer < pBufferEnd)
		{
			// normalize the incoming infrared data (ushort) to a float ranging from 
			// [InfraredOutputValueMinimum, InfraredOutputValueMaximum] by
			// 1. dividing the incoming value by the source maximum value
			float intensityRatio = static_cast<float>(*pBuffer) / InfraredSourceValueMaximum;

			// 2. dividing by the (average scene value * standard deviations)
			intensityRatio /= InfraredSceneValueAverage * InfraredSceneStandardDeviations;

			// 3. limiting the value to InfraredOutputValueMaximum
			intensityRatio = min(InfraredOutputValueMaximum, intensityRatio);

			// 4. limiting the lower value InfraredOutputValueMinimym
			intensityRatio = max(InfraredOutputValueMinimum, intensityRatio);

			// 5. converting the normalized value to a byte and using the result
			// as the RGB components required by the image
			byte intensity = static_cast<byte>(intensityRatio * 255.0f); 

			cam_data->get_pIR_IplImage()->imageData[index_IR++] = intensity;
			cam_data->get_pIR_IplImage()->imageData[index_IR++] = intensity;
			cam_data->get_pIR_IplImage()->imageData[index_IR++] = intensity;
			pBuffer++;
		}
	}
}

/// <summary>
/// Handle new depth data
/// <param name="nTime">timestamp of frame</param>
/// <param name="pBuffer">pointer to frame data</param>
/// <param name="nWidth">width (in pixels) of input image data</param>
/// <param name="nHeight">height (in pixels) of input image data</param>
/// <param name="nMinDepth">minimum reliable depth</param>
/// <param name="nMaxDepth">maximum reliable depth</param>
/// </summary>
void KinectManager::ProcessDepth(INT64 nTime, const UINT16* pBuffer, int nWidth, int nHeight, USHORT nMinDepth, USHORT nMaxDepth)
{
	FPS_Check(2, nTime);

	// Make sure we've received valid data
	if (pBuffer && (nWidth == _IR_Width_) && (nHeight == _IR_Height_))
	{
		// end pixel is start + width*height - 1
		const UINT16* pBufferEnd = pBuffer + (nWidth * nHeight);
		int index_Depth = 0;

		while (pBuffer < pBufferEnd)
		{
			USHORT depth = *pBuffer;

			// To convert to a byte, we're discarding the most-significant
			// rather than least-significant bits.
			// We're preserving detail, although the intensity will "wrap."
			// Values outside the reliable depth range are mapped to 0 (black).

			// Note: Using conditionals in this loop could degrade performance.
			// Consider using a lookup table instead when writing production code.

			BYTE intensity = 0;
			if((depth >= nMinDepth) && (depth <= nMaxDepth))
			{
				intensity = (BYTE)~((depth >= nMinDepth) && (depth <= nMaxDepth) ? depth*255/8000 : 0);
			}

			cam_data->get_pDepth_IplImage()->imageData[index_Depth++] = intensity;
			cam_data->get_pDepth_IplImage()->imageData[index_Depth++] = intensity;
			cam_data->get_pDepth_IplImage()->imageData[index_Depth++] = intensity;
			pBuffer++;
		}
	}
}

/// <summary>
/// Handle new bodyIndex data
/// <param name="nTime">timestamp of frame</param>
/// <param name="pBuffer">pointer to frame data</param>
/// <param name="nWidth">width (in pixels) of input image data</param>
/// <param name="nHeight">height (in pixels) of input image data</param>
/// </summary>
void KinectManager::ProcessBodyIndex(INT64 nTime, const UCHAR* pBuffer, int nWidth, int nHeight)
{
	FPS_Check(3, nTime);

	cv::Vec3b color[BODY_COUNT];  
	color[0] = cv::Vec3b(255, 0, 0);
	color[1] = cv::Vec3b(0, 255, 0);
	color[2] = cv::Vec3b(0, 0, 255);
	color[3] = cv::Vec3b(255, 255, 0);
	color[4] = cv::Vec3b(255, 0, 255);
	color[5] = cv::Vec3b(0, 255, 255);


	for (int y = 0; y < nHeight; y++)
	{
		for (int x = 0; x < nWidth; x++)
		{
			unsigned int index = y * nWidth + x;

			if (pBuffer[index] != 0xff)
			{
				cam_data->get_pBodyIndex_Mat()->at < cv::Vec3b >(y, x) = color[pBuffer[index]];
			}
			else
			{
				cam_data->get_pBodyIndex_Mat()->at < cv::Vec3b >(y, x) = cv::Vec3b(0, 0, 0);
			}
		}
	}
}

/// <summary>
/// Handle new body data
/// <param name="nTime">timestamp of frame</param>
/// <param name="nBodyCount">body data count</param>
/// <param name="ppBodies">body data in frame</param>
/// </summary>
void KinectManager::ProcessBody(INT64 nTime, int nBodyCount, IBody** ppBodies)	// not done
{
	FPS_Check(4, nTime);

	for (int count = 0; count < nBodyCount; count++)
	{
		// 인물을 추적 할 수 있는지를 확인한다
		BOOLEAN bTracked = false;  
		HRESULT hResult = ppBodies[count]->get_IsTracked(&bTracked);

		Joint joint[JointType::JointType_Count];	// 몸 점들로 추정댐

		// 인물에서 Joint (절)를 취득한다.
		if (SUCCEEDED(hResult) && bTracked) 
		{
			hResult = ppBodies[count]->GetJoints(JointType::JointType_Count, joint);
		}

		if (SUCCEEDED(hResult))
		{
			rgb_joints.clear();
			ir_joints.clear();

			ColorSpacePoint colorSpacePoint = { 0 };

			for (int i = 0; i < JointType::JointType_Count; i++)
			{
				// set rgb points from ir points
				Joint rgb_joint = joint[i];

				m_pCoordinateMapper->MapCameraPointToColorSpace(joint[i].Position, &colorSpacePoint);

				int x = static_cast <int> (colorSpacePoint.X);
				int y = static_cast <int> (colorSpacePoint.Y);

				CameraSpacePoint rgb_point;
				rgb_point.X = x;
				rgb_point.Y = y;

				rgb_joint.Position = rgb_point;

				// insert to rgb joints, ir joints 
				rgb_joints.push_back(rgb_joint);
				ir_joints.push_back(joint[i]);
			}
		}

		/*

		// Left Hand State
		if (SUCCEEDED(hResult))
		{
			HandState leftHandState = HandState::HandState_Unknown;
			hResult = ppBodies[count]->get_HandLeftState(&leftHandState);
		}

		// 그리는 데 Joint의 Camera 좌표계에서 Color 좌표계에 정렬한다. 
		// 정렬 좌표가 그리기 영역(여기에서는 Color 이미지 크기 1920 × 1080)를 넘지 않는지 확인한다.
		if (SUCCEEDED(hResult))
		{
			ColorSpacePoint colorSpacePoint = { 0 };   
			hResult = pCoordinateMapper->MapCameraPointToColorSpace(joint[JointType::JointType_HandLeft].Position, &colorSpacePoint); 
		}
		*/

		
		/*
		// 8 상태에 대응하는 색상 ◯ (원형)을 그려 Hand State를 시각화한다. 
		// 여기에서는 열기(Open : 파), Closed(닫기 : 굿), Lasso(올가미 : 조각)를 각각 대응하는 색으로 그립니다.상태를 감지 할 수없
		if (SUCCEEDED(hResult)) 
		{
			int x = static_cast <int> (colorSpacePoint.X);
			int y = static_cast <int> (colorSpacePoint.Y);

			// width, height : width, height of Mat
			if ((x >= 0) && (x < width) && (y > = 0) && (y < height)) 
			{
				if (leftHandState == HandState::HandState_Open) { 
					cv::circle(bufferMat, cv::Point(x, y), 75, cv::Scalar(0, 128, 0), 5, CV_AA);
				}
				else if(leftHandState == HandState::HandState_Closed) {
					cv::circle(bufferMat, cv::Point(x, y), 75, cv::Scalar(0, 0, 128), 5, CV_AA);
				}
				else if(leftHandState == HandState::HandState_Lasso) { 
					cv::circle(bufferMat, cv::Point(x, y), 75, cv::Scalar(128, 128, 0), 5, CV_AA);
				}
			}
		}
		*/

		/*
		// Right Hand State
		// 9 Joint를 인물에 대응하는 색상 표 색상을 참조립니다. 
		// Hand State와 마찬가지로 Camera 좌표계에서 Color 좌표계에 정렬하고 ●(원형) 그립니다
		for (int type = 0; type < JointType::JointType_Count; type++) 
		{
			ColorSpacePoint colorSpacePoint = { 0 };
			pCoordinateMapper->MapCameraPointToColorSpace(joint[type].Position, &colorSpacePoint);
			int x = static_cast <int> (colorSpacePoint.X);
			int y = static_cast <int> (colorSpacePoint.Y);

			if ((x > = 0) && (x < width) && (y > = 0) && (y < height)) 
			{
				cv::circle(bufferMat, cv::Point(x, y), 5, static_cast <cv::Scalar> (color[count]) - 1, CV_AA);
			}
		}
		*/
	}
}





/// <summary>
/// Set the status bar message
/// </summary>
/// <param name="showTimeMsec">time in milliseconds to ignore future status messages</param>
/// <param name="bForce">force status update</param>
bool KinectManager::SetStatusMessage(DWORD nShowTimeMsec, bool bForce, int index)
{
	INT64 now = GetTickCount64();

	if (bForce || (m_nNextStatusTime[index] <= now))
	{
		m_nNextStatusTime[index] = now + nShowTimeMsec;

		return true;
	}

	return false;
}

void KinectManager::FPS_Check(int index, INT64 nTime)
{
	//////////////////////////////////////////////////////////////////////////
	//FPS
	//////////////////////////////////////////////////////////////////////////
	if(!m_nStartTime[index])
	{
		m_nStartTime[index] = nTime;
	}

	LARGE_INTEGER qpcNow = {0};
	if (m_fFreq[index])
	{
		if (QueryPerformanceCounter(&qpcNow))
		{
			if (m_nLastCounter)
			{
				m_nFramesSinceUpdate[index]++;
				m_fFPS[index] = m_fFreq[index] * m_nFramesSinceUpdate[index] / double(qpcNow.QuadPart - m_nLastCounter[index]);
			}
		}
	}

	m_nProcTime[index] = (nTime - m_nStartTime[index]);

	if(SetStatusMessage(1000, false, index))
	{
		m_nLastCounter[index] = qpcNow.QuadPart;
		m_nFramesSinceUpdate[index] = 0;
	}
}

void KinectManager::FPS_Render()
{
	printf_s("RGB=%0.2f(Time:%I64d), IR=%0.2f(Time:%I64d), D=%0.2f(Time:%I64d)\n", m_fFPS[0], m_nProcTime[0], m_fFPS[1], m_nProcTime[1], m_fFPS[2], m_nProcTime[2]);
}
