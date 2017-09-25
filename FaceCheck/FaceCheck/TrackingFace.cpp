#include "stdafx.h"
#include <float.h>
#include "TrackingFace.h"
#include "face_tracker.h"

STA106		sta106_1D30 = { NULL };
int			identifier = 1;
#define		MAX_TRACKING_FRAME_COUNT		5
//Calcuate 3 X 3 Determinant
float calcDeterminant(float* data)
{
	return (data[0] * (data[4] * data[8] - data[5] * data[7]) - data[1] * (data[3] * data[8] - data[5] * data[6]) + data[2] * (data[3] * data[7] - data[4] * data[6]));
}

/*
Recursive least square algorithm - 2012/02/10
*/
void sub_6EDAB2C0(float* pfltArg_0, float* pfltArg_4, float* pfltArg_8, float* pfltArg_C, float* pfltArg_10, float fltArg_14)
{
	float fltTb_Var_1C[0x4];
	float fltTb_Var_2C[0x4];
	float fltTb_Var_3C[0x4];
	float fltTb_Var_7C[0x10];
	int	  nVar_84;
	//int   nVar_88;
	float fltVar_8C;
	float fltVar_90;
	float fltVar_94;
	float fltVar_98;
	float fltVar_9C;
	float fltVar_A0;
	float fltVar_A4;
	float fltVar_A8;
	float* pfltVar_AC;

	for (int i = 0; i < 0xC; i++)
	{
		fltTb_Var_7C[i] = pfltArg_0[i];
	}

	fltTb_Var_2C[0] = pfltArg_4[0];
	fltTb_Var_2C[1] = pfltArg_4[1];
	fltTb_Var_2C[2] = pfltArg_4[2];
	fltTb_Var_2C[3] = pfltArg_4[3];

	fltVar_94 = fltTb_Var_2C[0];
	fltVar_98 = fltTb_Var_2C[1];
	fltVar_9C = fltTb_Var_2C[2];
	fltVar_A0 = fltTb_Var_2C[3];

	nVar_84 = 0;
	int nEbx = 1;

	float* pflt_Edi = fltTb_Var_7C;
	pfltVar_AC = &fltTb_Var_7C[0x3];
	float* pflt_Ebp = &fltTb_Var_7C[0xC];// Var_4C
	float* pflt_Esi = fltTb_Var_3C;

	double dbl_st00;
	double dbl_st01;
	for (int i = 0; i < 3; i++)
	{
		fltTb_Var_3C[0] = pflt_Edi[i];
		fltTb_Var_3C[1] = pflt_Edi[i + 3];
		fltTb_Var_3C[2] = pflt_Edi[i + 6];
		fltTb_Var_3C[3] = pflt_Edi[i + 9];

		dbl_st00 = 0;

		for (int j = i; j < 4; j++)
		{
			dbl_st00 = dbl_st00 + pflt_Esi[j] * pflt_Esi[j];
		}
		//loc_6EDAB4B0
		dbl_st01 = sqrt((float)dbl_st00);
		dbl_st00 = pflt_Esi[i];

		if (dbl_st00 < 0)
		{
			//loc_6EDABA60:
			dbl_st01 = (-1) * dbl_st01;
		}
		//loc_6EDAB4C9
		for (int j = 0; j < nVar_84; j++)
		{
			fltTb_Var_7C[0x0C + j] = 0;
		}
		//loc_6EDAB5A5
		//nVar_88 =  ebx + 1 = i + 2;
		pflt_Ebp[i] = (float)(dbl_st00 + dbl_st01);
		dbl_st00 = dbl_st01;

		for (int nEcx = i + 1; nEcx < 4; nEcx++)
		{
			//loc_6EDAB64E:	
			pflt_Ebp[nEcx] = pflt_Esi[nEcx];
		}

		//loc_6EDAB6B0:
		float *pflt_Edx = pflt_Edi;
		fltVar_8C = (float)(dbl_st00 * pflt_Ebp[i]);

		fltVar_A4 = fltTb_Var_7C[0xE];
		fltVar_A8 = fltTb_Var_7C[0xF];

		fltVar_90 = 0.0;
		do
		{
			double dbl_tmp = ((double)fltVar_90 + fltTb_Var_7C[0x0C] * pflt_Edx[0] + fltTb_Var_7C[0x0D] * pflt_Edx[3] + fltVar_A4 * pflt_Edx[6] + fltVar_A8 * pflt_Edx[9]) / fltVar_8C;
			pflt_Edx[0] = (float)((double)pflt_Edx[0] - dbl_tmp * fltTb_Var_7C[0x0C]);
			pflt_Edx[3] = (float)((double)pflt_Edx[3] - dbl_tmp * fltTb_Var_7C[0x0D]);
			pflt_Edx[6] = (float)((double)pflt_Edx[6] - dbl_tmp * fltVar_A4);
			pflt_Edx[9] = (float)((double)pflt_Edx[9] - dbl_tmp * fltVar_A8);
			pflt_Edx++;
		} while (pflt_Edx != pfltVar_AC);

		//loc_6EDAB889
		nVar_84++;

		double dbl_tmp = ((double)fltVar_90 + fltVar_94 * fltTb_Var_7C[0x0C] + fltVar_98 * fltTb_Var_7C[0x0D] + fltVar_9C * fltVar_A4 + fltVar_A0 * fltVar_A8) / fltVar_8C;

		fltVar_94 = (float)((double)fltVar_94 - fltTb_Var_7C[0x0C] * dbl_tmp);
		fltTb_Var_2C[0] = fltVar_94;

		fltVar_98 = (float)((double)fltVar_98 - fltTb_Var_7C[0x0D] * dbl_tmp);
		fltTb_Var_2C[1] = fltVar_98;

		fltVar_9C = (float)((double)fltVar_9C - fltVar_A4 * dbl_tmp);
		fltTb_Var_2C[2] = fltVar_9C;

		fltVar_A0 = (float)((double)fltVar_A0 - fltVar_A8 * dbl_tmp);
		fltTb_Var_2C[3] = fltVar_A0;

		dbl_st00 = fltTb_Var_2C[2];

	}//while(nVar_88 != 4);

	//0x6EDAB917
	int nEdx = 3;
	dbl_st00 = dbl_st00 / fltTb_Var_7C[8];
	fltTb_Var_1C[2] = (float)dbl_st00;

	do
	{
		//loc_6EDAB92E
		int nEbp = 4 * nEdx - 7;
		fltTb_Var_1C[nEdx - 2] = fltTb_Var_2C[nEdx - 2];
		nEbx = nEdx - 1;
		float* pfltEax = fltTb_Var_1C + nEbx;
		float* pfltEcx = pflt_Edi + nEbp;

		while (TRUE)
		{
			pfltEax[0];

			//loc_6EDAB950
			dbl_st00 = fltTb_Var_1C[nEdx - 2] - pfltEax[0] * pfltEcx[0];
			fltTb_Var_1C[nEdx - 2] = (float)dbl_st00;
			pfltEax++;
			pfltEcx++;

			if (pfltEax == &fltTb_Var_1C[3])
			{
				//0x6EDAB96D
				dbl_st00 = dbl_st00 / pflt_Edi[4 * nEdx - 8];
				fltTb_Var_1C[nEdx - 2] = (float)dbl_st00;
				break;
			}
		}
		//0x6EDAB97A
		nEdx = nEbx;
		nEbx--;
	} while (nEbx != 0);

	//0x6EDAB981
	pfltArg_10[0] = fltTb_Var_1C[0];
	pfltArg_10[1] = fltTb_Var_1C[1];
	pfltArg_10[2] = fltTb_Var_1C[2];

	for (int i = 0; i < 9; i++)
	{
		dbl_st00 = fltArg_14 * pflt_Edi[i];
		pfltArg_8[i] = (float)dbl_st00;
	}

	dbl_st00 = fltVar_94 * fltArg_14;
	pfltArg_C[0] = (float)dbl_st00;

	dbl_st00 = fltVar_98 * fltArg_14;
	pfltArg_C[1] = (float)dbl_st00;

	dbl_st00 = fltVar_9C * fltArg_14;
	pfltArg_C[2] = (float)dbl_st00;
}

//2012 - 02 - 03

void Initialize()
{
	identifier = 0;

	sta106_1D30.psta107_00 = NULL;
	sta106_1D30.psta109_04 = NULL;
	sta106_1D30.psta109_08 = NULL;
}

tracked_object_list_type track_objects(FaceInfo* pFaceInfo)
{
	tracked_object_list_type object_list = { 0 };

	sub_6EF5B380(&sta106_1D30, pFaceInfo);

	STA107* psta107_Eax = sta106_1D30.psta107_00;
	STA107* psta107_Edi = psta107_Eax->psta107_04;

	if (psta107_Edi != NULL)
	{
		STA107* psta107_Eax = psta107_Edi;
		while (psta107_Eax->psta107_prev != NULL)
			psta107_Eax = psta107_Eax->psta107_prev;

		int nEbx = 0;
		while (psta107_Eax != NULL)
		{
			psta107_Eax = psta107_Eax->psta107_next;
			nEbx++;
		}

		object_list.num_tracked_objects = nEbx;
		object_list.tracked_objects = (tracked_object_type*)malloc(sizeof(tracked_object_type) * nEbx);

		psta107_Eax = psta107_Edi->psta107_prev;
		while (psta107_Eax != NULL)
		{
			psta107_Edi = psta107_Eax;
			psta107_Eax = psta107_Eax->psta107_prev;
		}

		int nEsi = 0;
		while (psta107_Edi != NULL)
		{
			object_list.tracked_objects[nEsi].tracked_id = psta107_Edi->track_id;
			object_list.tracked_objects[nEsi].track_confidence = psta107_Edi->track_confidence;
			object_list.tracked_objects[nEsi].track_info = psta107_Edi->track_info;
			object_list.tracked_objects[nEsi].object = (KipFaceLandmark*)malloc(sizeof(KipFaceLandmark) * 4);
			object_list.tracked_objects[nEsi].detected_id = psta107_Edi->detected_id;
			memcpy(object_list.tracked_objects[nEsi].object, psta107_Edi->pFaceLandmark, sizeof(KipFaceLandmark) * 4);

			psta107_Edi = psta107_Edi->psta107_next;
			nEsi++;
		}
	}

	return object_list;
}

void discard_unreturned_complete_tracks()
{
	sub_6EF5B290(&sta106_1D30);
}

