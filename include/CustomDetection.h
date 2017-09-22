#pragma once

#include "MyImage.h"
#define THRESHOLD_VAL 30
class CCustomDetection
{
private:
	int sum;
	bool is_vertical;

	int nWidth;
	int nHeight;
	int nImageSize;
	BYTE** szPixelData;
	BYTE** szResultData;


public:
	CCustomDetection(void);
	~CCustomDetection(void);

	CMyImage* DoDetection(CMyImage*, BYTE**);
	void CompareAvg(vector<BYTE> vec, int size);
};
