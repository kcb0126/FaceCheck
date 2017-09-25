#pragma once
#include "KipTypes.h"
#include "types.h"

typedef struct KipEstimateData
{
	float		data[8][0x0F];
} KipEstimateData;


class CTrackingFace
{
public:
	CTrackingFace();
	~CTrackingFace();

	float				Calcuate_Overlapping(KipFace*);
	void				UpdateWithData(KipFace*, float);
	void				UpdateWithoutData();
	void				Init(KipFace*, float);

private:
	KipEstimateData		m_stEstimateData;
	KipFace				m_stKipFace;
	float				m_fConfidence;
	int					m_nNoFrameCount;
};