void sub_6EDAC520(OverlapRatio* pOverlap_Ratio, Float_Matrix* pMat)
{
	int			nVar_14;
	int			nVar_18;
	int			nVar_20;
	int			nVar_54;
	int			nVar_58;
	int			nVar_70;
	int			nVar_74;
	int			nVar_78;
	int			nVar_7C;
	int			nVar_80;
	int			nVar_84;
	int			nVar_88;
	int			nVar_8C;
	int			nVar_90;
	int			nVar_94;
	int			nVar_98;
	int			nVar_120;
	float*		pfltVar_CC;
	float*		pfltVar_D0;
	int*		pnVar_D4;
	int*		pnVar_D8;
	int*		pnVar_DC;
	int*		pnVar_E0;
	int			nVar_FC;

	int row_begin = 0;
	int row_end = pMat->row - 1;
	int col_begin = 0;
	int col_end = pMat->col - 1;
	int col_len = pMat->col;

	double st02;

	pfltVar_CC = (float*)malloc(sizeof(float) * pMat->row);
	//loc_6EDAC598
	for (int i = row_begin; i <= row_end; i++)
		pfltVar_CC[i - row_begin] = 0;

	//loc_6EDAC5B0
	pfltVar_D0 = (float*)malloc(sizeof(float) * pMat->row);
	//loc_6EDAC60D
	for (int i = row_begin; i <= row_end; i++)
		pfltVar_D0[i - row_begin] = 0;

	//loc_6EDAC63F
	pnVar_D4 = (int*)malloc(sizeof(int) * pMat->row);
	//loc_6EDAC682
	for (int i = row_begin; i <= row_end; i++)
		pnVar_D4[i - row_begin] = 0;

	//loc_6EDAC6B4
	pnVar_D8 = (int*)malloc(sizeof(int) * pMat->row);
	//loc_6EDAC6F7
	for (int i = row_begin; i <= row_end; i++)
		pnVar_D8[i - row_begin] = 0;

	//loc_6EDAC729
	pnVar_DC = (int*)malloc(sizeof(int) * pMat->row);
	//loc_6EDAC76C
	for (int i = row_begin; i <= row_end; i++)
	{
		pnVar_DC[i - row_begin] = 0;
	}

	//loc_6EDAC79E
	pnVar_E0 = (int*)malloc(sizeof(int) * pMat->row);

	//loc_6EDAC7E1
	for (int i = row_begin; i <= row_end; i++)
	{
		pnVar_E0[i - row_begin] = 0;
	}

	if (pMat->row == 0 || pMat->col == 0)
		printf("DATA_ASSOCIATION.OPTIMIZE_DATA_ASSOCIATION_INTERNAL.COST_MATRIX_IS_NOT_COMPLIANT\n""data_association.adb:171");

	//loc_6EDAC8E6

	pOverlap_Ratio->num = pMat->row;
	pOverlap_Ratio->ratio = (int*)malloc(sizeof(int) * pMat->row);

	//loc_6EDAC924
	pOverlap_Ratio->n08 = pMat->row;
	pOverlap_Ratio->pn0C = (int*)malloc(sizeof(int) * pMat->row);

	//loc_6EDAC970
	for (int nEdx = row_begin; nEdx <= row_end; nEdx++)
	{
		pOverlap_Ratio->ratio[nEdx - row_begin] = 0;
	}

	//loc_6EDAC999
	for (int nEdx = row_begin; nEdx <= row_end; nEdx++)
	{
		pOverlap_Ratio->pn0C[nEdx - row_begin] = 0;
	}

	//loc_6EDAC9A9
	for (int nVar_68 = row_end; nVar_68 >= row_begin; nVar_68--)
	{
		int nEsi = (nVar_68 - col_begin) - row_begin * col_len;
		float st00 = pMat->data[nEsi];
		nVar_98 = 0;
		for (int nEcx = 1; nEcx <= row_end; nEcx++)
		{
			int nEax = (nVar_68 - col_begin) + (nEcx - row_begin) * col_len;
			if (st00 > pMat->data[nEax])
			{
				st00 = pMat->data[nEax];
				nVar_98 = nEcx;
			}
		}

		//loc_6EDACD34
		pfltVar_CC[nVar_68 - row_begin] = st00;
		int nEdx = pnVar_DC[nVar_98 - row_begin];
		pnVar_DC[nVar_98 - row_begin]++;

		if (nEdx != 0)
		{
			pOverlap_Ratio->pn0C[nVar_68] = -1;
		}
		else
		{
			//loc_6EDACDC0
			pOverlap_Ratio->ratio[nVar_98] = nVar_68;
			pOverlap_Ratio->pn0C[nVar_68] = nVar_98;
		}
	}

	//loc_6EDACDFB
	nVar_94 = 0;
	for (int nVar_64 = row_begin; nVar_64 <= row_end; nVar_64++)
	{
		if (pnVar_DC[nVar_64 - row_begin] == 0)
		{
			pnVar_D4[nVar_94 - row_begin] = nVar_64;
			nVar_94++;
		}
		else if (pnVar_DC[nVar_64 - row_begin] == 1)
		{
			nVar_20 = pOverlap_Ratio->ratio[nVar_64];
			double st00 = FLT_MAX;
			for (int nEsi = row_begin; nEsi <= row_end; nEsi++)
			{
				if (nEsi != nVar_20)
				{
					int nEdx = (nEsi - col_begin) + (nVar_64 - row_begin) * col_len;
					double st01 = (double)pMat->data[nEdx] - (double)pfltVar_CC[nEsi - row_begin];
					if (st01 < st00)
					{
						st00 = st01;
					}
				}
			}

			//loc_6EDAD059
			pfltVar_CC[nVar_20 - row_begin] = (float)((double)pfltVar_CC[nVar_20 - row_begin] - st00);
		}
	}

	//loc_6EDAD086
	nVar_90 = 0;
	nVar_74 = 0;
	nVar_FC = -row_begin * 4;

	while (TRUE)
	{
		//loc_6EDAD0A8
		nVar_14 = 0;
		nVar_8C = 0;
		if (nVar_94 != 0)
		{
			do
			{
				//loc_6EDAE1D7
				nVar_88 = pnVar_D4[nVar_8C - row_begin];
				nVar_8C++;
				int index = (nVar_88 - row_begin) * col_len - col_begin;
				double st00 = (double)pMat->data[index] - (double)pfltVar_CC[nVar_FC];
				double st01 = FLT_MAX;
				int nEsi = 0;
				for (int nEcx = 1; nEcx <= row_end; nEcx++)
				{
					int nEdx_1 = (nVar_88 - row_begin) * col_len + (nEcx - col_begin);
					st02 = (double)pMat->data[nEdx_1] - (double)pfltVar_CC[nEcx - row_begin];
					if (st02 < st01)
					{
						st01 = st02;
						nVar_90 = nEcx;
						if (st01 < st00)
						{
							double temp = st00;
							st00 = st01;
							st01 = temp;
							nVar_90 = nEsi;
							nEsi = nEcx;
						}
					}
				}

				//loc_6EDAE0FA
				st02 = fabs(st00 - st01);
				double st03 = 0.001f;
				int nEdx = pOverlap_Ratio->pn0C[nEsi];
				BYTE byBl = (st02 > st03) ? 1 : 0;
				if (st02 > st03 && st01 > st00)
				{
					pfltVar_CC[nEsi - row_begin] = (float)((double)pfltVar_CC[nEsi - row_begin] - (st01 - st00));
				}
				else
				{
					if (nEdx >= 0)
					{
						nEdx = pOverlap_Ratio->pn0C[nVar_90];
						nEsi = nVar_90;
					}
				}

				//loc_6EDAE158
				pOverlap_Ratio->ratio[nVar_88] = nEsi;
				pOverlap_Ratio->pn0C[nEsi] = nVar_88;
				if (nEdx >= 0)
				{
					if (byBl != 0 && st01 > st00)
					{
						nVar_8C--;
						pnVar_D4[nVar_8C - row_begin] = nEdx;
					}
					else
					{
						pnVar_D4[nVar_14 - row_begin] = nEdx;
						nVar_14++;
					}
				}
			} while (nVar_8C < nVar_94);
		}

		//loc_6EDAD0C7
		nVar_74++;
		if (nVar_74 == 2)
		{
			nVar_70 = nVar_14 - 1;
			if (nVar_14 != 0)
			{
				//0x6EDAD0E7
				nVar_78 = 0;
				nVar_58 = 0;
				int nEsi;
				bool bFlag = false;

				for (nVar_58 = 0; nVar_58 <= nVar_70; nVar_58++)
				{
					//loc_6EDAD104
					nVar_84 = pnVar_D4[nVar_58 - row_begin];

					for (nEsi = row_begin; nEsi <= row_end; nEsi++)
					{
						int nEax = (nEsi - col_begin) + (nVar_84 - row_begin) * col_len;
						pfltVar_D0[nEsi - row_begin] = pMat->data[nEax] - pfltVar_CC[nEsi - row_begin];

						pnVar_E0[nEsi - row_begin] = nVar_84;
						pnVar_D8[nEsi - row_begin] = nEsi;
					}

					//loc_6EDAD1FC
					int nEdi = 0;
					nVar_80 = 0;
					nVar_7C = nEdi;

					int nEcx;
					double st00;
					while (true)
					{
						nEdi = nVar_7C;
						if (nEdi == nVar_80)
						{
							//loc_6EDAD60A
							nVar_78 = nEdi - 1;
							int nEax = pnVar_D8[nEdi - row_begin];
							st00 = pfltVar_D0[nEax - row_begin];
							nVar_7C = nEdi + 1;
							for (int nEbx = nVar_7C; nEbx <= row_end; nEbx++)
							{
								nEcx = pnVar_D8[nEbx - row_begin];
								if (st00 >= pfltVar_D0[nEcx - row_begin])
								{
									if (st00 > pfltVar_D0[nEcx - row_begin])
									{
										st00 = pfltVar_D0[nEcx - row_begin];
										nVar_7C = nEdi;
									}

									//loc_6EDAD698
									nVar_120 = pnVar_D8[nVar_7C - row_begin];
									pnVar_D8[nEbx - row_begin] = nVar_120;
									pnVar_D8[nVar_7C - row_begin] = nEcx;
									nVar_7C++;
								}
							}

							//loc_6EDAD910
							nVar_54 = nVar_7C - 1;
							for (nEsi = nEdi; nEsi <= nVar_54; nEsi++)
							{
								nEax = pnVar_D8[nEsi - row_begin];
								nEax = pOverlap_Ratio->pn0C[nEax];
								if (nEax < 0)
								{
									//loc_6EDADB77
									nEcx = pnVar_D8[nEsi - row_begin];

									//loc_6EDADB88
									bFlag = true;
									break;
								}
							}
						}

						if (bFlag == true)
						{
							bFlag = false;
							break;
						}

						//loc_6EDAD211
						nEsi = pnVar_D8[nVar_80 - row_begin];
						nVar_80++;
						nVar_18 = pOverlap_Ratio->pn0C[nEsi];
						nEcx = (nEsi - col_begin) + (nVar_18 - row_begin) * col_len;
						double st01 = pMat->data[nEcx] - pfltVar_CC[nEsi - row_begin] - st00;

						for (int nVar_50 = nVar_7C; nVar_50 <= row_end; nVar_50++)
						{
							nEsi = pnVar_D8[nVar_50 - row_begin];
							nEcx = (nEsi - col_begin) + (nVar_18 - row_begin) * col_len;
							st02 = (double)pMat->data[nEcx] - (double)pfltVar_CC[nEsi - row_begin] - st01;
							double st03 = pfltVar_D0[nEsi - row_begin];

							if (st03 > st02)
							{
								nEcx = nVar_18;
								pnVar_E0[nEsi - row_begin] = nEcx;
								double temp = st00;
								st00 = st02;
								st02 = temp;
								if (st02 == st00)
								{
									if (pOverlap_Ratio->pn0C[nEsi] < 0)
									{
										nEcx = nEsi;

										//loc_6EDADB88
										bFlag = true;
										break;
									}
									else
									{
										//0x6EDAD372
										pnVar_D8[nVar_50 - row_begin] = pnVar_D8[nVar_7C - row_begin];
										pnVar_D8[nVar_7C - row_begin] = nEsi;
										double temp = st02;
										st02 = st00;
										st00 = temp;
									}
								}

								//loc_6EDAD3A2
								pfltVar_D0[nEsi - row_begin] = (float)st00;
							}
						}

						if (bFlag == true)
						{
							bFlag = false;
							break;
						}
					}

					//loc_6EDADB88
					for (int nEbx = 0; nEbx <= nVar_78; nEbx++)
					{
						pfltVar_CC[pnVar_D8[nEbx - row_begin] - row_begin] = pfltVar_CC[pnVar_D8[nEbx - row_begin] - row_begin] + pfltVar_D0[pnVar_D8[nEbx - row_begin] - row_begin] - (float)st02;
						//	pfltVar_CC[pnVar_D8[nEbx + 1 - row_begin] - row_begin] = pfltVar_CC[pnVar_D8[nEbx + 1 - row_begin] - row_begin] + pfltVar_D0[pnVar_D8[nEbx + 1] - row_end] - (float)st02;
						//	pfltVar_CC[pnVar_D8[nEbx + 2 - row_begin] - row_begin] = pfltVar_CC[pnVar_D8[nEbx + 2 - row_begin] - row_begin] + pfltVar_D0[pnVar_D8[nEbx + 2] - row_end]- (float)st02;
					}

					//loc_6EDADDA2
					int nEdx;
					do
					{
						nEdx = pnVar_E0[nEcx - row_begin];
						pOverlap_Ratio->pn0C[nEcx] = nEdx;
						nEsi = pOverlap_Ratio->ratio[pnVar_E0[nEcx - row_begin]];
						pOverlap_Ratio->ratio[pnVar_E0[nEcx - row_begin]] = nEcx;
						nEcx = nEsi;
					} while (nVar_84 != nEdx);
				}

				//loc_6EDADE1A
				double st00 = 0;
				for (nEsi = row_begin; nEsi <= row_end; nEsi++)
				{
					int nEdx_1 = (nEsi - row_begin) * col_len + (pOverlap_Ratio->ratio[nEsi] - col_begin);
					st00 = st00 + (double)pMat->data[nEdx_1];
				}

				//loc_6EDAE0A5
				pOverlap_Ratio->flt10 = (float)st00;
				free(pfltVar_CC);
				free(pfltVar_D0);
				free(pnVar_D4);
				free(pnVar_D8);
				free(pnVar_DC);
				free(pnVar_E0);	//20120110 by pdh 			
				return;
			}
			else
			{
				//loc_6EDADE1A
				double st00 = 0;
				for (int nEsi = row_begin; nEsi <= row_end; nEsi++)
				{
					int nEdx = (nEsi - row_begin) * col_len + (pOverlap_Ratio->ratio[nEsi] - col_begin);
					st00 = st00 + (double)pMat->data[nEdx];
				}

				//loc_6EDAE0A5
				pOverlap_Ratio->flt10 = (float)st00;

				free(pfltVar_CC);
				free(pfltVar_D0);
				free(pnVar_D4);
				free(pnVar_D8);
				free(pnVar_DC);
				free(pnVar_E0);
				return;
			}
		}
		else
		{
			//loc_6EDAE0E4
			nVar_94 = nVar_14;
		}
	}
}

void sub_6EDAE360(OverlapRatio* pOverlap_Ratio, float* pfltArg_4, int row, int col)
{
	Float_Matrix fill_sparse = sub_6EDABFB0(pfltArg_4, row, col);
	sub_6EDAC520(pOverlap_Ratio, &fill_sparse);

	int* pnRatio_1 = (int*)malloc(sizeof(int) * row);
	int* pnRatio_2 = (int*)malloc(sizeof(int) * col);

	for (int i = 0; i < row; i++)
	{
		if (pOverlap_Ratio->ratio[i] + 1 <= col)
			pnRatio_1[i] = pOverlap_Ratio->ratio[i];
		else
			pnRatio_1[i] = -1;
	}

	for (int i = 0; i < col; i++)
	{
		if (pOverlap_Ratio->pn0C[i] + 1 <= row)
			pnRatio_2[i] = pOverlap_Ratio->pn0C[i];
		else
			pnRatio_2[i] = -1;
	}

	free(pOverlap_Ratio->ratio);
	free(pOverlap_Ratio->pn0C);

	pOverlap_Ratio->num = row;
	pOverlap_Ratio->ratio = pnRatio_1;
	pOverlap_Ratio->n08 = col;
	pOverlap_Ratio->pn0C = pnRatio_2;
}

void sub_6EDAE940(OverlapRatio* pOverlap_Ratio, float* pfltArg_4, int row, int col)
{
	sub_6EDAE360(pOverlap_Ratio, pfltArg_4, row, col);
}

Float_Matrix sub_6EDABFB0(float* pfltArg_0, int row, int col)
{
	Float_Matrix flt_mat;
	int max_num = max(row, col);
	int min_num = min(row, col);

	flt_mat.row = max_num;
	flt_mat.col = max_num;
	flt_mat.data = (float*)malloc(sizeof(float) * max_num * max_num);
	for (int i = 0; i < max_num; i++)
	{
		for (int j = 0; j < max_num; j++)
		{
			int index = i + j * max_num;
			flt_mat.data[index] = 1.0f;
		}
	}

	int index_2 = 0;
	for (int i = 0; i < max_num; i++)
	{
		for (int j = 0; j < min_num; j++)
		{
			int index_1 = j + i * min_num;
			flt_mat.data[index_2] = pfltArg_0[index_1];
			index_2 = index_2 + 1;
		}
		if (row > col)
			index_2 = index_2 + (max_num - min_num);
	}

	return flt_mat;
}

void sub_6EDFA840(float* pfltArg_0, Index_List* pIndex_List, int begin, int end)
{
	int arg_0_begin = 1;
	int nArg_10 = begin;
	int nArg_14 = end;

	for (int i = nArg_10 + 1; i <= nArg_14; i = nArg_10 + 1)
	{
		float flt_st00 = pfltArg_0[nArg_10 - arg_0_begin];

		//loc_6EEADD34
		int nEcx;

		for (int j = i;; j++)
		{
			if (j > nArg_14)
				return;

			int nEdi = j - arg_0_begin;

			if (pfltArg_0[nEdi] > flt_st00)
			{
				nEcx = nArg_10;
				break;
			}

			if (pfltArg_0[nEdi] < flt_st00)
			{
				//loc_6EEAE039
				nEcx = j;
				break;
			}

		}

		//loc_6EEAE084
		int arg_8_begin = 1;
		flt_st00 = pfltArg_0[nEcx - arg_0_begin];
		int nEdi = nArg_10;

		for (int nVar_4 = nArg_14; nVar_4 >= nEdi;)
		{
			//loc_6EEAE0B1
			float fltVar_28 = pfltArg_0[nEdi - arg_0_begin];
			int tmp = pIndex_List->pIndex[nEdi - arg_8_begin];

			pfltArg_0[nEdi - arg_0_begin] = pfltArg_0[nVar_4 - arg_0_begin];
			pIndex_List->pIndex[nEdi - arg_8_begin] = pIndex_List->pIndex[nVar_4 - arg_8_begin];

			pfltArg_0[nVar_4 - arg_0_begin] = fltVar_28;
			pIndex_List->pIndex[nVar_4 - arg_8_begin] = tmp;

			while (pfltArg_0[nEdi - arg_0_begin] > flt_st00)
				nEdi++;

			//loc_6EEAE301				
			while (pfltArg_0[nVar_4 - arg_0_begin] <= flt_st00)
				nVar_4--;

			//loc_6EEAE313
		}

		//loc_6EEAE323
		sub_6EDFA840(pfltArg_0, pIndex_List, nArg_10, nEdi - 1);
		nArg_10 = nEdi;
	}
}

Index_List sub_6EDFC5A0(float* pfltArg_0, int count)
{
	Index_List id_list;

	id_list.num = count;
	id_list.pIndex = (int*)malloc(sizeof(int) * count);

	for (int i = 0; i < count; i++)
		id_list.pIndex[i] = i + 1;

	sub_6EDFA840(pfltArg_0, &id_list, 1, count);

	return id_list;
}

void sub_6EE5C3B0(STC11* pstc11_Arg_0)
{
	float ramda = 0.75f;
	float weight = 0.68f;

	for (int i = 0; i < 4; i++)
	{
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[0] = pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[0] + weight * pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[1] + weight * weight * pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[2];
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[3] = pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[3] * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[4] = pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[4] * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[5] = pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[5] * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[6] = pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[6] * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[7] = (pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[7] - pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[6]) * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[8] = (pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[8] - 2 * pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[7] + pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[6]) * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[9] = pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[9] * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[10] = (pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[10] - pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[9]) * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[11] = (pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[11] - 2 * pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[10] + pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[9]) * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[12] = pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[12] * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[13] = (pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[13] - pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[12]) * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[14] = (pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[14] - 2 * pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[13] + pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[12]) * ramda;

		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[0] = pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[0] + weight * pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[1] + weight * weight * pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[2];
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[3] = pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[3] * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[4] = pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[4] * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[5] = pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[5] * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[6] = pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[6] * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[7] = (pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[7] - pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[6]) * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[8] = (pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[8] - 2 * pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[7] + pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[6]) * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[9] = pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[9] * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[10] = (pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[10] - pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[9]) * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[11] = (pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[11] - 2 * pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[10] + pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[9]) * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[12] = pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[12] * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[13] = (pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[13] - pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[12]) * ramda;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[14] = (pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[14] - 2 * pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[13] + pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[12]) * ramda;
	}

	double st00 = 0;
	for (int i = 0; i < 4; i++)
	{
		float fltX = calcDeterminant(&pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[6]);
		float fltY = calcDeterminant(&pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[6]);
		st00 = st00 + fabs(fltX) + fabs(fltY);
	}

	pstc11_Arg_0->stc23_00.flt1A8 = (float)(st00 / 8);
}

