#pragma once

#include <math.h>

#include <stdio.h>
#include <malloc.h>
#include "KipFaceDefs.h"
#include "types.h"

void sub_6EDAB2C0(float*, float*, float*, float*, float*, float);
void						Initialize();
tracked_object_list_type	track_objects(FaceInfo*);
void						discard_unreturned_complete_tracks();

void	sub_6EDAC520(OverlapRatio*, Float_Matrix*);
void	sub_6EDAE360(OverlapRatio*, float*, int, int);
void	sub_6EDAE940(OverlapRatio*, float*, int, int);
Float_Matrix	sub_6EDABFB0(float*, int, int);
void	sub_6EDFA840(float*, Index_List*, int, int);
Index_List			sub_6EDFC5A0(float*, int);
void	sub_6EE5C3B0(STC11*);
void	sub_6EE5CAD0(STC23*, KipFaceLandmark*, float);
void	sub_6EE5D1C0(STC11*, KipFaceLandmark*, float);
int		sub_6EEDCF00(FaceInfo*, float);
FaceInfo*	sub_6EEDE0B0(FaceInfo*, BYTE);
void	sub_6EF17E20(STC11* pstc11_Arg_0);
void	sub_6EF195E0(STC11*, KipFaceLandmark*, float);
void	sub_6EF1C280(STA111*);
STA107* sub_6EF1C790(STA107*);
STA112* sub_6EF1C800(STA112*);
STA107* sub_6EF1C830(STA107*);
STA112* sub_6EF1C860(STA107*);
STA107* sub_6EF1E510(STA107*, KipFaceLandmark*, BYTE);
BoundingBox_List	sub_6EF1E5C0(STA107*);
int		sub_6EF1ED40(STA107*, int*, int);
BoundingBox_List	sub_6EF1EE10(STA107*, int, int*);
STA107* sub_6EF1F1C0(STA107*, BYTE);
STA112* sub_6EF1F390(STA112*);
STA107* sub_6EF1F9B0(STA107*, int);
STA107* sub_6EF1FAE0(STA107*);
STA107* sub_6EF1FB50(STA107*, KipFaceLandmark*, float, float, int, int, float, int);
STA107*	sub_6EF1FC10(STA107*, FaceInfo*, float, BYTE);
STA107* sub_6EF1FE00(STA107*, FaceInfo*, float, BYTE);
void	sub_6EF20240(OverlapRatio*, BoundingBox_List, BoundingBox_List);
STA109*	sub_6EF20F60(STA109*, STA109*);
STA109* sub_6EF20FE0(STA109*);
int		sub_6EF21A10(STA109*, int**);
STA114	sub_6EF223B0(STA107*);
STA111* sub_6EF22590(STA111*, BYTE);
STA109* sub_6EF227C0(STA109*, BYTE);
STA109* sub_6EF22C30(STA109*, BYTE);
void	sub_6EF236B0(STA106*, STA107*, STA109*, STA109*);
STA112*	sub_6EF23850(STA112*);
STA112* sub_6EF23BF0(STA112*);
STA114	sub_6EF23DE0(STA107*, STA109*);
STA114	sub_6EF24220(STA107*, STA109*);
void	sub_6EF24630(STA106*, STA107*, STA109*, STA109*, FaceInfo*);
void	sub_6EF249D0(STA106*, STA107*, STA109*, STA109*, FaceInfo*);
void	sub_6EE420A0(KipCoord_List*);
KipCoord_List			sub_6EE42480(KipCoord_List*, KipCoord_List*);
KipCoord_List			sub_6EE43A50(KipCoord_List*, KipCoord_List*);
float	sub_6EE43B70(KipCoord_List*, KipCoord_List*);
void	sub_6EF5B290(STA106*);
void	sub_6EF5B380(STA106*, FaceInfo*);

float	sub_6F01E730(float, float);
float	sub_6F01EB90(float, float);
float	sub_6F020D50(float, float);