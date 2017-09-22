
// EdgeDetectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EdgeDetection.h"
#include "EdgeDetectionDlg.h"
#include "ActivProcess.h"
#include "MyImage.h"


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CEdgeDetectionDlg dialog




CEdgeDetectionDlg::CEdgeDetectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEdgeDetectionDlg::IDD, pParent)
	, m_edFilePath(_T(""))
	, m_edFileInfo(_T(""))
	, m_edResult(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEdgeDetectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILEPATH, m_edFilePath);
	DDX_Text(pDX, IDC_FILEINFO, m_edFileInfo);
	DDX_Text(pDX, IDC_EDIT1, m_edResult);
	DDX_Control(pDX, IDC_ALGORITHM_LIST, m_cbAlgorithmControl);
}

BEGIN_MESSAGE_MAP(CEdgeDetectionDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_FILEOPEN, &CEdgeDetectionDlg::OnBnClickedFileopen)
	ON_BN_CLICKED(IDC_ACTIVE, &CEdgeDetectionDlg::OnBnClickedActive)
	ON_CBN_SELCHANGE(IDC_ALGORITHM_LIST, &CEdgeDetectionDlg::OnCbnSelchangeAlgorithmList)
END_MESSAGE_MAP()


// CEdgeDetectionDlg message handlers

BOOL CEdgeDetectionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_cbAlgorithmControl.AddString(_T("1. Sobel Algorithm"));
	m_cbAlgorithmControl.AddString(_T("2. Custom Algorithm"));
	m_cbAlgorithmControl.SetCurSel(1);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEdgeDetectionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEdgeDetectionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEdgeDetectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CEdgeDetectionDlg::OnCbnSelchangeAlgorithmList(){}

void CEdgeDetectionDlg::OnBnClickedFileopen()
{
	m_edFileInfo = "";
	m_edResult = "";
	
	// Open File Dialog
	TCHAR szFilter[] = _T("BMP Files(*.bmp)|*.bmp|");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

	if(dlg.DoModal() == IDOK)
	{
		m_edFilePath = dlg.GetPathName();
		UpdateData(FALSE);
	
		// Create BitMap
		HBITMAP hBitmap;
		if((hBitmap = (HBITMAP)LoadImage(NULL, m_edFilePath, IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE)) == NULL)
		{
			AfxMessageBox(_T("This File is Broken BMP"));
			return;
		}
		else
		{
			CBitmap *pBitmap = CBitmap::FromHandle(hBitmap);
			BITMAP Bitmap;
			pBitmap->GetBitmap(&Bitmap);
			
			CString strMsg, strColorType;

			// Print File-Name, Width, Height
			strMsg.Format(_T("File Name		%s\r\n"), dlg.GetFileName());
			m_edFileInfo += strMsg;
			strMsg.Format(_T("Image Width	%d px\r\n"), (m_width = Bitmap.bmWidth));
			m_edFileInfo += strMsg;
			strMsg.Format(_T("Image Height	%d px\r\n"), (m_height = Bitmap.bmHeight));
			m_edFileInfo += strMsg;

			// Calc File Size
			dwFileSize = Bitmap.bmHeight * Bitmap.bmWidthBytes;
			m_fileSize = (int)dwFileSize;
			m_imageSize = m_width * m_height;

			// Print Image-Size
			strMsg.Format(_T("Image Size	%d Kb\r\n"), dwFileSize / 1024);
			m_edFileInfo += strMsg;

			// Get Color Type
			m_pixelBit = Bitmap.bmBitsPixel;
			if(Bitmap.bmBitsPixel == 8) strColorType = _T("Gray Scale");
			else if(Bitmap.bmBitsPixel == 16) strColorType = _T("16Bit");
			else if(Bitmap.bmBitsPixel == 24) strColorType = _T("24Bit True Color");
			else if(Bitmap.bmBitsPixel == 32) strColorType = _T("32Bit True Color");
			else strColorType = _T("Not Defined");

			// Print Color Type(GrayScale or RGB)
			strMsg.Format(_T("Color Type	%s\r\n"), strColorType);
			m_edFileInfo += strMsg;
			UpdateData(FALSE);
		}
	}
}


void CEdgeDetectionDlg::OnBnClickedActive()
{
	CMyImage *pFile = new CMyImage(m_edFilePath, m_width, m_height, m_pixelBit);
	CActivProcess active(m_cbAlgorithmControl.GetCurSel());
	if( !active.Execute(pFile) )
	{
		return;
	}	
	else
	{
		CString strMsg;
		strMsg.Format(_T("Processing Time	%d (ms)\r\n\r\n"), (int)(dwEndTime - dwStartTime));
		m_edResult += strMsg;

		if(g_nPointCount == 0)
		{
			AfxMessageBox(_T("There are no found"));
			return;
		}
		else
		{
			MessageBox(_T("Result File Created"));
			PrintResult();
		}
	}	
	m_edResult = "";
	g_nPointCount = 0;
	g_cor.clear();
}


void CEdgeDetectionDlg::PrintResult()
{
	CString strMsg;
	strMsg.Format(_T("Detection Count	%d\r\n"), g_nPointCount);
	m_edResult += strMsg;
	if(m_cbAlgorithmControl.GetCurSel() == 0)
	{
		strMsg.Format(_T("\r\nStarting Point of the Found Pixels\r\n"));
		m_edResult += strMsg;
		for( int i = 0; i < g_cor.size(); i++)
		{
			strMsg.Format(_T("[%d] X : %d	Y : %d\r\n"), i+1, g_cor[i].x, g_cor[i].y);
			m_edResult += strMsg;
		}
	}
	else if(m_cbAlgorithmControl.GetCurSel() == 1)
	{
		strMsg.Format(_T("\r\nFind Line List\r\n"));
		m_edResult += strMsg;
		for( int i = 0; i < g_cor.size(); i++)
		{

			strMsg.Format(_T("	Pos	%d\r\n"), g_cor[i].line);
			m_edResult += g_cor[i].corr + strMsg;
		}
	}	
	UpdateData(FALSE);
}