void sub_6EE5CAD0(STC23* pstc23_Arg_0, KipFaceLandmark* pFaceLandmark, float confidence)
{
	float test_data[16];

	for (int i = 0; i < 4; i++)
	{
		test_data[0] = confidence; test_data[1] = 0; test_data[2] = 0;
		test_data[3] = pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[6];
		test_data[4] = pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[7] - pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[6];
		test_data[5] = pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[6] - 2 * pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[7] + pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[8];
		test_data[6] = pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[9];
		test_data[7] = pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[10] - pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[9];
		test_data[8] = pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[9] - 2 * pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[10] + pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[11];
		test_data[9] = pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[12];
		test_data[10] = pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[13] - pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[12];
		test_data[11] = pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[12] - 2 * pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[13] + pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[14];
		test_data[12] = confidence * pFaceLandmark[i].pos.x;
		test_data[13] = pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[3];
		test_data[14] = pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[4];
		test_data[15] = pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[5];

		sub_6EDAB2C0(test_data, &test_data[12], &pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[6],
			&pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[3], &pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[0], 0.75f);

		test_data[0] = confidence; test_data[1] = 0; test_data[2] = 0;
		test_data[3] = pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[6];
		test_data[4] = pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[7] - pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[6];
		test_data[5] = pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[6] - 2 * pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[7] + pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[8];
		test_data[6] = pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[9];
		test_data[7] = pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[10] - pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[9];
		test_data[8] = pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[9] - 2 * pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[10] + pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[11];
		test_data[9] = pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[12];
		test_data[10] = pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[13] - pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[12];
		test_data[11] = pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[12] - 2 * pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[13] + pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[14];
		test_data[12] = confidence * pFaceLandmark[i].pos.y;
		test_data[13] = pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[3];
		test_data[14] = pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[4];
		test_data[15] = pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[5];

		sub_6EDAB2C0(test_data, &test_data[12], &pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[6],
			&pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[3], &pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[0], 0.75f);
	}

	double st00 = 0;
	for (int i = 0; i < 4; i++)
	{
		float fltX = calcDeterminant(&pstc23_Arg_0->stc14Tb_00[2 * i].fltTb_00[6]);
		float fltY = calcDeterminant(&pstc23_Arg_0->stc14Tb_00[2 * i + 1].fltTb_00[6]);
		st00 = st00 + fabs(fltX) + fabs(fltY);
	}

	pstc23_Arg_0->flt1A8 = (float)(st00 / 8);
	pstc23_Arg_0->flt1A4 = confidence;
}

void sub_6EE5D1C0(STC11* pstc11_Arg_0, KipFaceLandmark* pFaceLandmark, float confidence)
{
	float mask[9] = { 1.f, 0, 0, 1.f, -1.f, 1.f, 1.f, -2.f, 4.f };

	for (int i = 0; i < 4; i++)
	{
		//Initialize Element X
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[0] = pFaceLandmark[i].pos.x;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[1] = 0;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[2] = 0;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[3] = pFaceLandmark[i].pos.x * confidence;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[4] = pFaceLandmark[i].pos.x * confidence;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[5] = pFaceLandmark[i].pos.x * confidence;

		for (int j = 0; j < 9; j++)
			pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[j + 6] = mask[j] * confidence;

		//Initialize Element Y
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[0] = pFaceLandmark[i].pos.y;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[1] = 0;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[2] = 0;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[3] = pFaceLandmark[i].pos.y * confidence;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[4] = pFaceLandmark[i].pos.y * confidence;
		pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[5] = pFaceLandmark[i].pos.y * confidence;

		for (int j = 0; j < 9; j++)
			pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[j + 6] = mask[j] * confidence;
	}
}

int sub_6EEDCF00(FaceInfo* pFaceInfo, float fltArg_4)
{
	if (pFaceInfo == NULL)
		return 0;

	int nEbp = 0;
	for (int i = 0; i < pFaceInfo->num; i++)
	{
		if (pFaceInfo->confidence[i] >= fltArg_4)
			nEbp++;
	}

	return nEbp;
}

inline void loc_6EF19710(STC11* pstc11_Esi, BYTE byAl, BYTE byDl, BYTE byEdi, BYTE byBp, BYTE byCl, int nEbx)
{
	pstc11_Esi->by1B5 = byAl;
	pstc11_Esi->by1B8 = byDl;
	pstc11_Esi->by1B9 = 0;
	pstc11_Esi->by1B7 = byEdi;
	pstc11_Esi->by1B6 = byBp;
	pstc11_Esi->by1B4 = byCl;
	pstc11_Esi->n1B0 = nEbx;
	pstc11_Esi->n1AC = 0;
}

FaceInfo* sub_6EEDE0B0(FaceInfo* pFaceInfo, BYTE byArg_4)
{
	if (pFaceInfo != NULL)
	{
		//loc_6EEDE115
		if (byArg_4 != 0)
		{
			//loc_6EEDE131
			for (int i = 0; i < pFaceInfo->num; i++)
				free(pFaceInfo->pFaceLandmark[i]);
		}

		//loc_6EEDE11B
		free(pFaceInfo);
	}
	return NULL;
}

void sub_6EF17E20(STC11* pstc11_Arg_0)
{
	STC23	stc23_Var_1BC;
	BYTE	byVar_1C1;

	memcpy((LPBYTE)&stc23_Var_1BC, (LPBYTE)&pstc11_Arg_0->stc23_00, sizeof(STC23));

	byVar_1C1 = pstc11_Arg_0->by1B4;

	float flt_st01 = stc23_Var_1BC.flt1A4;
	float flt_st00 = stc23_Var_1BC.flt1A8;

	BYTE Dl;
	BYTE Cl;
	int nEdi;

	if (byVar_1C1 != 0)
	{
		//loc_6EF17F40
		if (0.2 <= flt_st01 || 0.001 <= flt_st00)	//detection_stop_threshold, motion_stop_threshold
		{
			//loc_6EF17F7A
			nEdi = pstc11_Arg_0->n1AC;
			if (nEdi <= 15)
			{
				//loc_6EF17FC3
				pstc11_Arg_0->n1B0 += 1;
				Dl = pstc11_Arg_0->by1B6;
				Cl = pstc11_Arg_0->by1B7;
			}
			else
			{
				//0x6EF17F56
				pstc11_Arg_0->by1B9 = 1;
				Dl = pstc11_Arg_0->by1B6;
				Cl = pstc11_Arg_0->by1B7;
			}
		}
		else
		{
			//0x6EF17F56
			pstc11_Arg_0->by1B9 = 1;
			Dl = pstc11_Arg_0->by1B6;
			Cl = pstc11_Arg_0->by1B7;
			nEdi = pstc11_Arg_0->n1AC;
		}
	}
	else
	{
		//0x6EF17E7E
		if (flt_st01 >= 0.2)	//detection_start_threshold
		{
			pstc11_Arg_0->by1B6 = 1;
		}
		//loc_6EF17E93
		if (flt_st00 >= 0.0075)	//motion_start_threshold
		{
			pstc11_Arg_0->by1B7 = 1;
		}
		flt_st00 = flt_st01;
		//loc_6EF17EA6
		Dl = pstc11_Arg_0->by1B6;
		Cl = pstc11_Arg_0->by1B7;

		if (Dl != 0)
		{
			//loc_6EF17FA0
			if (Cl != 0)
			{
				pstc11_Arg_0->by1B4 = 1;
				pstc11_Arg_0->n1B0 = 1;
				byVar_1C1 = 1;
			}
		}
		//loc_6EF17EBC
		nEdi = pstc11_Arg_0->n1AC;
	}
	//loc_6EF17EC2
	if (flt_st00 >= 0.6)	//High Confidence
	{
		if (byVar_1C1 != 0)
		{
			//loc_6EF17F30
			pstc11_Arg_0->by1B8 = 1;
		}
	}
	//loc_6EF17ED5
	BYTE byAl = 0;
	if (Dl != 0 || Cl != 0)
	{
		//loc_6EF17F11
		byAl = 1;
		if (Dl == Cl)
		{
			Dl = pstc11_Arg_0->by1B8;
			byAl = (Dl < 1) ? 2 : 3;
		}
	}
	//loc_6EF17EDF
	if (nEdi > 0)
	{
		byAl = 1;
	}

	//loc_6EF17EE8
	pstc11_Arg_0->by1B5 = byAl;
}

void sub_6EF195E0(STC11* pstc11_Arg_0, KipFaceLandmark* pFaceLandmark, float confidence)
{
	float conf = confidence + 0.05f;
	sub_6EE5D1C0(pstc11_Arg_0, pFaceLandmark, conf);

	double st00 = 0;
	for (int i = 0; i < 4; i++)
	{
		float fltX = calcDeterminant(&pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i].fltTb_00[6]);
		float fltY = calcDeterminant(&pstc11_Arg_0->stc23_00.stc14Tb_00[2 * i + 1].fltTb_00[6]);
		st00 = st00 + fabs(fltX) + fabs(fltY);
	}

	pstc11_Arg_0->stc23_00.flt1A8 = (float)(st00 / 8);
	pstc11_Arg_0->stc23_00.flt1A4 = conf;

	BYTE byDl = 0;
	if (pstc11_Arg_0->stc23_00.flt1A4 >= 0.2)
		byDl = 1;

	BYTE byAl;

	BYTE byEdi = 1;
	BYTE byBp = byDl;

	if (pstc11_Arg_0->stc23_00.flt1A8 < 0.075)
	{
		//loc_6EF197D4, Db
		byAl = byDl;
		byEdi = 0;
		if (byDl == 0)
		{
			//loc_6EF19800
			loc_6EF19710(pstc11_Arg_0, byAl, 0, byEdi, byBp, 0, 0);
			return;
		}
	}
	else
	{
		//6EF196CB, Db
		byEdi = 1;

		if (byBp != 0)
		{
			if (pstc11_Arg_0->stc23_00.flt1A4 > 0.6f)
			{
				loc_6EF19710(pstc11_Arg_0, 3, 1, 1, byBp, 1, 1);
				return;
			}
			else
			{
				loc_6EF19710(pstc11_Arg_0, 2, 1, 1, byBp, 1, 1);
				return;
			}
		}
	}

	//loc_6EF197E2
	if (byBp == byEdi)
	{
		//loc_6EF1980B
		loc_6EF19710(pstc11_Arg_0, 2, 0, byEdi, byBp, 0, 0);
		return;
	}
	else
	{
		//6EF197EA, db
		loc_6EF19710(pstc11_Arg_0, 1, 0, byEdi, byBp, 0, 0);
		return;
	}
}

void sub_6EF1C280(STA111* psta111_Arg_0)
{
	psta111_Arg_0->n00 = INT_MIN;
	psta111_Arg_0->psta112_04 = NULL;
	psta111_Arg_0->stc11_08.n1AC = 0;
	psta111_Arg_0->stc11_08.n1B0 = 0;
	psta111_Arg_0->stc11_08.by1B4 = 0;
	psta111_Arg_0->stc11_08.by1B6 = 0;
	psta111_Arg_0->stc11_08.by1B7 = 0;
	psta111_Arg_0->stc11_08.by1B8 = 0;
	psta111_Arg_0->stc11_08.by1B9 = 0;
}

STA107* sub_6EF1C790(STA107* psta107_Arg_0)
{
	if (psta107_Arg_0 == NULL)
		return psta107_Arg_0;

	STA107* psta107_Edx = psta107_Arg_0;
	while (psta107_Edx->psta107_next != NULL)
		psta107_Edx = psta107_Edx->psta107_next;

	return psta107_Edx;
}

STA112* sub_6EF1C800(STA112* psta112_Arg_0)
{
	STA112 * psta112_Eax = psta112_Arg_0;

	if (psta112_Eax == NULL || psta112_Eax->psta112_04 == NULL)
	{
		//loc_6EF1C820
		return psta112_Eax;
	}
	STA112 * psta112_Edx = psta112_Eax->psta112_04;

	while (TRUE)
	{
		psta112_Eax = psta112_Edx->psta112_04;

		if (psta112_Eax == NULL)
			break;

		psta112_Edx = psta112_Eax;
	}
	return psta112_Edx;
}

STA107* sub_6EF1C830(STA107* psta107_Arg_0)
{
	if (psta107_Arg_0 == NULL)
		return NULL;

	STA107* psta107_Edx = psta107_Arg_0;

	while (psta107_Edx->psta107_prev != NULL)
		psta107_Edx = psta107_Edx->psta107_prev;

	return psta107_Edx;
}

STA112* sub_6EF1C860(STA107* psta107_Arg_0)
{
	STA107 * psta107_Edx = psta107_Arg_0;

	if (psta107_Edx != NULL)
	{
		//loc_6EF1C873
		while (psta107_Edx->psta107_next != NULL)
		{
			psta107_Edx = psta107_Edx->psta107_next;
		}
	}
	//loc_6EF1C880
	return (STA112 *)psta107_Edx;
}

STA107* sub_6EF1E510(STA107* psta107_Arg_0, KipFaceLandmark* pFaceLandmark, BYTE byArg_8)
{
	if (psta107_Arg_0 == NULL)
	{
		psta107_Arg_0 = (STA107*)malloc(sizeof(STA107));
		psta107_Arg_0->face_info = NULL;
		psta107_Arg_0->psta107_04 = NULL;
		psta107_Arg_0->psta107_prev = NULL;
		psta107_Arg_0->psta107_next = NULL;
		psta107_Arg_0->psta107_10 = NULL;
		psta107_Arg_0->psta109_14 = NULL;
		psta107_Arg_0->track_id = -1;
		psta107_Arg_0->pFaceLandmark = NULL;
		psta107_Arg_0->yaw_angle = 0;
		psta107_Arg_0->detected_id = -1;
	}

	if (byArg_8 != 0)
	{
		psta107_Arg_0->pFaceLandmark = (KipFaceLandmark*)malloc(sizeof(KipFaceLandmark) * 4);
		memcpy(psta107_Arg_0->pFaceLandmark, pFaceLandmark, sizeof(KipFaceLandmark) * 4);
	}
	else
		psta107_Arg_0->pFaceLandmark = pFaceLandmark;

	return psta107_Arg_0;
}

BoundingBox_List sub_6EF1E5C0(STA107* psta107_Arg_0)
{
	BoundingBox_List bb_list = { 0 };

	if (psta107_Arg_0 == NULL)
		return bb_list;

	STA107* psta107_Edx = psta107_Arg_0;
	while (psta107_Edx->psta107_prev != NULL)
		psta107_Edx = psta107_Edx->psta107_prev;

	STA107* psta107_Eax = psta107_Edx;
	int nEbx = 0;
	while (psta107_Eax != NULL)
	{
		nEbx++;
		psta107_Eax = psta107_Eax->psta107_next;
	}

	bb_list.num = nEbx;
	bb_list.pBounding_Box = (BoundingBox*)malloc(sizeof(BoundingBox) * nEbx);

	STA107* psta107_Esi = psta107_Arg_0;
	psta107_Eax = psta107_Esi->psta107_prev;

	while (psta107_Eax != NULL)
	{
		psta107_Edx = psta107_Eax;
		psta107_Eax = psta107_Eax->psta107_prev;
	}

	int index = 0;
	while (psta107_Edx != NULL)
	{
		bb_list.pBounding_Box[index].coord_00_04 = psta107_Edx->pFaceLandmark[3].pos;
		bb_list.pBounding_Box[index].coord_08_0C = psta107_Edx->pFaceLandmark[2].pos;
		bb_list.pBounding_Box[index].coord_10_14 = psta107_Edx->pFaceLandmark[1].pos;
		bb_list.pBounding_Box[index].coord_18_1C = psta107_Edx->pFaceLandmark[0].pos;

		bb_list.pBounding_Box[index].flt24 = psta107_Edx->confidence;
		bb_list.pBounding_Box[index].flt28 = psta107_Edx->yaw_angle;
		bb_list.pBounding_Box[index].psta112_2C = (STA112*)psta107_Edx;

		index++;
		psta107_Edx = psta107_Edx->psta107_next;
	}

	return bb_list;
}

