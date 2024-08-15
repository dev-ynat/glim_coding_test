
// gSW_ProjectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "gSW_Project.h"
#include "gSW_ProjectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CgSWProjectDlg 대화 상자



CgSWProjectDlg::CgSWProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GSW_PROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgSWProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgSWProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CgSWProjectDlg::OnBnClickedBtnDraw)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_ACTION, &CgSWProjectDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CgSWProjectDlg::OnBnClickedBtnOpen)
END_MESSAGE_MAP()


// CgSWProjectDlg 메시지 처리기

BOOL CgSWProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
	
	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(0, 0, m_nWidth, m_nHeight);
	SetDlgItemInt(IDC_START_X, 0);
	SetDlgItemInt(IDC_START_Y, 0);
	SetDlgItemInt(IDC_END_X, 0);
	SetDlgItemInt(IDC_END_Y, 0);
	InitImage();


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CgSWProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CgSWProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CgSWProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CgSWProjectDlg::InitImage()
{
	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_CDlgImage, this);
	m_pDlgImage->ShowWindow(SW_SHOW);
	m_pDlgImage->MoveWindow(10, 10, m_nDlgWidth, m_nDlgHeight);
	m_pDlgImage->InitImage(m_nDlgWidth, m_nDlgHeight);
}

void CgSWProjectDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	lpMMI->ptMinTrackSize = CPoint(m_nWidth, m_nHeight);
	lpMMI->ptMaxTrackSize = CPoint(m_nWidth, m_nHeight);
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

void CgSWProjectDlg::OnBnClickedBtnDraw()
{
	m_pDlgImage->m_bAction = false;
	if (PointCheck()) {
		return;
	}
	if (m_pDlgImage->m_image != NULL) {
		m_pDlgImage->m_image.Destroy();
		m_pDlgImage->InitImage(m_nWidth, m_nHeight);
	}
	m_pDlgImage->InitPoint(GetDlgItemInt(IDC_START_X), GetDlgItemInt(IDC_START_Y), GetDlgItemInt(IDC_END_X), GetDlgItemInt(IDC_END_Y));
	m_pDlgImage->Invalidate();
}





void CgSWProjectDlg::OnBnClickedBtnAction()
{
	int nStartX = GetDlgItemInt(IDC_START_X);
	int nStartY = GetDlgItemInt(IDC_START_Y);
	int nEndX = GetDlgItemInt(IDC_END_X);
	int nEndY = GetDlgItemInt(IDC_END_Y);
	if (PointCheck()) {
		return;
	}
	m_pDlgImage->m_bAction = true;
	m_pDlgImage->InitPoint(nStartX, nStartY, nEndX, nEndY);
	
	int nX = nStartX;
	int nY = nStartY;

	bool bX = (nStartX - nEndX) <= 0 ? true : false;
	bool bY = (nStartY - nEndY) <= 0 ? true : false;

	int nIncrease = GetDlgItemInt(IDC_POINTMOVE) > 1 ? GetDlgItemInt(IDC_POINTMOVE) : 1;
	// 반복횟수 구함
	double nDivision = RepeatValue(nStartX, nStartY, nEndX, nEndY, nIncrease);
	
	// 이동할 거리 구해야함
	double nXdivision = DistanceValue(nStartX, nEndX, nDivision);
	double nYdivision = DistanceValue(nStartY, nEndY, nDivision);
	
	CString filePath;
	int k = 1;
	

	CheckDir();
	for(int i = 0; i < nDivision; i++)
	{
		filePath.Format(_T("C:\\image\\%d.bmp"), k++);
		if (i == nDivision-1) {
			nX = nEndX;
			nY = nEndY;
		}
		m_pDlgImage->drawCircle(nX, nY, true);
		m_pDlgImage->SaveImage(filePath);
		std::cout << "X 좌표 : " << nX << std::endl;
		std::cout << "Y 좌표 : " << nY << std::endl;
		if (nX != nEndX) {
			nX = comparePoint(bX, nStartX, i, nXdivision, nEndX);
		}
		if (nY != nEndY) {
			nY = comparePoint(bY, nStartY, i, nYdivision, nEndY);
		}
		Sleep(10);
	}
}

// 이동할 거리 구해야함
double CgSWProjectDlg::DistanceValue(int start, int end, double divison)
{
	double ndivision = 0;
	if (divison == 1) {
		return divison;
	}
	if (abs(start - end) / divison > 0) {
		ndivision = (abs(start - end) / divison);
	}
	return ndivision;
}


int CgSWProjectDlg::RepeatValue(int startX, int startY, int endX, int endY, int nIncre)
{
	int nMin;
	nMin = abs(startX - endX) <= abs(startY - endY) ? abs(startX - endX) : abs(startY - endY);
	if (abs(startX - endX) == 0) {
		nMin = abs(startY - endY);
	}
	if (abs(startY - endY) == 0) {
		nMin = abs(startX - endX);
	}
	return nMin / nIncre == 1 ? nIncre : nMin / nIncre;
}

int CgSWProjectDlg::comparePoint(bool check, int point, int repeat, double incre, int EndPoint)
{
	if (check) {
		return point + incre * repeat > EndPoint ? EndPoint : point + incre * repeat;
	}
	else {
		return point - incre * repeat < EndPoint ? EndPoint : point - incre * repeat;
	}
}

bool CgSWProjectDlg::PointCheck()
{
	bool bCheck = false;
	if (GetDlgItemInt(IDC_START_X) > m_nDlgWidth || GetDlgItemInt(IDC_END_X) > m_nDlgWidth) {
		AfxMessageBox(_T("최대 가로길이 1020를 넘을 수는 없습니다"));
		bCheck = true;
	}
	else if (GetDlgItemInt(IDC_START_Y) > m_nDlgHeight || GetDlgItemInt(IDC_END_Y) > m_nDlgHeight) {
		AfxMessageBox(_T("최대 세로길이 480를 넘을 수는 없습니다."));
		bCheck = true;
	}
	if (GetDlgItemInt(IDC_START_X) == GetDlgItemInt(IDC_END_X) && GetDlgItemInt(IDC_START_Y) == GetDlgItemInt(IDC_END_Y)) {
		AfxMessageBox(_T("시작좌표와 종료좌표는 같을 수 없습니다."));
		bCheck = true;
	}
	return bCheck;
}

void CgSWProjectDlg::CheckDir()
{
	CFileFind file;
	CString strFile;
	strFile = "C:\\image";
	if (GetFileAttributes((LPCTSTR)strFile) == -1) {
		CreateDirectory(strFile, NULL);
	}
}


void CgSWProjectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	if (m_pDlgImage) delete m_pDlgImage;
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CgSWProjectDlg::OnBnClickedBtnOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szFile[] = _T("모든파일(*.*)|*.*||");

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFile);

	if (IDOK == dlg.DoModal())
	{
		CString pathName = dlg.GetPathName();
		m_pDlgImage->ImageLoad(pathName);
	}
	int nX = m_pDlgImage->findPoint(true);
	int nY = m_pDlgImage->findPoint(false);
	SetDlgItemInt(IDC_RESULT_X, nX);
	SetDlgItemInt(IDC_RESULT_Y, nY);
	m_pDlgImage->drawCross(nX, nY);
}
