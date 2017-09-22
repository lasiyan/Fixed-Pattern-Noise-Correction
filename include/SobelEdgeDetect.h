#pragma once

#include "MyImage.h"

#define MAX_PIXEL_VAL 255
#define DIFFERENCE_VAL 90 / 100
#define DETECTION_POINT 255 * (100 - 80) / 100
class CSobelEdgeDetect
{

private:
	int x, y, i, j;	// Loop variable	
	double dPixelVal;
	double doubleMin, doubleMax;

	int nWidth;
	int nHeight;
	int nImageSize;
	
	BYTE** szResultData;

public:
	CSobelEdgeDetect(void);
	~CSobelEdgeDetect(void);


	CMyImage* DoDetection(CMyImage*, BYTE**);
};

BOOL CheckNearPoint(_Point cur);
double Distence(_Point p1, _Point p2);