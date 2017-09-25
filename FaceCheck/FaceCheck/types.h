#pragma once

#include "KipFaceDetector.h"
#include "KipAgeEstimator.h"
#include "KipGenderEstimator.h"
#include "KipHeadPosition.h"

#include "ximage.h"
#include <vector>
using namespace std;

#define MAX_NAME	50
#define MAX_URL		500

#ifndef MIN
#define MIN(a,b)  ((a) > (b) ? (b) : (a))
#endif

#ifndef MAX
#define MAX(a,b)  ((a) < (b) ? (b) : (a))
#endif

#define		DATA_DIM					0x414	//picasa특징량 개수
#define		LANDMARK_COUNT				4		//얼굴특징점개수
// #define		THRESHOLD_LOW				0.87
// #define		THRESHOLD_HIGH				0.92
#define		THRESHOLD_TRACKING			0.3
#define		MAX_RECOGINFO_COUNT			5

#define REG_IMAGE_W			100
#define REG_IMAGE_H			100

#define INT_MIN     (-2147483647 - 1) /* minimum (signed) int value */

typedef struct KipFace
{
	KipCoord2f	rect[4];
} KipFace;

class CTrackingFace;

namespace KIP
{

	//사람정보(얼굴 및 머리령역자료, 성별, 나이자료 등...)
	typedef struct tagFaceData {
		//	class tagFageData {
		void initialize() {				// Added by Koo to prevent memoryleak
			imgCamera = NULL;
			imgRegistered = NULL;
		}

		void cleanMemory() {			// Added by Koo to prevent memoryleak
			//free(pTrackingFace);
			//pTrackingFace = NULL;

			if (imgCamera != NULL)
			{
				imgCamera->~CxImage();
				free(imgCamera);
				imgCamera = NULL;
			}

			if (imgRegistered)
			{
				imgRegistered->~CxImage();
				free(imgRegistered);
				imgRegistered = NULL;
			}
		}
		int				id;						//계수번호
		RECT			bound;					//얼굴 및 머리령역사각형령역
		KipFace			faceCorner;				//얼굴특징점들의 위치정보(얼굴인 경우) 
		vector<PBYTE>	vRecog;					//picasa 특징량
		float			confidence;				//얼굴의 신뢰도값
		float			fViewAngle;				//얼굴의 보기각도(얼굴인 경우) 
		float			depth;
		float			fSimilar;				//GetEmployee에서 얻은 류사도
		int				gender;					//성별(얼굴인 경우) 
		int				age;					//나이(얼굴인 경우) 
		int				FrontCount;				//정면얼굴개수
		time_t			initialTime;			//최초본시간
		time_t			lasttime;				//마지막으로 본시간
		double			duration;				//시청자가 본시간
		BOOL			bIsOneSecond;			//정면얼굴로 1초이상 있었는가?
		BOOL			bIsVisible;				// 현재 프레임에 현시하는가?
		BOOL			bLastFrontal;			// 마지막 프레임에서 정면얼굴이였는가?
		BOOL			bIsEmployee;			//직원인가?
		TCHAR			szDbName[MAX_PATH];		//가족DB의 이름
		TCHAR			szName[MAX_PATH];		//가족DB의 이름
		TCHAR			szURL[MAX_URL];			//URL
		CTrackingFace	*	pTrackingFace;
		// Add by Apollo 2013.08.08
		CxImage		*	imgCamera;				// 카메라에서 켑쳐된 얼굴영상
		CxImage		*	imgRegistered;			// 등록된 얼굴영상
		int				nOutputData;
	}FaceData;

	typedef struct tagFaceEyeData {
		RECT			bound;					//얼굴 및 머리령역사각형령역
		KipFaceLandmark land[28];
		BOOL			bFace;
	}FaceEyeData;

	struct FaceDrawingData{
		int				id;
		RECT			bound;
		float			depth;
		int				gender;					//성별(얼굴인 경우) 
		int				age;					//나이(얼굴인 경우) 
		BOOL			bIsOneSecond;			//정면얼굴로 1초이상 있었는가?
		BOOL			bIsVisible;				// 현재 프레임에 현시하는가?
		BOOL			bIsEmployee;			//직원인가?
		PBYTE			pRecogInfo;					//picasa 특징량
		CString			szName;
		CString			szURL;					//URL
	};