int sub_6EF1ED40(STA107* psta107_Arg_0, int* pnArg_4, int count)
{
	if (pnArg_4 == NULL || psta107_Arg_0 == NULL)
		return 0;

	STA107* psta107_Edx = psta107_Arg_0;
	while (psta107_Edx->psta107_prev != NULL)
		psta107_Edx = psta107_Edx->psta107_prev;

	if (psta107_Edx == NULL)
		return 0;

	STA107* psta107_Ebx = psta107_Edx;

	int nEsi = 0;

	do
	{
		for (int i = 0; i < count; i++)
		{
			if (pnArg_4[i] == psta107_Ebx->track_id)
				nEsi++;
		}
		psta107_Ebx = psta107_Ebx->psta107_next;
	} while (psta107_Ebx != NULL);

	return nEsi;
}

BoundingBox_List sub_6EF1EE10(STA107* psta107_Arg_0, int count, int* pnArg_8)
{
	BoundingBox_List bb_list = { 0 };

	if (psta107_Arg_0 == NULL)
		return bb_list;

	STA107* psta107_Edx = psta107_Arg_0;
	while (psta107_Edx->psta107_prev != NULL)
		psta107_Edx = psta107_Edx->psta107_prev;

	STA107* psta107_Ebx = psta107_Edx;

	int nEsi = 0;
	while (psta107_Ebx != NULL)
	{
		for (int i = 0; i < count; i++)
		{
			if (pnArg_8[i] == psta107_Ebx->track_id)
			{
				nEsi++;
				break;
			}
		}
		psta107_Ebx = psta107_Ebx->psta107_next;
	}

	if (nEsi == 0)
		return bb_list;

	bb_list.num = nEsi;
	bb_list.pBounding_Box = (BoundingBox*)malloc(sizeof(BoundingBox) * nEsi);

	STA107* psta107_Ebp = psta107_Arg_0;
	STA107* psta107_Eax = psta107_Ebp->psta107_prev;

	while (psta107_Eax != NULL)
	{
		psta107_Edx = psta107_Eax;
		psta107_Eax = psta107_Eax->psta107_prev;
	}

	psta107_Ebp = psta107_Edx;
	if (psta107_Edx == NULL)
		return bb_list;

	int index = 0;
	while (psta107_Ebp != NULL)
	{
		bool bExistence = false;
		for (int i = 0; i < count; i++)
		{
			if (pnArg_8[i] == psta107_Ebp->track_id)
			{
				bExistence = true;
				break;
			}
		}

		if (bExistence == true)
		{
			bb_list.pBounding_Box[index].coord_00_04 = psta107_Ebp->pFaceLandmark[3].pos;
			bb_list.pBounding_Box[index].coord_08_0C = psta107_Ebp->pFaceLandmark[2].pos;
			bb_list.pBounding_Box[index].coord_10_14 = psta107_Ebp->pFaceLandmark[1].pos;
			bb_list.pBounding_Box[index].coord_18_1C = psta107_Ebp->pFaceLandmark[0].pos;

			bb_list.pBounding_Box[index].flt24 = psta107_Ebp->confidence;
			bb_list.pBounding_Box[index].flt28 = psta107_Ebp->yaw_angle;
			bb_list.pBounding_Box[index].psta112_2C = (STA112*)psta107_Ebp;
			index++;
		}

		psta107_Ebp = psta107_Ebp->psta107_next;
	}

	return bb_list;
}

STA107* sub_6EF1F1C0(STA107* psta107_Arg_0, BYTE byArg_4)
{
	if (byArg_4 == 0)
		//loc_6EF1F230
		psta107_Arg_0->face_info = sub_6EEDE0B0(psta107_Arg_0->face_info, 1);

	//loc_6EF1F1D6
	STA107 * psta107_Ebx = psta107_Arg_0->psta107_04;
	if (psta107_Ebx != NULL)
	{
		//0x6EF1F1DD
		STA107 * psta107_Eax = psta107_Ebx->psta107_prev;

		if (psta107_Eax == NULL)
		{
			while (TRUE)
			{
				//loc_6EF1F222
				STA107 * psta107_Esi = psta107_Ebx->psta107_next;

				if (byArg_4 == 0)
				{
					//loc_6EF1F206
					free(psta107_Ebx->pFaceLandmark);
				}

				//loc_6EF1F214
				free(psta107_Ebx);

				if (psta107_Esi == NULL)
					break;

				psta107_Ebx = psta107_Esi;
			}
		}
		else
		{
			//loc_6EF1F1E4
			do
			{
				psta107_Ebx = psta107_Eax;
				psta107_Eax = psta107_Eax->psta107_prev;
			} while (psta107_Eax != NULL);

			if (psta107_Ebx != NULL)
			{
				while (TRUE)
				{
					//loc_6EF1F222
					STA107 * psta107_Esi = psta107_Ebx->psta107_next;

					if (byArg_4 == 0)
					{
						//loc_6EF1F206
						free(psta107_Ebx->pFaceLandmark);
					}

					//loc_6EF1F214
					free(psta107_Ebx);

					if (psta107_Esi == NULL)
						break;

					psta107_Ebx = psta107_Esi;
				}

			}
		}
	}
	//loc_6EF1F1F1
	psta107_Arg_0->psta107_04 = NULL;
	if (psta107_Arg_0 != NULL)
		free(psta107_Arg_0);

	return NULL;
}

STA112* sub_6EF1F390(STA112* psta112_Arg_0)
{
	STA112 * psta112_Ebx = psta112_Arg_0;
	STA112* psta112_Ecx;
	STA112* psta112_Edi;
	STA112* psta112_Esi;

	if (psta112_Ebx == NULL)
	{
		return NULL;
	}
	STA112* psta112_Edx = psta112_Ebx->psta112_00;

	if (psta112_Edx != NULL)
	{
		//0x6EF1F3A5
		do
		{
			psta112_Ebx = psta112_Edx;
			psta112_Edx = psta112_Edx->psta112_00;
		} while (psta112_Edx != NULL);

		if (psta112_Ebx == NULL)
			return NULL;
	}

	while (TRUE)
	{
		//loc_6EF1F41F
		int nEdi = (psta112_Edx != NULL) ? 1 : 0;

		psta112_Ecx = psta112_Ebx->psta112_04;
		int nEsi = (psta112_Ecx != NULL) ? 1 : 0;

		if (nEdi == 0)
		{
			//loc_6EF1F3C0
			psta112_Edi = 0;
			if (nEsi != 0)
			{
				psta112_Ecx->psta112_00 = NULL;
				psta112_Edi = psta112_Ecx;
			}
		}
		else
		{
			if (nEsi != 0)
			{
				//loc_6EF1F456
				psta112_Edx->psta112_04 = psta112_Ecx;
				psta112_Esi = psta112_Ebx->psta112_04;
				psta112_Esi->psta112_00 = psta112_Edx;
				psta112_Edi = psta112_Esi;
			}
			else
			{
				//0x6EF1F43C
				psta112_Edx->psta112_04 = NULL;
				psta112_Edi = psta112_Edx;
			}
		}

		//loc_6EF1F3D0
		psta112_Edx = psta112_Ebx->psta112_08;
		int nEbp = (psta112_Edx != NULL) ? 1 : 0;

		psta112_Ecx = psta112_Ebx->psta112_0C;
		nEsi = (psta112_Ecx != NULL) ? 1 : 0;

		//0x6EF1F3E6
		if (nEbp != 0)
		{
			//loc_6EF1F447
			if (nEsi != 0)
			{
				//loc_6EF1F465
				psta112_Edx->psta112_0C = psta112_Ecx;
				psta112_Esi = psta112_Ebx->psta112_0C;
				psta112_Esi->psta112_08 = psta112_Edx;
				psta112_Edx = psta112_Esi;
			}
			else
			{
				psta112_Edx->psta112_0C = NULL;
			}
		}
		else
		{
			//0x6EF1F3EA
			psta112_Edx = NULL;
			if (nEsi != 0)
			{
				psta112_Ecx->psta112_08 = NULL;
				psta112_Edx = psta112_Ecx;
			}
		}
		//loc_6EF1F3FB
		psta112_Ebx->psta107_10->psta107_04 = (STA107*)psta112_Edx;
		free(psta112_Ebx->pFaceLandmark);

		free(psta112_Ebx);

		if (psta112_Edi == NULL)
			break;

		psta112_Edx = psta112_Edi->psta112_00;
		psta112_Ebx = psta112_Edi;
	}

	return NULL;
}

STA107* sub_6EF1F9B0(STA107* psta107_Arg_0, int nArg_4)
{
	STA107* psta107_Edi = psta107_Arg_0;
	if (psta107_Edi == NULL)
		return NULL;

	STA107* psta107_Esi = psta107_Edi->psta107_prev;
	STA107* psta107_Ebx = psta107_Edi->psta107_next;
	STA107* psta107_Edx;
	STA107* psta107_Ebp;
	STA107* psta107_Eax;

	BYTE byAl = (psta107_Esi == NULL) ? 1 : 0;
	BYTE byDl = (psta107_Ebx == NULL) ? 1 : 0;

	if (byAl != 0)
	{
		//loc_6EF1FA72
		if (byDl != NULL)
		{
			sub_6EF1F1C0(psta107_Edi, 0);
			psta107_Edi = psta107_Ebx;
		}
		else
		{
			//loc_6EF1FA90
			psta107_Ebx->psta107_prev = NULL;
			sub_6EF1F1C0(psta107_Edi, 0);
			psta107_Edi = psta107_Ebx;
		}
		return psta107_Edi;
	}

	//0x6EF1F9DC
	if (byDl != 0)
	{
		//loc_6EF1FABB
		psta107_Esi->psta107_next = NULL;
		sub_6EF1F1C0(psta107_Edi, 0);
		psta107_Edi = psta107_Esi;
		return psta107_Edi;
	}
	//0x6EF1F9E4
	psta107_Esi->psta107_next = psta107_Ebx;
	psta107_Edx = psta107_Edi->psta107_next;
	psta107_Edx->psta107_prev = psta107_Esi;
	psta107_Ebp = psta107_Edx;

	if (nArg_4 == 3)
	{
		psta107_Ebp = psta107_Edi->psta107_prev;
	}
	//0x6EF1F9F8
	psta107_Edi->face_info = sub_6EEDE0B0(psta107_Edi->face_info, 1);
	psta107_Ebx = psta107_Edi->psta107_04;

	if (psta107_Ebx != NULL)
	{
		//0x6EF1FA13
		psta107_Eax = psta107_Ebx->psta107_prev;
		if (psta107_Eax != NULL)
		{
			//loc_6EF1FA20
			do
			{
				psta107_Ebx = psta107_Eax;
				psta107_Eax = psta107_Eax->psta107_prev;
			} while (psta107_Eax != NULL);

			while (TRUE)
			{
				//loc_6EF1FA52
				psta107_Esi = psta107_Ebx->psta107_next;

				free(psta107_Ebx->pFaceLandmark);
				free(psta107_Ebx);

				if (psta107_Esi == NULL)
					break;

				//loc_6EF1FA50
				psta107_Ebx = psta107_Esi;
			}
		}
		else
		{
			while (TRUE)
			{
				//loc_6EF1FA52
				psta107_Esi = psta107_Ebx->psta107_next;

				free(psta107_Ebx->pFaceLandmark);
				free(psta107_Ebx);

				if (psta107_Esi == NULL)
					break;

				//loc_6EF1FA50
				psta107_Ebx = psta107_Esi;
			}
		}
	}

	//loc_6EF1FA30
	psta107_Edi->psta107_04 = NULL;
	free(psta107_Edi);
	return psta107_Ebp;
}

STA107* sub_6EF1FAE0(STA107* psta107_Arg_0)
{
	if (psta107_Arg_0 == NULL)
		return psta107_Arg_0;

	STA107* psta107_Ebx = psta107_Arg_0;
	STA107* psta107_Eax = psta107_Ebx->psta107_next;

	STA107* psta107_Edx;

	if (psta107_Eax != NULL)
	{
		do
		{
			//loc_6EF1FAF3
			psta107_Ebx = psta107_Eax;
			psta107_Eax = psta107_Eax->psta107_next;
		} while (psta107_Eax != NULL);

		if (psta107_Ebx == NULL)
			return NULL;
	}
	//loc_6EF1FB00
	psta107_Edx = psta107_Ebx->psta107_prev;

	if (psta107_Edx == NULL)
	{
		//loc_6EF1FB40
		psta107_Eax = psta107_Ebx;
	}
	else
	{
		do
		{
			psta107_Eax = psta107_Edx;
			psta107_Edx = psta107_Edx->psta107_prev;
		} while (psta107_Edx != NULL);
	}

	//loc_6EF1FB10
	while (psta107_Eax != NULL)
	{
		//loc_6EF1FB20
		psta107_Edx = psta107_Eax->psta107_04;

		if (psta107_Edx != NULL)
			return psta107_Ebx;

		psta107_Eax = sub_6EF1F9B0(psta107_Eax, 2);
	}

	return NULL;
}

STA107* sub_6EF1FB50(STA107* psta107_Arg_0, KipFaceLandmark* pFaceLandmark, float confidence, float m_confidence, int track_id, int track_confidence, float yaw, int detected_id)
{
	STA107 * psta107_Ebx;
	STA107 * psta107_Edi = psta107_Arg_0->psta107_04;

	if (psta107_Edi == NULL || psta107_Edi->psta107_next == NULL)
	{
		//loc_6EF1FBC0
		psta107_Ebx = psta107_Edi;
	}
	else
	{
		psta107_Ebx = psta107_Edi->psta107_next;

		while (psta107_Ebx->psta107_next != NULL)
		{
			//loc_6EF1FB76
			psta107_Ebx = psta107_Ebx->psta107_next;
		}
	}
	//loc_6EF1FB7D
	if (pFaceLandmark != NULL)
	{
		if (psta107_Ebx == NULL)
		{
			//loc_6EF1FBC4
			if (psta107_Edi == 0)
			{
				//loc_6EF1FBF5
				psta107_Edi = (STA107 *)malloc(sizeof(STA107));
				psta107_Edi->face_info = NULL;
				psta107_Edi->psta107_04 = NULL;
				psta107_Edi->psta107_next = NULL;
				psta107_Edi->psta107_prev = NULL;
				psta107_Edi->psta107_10 = NULL;
				psta107_Edi->psta109_14 = NULL;
				psta107_Edi->pFaceLandmark = NULL;
				psta107_Edi->track_id = 0;
				psta107_Edi->confidence = 0;
				psta107_Edi->track_info = INIT_RESULT;
				psta107_Edi->motion_confidence = 0;
				psta107_Edi->yaw_angle = 0;
				psta107_Edi->detected_id = -1;
			}

			psta107_Edi->pFaceLandmark = pFaceLandmark;
			psta107_Edi->confidence = confidence;
			psta107_Edi->track_id = track_id;
			psta107_Edi->track_confidence = track_confidence;
			psta107_Edi->motion_confidence = m_confidence;
			psta107_Edi->track_info = TRACKED_RESULT;
			psta107_Edi->yaw_angle = yaw;
			psta107_Edi->detected_id = detected_id;
			psta107_Edi->psta107_10 = psta107_Arg_0;
		}
		else
		{
			STA107 * psta107_Esi = psta107_Ebx->psta107_next;
			if (psta107_Esi == 0)
			{
				//loc_6EF1FBF5
				psta107_Esi = (STA107 *)malloc(sizeof(STA107));
				psta107_Esi->face_info = NULL;
				psta107_Esi->psta107_04 = NULL;
				psta107_Esi->psta107_next = NULL;
				psta107_Esi->psta107_prev = NULL;
				psta107_Esi->psta107_10 = NULL;
				psta107_Esi->psta109_14 = NULL;
				psta107_Esi->pFaceLandmark = NULL;
				psta107_Esi->track_id = 0;
				psta107_Esi->track_info = INIT_RESULT;
				psta107_Esi->confidence = 0;
				psta107_Esi->motion_confidence = 0;
				psta107_Esi->yaw_angle = 0;
			}

			psta107_Esi->pFaceLandmark = pFaceLandmark;
			psta107_Esi->confidence = confidence;
			psta107_Esi->track_id = track_id;
			psta107_Esi->track_confidence = track_confidence;
			psta107_Esi->track_info = TRACKED_RESULT;
			psta107_Esi->yaw_angle = yaw;
			psta107_Esi->detected_id = detected_id;
			psta107_Esi->motion_confidence = m_confidence;

			//loc_6EF1FBA6
			psta107_Ebx->psta107_next = psta107_Esi;
			psta107_Edi = psta107_Edi->psta107_next;
			psta107_Esi->psta107_prev = psta107_Ebx;
			psta107_Esi->psta107_10 = psta107_Arg_0;
		}
	}
	//loc_6EF1FBB2
	psta107_Arg_0->psta107_04 = psta107_Edi;

	return psta107_Arg_0;
}

