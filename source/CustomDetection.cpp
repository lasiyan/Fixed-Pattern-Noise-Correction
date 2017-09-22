#include "StdAfx.h"
#include <cmath>
#include "CustomDetection.h"

CCustomDetection::CCustomDetection(void){}
CCustomDetection::~CCustomDetection(void){}

CMyImage* CCustomDetection::DoDetection(CMyImage* pFile, BYTE** szPixelData)
{
	dwStartTime = timeGetTime();

	// 0. init data
	nWidth = pFile->GetWidth();
	nHeight = pFile->GetHeight();
	
	// 1. Make Result Image and Setting Datas
	CMyImage* pResult = new CMyImage(pFile->GetFileName(), nWidth, nHeight, 8);
	szResultData = pResult->GetPixels2D();
	memset(szResultData[0], 255, pResult->GetImageSize());
	
	// Make Array List
	vector<BYTE> vecRowAvg(nHeight, 0);
	vector<BYTE> vecColAvg(nWidth, 0);
	

	int vecColCount;
	is_vertical = true;
	// 2. Col Calc ( Fill Col Avg Array and Compare )
	for(int x = 0; x < nWidth; x++)
	{
		sum = 0;
		for(int y = 0; y < nHeight; y++)
		{
			sum += szPixelData[y][x];	// Calc one col's sum val;
		}
		vecColAvg[x] = sum / nHeight;
	}
	CompareAvg(vecColAvg, nWidth);
	for(vecColCount = 0; vecColCount < g_cor.size(); vecColCount++)	// 0
	{
		for(int j = 0; j < nHeight; j++)
		{
			szResultData[j][g_cor[vecColCount].line] = 0;	// black
		}
	}

	is_vertical = false;
	// 3. Row Calc ( Fill Row Avg Array and Compare )
	for(int x = 0; x < nHeight; x++)
	{
		sum = 0;
		for(int y = 0; y < nWidth; y++)
		{
			sum += szPixelData[x][y];	// Calc one Row's sum val;
		}
		vecRowAvg[x] = sum / nWidth;
	}
	CompareAvg(vecRowAvg, nHeight);
	for(int i = 0; i < g_cor.size() - vecColCount; i++)	// draw Image without Col line
	{
		for(int j = 0; j < nHeight; j++)
		{
			szResultData[j][g_cor[i].line] = 0;	// black
		}
	}

	vecColAvg.clear();
	vecRowAvg.clear();
	dwEndTime = timeGetTime();
	return pResult;
}

void CCustomDetection::CompareAvg(vector<BYTE> vecAvg, int size)
{
	CString cor;
	if( is_vertical ) cor.SetString(_T("Vertical"));
	else cor.SetString(_T("Horizental"));

	
	int postIdx = 0;
	for(int curIdx = 0; curIdx < size; curIdx++)
	{
		postIdx = curIdx + 1;
		if(curIdx == size - 1) postIdx = 0;

		if(abs(vecAvg[curIdx] - vecAvg[postIdx]) >= THRESHOLD_VAL)
		{
			g_cor.push_back(_Point(curIdx, cor));	
			g_nPointCount++;
		}	
	}
}