	typedef struct tagShowPeopleInfo
	{
		CRect  bound;
		PBYTE bRecog;
		CxImage xImage;
	}ShowPeopleInfo;

	typedef struct tagMaskingData
	{
		RECT			bound;					//얼굴 및 머리령역사각형령역
		int				width;
		int				height;
		int				eff_width;
		PBYTE			pbyImg;
	}MaskingData;
}

// ------------------------ Pipatt Tracker def --------------------------//
enum Track_Info
{
	INIT_RESULT = 0,
	DETECTED_RESULT = 1,
	TRACKED_RESULT = 2
};

struct STC14
{
	float		fltTb_00[0x0F];
};	//size = 0x3C

struct STC23
{
	STC14		stc14Tb_00[8];
	float		flt1A4;
	float		flt1A8;
};// size = 0x1AC

struct STC11
{
	STC23       stc23_00;
	int			n1AC;
	int			n1B0;
	unsigned char		by1B4;
	unsigned char		by1B5;
	unsigned char		by1B6;
	unsigned char		by1B7;
	unsigned char		by1B8;
	unsigned char		by1B9;
	unsigned char		by1BA;
	unsigned char		by1BB;
};	//size = 0x1BC

struct STA107;
struct STA109;
struct FaceInfo;

struct STA112
{
	STA112*		psta112_00;
	STA112*		psta112_04;
	STA112*		psta112_08;		//Unknown Type
	STA112*		psta112_0C;		//Unknown Type
	STA107*		psta107_10;
	STA109*		psta109_14;
	int					track_id;
	int					track_confidence;
	float				motion_confidence;
	float				confidence;
	float				yaw_angle;
	int					detected_id;
	Track_Info			track_info;
	KipFaceLandmark*	pFaceLandmark;
};

struct STA111
{
	int			n00;
	STA112*		psta112_04;
	STC11		stc11_08;
};

struct STA109
{
	STA109*		psta109_00;
	STA109*		psta109_04;
	STA111*		psta111_08;
};

struct STA107
{
	FaceInfo *	 face_info;
	STA107 * psta107_04;
	STA107 * psta107_prev;  //08
	STA107 * psta107_next;  //0C
	STA107 * psta107_10;
	STA109 * psta109_14;
	int					track_id;
	int					track_confidence;
	float				motion_confidence;
	float				confidence;
	float				yaw_angle;
	int					detected_id;
	Track_Info			track_info;
	KipFaceLandmark*	pFaceLandmark;
};

struct STA106
{
	STA107* psta107_00;
	STA109* psta109_04;
	STA109* psta109_08;
};

struct STA114
{
	STA107*		psta107_00;
	STA109*		psta109_04;
};

struct BoundingBox
{
	KipCoord2f		coord_00_04;
	KipCoord2f		coord_08_0C;
	KipCoord2f		coord_10_14;
	KipCoord2f		coord_18_1C;
	float flt24;
	float flt28;
	STA112*	psta112_2C;
}; //size = 0x30

struct BoundingBox_List
{
	int					num;
	BoundingBox*		pBounding_Box;
};

struct OverlapRatio
{
	int		num;
	int*	ratio;
	int		n08;
	int*	pn0C;
	float	flt10;
};

struct KipCoord_List
{
	int					num;
	KipCoord2f*			pCoord_Pos;
};

struct Index_List
{
	int		num;
	int*	pIndex;
};

struct Float_Matrix
{
	int		row;
	int		col;
	float*	data;
};

struct FaceInfo
{
	int					frame_index;
	int					num;
	KipFaceLandmark**	pFaceLandmark;
	float*				confidence;
	float*				yaw;
	int*				detected_id;
};	//size = 0x50

typedef struct
{
	int index;
	int tracked_id;
	int track_confidence;
	Track_Info track_info;
	KipFaceLandmark* object;
	int detected_id;
} tracked_object_type;

typedef struct
{
	int num_tracked_objects;
	tracked_object_type *tracked_objects;
} tracked_object_list_type;

extern STA106		sta106_1D30;
extern int			identifier;