STA107*	sub_6EF1FC10(STA107* psta107_Arg_0, FaceInfo* pFaceInfo, float fltArg_8, BYTE byArg_C)
{
	if (psta107_Arg_0 == NULL)
	{
		psta107_Arg_0 = (STA107*)malloc(sizeof(STA107));
		psta107_Arg_0->face_info = 0;
		psta107_Arg_0->psta107_04 = 0;
		psta107_Arg_0->psta107_prev = 0;
		psta107_Arg_0->psta107_next = 0;
	}

	if (byArg_C != 0)
	{
		psta107_Arg_0->face_info = (FaceInfo*)malloc(sizeof(FaceInfo));
		psta107_Arg_0->face_info->frame_index = pFaceInfo->frame_index;
		psta107_Arg_0->face_info->num = pFaceInfo->num;
		psta107_Arg_0->face_info->pFaceLandmark = (KipFaceLandmark**)malloc(4 * pFaceInfo->num);

		for (int i = 0; i < pFaceInfo->num; i++)
		{
			psta107_Arg_0->face_info->pFaceLandmark[i] = (KipFaceLandmark*)malloc(sizeof(KipFaceLandmark) * 4);
			memcpy(psta107_Arg_0->face_info->pFaceLandmark[i], pFaceInfo->pFaceLandmark[i], sizeof(KipFaceLandmark) * 4);
		}

		psta107_Arg_0->face_info->confidence = (float*)malloc(sizeof(float) * pFaceInfo->num);
		memcpy(psta107_Arg_0->face_info->confidence, pFaceInfo->confidence, sizeof(float) * pFaceInfo->num);
		psta107_Arg_0->face_info->yaw = (float*)malloc(sizeof(float) * pFaceInfo->num);
		memcpy(psta107_Arg_0->face_info->yaw, pFaceInfo->yaw, sizeof(float) * pFaceInfo->num);
		psta107_Arg_0->face_info->detected_id = (int*)malloc(sizeof(int) * pFaceInfo->num);
		memcpy(psta107_Arg_0->face_info->detected_id, pFaceInfo->detected_id, sizeof(float) * pFaceInfo->num);
	}
	else
		psta107_Arg_0->face_info = pFaceInfo;

	for (int i = 0; i < psta107_Arg_0->face_info->num; i++)
	{
		if (psta107_Arg_0->face_info->confidence[i] >= fltArg_8)
		{
			STA107* psta107_Ebx = psta107_Arg_0;
			STA107* psta107_Ebp = psta107_Ebx->psta107_04;
			psta107_Ebx = psta107_Ebp;

			if (psta107_Ebp != NULL)
			{
				while (psta107_Ebx->psta107_next != NULL)
					psta107_Ebx = psta107_Ebx->psta107_next;
			}

			if (psta107_Arg_0->face_info->pFaceLandmark[i] != NULL)
			{
				if (psta107_Ebx != NULL)
				{
					STA107* psta107_Esi = psta107_Ebx->psta107_next;
					if (psta107_Esi == NULL)
					{
						psta107_Esi = (STA107*)malloc(sizeof(STA107));
						psta107_Esi->face_info = NULL;
						psta107_Esi->psta107_04 = NULL;
						psta107_Esi->psta107_prev = NULL;
						psta107_Esi->psta107_next = NULL;
						psta107_Esi->psta107_10 = NULL;
						psta107_Esi->psta109_14 = NULL;
						psta107_Esi->track_id = 0;
						psta107_Esi->pFaceLandmark = NULL;
						psta107_Esi->yaw_angle = 0;
						psta107_Esi->detected_id = -1;
					}

					if (byArg_C != 0)
					{
						psta107_Esi->pFaceLandmark = (KipFaceLandmark*)malloc(sizeof(KipFaceLandmark) * 4);
						memcpy(psta107_Esi->pFaceLandmark, psta107_Arg_0->face_info->pFaceLandmark[i], sizeof(KipFaceLandmark) * 4);
					}
					else
						psta107_Esi->pFaceLandmark = psta107_Arg_0->face_info->pFaceLandmark[i];

					psta107_Esi->confidence = psta107_Arg_0->face_info->confidence[i];
					psta107_Esi->yaw_angle = psta107_Arg_0->face_info->yaw[i];
					psta107_Esi->detected_id = psta107_Arg_0->face_info->detected_id[i];

					psta107_Ebx->psta107_next = psta107_Esi;
					psta107_Esi->psta107_prev = psta107_Ebx;
					psta107_Esi->psta107_10 = psta107_Arg_0;
					psta107_Ebp = psta107_Ebp->psta107_next;
				}
				else
				{
					psta107_Ebp = sub_6EF1E510(psta107_Ebp, psta107_Arg_0->face_info->pFaceLandmark[i], byArg_C);
					psta107_Ebp->confidence = psta107_Arg_0->face_info->confidence[i];
					psta107_Ebp->yaw_angle = psta107_Arg_0->face_info->yaw[i];
					psta107_Ebp->detected_id = psta107_Arg_0->face_info->detected_id[i];
					psta107_Ebp->psta107_10 = psta107_Arg_0;
				}
			}

			psta107_Arg_0->psta107_04 = psta107_Ebp;
		}
	}

	return psta107_Arg_0;
}

STA107* sub_6EF1FE00(STA107* psta107_Arg_0, FaceInfo* pFaceInfo, float fltArg_8, BYTE byArg_C)
{
	STA107* psta107_Esi = psta107_Arg_0;
	STA107* psta107_Ebx = psta107_Arg_0;

	if (psta107_Ebx != NULL)
	{
		while (psta107_Esi->psta107_next != NULL)
			psta107_Esi = psta107_Esi->psta107_next;
	}

	if (pFaceInfo != NULL)
	{
		if (psta107_Esi == NULL)
		{
			return sub_6EF1FC10(psta107_Ebx, pFaceInfo, fltArg_8, byArg_C);
		}
		else
		{
			STA107* psta107_Eax = sub_6EF1FC10(psta107_Esi->psta107_next, pFaceInfo, fltArg_8, byArg_C);

			psta107_Esi->psta107_next = psta107_Eax;
			psta107_Ebx = psta107_Ebx->psta107_next;
			psta107_Eax->psta107_prev = psta107_Esi;
		}
	}

	return psta107_Ebx;
}
/*
Calcuate the overlap ratio - 2012/02/04
*/
void sub_6EF20240(OverlapRatio* overlap_ratio, BoundingBox_List bb_list_prev, BoundingBox_List bb_list_cur)
{
	int row_begin = 1;
	int row_end = bb_list_prev.num;
	int col_begin = 1;
	int col_end = bb_list_cur.num;

	BYTE weight_by_cofidence = 1;

	KipCoord_List coord_list;
	for (int i = 0; i < bb_list_prev.num; i++)
	{
		coord_list.num = 4;
		coord_list.pCoord_Pos = (KipCoord2f*)&bb_list_prev.pBounding_Box[i];
		sub_6EE420A0(&coord_list);
	}

	for (int i = 0; i < bb_list_cur.num; i++)
	{
		coord_list.num = 4;
		coord_list.pCoord_Pos = (KipCoord2f*)&bb_list_cur.pBounding_Box[i];
		sub_6EE420A0(&coord_list);
	}

	float* pSparse = (float*)malloc(sizeof(float) * row_end * col_end);
	for (int i = row_begin; i <= row_end; i++)
	{
		for (int j = col_begin; j <= col_end; j++)
		{
			KipCoord_List coord_list1;
			coord_list1.num = 4;
			coord_list1.pCoord_Pos = &bb_list_prev.pBounding_Box[i - row_begin].coord_00_04;
			KipCoord_List coord_list2;
			coord_list2.num = 4;
			coord_list2.pCoord_Pos = &bb_list_cur.pBounding_Box[j - col_begin].coord_00_04;

			float st00 = sub_6EE43B70(&coord_list1, &coord_list2);
			st00 = sqrt(st00);

			if (st00 >= 0.3f)	//Overlap_Thresold
			{
				float st01 = fabs(bb_list_cur.pBounding_Box[j - col_begin].flt28 - bb_list_prev.pBounding_Box[i - row_begin].flt28);
				if (st01 <= 60.f)			//Yaw Angle
				{
					st00 = -st00;
					if (weight_by_cofidence != 0)
					{
						if (bb_list_prev.pBounding_Box[i - row_begin].flt24 > 0 && bb_list_cur.pBounding_Box[j - col_begin].flt24)
						{
							float fltVar_9C = st00;
							st00 = bb_list_prev.pBounding_Box[i - row_begin].flt24 * bb_list_cur.pBounding_Box[j - col_begin].flt24;
							st00 = sqrt(st00);
							st00 = st00 * fltVar_9C;
						}
					}
				}
				else
					st00 = 1.0f;
			}
			else
				st00 = 1.0f;

			pSparse[(j - col_begin) + (i - row_begin) * bb_list_cur.num] = st00;
		}
	}

	sub_6EDAE940(overlap_ratio, pSparse, bb_list_prev.num, bb_list_cur.num);

	for (int i = 0; i < overlap_ratio->num; i++)
	{
		if (overlap_ratio->ratio[i] >= 0)
		{
			if (pSparse[overlap_ratio->ratio[i] + i * overlap_ratio->n08] > 0.5f)
				overlap_ratio->ratio[i] = -1;
		}
	}

	for (int i = 0; i < overlap_ratio->n08; i++)
	{
		if (overlap_ratio->pn0C[i] >= 0)
		{
			if (pSparse[i + overlap_ratio->pn0C[i] * overlap_ratio->n08] > 0.5f)
				overlap_ratio->pn0C[i] = -1;
		}
	}
}

STA109*	sub_6EF20F60(STA109* psta109_Arg_0, STA109* psta109_Arg_4)
{
	STA109*	psta109_Eax = psta109_Arg_0;

	if (psta109_Eax != NULL)
	{
		//loc_6EF20F72
		while (psta109_Eax->psta109_04 != NULL)
			psta109_Eax = psta109_Eax->psta109_04;

		psta109_Eax->psta109_04 = psta109_Arg_4;
		psta109_Arg_4->psta109_00 = psta109_Eax;
		psta109_Arg_4->psta109_04 = NULL;

		return psta109_Eax->psta109_04;
	}
	else
	{
		//0xloc_6EF20F89
		psta109_Arg_4->psta109_00 = NULL;
		psta109_Arg_4->psta109_04 = NULL;
		return psta109_Arg_4;
	}
}

STA109* sub_6EF20FE0(STA109* psta109_Arg_0)
{
	STA109 * psta109_Eax = psta109_Arg_0;

	if (psta109_Eax == NULL || psta109_Eax->psta109_00 == NULL)
	{
		return psta109_Eax;
	}
	STA109 * psta109_Edx = psta109_Eax->psta109_00;

	while (TRUE)
	{
		psta109_Eax = psta109_Edx->psta109_00;

		if (psta109_Eax == NULL)
			break;

		psta109_Edx = psta109_Eax;
	}

	return psta109_Edx;
}

int sub_6EF21A10(STA109* psta109_Arg_0, int** pnArg_4)
{
	int*	pnVar_2C;
	int		index = 0;

	STA109* psta109_Edx = psta109_Arg_0;
	if (psta109_Arg_0 == NULL)
		return NULL;
	else
	{
		while (psta109_Edx->psta109_00 != NULL)
			psta109_Edx = psta109_Edx->psta109_00;

		int nEsi = 0;
		while (psta109_Edx != NULL)
		{
			psta109_Edx = psta109_Edx->psta109_04;
			nEsi++;
		}

		pnVar_2C = (int*)malloc(sizeof(int) * nEsi);
		STA109* psta109_Ebx = psta109_Arg_0;
		while (psta109_Ebx->psta109_00 != NULL)
			psta109_Ebx = psta109_Ebx->psta109_00;
		psta109_Edx = psta109_Ebx;

		while (psta109_Edx != NULL)
		{
			pnVar_2C[index] = psta109_Edx->psta111_08->n00;
			psta109_Edx = psta109_Edx->psta109_04;
			index++;
		}

		*pnArg_4 = pnVar_2C;
	}

	return index;
}

STA114 sub_6EF223B0(STA107* psta107_Arg_0)
{
	STA114 sta114_ret = { 0 };
	STC11 stc11_Var_1D8;

	if (psta107_Arg_0 == NULL)
		return sta114_ret;

	STA109* psta109_Ebp = (STA109*)malloc(sizeof(STA109));
	psta109_Ebp->psta109_00 = NULL;
	psta109_Ebp->psta109_04 = NULL;
	psta109_Ebp->psta111_08 = NULL;

	STA111* psta111_Ebx = (STA111*)malloc(sizeof(STA111));
	sub_6EF1C280(psta111_Ebx);

	psta109_Ebp->psta111_08 = psta111_Ebx;
	psta111_Ebx->n00 = identifier;
	identifier++;

	psta109_Ebp->psta111_08->psta112_04 = (STA112*)psta107_Arg_0;
	psta107_Arg_0->psta109_14 = psta109_Ebp;
	psta107_Arg_0->track_id = psta109_Ebp->psta111_08->n00;
	psta107_Arg_0->track_info = DETECTED_RESULT;

	sub_6EF195E0(&stc11_Var_1D8, psta107_Arg_0->pFaceLandmark, psta107_Arg_0->confidence);
	memcpy(&psta109_Ebp->psta111_08->stc11_08, &stc11_Var_1D8, sizeof(STC11));

	psta107_Arg_0->motion_confidence = psta109_Ebp->psta111_08->stc11_08.stc23_00.flt1A8;
	psta107_Arg_0->track_confidence = psta109_Ebp->psta111_08->stc11_08.by1B5;

	sta114_ret.psta107_00 = psta107_Arg_0;
	sta114_ret.psta109_04 = psta109_Ebp;

	return sta114_ret;
}

STA111* sub_6EF22590(STA111* psta111_Arg_0, BYTE byArg_4)
{
	if (psta111_Arg_0 != NULL)
	{
		//0x6EF225A1
		if (byArg_4 != 0)
			psta111_Arg_0->psta112_04 = sub_6EF1F390(psta111_Arg_0->psta112_04);

		//loc_6EF225A5
		free(psta111_Arg_0);
	}

	return NULL;
}

