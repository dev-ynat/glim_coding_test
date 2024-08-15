
// gSW_ProjectDlg.h: 헤더 파일
//

#pragma once
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#include "DlgImage.h"
#include <cmath>
#include <math.h>
// CgSWProjectDlg 대화 상자
class CgSWProjectDlg : public CDialogEx
{
// 생성입니다.
public:
	CgSWProjectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

private:
	CDlgImage* m_pDlgImage;

	int m_nWidth = 1060;
	int m_nHeight = 710;

	int m_nDlgWidth = 1020;
	int m_nDlgHeight = 480;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GSW_PROJECT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

private:
	void InitImage();
	bool PointCheck();
	int comparePoint(bool check, int point, int reapeat, double incr, int EndPoint);
	double DistanceValue(int start, int end, double divison);
	int RepeatValue(int startX, int startY, int endX, int endY, int nIncre);

	void CheckDir();
protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnOpen();
};