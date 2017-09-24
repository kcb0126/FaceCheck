#pragma once

//////////////////////////////////////////////////////////////////////////
//																		//
//						KipCameraManager.h								//
//	KIP CameraManager module header file								//
//									Created by Apollo 2012/3/23			//
//																		//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//																		//
//						Camera type list								//
//																		//
#define KIP_CAMERA_SELECT											0	//
//	Show camera selecting dialog.
#define KIP_CAMERA_VIDEO_FILE										1	//
//	Get camera frame data from the video file.							//
#define KIP_CAMERA_USB_WEBCAM										2	//
//	Get	camera frame data from the USB Webcam.							//
#define KIP_CAMERA_PCI_COMART										3	//
#define KIP_CAMERA_IP_WEBGATE										4	//
//	Get camera frame data from the IP camera.							//
//	To create camera with KIP_CAMERA_WESP_IP,							//
//		the WESP SDK must be installed in the client, and				//
//		you must set DEP option of the application with /NTCOMPAT:NO	//
//		in Linker/Advanced of project's property page because WESP SDK.	//
//																		//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//																		//
//							parameter list								//
//																		//
//	used by options in KipCM_Create function.							//
//	options = -[prama_name1]=[value1] -[param_name2]=[value2] ...		//
//	ex:																	//
//		KipCM_Create(KIP_CAMERA_VIDEO_FILE, "-filename='d:\\video\\video1.mpg' -fast_play=1");
//		KipCM_Create(KIP_CAMERA_USB_WEBCAM, "-select_camera='0' -frame_width=320 -frame_height=240");
//
//		[name]			[in/out]	[type]	[default value]		[comment]
//	Common
//		camera_type		in,out		int			1				camera type, see above camera type list.
//		options			in			string						current camera options.
//		frame_width		in,out		int			640				recommend frame width
//		frame_height	in,out		int			480				recommend frame height
//		frame_rate		in,out		int			30				recommend frame rate
//		sample_time		out			float						current sample time in seconds
//	KIP_CAMERA_SELECT
//		video_file		in			int			1				if hide video file options, set 0
//		usb_webcam		in			int			1				if hide USB Webcam options, set 0
//		pci_comart		in			int			1				if hide PCI Comart options, set 0
//		ip_webgate		in			int			1				if hide IP Webgate options, set 0
//	KIP_CAMERA_VIDEO_FILE
//		file_name		in			string						video file full path name
//		fast_play		in			int			0				if fast play video, set 1
//		duration		out			float						total video durations in seconds
//	KIP_CAMERA_COMART_PCI
//		chanel_count		out		int
//		resolution_count	out		int
//		resolution_width1	out		int
//		resolution_height1	out		int
//	KIP_CAMERA_USB_WEBCAM
//		select_camera	in			int			1				if show camera selecting dialog, set 1.
//		horiz_fov		in,out		int			0				if show camera selecting dialog with horizontal field of view option.
//		camera_name		in,out		string						recommend camera name and selected camera name
//	KIP_CAMERA_WESP_IP
//		server			in			string						server ip address, ex 170.102.126.211
//		port			in			int			80				server ip port number
//		user			in			string		admin			server user name
//		password		in			string		admin			server user password
//		chanel			in			int			1				server video chanel number
//		resolution		in			string		normal			server video resolution, available lowest, low, normal, high, highest, 720p, 1080p
//																		//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//																		//
//							Camera event list							//
//																		//
//	notify message is message specified with KipCM_SetNotifyWindow		//
//	WPARAM	camera event code, LPARAM camera handle						//
#define KIP_CAMERA_CREATED											1
#define KIP_CAMERA_DESTROYED										2
#define KIP_CAMERA_CONNECTED										3
#define KIP_CAMERA_DISCONNECTED										4

#define KIP_CAMERA_PLAY												5
#define KIP_CAMERA_STOP												6
#define KIP_CAMERA_FINISHED											7
//																		//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//																		//
//							Camera error code							//
//																		//
//	returned from KipCM_GetLastError function.							//
//																		//
#define KIP_CAMERA_ERROR_SUCCESS									0
#define KIP_CAMERA_ERROR_CONNECT_FAIL								-100
#define KIP_CAMERA_ERROR_DICONECTED									-101
#define KIP_CAMERA_ERROR_UNAUTH_IP									-102
#define KIP_CAMERA_ERROR_UNAUTH_USER								-103
#define KIP_CAMERA_ERROR_UNAUTH_SERVER								-104
#define KIP_CAMERA_ERROR_SERVER_BUSY								-105
#define KIP_CAMERA_ERROR_INVALID_DATA								-105
#define KIP_CAMERA_ERROR_INVALID_DEVICE								-106
#define KIP_CAMERA_ERROR_NO_SIGNAL									-107
//																		//
//////////////////////////////////////////////////////////////////////////

#include "KipTypes.h"
typedef void * KipEngineHandle;

typedef int (CALLBACK * KipCM_FrameCallback)(const KipImageInfo *pImage, DWORD_PTR dwUserData);

KipEngineHandle	KipCM_Create(int nCameraType, const wchar_t * options);
void	KipCM_Destroy(KipEngineHandle hEngine);

int KipCM_Play(KipEngineHandle hEngine);
int KipCM_Pause(KipEngineHandle hEngine);
int KipCM_Stop(KipEngineHandle hEngine);

int KipCM_GetImageInfo(KipEngineHandle hEngine, KipImageInfo * pInfo);

int KipCM_GetIntParam(KipEngineHandle hEngine, const wchar_t * name, int default_value);
float KipCM_GetFloatParam(KipEngineHandle hEngine, const wchar_t * name, float default_value);
void KipCM_GetStringParam(KipEngineHandle hEngine, const wchar_t * name, wchar_t * param, int len);

int KipCM_GetLastError(KipEngineHandle hEngine);

void KipCM_SetFrameCallback(KipEngineHandle hEngine, KipCM_FrameCallback pCallback, DWORD_PTR dwUserData);
void KipCM_SetNotifyWindow(KipEngineHandle hEngine, HWND hWnd, UINT nMsg);