STA109* sub_6EF227C0(STA109* psta109_Arg_0, BYTE byArg_4)
{
	if (psta109_Arg_0 == NULL)
		return NULL;

	STA109 *psta109_Eax;
	STA109 * psta109_Esi = psta109_Arg_0->psta109_00;
	STA109 * psta109_Edi = psta109_Arg_0->psta109_04;

	//0x6EF227E1
	BYTE byAl = (psta109_Esi == NULL) ? 1 : 0;
	BYTE byCl = (psta109_Edi == NULL) ? 1 : 0;

	//6EF227EB
	if (byAl != 0)
	{
		//loc_6EF22860
		if (byCl == 0)
		{
			//loc_6EF22885
			psta109_Arg_0->psta111_08 = sub_6EF22590(psta109_Arg_0->psta111_08, byArg_4);
			psta109_Eax = psta109_Edi;
			free(psta109_Arg_0->psta109_00);
			psta109_Edi->psta109_00 = NULL;
		}
		else
		{
			//0x6EF22864
			psta109_Arg_0->psta111_08 = sub_6EF22590(psta109_Arg_0->psta111_08, byArg_4);
			psta109_Eax = NULL;
			free(psta109_Arg_0->psta109_00);
		}
	}
	else
	{
		//0x6EF227EF
		if (byCl == 0)
		{
			psta109_Edi->psta109_00 = psta109_Esi;
			psta109_Esi->psta109_04 = psta109_Edi;
			STA111* psta111_Esi = psta109_Arg_0->psta111_08;

			//0x6EF227FF
			if (psta111_Esi != NULL)
			{
				//0x6EF22803
				if (byArg_4 != 0)
					psta111_Esi->psta112_04 = sub_6EF1F390(psta111_Esi->psta112_04);//loc_6EF228B0

				//0x6EF2280B
				free(psta111_Esi);
			}

			//loc_6EF22837
			psta109_Arg_0->psta111_08 = NULL;
			free(psta109_Arg_0);
			psta109_Eax = psta109_Edi;
		}
		else
		{
			//loc_6EF228C3
			STA111* psta111_Edi = psta109_Arg_0->psta111_08;

			if (psta111_Edi != NULL)
			{
				if (byArg_4 != 0)
					psta111_Edi->psta112_04 = sub_6EF1F390(psta111_Edi->psta112_04); 	//6EF228CA

				//loc_6EF228CE
				free(psta111_Edi);
			}

			//loc_6EF228FA
			psta109_Arg_0->psta111_08 = NULL;
			psta109_Eax = psta109_Esi;
			free(psta109_Arg_0);
			psta109_Esi->psta109_04 = NULL;
		}
	}

	return psta109_Eax;
}

STA109* sub_6EF22C30(STA109* psta109_Arg_0, BYTE byArg_4)
{
	STA109 * psta109_Eax = psta109_Arg_0;

	if (psta109_Eax != NULL)
	{
		//0x6EF22C44
		STA109 * psta109_Edx = psta109_Eax->psta109_00;
		if (psta109_Edx != NULL)
		{
			do
			{
				//loc_6EF22C48
				psta109_Eax = psta109_Edx;
				psta109_Edx = psta109_Edx->psta109_00;
			} while (psta109_Edx != NULL);

			if (psta109_Eax == NULL)
				return NULL;
		}

		//loc_6EF22C54
		STA109 * psta109_Ebx;
		do
		{
			psta109_Ebx = psta109_Eax->psta109_04;
			psta109_Eax = sub_6EF227C0(psta109_Eax, byArg_4);
			psta109_Eax = psta109_Ebx;

		} while (psta109_Ebx != NULL);
	}

	//loc_6EF22C6C
	return NULL;
}

void sub_6EF236B0(STA106* psta106_Arg_0, STA107* psta107_Arg_4, STA109* psta109_Arg_8, STA109* psta109_Arg_C)
{
	int		nVar_4;
	STA107* psta107_Esi = psta107_Arg_4;
	STA109*	psta109_Edi = psta109_Arg_C;

	if (psta107_Arg_4 != NULL)
	{
		//0x6EF236CA
		psta107_Esi = sub_6EF1C790(psta107_Arg_4);
		nVar_4 = psta107_Esi->face_info->frame_index;
		STA109 * psta109_Ebx = sub_6EF20FE0(psta109_Arg_8);

		while (psta109_Ebx != NULL)
		{
			//loc_6EF23724
			STA112 * psta112_Eax = sub_6EF1C800(psta109_Ebx->psta111_08->psta112_04);
			psta109_Ebx = psta109_Ebx->psta109_04;
		}
	}

	//loc_6EF23767
	psta106_Arg_0->psta107_00 = psta107_Esi;
	psta106_Arg_0->psta109_04 = psta109_Arg_8;
	psta106_Arg_0->psta109_08 = psta109_Edi;
}

/*
Estimate the feature points - 2012/02/09
*/
STA112*	sub_6EF23850(STA112* psta112_Arg_0)
{
	STA112* psta112_Ebp = psta112_Arg_0;
	STA109* psta109_Ebx = psta112_Ebp->psta109_14;
	STA111* psta111_Esi = psta109_Ebx->psta111_08;

	float conf = psta112_Arg_0->confidence + 0.05f;
	STC23 stc23_Var_1FC = psta111_Esi->stc11_08.stc23_00;
	sub_6EE5CAD0(&stc23_Var_1FC, psta112_Arg_0->pFaceLandmark, conf);

	psta112_Ebp->psta109_14->psta111_08->stc11_08.stc23_00 = stc23_Var_1FC;

	psta112_Arg_0->pFaceLandmark[0].pos.x = stc23_Var_1FC.stc14Tb_00[0].fltTb_00[0];
	psta112_Arg_0->pFaceLandmark[0].pos.y = stc23_Var_1FC.stc14Tb_00[1].fltTb_00[0];
	psta112_Arg_0->pFaceLandmark[1].pos.x = stc23_Var_1FC.stc14Tb_00[2].fltTb_00[0];
	psta112_Arg_0->pFaceLandmark[1].pos.y = stc23_Var_1FC.stc14Tb_00[3].fltTb_00[0];
	psta112_Arg_0->pFaceLandmark[2].pos.x = stc23_Var_1FC.stc14Tb_00[4].fltTb_00[0];
	psta112_Arg_0->pFaceLandmark[2].pos.y = stc23_Var_1FC.stc14Tb_00[5].fltTb_00[0];
	psta112_Arg_0->pFaceLandmark[3].pos.x = stc23_Var_1FC.stc14Tb_00[6].fltTb_00[0];
	psta112_Arg_0->pFaceLandmark[3].pos.y = stc23_Var_1FC.stc14Tb_00[7].fltTb_00[0];

	psta112_Ebp->psta109_14->psta111_08->stc11_08.n1AC = 0;
	sub_6EF17E20(&psta112_Ebp->psta109_14->psta111_08->stc11_08);
	psta112_Arg_0->motion_confidence = psta112_Ebp->psta109_14->psta111_08->stc11_08.stc23_00.flt1A8;
	psta112_Arg_0->track_confidence = psta112_Ebp->psta109_14->psta111_08->stc11_08.by1B5;

	return psta112_Ebp;
}

STA112* sub_6EF23BF0(STA112* psta112_Arg_0)
{
	if (psta112_Arg_0->psta109_14->psta111_08->stc11_08.by1B4 != 0 && psta112_Arg_0->psta109_14->psta111_08->stc11_08.n1B0 >= 2)
	{
		sub_6EE5C3B0(&psta112_Arg_0->psta109_14->psta111_08->stc11_08);
		psta112_Arg_0->psta109_14->psta111_08->stc11_08.n1AC++;
		sub_6EF17E20(&psta112_Arg_0->psta109_14->psta111_08->stc11_08);

		if (psta112_Arg_0->psta109_14->psta111_08->stc11_08.by1B9 == 0)
		{
			//loc_6EF23C98
			if (psta112_Arg_0->pFaceLandmark != NULL)
			{
				KipFaceLandmark* pFaceLandmark = (KipFaceLandmark*)malloc(sizeof(KipFaceLandmark) * 4);
				pFaceLandmark[0].id = KipFaceLandmarkFaceCornerTopLeft;
				pFaceLandmark[0].pos.x = psta112_Arg_0->psta109_14->psta111_08->stc11_08.stc23_00.stc14Tb_00[0].fltTb_00[0];
				pFaceLandmark[0].pos.y = psta112_Arg_0->psta109_14->psta111_08->stc11_08.stc23_00.stc14Tb_00[1].fltTb_00[0];
				pFaceLandmark[1].id = KipFaceLandmarkFaceCornerTopRight;
				pFaceLandmark[1].pos.x = psta112_Arg_0->psta109_14->psta111_08->stc11_08.stc23_00.stc14Tb_00[2].fltTb_00[0];
				pFaceLandmark[1].pos.y = psta112_Arg_0->psta109_14->psta111_08->stc11_08.stc23_00.stc14Tb_00[3].fltTb_00[0];
				pFaceLandmark[2].id = KipFaceLandmarkFaceCornerBottomRight;
				pFaceLandmark[2].pos.x = psta112_Arg_0->psta109_14->psta111_08->stc11_08.stc23_00.stc14Tb_00[4].fltTb_00[0];
				pFaceLandmark[2].pos.y = psta112_Arg_0->psta109_14->psta111_08->stc11_08.stc23_00.stc14Tb_00[5].fltTb_00[0];
				pFaceLandmark[3].id = KipFaceLandmarkFaceCornerBottomLeft;
				pFaceLandmark[3].pos.x = psta112_Arg_0->psta109_14->psta111_08->stc11_08.stc23_00.stc14Tb_00[6].fltTb_00[0];
				pFaceLandmark[3].pos.y = psta112_Arg_0->psta109_14->psta111_08->stc11_08.stc23_00.stc14Tb_00[7].fltTb_00[0];

				float confidence = 0.2f;
				float motion_confidence = psta112_Arg_0->psta109_14->psta111_08->stc11_08.stc23_00.flt1A8;
				int track_confidence = psta112_Arg_0->psta109_14->psta111_08->stc11_08.by1B5;
				int track_id = psta112_Arg_0->psta109_14->psta111_08->n00;

				psta112_Arg_0->psta107_10->psta107_next = sub_6EF1FB50(psta112_Arg_0->psta107_10->psta107_next, pFaceLandmark, confidence, motion_confidence, track_id, track_confidence, psta112_Arg_0->yaw_angle, psta112_Arg_0->detected_id);

				STA112 * psta112_Eax = sub_6EF1C860(psta112_Arg_0->psta107_10->psta107_next->psta107_04);

				psta112_Eax->psta109_14 = psta112_Arg_0->psta109_14;
				psta112_Eax->psta112_00 = psta112_Arg_0;
				psta112_Arg_0->psta112_04 = psta112_Eax;
				psta112_Arg_0->psta109_14->psta111_08->psta112_04 = psta112_Eax;
			}
		}
	}

	return psta112_Arg_0;
}

STA114 sub_6EF23DE0(STA107* psta107_Arg_0, STA109* psta109_Arg_4)
{
	STA114 sta114_ret = { 0 };

	int* pnEbx = NULL;
	int count = sub_6EF21A10(psta109_Arg_4, &pnEbx);
	STA107* psta107_Eax = sub_6EF1C790(psta107_Arg_0);
	STA107* psta107_Var_14 = psta107_Eax->psta107_prev;

	if (psta107_Var_14 != NULL)
	{
		STA112* psta112_Ebx = (STA112*)sub_6EF1C830(psta107_Var_14->psta107_04);
		while (psta112_Ebx != NULL)
		{
			for (int i = 0; i < count; i++)
			{
				if (psta112_Ebx->track_id == pnEbx[i])
				{
					psta112_Ebx = sub_6EF23BF0(psta112_Ebx);
					break;
				}
			}
			psta112_Ebx = psta112_Ebx->psta112_0C;
		}
	}

	sta114_ret.psta107_00 = psta107_Var_14;
	sta114_ret.psta109_04 = psta109_Arg_4;

	return sta114_ret;
}

STA114 sub_6EF24220(STA107* psta107_Arg_0, STA109* psta109_Arg_4)
{
	STA114 sta114_ret = { 0 };

	int* pnEbx = NULL;
	int count = sub_6EF21A10(psta109_Arg_4, &pnEbx);
	STA107* psta107_Var_28 = sub_6EF1C790(psta107_Arg_0);

	if (psta107_Var_28 == NULL || psta107_Var_28->psta107_prev == NULL)
		return sta114_ret;

	BoundingBox_List bb_list_prev = sub_6EF1EE10(psta107_Var_28->psta107_prev->psta107_04, count, pnEbx);
	BoundingBox_List bb_list_cur = sub_6EF1E5C0(psta107_Var_28->psta107_04);

	OverlapRatio overlap_ratio;
	sub_6EF20240(&overlap_ratio, bb_list_prev, bb_list_cur);

	for (int i = 0; i < overlap_ratio.num; i++)
	{
		if (overlap_ratio.ratio[i] < 0)
		{
			bb_list_prev.pBounding_Box[i].psta112_2C = sub_6EF23BF0(bb_list_prev.pBounding_Box[i].psta112_2C);
		}
		else
		{
			STA112* psta112_Ebx = bb_list_cur.pBounding_Box[overlap_ratio.ratio[i]].psta112_2C;
			STA112* psta112_Esi = bb_list_prev.pBounding_Box[i].psta112_2C;
			int track_id = psta112_Esi->track_id;
			psta112_Ebx->track_info = DETECTED_RESULT;
			psta112_Ebx->track_id = track_id;
			psta112_Ebx->yaw_angle = psta112_Esi->yaw_angle;
			psta112_Ebx->detected_id = psta112_Esi->detected_id;
			psta112_Ebx->psta112_00 = psta112_Esi;
			psta112_Esi->psta112_04 = psta112_Ebx;
			psta112_Ebx->psta109_14 = psta112_Esi->psta109_14;
			psta112_Esi->psta109_14->psta111_08->psta112_04 = psta112_Ebx;
			bb_list_cur.pBounding_Box[overlap_ratio.ratio[i]].psta112_2C = sub_6EF23850(psta112_Ebx);
			bb_list_prev.pBounding_Box[i].psta112_2C = psta112_Esi;
		}
	}

	for (int i = 0; i < overlap_ratio.n08; i++)
	{
		if (overlap_ratio.pn0C[i] < 0)
		{
			STA112* psta112_Eax = bb_list_cur.pBounding_Box[i].psta112_2C;
			STA114 sta114_Esi_Edx = sub_6EF223B0((STA107*)psta112_Eax);
			psta109_Arg_4 = sub_6EF20F60(psta109_Arg_4, sta114_Esi_Edx.psta109_04);
			bb_list_cur.pBounding_Box[i].psta112_2C = (STA112*)sta114_Esi_Edx.psta107_00;
		}
	}

	free(overlap_ratio.ratio);
	free(overlap_ratio.pn0C);
	free(bb_list_prev.pBounding_Box);
	free(bb_list_cur.pBounding_Box);

	sta114_ret.psta107_00 = psta107_Var_28;
	sta114_ret.psta109_04 = psta109_Arg_4;

	return sta114_ret;
}

void sub_6EF24630(STA106* psta106_Arg_0, STA107* psta107_Arg_4, STA109* psta109_Arg_8, STA109* psta109_Arg_C, FaceInfo* pFaceInfo)
{
	STA107*	psta107_Ebp = sub_6EF1C790(psta107_Arg_4);
	int* pnEbx = NULL;
	int count = sub_6EF21A10(psta109_Arg_8, &pnEbx);

	STA107* psta107_Eax = NULL;
	if (psta107_Ebp != NULL)
		psta107_Eax = psta107_Ebp->psta107_04;

	int nEsi = sub_6EF1ED40(psta107_Eax, pnEbx, count);
	int nEbx = sub_6EEDCF00(pFaceInfo, 0.2f);
	psta107_Eax = sub_6EF1FE00(psta107_Ebp, pFaceInfo, 0.2f, 1);

	STA107* psta107_Esi;
	STA114 sta114_Eax_Edx;
	STA106 sta106_Var_C;

	sta114_Eax_Edx.psta107_00 = psta107_Eax;

	if (nEsi == 0)
	{
		psta107_Esi = sub_6EF1C790(psta107_Eax);
		if (psta107_Esi != NULL)
		{
			psta107_Eax = sub_6EF1C830(psta107_Esi->psta107_04);

			//loc_6EF24967
			while (psta107_Eax != NULL)
			{
				//loc_6EF24930
				sta114_Eax_Edx = sub_6EF223B0(psta107_Eax);
				psta109_Arg_8 = sub_6EF20F60(psta109_Arg_8, sta114_Eax_Edx.psta109_04);
				psta107_Eax = sta114_Eax_Edx.psta107_00->psta107_next;
			}
		}
	}
	else
	{
		if (nEbx == 0)
		{
			sta114_Eax_Edx = sub_6EF23DE0(psta107_Eax, psta109_Arg_8);
		}
		else
		{
			sta114_Eax_Edx = sub_6EF24220(psta107_Eax, psta109_Arg_8);
		}

		psta109_Arg_8 = sta114_Eax_Edx.psta109_04;
		psta107_Esi = sta114_Eax_Edx.psta107_00;
	}

	sub_6EF236B0(&sta106_Var_C, psta107_Esi, psta109_Arg_8, psta109_Arg_C);
	STA109* psta109_Ebx = sta106_Var_C.psta109_04;

	psta106_Arg_0->psta107_00 = sta106_Var_C.psta107_00;
	psta106_Arg_0->psta109_04 = psta109_Ebx;
	psta106_Arg_0->psta109_08 = sta106_Var_C.psta109_08;
}

