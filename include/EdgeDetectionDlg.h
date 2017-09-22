
// EdgeDetectionDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CEdgeDetectionDlg dialog
class CEdgeDetectionDlg : public CDialog
{
// Construction
public:
	CEdgeDetectionDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EDGEDETECTION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_edFilePath;
	CString m_edFileInfo;
	CComboBox m_cbAlgorithmControl;

	int m_width;
	int m_height;
	int m_fileSize;
	int m_imageSize;
	int m_pixelBit;

	afx_msg void OnBnClickedFileopen();
	afx_msg void OnBnClickedActive();
	afx_msg void OnCbnSelchangeAlgorithmList();
	void PrintResult();

	DWORD dwFileSize;
	CString m_edResult;
	vector<int>::iterator iter;	// vector
};

void MakeUniqueVector(vector<int> v);