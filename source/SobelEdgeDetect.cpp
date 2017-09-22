#include "StdAfx.h"
#include <cmath>
#include "SobelEdgeDetect.h"


CSobelEdgeDetect::CSobelEdgeDetect(void){}
CSobelEdgeDetect::~CSobelEdgeDetect(void){}

CMyImage* CSobelEdgeDetect::DoDetection(CMyImage *pFile, BYTE** szPixelData)
{
	dwStartTime = timeGetTime();

	// Init Mask - find vertical Edges
	int szWeight[3][3] = {
		{ -1,  0,  1 },
		{ -2,  0,  2 },
		{ -1,  0,  1 }
	};

	// Get Origin Image's Info. to make Result Image
	nWidth = pFile->GetWidth();
	nHeight = pFile->GetHeight();	

	// Make result Image
	CMyImage *pResult = new CMyImage(pFile->GetFileName(), nWidth, nHeight, 8);
	szResultData = pResult->GetPixels2D();
	
	// 1. Set double's range ( Set Max and Min threshold )
	doubleMin = DBL_MAX;
	doubleMax = -DBL_MAX;
	for(y = 1; y < nHeight - 1; y++ )
	{
		for(x = 1; x < nWidth - 1; x++)
		{
			dPixelVal = 0.0;
			for(j = -1; j <= 1; j++)
			{
				for(i = -1; i <= 1; i++)
				{
					dPixelVal += szWeight[j + 1][i + 1] * szPixelData[y + j][x + i];
				}
			}
			if(dPixelVal < doubleMin) doubleMin = dPixelVal;
			if(dPixelVal > doubleMax) doubleMax = dPixelVal;
		}
	}


	// 2. Sobel Algorithm start - Detect 80% diff value, else = 255
	_Point cur;
	for(cur.y = 1; cur.y < nHeight - 1; cur.y++)
	{
		for(cur.x = 1; cur.x < nWidth - 1; cur.x++)
		{
			dPixelVal = 0.0;
			
			for(j = -1; j <= 1; j++) 
			{
				for(i = -1; i <= 1; i++)
				{
					dPixelVal += szWeight[j + 1][i + 1] * szPixelData[cur.y + j][cur.x + i];
				}
			}
			// Normalization  [doubleMin ~ doubleMax] to [0 ~ 255]
			dPixelVal = MAX_PIXEL_VAL * (dPixelVal - doubleMin) / (doubleMax - doubleMin);
			
			if( dPixelVal <= DETECTION_POINT) // differentiation value >= 80% (ex. 200 color to 100 is 50%)
			{
				szResultData[cur.y][cur.x] = (BYTE)dPixelVal;
								
				if( CheckNearPoint(cur) == FALSE )
				{
					g_cor.push_back(_Point(cur.x, cur.y));
					g_nPointCount++;
				}
			}			
			else
			{
				szResultData[cur.y][cur.x] = (BYTE)255;
			}
			
		}
	}
	dwEndTime = timeGetTime();
	return pResult;
}	

BOOL CheckNearPoint(_Point cur)
{
	double distence = 0.0;

	for(UINT i = 0; i < g_cor.size(); i++)
	{
		distence = Distence(g_cor[i], cur);	 // check cur point's left, left-top, top, ... 1*1 range
		if(distence <= sqrt((double)1*1 + 1*1)) 
		{
			return TRUE;
		}
		else if(abs(cur.x - g_cor[i].x) <= 1 || abs(cur.y - g_cor[i].y) <= 1)
		{
			return TRUE;
		}
	}
	return FALSE;
}

double Distence(_Point p1, _Point p2)
{
	return sqrt(double(
		(p1.x - p2.x) * (p1.x - p2.x) +
		(p1.y - p2.y) * (p1.y - p2.y)
	));
}