void sub_6EF249D0(STA106* psta106_Arg_0, STA107* psta107_Arg_4, STA109* psta109_Arg_8, STA109* psta109_Arg_C, FaceInfo* pFaceInfo)
{
	STA106		sta106_Var_0C;

	sub_6EF24630(&sta106_Var_0C, psta107_Arg_4, psta109_Arg_8, psta109_Arg_C, pFaceInfo);

	psta106_Arg_0->psta107_00 = sta106_Var_0C.psta107_00;
	psta106_Arg_0->psta109_04 = sta106_Var_0C.psta109_04;
	psta106_Arg_0->psta109_08 = sta106_Var_0C.psta109_08;
}

/*
Normalize the bounding box - 2012/02/08
*/
void sub_6EE420A0(KipCoord_List* pCoord_List_Arg_0)
{
	float* pfltVar_50 = (float*)malloc(sizeof(float) * pCoord_List_Arg_0->num);
	KipCoord2f* pcoord_Var_4C_48 = (KipCoord2f*)malloc(sizeof(KipCoord2f) * pCoord_List_Arg_0->num);

	if (pCoord_List_Arg_0->num > 0)
	{
		double st00 = 0;
		double st01 = 0;
		for (int i = 0; i < pCoord_List_Arg_0->num; i++)
		{
			st00 = st00 + pCoord_List_Arg_0->pCoord_Pos[i].x;
			st01 = st01 + pCoord_List_Arg_0->pCoord_Pos[i].y;
		}

		float fltVar_24 = (float)(-(st00 / pCoord_List_Arg_0->num));
		float fltVar_28 = (float)(-(st01 / pCoord_List_Arg_0->num));

		for (int nEsi = 0; nEsi < pCoord_List_Arg_0->num; nEsi++)
		{
			//loc_6EE423A0

			if (9.9999997e-6f <= fabs(fltVar_28 + pCoord_List_Arg_0->pCoord_Pos[nEsi].x) || 9.9999997e-6f <= fabs(fltVar_24 + pCoord_List_Arg_0->pCoord_Pos[nEsi].x))
			{
				//loc_6EE42380
				pfltVar_50[nEsi] = sub_6F01EB90(fltVar_28 + pCoord_List_Arg_0->pCoord_Pos[nEsi].y, fltVar_24 + pCoord_List_Arg_0->pCoord_Pos[nEsi].x);
			}
			else
			{
				pfltVar_50[nEsi] = 0.0f;
			}
		}

		//loc_6EE423E0
		Index_List id_list = sub_6EDFC5A0(pfltVar_50, pCoord_List_Arg_0->num);

		for (int i = 0; i < id_list.num; i++)
		{
			pcoord_Var_4C_48[i] = pCoord_List_Arg_0->pCoord_Pos[id_list.pIndex[i] - 1];
		}

		for (int i = 0; i < id_list.num; i++)
			pCoord_List_Arg_0->pCoord_Pos[i] = pcoord_Var_4C_48[i];
	}

	free(pcoord_Var_4C_48);
	free(pfltVar_50);
}

/*
Calcuate euclid distance between bounding boxes - 2012/02/07
*/
KipCoord_List sub_6EE42480(KipCoord_List* pCoord_Arg_0, KipCoord_List* pCoord_Arg_4)
{
	KipCoord2f			coord_TbVar_334[0x64];
	float				avgY1;
	float				avgX1;
	float				fltVar_35C;
	float				Y2;
	float				Y1;
	float				avgY2;
	float				avgX2;
	float				fltVar_370;
	float				fltVar_374;
	float				fltVar_378;
	float				fltVar_37C;
	float				fltVar_380;
	float				fltVar_384;
	float				fltVar_388;
	float				fltVar_38C;
	float				fltVar_390;
	float				fltVar_394;
	float				fltVar_398;
	float				fltVar_39C;
	float				fltVar_3A0;
	int					nVar_404;

	//loc_6EE424D2
	BYTE* pbyVar_3E4 = (BYTE*)malloc(pCoord_Arg_0->num);
	for (int i = 0; i < pCoord_Arg_0->num; i++)
		pbyVar_3E4[i] = 0;

	//loc_6EE42554
	BYTE* pbyVar_3E8 = (BYTE*)malloc(pCoord_Arg_4->num);
	for (int i = 0; i < pCoord_Arg_4->num; i++)
		pbyVar_3E8[i] = 0;

	//loc_6EE425AE
	int index = 0;
	for (int i = 0; i < pCoord_Arg_0->num; i++)
	{
		for (int j = 0; j < pCoord_Arg_4->num; j++)
		{
			if (pbyVar_3E4[i] == 0 && pbyVar_3E8[j] == 0)
			{
				float st00 = pCoord_Arg_0->pCoord_Pos[i].x - pCoord_Arg_4->pCoord_Pos[j].x;
				float st01 = pCoord_Arg_4->pCoord_Pos[j].y - pCoord_Arg_0->pCoord_Pos[i].y;
				float euclid_dist = sqrt(st00 * st00 + st01 * st01);

				if (euclid_dist >= -0.12828431f && 0.12828431f >= euclid_dist)
				{
					pbyVar_3E4[i] = 1;
					pbyVar_3E8[j] = 1;
					coord_TbVar_334[index] = pCoord_Arg_0->pCoord_Pos[i];
					index++;
				}
			}
		}
	}

	//loc_6EE4271A
	double st00 = 0;
	double st01 = 0;
	double st02 = 0;

	for (int i = 0; i < pCoord_Arg_4->num; i++)
	{
		st01 = st01 + pCoord_Arg_4->pCoord_Pos[i].x;
		st02 = st02 + pCoord_Arg_4->pCoord_Pos[i].y;
	}

	avgX2 = (float)(st01 / pCoord_Arg_4->num);
	avgY2 = (float)(st02 / pCoord_Arg_4->num);

	for (int i = 0; i < pCoord_Arg_0->num; i++)
	{
		int nEsi = 0;
		if (pbyVar_3E4[i] == 0)
		{
			Y1 = pCoord_Arg_0->pCoord_Pos[i].y;
			float X1 = pCoord_Arg_0->pCoord_Pos[i].x;

			fltVar_3A0 = 0;
			fltVar_39C = 0;
			fltVar_398 = 0;
			fltVar_394 = 0;
			for (int j = 0; j < pCoord_Arg_4->num; j++)
			{
				if (nEsi == 0)
				{
					st00 = avgY2 * X1 + Y1 * pCoord_Arg_4->pCoord_Pos[j].x + avgX2 * pCoord_Arg_4->pCoord_Pos[j].y;
					st01 = avgY2 * pCoord_Arg_4->pCoord_Pos[j].x + pCoord_Arg_4->pCoord_Pos[j].y * X1 + avgX2 * Y1;

					BYTE byBl = (0.001f <= (st00 - st01)) ? 1 : 0;

					int nVar_404 = 2 * byBl - 1;

					st00 = avgY2 * X1 + Y1 * pCoord_Arg_4->pCoord_Pos[(j + 1) % pCoord_Arg_4->num].x + avgX2 * pCoord_Arg_4->pCoord_Pos[(j + 1) % pCoord_Arg_4->num].y;
					st01 = avgY2 * pCoord_Arg_4->pCoord_Pos[(j + 1) % pCoord_Arg_4->num].x + pCoord_Arg_4->pCoord_Pos[(j + 1) % pCoord_Arg_4->num].y * X1 + avgX2 * Y1;

					if (0.001f <= (st00 - st01) && nVar_404 == -1)
					{
						fltVar_39C = pCoord_Arg_4->pCoord_Pos[j].y;
						fltVar_3A0 = pCoord_Arg_4->pCoord_Pos[j].x;
						fltVar_394 = pCoord_Arg_4->pCoord_Pos[(j + 1) % pCoord_Arg_4->num].y;
						fltVar_398 = pCoord_Arg_4->pCoord_Pos[(j + 1) % pCoord_Arg_4->num].x;
						nEsi = 1;
					}
				}
			}

			st00 = fltVar_3A0 * fltVar_394 + fltVar_39C * X1 + Y1 * fltVar_398;
			st01 = X1 * fltVar_394 + fltVar_3A0 * Y1 + fltVar_39C * fltVar_398;

			if (0.001f > (st00 - st01))
			{
				if (nEsi != 0)
				{
					pbyVar_3E4[i] = 1;
					coord_TbVar_334[index] = pCoord_Arg_0->pCoord_Pos[i];
					index++;
				}
			}
		}
	}

	//loc_6EE42E11
	st00 = 0;
	st01 = 0;
	st02 = 0;
	for (int i = 0; i < pCoord_Arg_0->num; i++)
	{
		st01 = st01 + pCoord_Arg_0->pCoord_Pos[i].y;
		st02 = st02 + pCoord_Arg_0->pCoord_Pos[i].x;
	}

	avgX1 = (float)(st02 / pCoord_Arg_0->num);
	avgY1 = (float)(st01 / pCoord_Arg_0->num);

	for (int i = 0; i < pCoord_Arg_4->num; i++)
	{
		int nEsi = 0;
		if (pbyVar_3E8[i] == 0)
		{
			Y2 = pCoord_Arg_4->pCoord_Pos[i].y;
			float X2 = pCoord_Arg_4->pCoord_Pos[i].x;

			fltVar_390 = 0;
			fltVar_38C = 0;
			fltVar_388 = 0;
			fltVar_384 = 0;

			for (int j = 0; j < pCoord_Arg_0->num; j++)
			{
				if (nEsi == 0)
				{
					st00 = avgY1 * X2 + Y2 * pCoord_Arg_0->pCoord_Pos[j].x + avgX1 * pCoord_Arg_0->pCoord_Pos[j].y;
					st01 = avgY1 * pCoord_Arg_0->pCoord_Pos[j].x + pCoord_Arg_0->pCoord_Pos[j].y * X2 + avgX1 * Y2;

					BYTE byBl = (0.001f <= (st00 - st01)) ? 1 : 0;

					nVar_404 = 2 * byBl - 1;

					st00 = avgY1 * X2 + Y2 * pCoord_Arg_0->pCoord_Pos[(j + 1) % pCoord_Arg_0->num].x + avgX1 * pCoord_Arg_0->pCoord_Pos[(j + 1) % pCoord_Arg_0->num].y;
					st01 = avgY1 * pCoord_Arg_0->pCoord_Pos[(j + 1) % pCoord_Arg_0->num].x + pCoord_Arg_0->pCoord_Pos[(j + 1) % pCoord_Arg_0->num].y * X2 + avgX1 * Y2;

					if (0.001f <= (st00 - st01) && nVar_404 == -1)
					{
						fltVar_38C = pCoord_Arg_0->pCoord_Pos[j].y;
						fltVar_390 = pCoord_Arg_0->pCoord_Pos[j].x;
						fltVar_384 = pCoord_Arg_0->pCoord_Pos[(j + 1) % pCoord_Arg_0->num].y;
						fltVar_388 = pCoord_Arg_0->pCoord_Pos[(j + 1) % pCoord_Arg_0->num].x;
						nEsi = 1;
					}
				}
			}

			st00 = fltVar_390 * fltVar_384 + fltVar_38C * X2 + fltVar_388 * Y2;
			st01 = X2 * fltVar_384 + fltVar_390 * Y2 + fltVar_38C * fltVar_388;

			if (0.001f > (st00 - st01) && nEsi != 0)
			{
				pbyVar_3E8[i] = 1;
				coord_TbVar_334[index] = pCoord_Arg_4->pCoord_Pos[i];
				index++;
			}
		}
	}

	//loc_6EE43501
	int nEdx;

	for (int i = 0; i < pCoord_Arg_0->num; i++)
	{
		for (int j = 0; j < pCoord_Arg_4->num; j++)
		{
			fltVar_35C = pCoord_Arg_0->pCoord_Pos[i].y;

			fltVar_370 = pCoord_Arg_4->pCoord_Pos[(j + 1) % pCoord_Arg_4->num].x - pCoord_Arg_4->pCoord_Pos[j].x;
			fltVar_374 = pCoord_Arg_4->pCoord_Pos[(j + 1) % pCoord_Arg_4->num].y - pCoord_Arg_4->pCoord_Pos[j].y;

			fltVar_380 = fltVar_370 * (pCoord_Arg_0->pCoord_Pos[(i + 1) % pCoord_Arg_0->num].y - pCoord_Arg_0->pCoord_Pos[i].y);
			fltVar_37C = fltVar_374 * (pCoord_Arg_0->pCoord_Pos[(i + 1) % pCoord_Arg_0->num].x - pCoord_Arg_0->pCoord_Pos[i].x);

			if ((fltVar_380 - fltVar_37C) < -1.0e-6f || 1.0e-6f < (fltVar_380 - fltVar_37C))
			{
				//loc_6EE436B3
				st00 = (pCoord_Arg_0->pCoord_Pos[i].x - pCoord_Arg_4->pCoord_Pos[j].x) * (pCoord_Arg_0->pCoord_Pos[(i + 1) % pCoord_Arg_0->num].y - pCoord_Arg_0->pCoord_Pos[i].y);
				st01 = (pCoord_Arg_4->pCoord_Pos[j].y - fltVar_35C) * (pCoord_Arg_0->pCoord_Pos[(i + 1) % pCoord_Arg_0->num].x - pCoord_Arg_0->pCoord_Pos[i].x);
				fltVar_378 = (float)((st01 + st00) / (fltVar_380 - fltVar_37C));

				st02 = (fltVar_35C - pCoord_Arg_4->pCoord_Pos[j].y) * fltVar_370 + (pCoord_Arg_4->pCoord_Pos[j].x - pCoord_Arg_0->pCoord_Pos[i].x) * fltVar_374;
				st02 = st02 / (fltVar_37C - fltVar_380);

				if (fltVar_378 >= -1.0e-6f && 1.000001f >= fltVar_378 && st02 >= -1.0e-6f && 1.000001f >= st02)
				{
					st00 = (pCoord_Arg_0->pCoord_Pos[(i + 1) % pCoord_Arg_0->num].y - pCoord_Arg_0->pCoord_Pos[i].y) * st02 + fltVar_35C;
					st01 = pCoord_Arg_0->pCoord_Pos[i].x + (pCoord_Arg_0->pCoord_Pos[(i + 1) % pCoord_Arg_0->num].x - pCoord_Arg_0->pCoord_Pos[i].x) * st02;
					nEdx = 1;
				}
				else
				{
					//loc_6EE4375C
					st00 = -1.0;
					st01 = -1.0;
					nEdx = 0;
					//loc_6EE435D4
				}
			}
			else
			{
				//loc_6EE43750
				st00 = -1.0;
				st01 = -1.0;
				nEdx = 0;
				//loc_6EE435D4
			}

			//loc_6EE435D4
			coord_TbVar_334[index].y = (float)st00;
			coord_TbVar_334[index].x = (float)st01;
			index = index + 1 - ((nEdx < 1) ? 1 : 0);
		}
	}

	KipCoord_List coord_list;

	coord_list.num = index;
	coord_list.pCoord_Pos = (KipCoord2f*)malloc(sizeof(KipCoord2f) * coord_list.num);

	for (int i = 0; i < index; i++)
		coord_list.pCoord_Pos[i] = coord_TbVar_334[i];

	sub_6EE420A0(&coord_list);

	//loc_6EE43999
	free(pbyVar_3E4);
	free(pbyVar_3E8);

	return coord_list;
}

KipCoord_List sub_6EE43A50(KipCoord_List* pCoord_Arg_0, KipCoord_List* pCoord_Arg_4)
{
	return sub_6EE42480(pCoord_Arg_0, pCoord_Arg_4);
}

float sub_6EE43B70(KipCoord_List* pCoord_Arg_0, KipCoord_List* pCoord_Arg_4)
{
	KipCoord_List coord_list = sub_6EE43A50(pCoord_Arg_0, pCoord_Arg_4);

	if (coord_list.num > 0)
	{
		double st00 = 0;
		for (int i = 0; i < coord_list.num; i++)
		{
			st00 = st00 + coord_list.pCoord_Pos[(i + 1) % coord_list.num].y * coord_list.pCoord_Pos[i].x;
			st00 = st00 - coord_list.pCoord_Pos[i].y * coord_list.pCoord_Pos[(i + 1) % coord_list.num].x;
		}

		st00 = fabs(st00 * 0.5);

		if (st00 >= -1.0e-6f)
		{
			if (st00 <= 1.0e-6f)
			{
				free(coord_list.pCoord_Pos);
				return 0;
			}
		}

		double st01 = 0;
		if (pCoord_Arg_0->num > 0)
		{
			for (int i = 0; i < pCoord_Arg_0->num; i++)
			{
				st01 = st01 + pCoord_Arg_0->pCoord_Pos[(i + 1) % pCoord_Arg_0->num].y * pCoord_Arg_0->pCoord_Pos[i].x;
				st01 = st01 - pCoord_Arg_0->pCoord_Pos[i].y * pCoord_Arg_0->pCoord_Pos[(i + 1) % pCoord_Arg_0->num].x;
			}

			st01 = fabs(st01 * 0.5);
		}

		double st02 = 0;
		if (pCoord_Arg_4->num > 0)
		{
			for (int i = 0; i < pCoord_Arg_4->num; i++)
			{
				st02 = st02 + pCoord_Arg_4->pCoord_Pos[(i + 1) % pCoord_Arg_4->num].y * pCoord_Arg_4->pCoord_Pos[i].x;
				st02 = st02 - pCoord_Arg_4->pCoord_Pos[i].y * pCoord_Arg_4->pCoord_Pos[(i + 1) % pCoord_Arg_4->num].x;
			}

			st02 = fabs(st02 * 0.5);
		}

		float fltVar_18 = (float)(st00 / (st01 + st02 - st00));
		if (fltVar_18 < 0)
			fltVar_18 = 0;

		free(coord_list.pCoord_Pos);
		return fltVar_18;
	}

	return 0;
}

void sub_6EF5B290(STA106* psta106_Arg_0)
{
	psta106_Arg_0->psta109_04 = sub_6EF22C30(psta106_Arg_0->psta109_04, 1);
	psta106_Arg_0->psta107_00 = sub_6EF1FAE0(psta106_Arg_0->psta107_00);
}

void sub_6EF5B380(STA106* psta106_Arg_0, FaceInfo* pFaceInfo)
{
	STA106		sta106_Var_1C;

	sub_6EF249D0(&sta106_Var_1C, psta106_Arg_0->psta107_00, psta106_Arg_0->psta109_08, psta106_Arg_0->psta109_04, pFaceInfo);

	psta106_Arg_0->psta107_00 = sta106_Var_1C.psta107_00;
	psta106_Arg_0->psta109_08 = sta106_Var_1C.psta109_04;
	psta106_Arg_0->psta109_04 = sta106_Var_1C.psta109_08;
}

float sub_6F01E730(float fltArg_0, float fltArg_4)
{
	double st00;

	if (fabs(fltArg_0) <= fabs(fltArg_4))
	{
		//loc_6F01E7B0
		st00 = fabs((double)fltArg_0 / fltArg_4);
	}
	else
	{
		st00 = fabs((double)fltArg_4 / fltArg_0);
	}

	//loc_6F01E753
	if (3.4526698e-4f <= st00)
	{
		if (st00 != 1.0f)
		{
			//loc_6F01E7D0
			st00 = (float)atan(st00);
		}
		else
		{
			st00 = 7.8539819e-1f;
		}
	}

	//loc_6F01E782
	if (fabs(fltArg_0) > fabs(fltArg_4))
	{
		st00 = 1.5707964f - st00;
	}

	//loc_6F01E791
	if (fltArg_4 <= 0)
	{
		//loc_6F01E7B8
		return sub_6F020D50((float)(3.1415927f - st00), fltArg_0);
	}
	else
	{
		return sub_6F020D50((float)st00, fltArg_0);
	}
}

float sub_6F01EB90(float fltArg_0, float fltArg_4)
{
	if (fltArg_4 != 0)
	{
		//loc_6F01EBC6
		//loc_6F01EBD0
		if (fltArg_0 != 0)
		{
			//loc_6F01EBE6
			//loc_6F01EBF0
			return sub_6F01E730(fltArg_0, fltArg_4);

		}
		if (fltArg_4 > 0)
		{
			return fltArg_4;
		}

		//loc_6F01EC00
		return sub_6F020D50(1.0f, fltArg_0) * 3.1415927f;
	}
	else
	{
		if (fltArg_0 == 0)
		{
			//loc_6F01EC1A
			printf("sub_6F01EB90", "a-ngelfu.adb:399");
		}

		//loc_6F01EBB6
		return sub_6F020D50(1.5707964f, fltArg_0);
	}
}

float sub_6F020D50(float fltArg_0, float fltArg_4)
{
	if (fltArg_4 >= 0)
	{
		if (fltArg_4 > 0)
		{
			//loc_6F020D6F

			return fabs(fltArg_0);
		}
		//loc_6F020D71
		if (fltArg_4 != 0)
		{
			//loc_6F020D84
			return -(fabs(fltArg_0));
		}
		else
		{
			//loc_6F020D6F
			return fabs(fltArg_0);
		}
	}
	//loc_6F020D80
	return -(fabs(fltArg_0));
}


CTrackingFace::CTrackingFace()
{
	m_nNoFrameCount = 0;
}

CTrackingFace::~CTrackingFace()
{
}

float CTrackingFace::Calcuate_Overlapping(KipFace* cur_face)
{
	if (m_nNoFrameCount > MAX_TRACKING_FRAME_COUNT)
		return 0;

	KipCoord_List coord_prev, coord_cur;

	coord_prev.num = 4;
	coord_prev.pCoord_Pos = new KipCoord2f[4];
	memcpy(coord_prev.pCoord_Pos, &m_stKipFace, sizeof(KipFace));
	sub_6EE420A0(&coord_prev);

	coord_cur.num = 4;
	coord_cur.pCoord_Pos = new KipCoord2f[4];
	memcpy(coord_cur.pCoord_Pos, cur_face, sizeof(KipFace));
	sub_6EE420A0(&coord_cur);

	float ret = sub_6EE43B70(&coord_prev, &coord_cur);
	delete[]coord_prev.pCoord_Pos;
	delete[]coord_cur.pCoord_Pos;

	return ret;
}

void CTrackingFace::Init(KipFace* cur_face, float confidence)
{
	memcpy(&m_stKipFace, cur_face, sizeof(KipFace));
	m_fConfidence = confidence;
	m_nNoFrameCount = 0;
	float mask[9] = { 1.f, 0, 0, 1.f, -1.f, 1.f, 1.f, -2.f, 4.f };

	for (int i = 0; i < 4; i++)
	{
		//Initialize Element X
		m_stEstimateData.data[2 * i][0] = cur_face->rect[i].x;
		m_stEstimateData.data[2 * i][1] = 0;
		m_stEstimateData.data[2 * i][2] = 0;
		m_stEstimateData.data[2 * i][3] = cur_face->rect[i].x * confidence;
		m_stEstimateData.data[2 * i][4] = cur_face->rect[i].x * confidence;
		m_stEstimateData.data[2 * i][5] = cur_face->rect[i].x * confidence;

		for (int j = 0; j < 9; j++)
			m_stEstimateData.data[2 * i][j + 6] = mask[j] * confidence;

		//Initialize Element Y
		m_stEstimateData.data[2 * i + 1][0] = cur_face->rect[i].y;
		m_stEstimateData.data[2 * i + 1][1] = 0;
		m_stEstimateData.data[2 * i + 1][2] = 0;
		m_stEstimateData.data[2 * i + 1][3] = cur_face->rect[i].y * confidence;
		m_stEstimateData.data[2 * i + 1][4] = cur_face->rect[i].y * confidence;
		m_stEstimateData.data[2 * i + 1][5] = cur_face->rect[i].y * confidence;

		for (int j = 0; j < 9; j++)
			m_stEstimateData.data[2 * i + 1][j + 6] = mask[j] * confidence;
	}
}

void CTrackingFace::UpdateWithData(KipFace* cur_face, float confidence)
{
	float test_data[16];
	m_nNoFrameCount = 0;
	for (int i = 0; i < 4; i++)
	{
		test_data[0] = confidence; test_data[1] = 0; test_data[2] = 0;
		test_data[3] = m_stEstimateData.data[2 * i][6];
		test_data[4] = m_stEstimateData.data[2 * i][7] - m_stEstimateData.data[2 * i][6];
		test_data[5] = m_stEstimateData.data[2 * i][6] - 2 * m_stEstimateData.data[2 * i][7] + m_stEstimateData.data[2 * i][8];
		test_data[6] = m_stEstimateData.data[2 * i][9];
		test_data[7] = m_stEstimateData.data[2 * i][10] - m_stEstimateData.data[2 * i][9];
		test_data[8] = m_stEstimateData.data[2 * i][9] - 2 * m_stEstimateData.data[2 * i][10] + m_stEstimateData.data[2 * i][11];
		test_data[9] = m_stEstimateData.data[2 * i][12];
		test_data[10] = m_stEstimateData.data[2 * i][13] - m_stEstimateData.data[2 * i][12];
		test_data[11] = m_stEstimateData.data[2 * i][12] - 2 * m_stEstimateData.data[2 * i][13] + m_stEstimateData.data[2 * i][14];
		test_data[12] = confidence * cur_face->rect[i].x;
		test_data[13] = m_stEstimateData.data[2 * i][3];
		test_data[14] = m_stEstimateData.data[2 * i][4];
		test_data[15] = m_stEstimateData.data[2 * i][5];

		sub_6EDAB2C0(test_data, &test_data[12], &m_stEstimateData.data[2 * i][6],
			&m_stEstimateData.data[2 * i][3], &m_stEstimateData.data[2 * i][0], 0.75f);

		test_data[0] = confidence; test_data[1] = 0; test_data[2] = 0;
		test_data[3] = m_stEstimateData.data[2 * i + 1][6];
		test_data[4] = m_stEstimateData.data[2 * i + 1][7] - m_stEstimateData.data[2 * i + 1][6];
		test_data[5] = m_stEstimateData.data[2 * i + 1][6] - 2 * m_stEstimateData.data[2 * i + 1][7] + m_stEstimateData.data[2 * i + 1][8];
		test_data[6] = m_stEstimateData.data[2 * i + 1][9];
		test_data[7] = m_stEstimateData.data[2 * i + 1][10] - m_stEstimateData.data[2 * i + 1][9];
		test_data[8] = m_stEstimateData.data[2 * i + 1][9] - 2 * m_stEstimateData.data[2 * i + 1][10] + m_stEstimateData.data[2 * i + 1][11];
		test_data[9] = m_stEstimateData.data[2 * i + 1][12];
		test_data[10] = m_stEstimateData.data[2 * i + 1][13] - m_stEstimateData.data[2 * i + 1][12];
		test_data[11] = m_stEstimateData.data[2 * i + 1][12] - 2 * m_stEstimateData.data[2 * i + 1][13] + m_stEstimateData.data[2 * i + 1][14];
		test_data[12] = confidence * cur_face->rect[i].y;
		test_data[13] = m_stEstimateData.data[2 * i + 1][3];
		test_data[14] = m_stEstimateData.data[2 * i + 1][4];
		test_data[15] = m_stEstimateData.data[2 * i + 1][5];

		sub_6EDAB2C0(test_data, &test_data[12], &m_stEstimateData.data[2 * i + 1][6],
			&m_stEstimateData.data[2 * i + 1][3], &m_stEstimateData.data[2 * i + 1][0], 0.75f);
	}
}

void CTrackingFace::UpdateWithoutData()
{
	float ramda = 0.75f;
	float weight = 0.68f;
	m_nNoFrameCount++;
	for (int i = 0; i < 4; i++)
	{
		m_stEstimateData.data[2 * i][0] = m_stEstimateData.data[2 * i][0] + weight * m_stEstimateData.data[2 * i][1] + weight * weight * m_stEstimateData.data[2 * i][2];
		m_stEstimateData.data[2 * i][3] = m_stEstimateData.data[2 * i][3] * ramda;
		m_stEstimateData.data[2 * i][4] = m_stEstimateData.data[2 * i][4] * ramda;
		m_stEstimateData.data[2 * i][5] = m_stEstimateData.data[2 * i][5] * ramda;
		m_stEstimateData.data[2 * i][6] = m_stEstimateData.data[2 * i][6] * ramda;
		m_stEstimateData.data[2 * i][7] = (m_stEstimateData.data[2 * i][7] - m_stEstimateData.data[2 * i][6]) * ramda;
		m_stEstimateData.data[2 * i][8] = (m_stEstimateData.data[2 * i][8] - 2 * m_stEstimateData.data[2 * i][7] + m_stEstimateData.data[2 * i][6]) * ramda;
		m_stEstimateData.data[2 * i][9] = m_stEstimateData.data[2 * i][9] * ramda;
		m_stEstimateData.data[2 * i][10] = (m_stEstimateData.data[2 * i][10] - m_stEstimateData.data[2 * i][9]) * ramda;
		m_stEstimateData.data[2 * i][11] = (m_stEstimateData.data[2 * i][11] - 2 * m_stEstimateData.data[2 * i][10] + m_stEstimateData.data[2 * i][9]) * ramda;
		m_stEstimateData.data[2 * i][12] = m_stEstimateData.data[2 * i][12] * ramda;
		m_stEstimateData.data[2 * i][13] = (m_stEstimateData.data[2 * i][13] - m_stEstimateData.data[2 * i][12]) * ramda;
		m_stEstimateData.data[2 * i][14] = (m_stEstimateData.data[2 * i][14] - 2 * m_stEstimateData.data[2 * i][13] + m_stEstimateData.data[2 * i][12]) * ramda;

		m_stEstimateData.data[2 * i + 1][0] = m_stEstimateData.data[2 * i + 1][0] + weight * m_stEstimateData.data[2 * i + 1][1] + weight * weight * m_stEstimateData.data[2 * i + 1][2];
		m_stEstimateData.data[2 * i + 1][3] = m_stEstimateData.data[2 * i + 1][3] * ramda;
		m_stEstimateData.data[2 * i + 1][4] = m_stEstimateData.data[2 * i + 1][4] * ramda;
		m_stEstimateData.data[2 * i + 1][5] = m_stEstimateData.data[2 * i + 1][5] * ramda;
		m_stEstimateData.data[2 * i + 1][6] = m_stEstimateData.data[2 * i + 1][6] * ramda;
		m_stEstimateData.data[2 * i + 1][7] = (m_stEstimateData.data[2 * i + 1][7] - m_stEstimateData.data[2 * i + 1][6]) * ramda;
		m_stEstimateData.data[2 * i + 1][8] = (m_stEstimateData.data[2 * i + 1][8] - 2 * m_stEstimateData.data[2 * i + 1][7] + m_stEstimateData.data[2 * i + 1][6]) * ramda;
		m_stEstimateData.data[2 * i + 1][9] = m_stEstimateData.data[2 * i + 1][9] * ramda;
		m_stEstimateData.data[2 * i + 1][10] = (m_stEstimateData.data[2 * i + 1][10] - m_stEstimateData.data[2 * i + 1][9]) * ramda;
		m_stEstimateData.data[2 * i + 1][11] = (m_stEstimateData.data[2 * i + 1][11] - 2 * m_stEstimateData.data[2 * i + 1][10] + m_stEstimateData.data[2 * i + 1][9]) * ramda;
		m_stEstimateData.data[2 * i + 1][12] = m_stEstimateData.data[2 * i + 1][12] * ramda;
		m_stEstimateData.data[2 * i + 1][13] = (m_stEstimateData.data[2 * i + 1][13] - m_stEstimateData.data[2 * i + 1][12]) * ramda;
		m_stEstimateData.data[2 * i + 1][14] = (m_stEstimateData.data[2 * i + 1][14] - 2 * m_stEstimateData.data[2 * i + 1][13] + m_stEstimateData.data[2 * i + 1][12]) * ramda;
	}
}