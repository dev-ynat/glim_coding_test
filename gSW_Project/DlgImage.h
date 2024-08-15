#pragma once
#include "afxdialogex.h"
#include <stdlib.h>
#include <iostream>
#include <ctime>

// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

private:

	

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage();
	CImage m_image;
	bool m_bAction = false;

	int m_nGray = 80;

	int m_nWidth;
	int m_nHeight;

	int m_nStartX;
	int m_nStartY;
	int m_nEndX;
	int m_nEndY;
	int m_nRadius;

	int m_nX1;
	int m_nX2;
	int m_nY1;
	int m_nY2;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgImage };
#endif
private:
	
	void processCircle();
	bool initCirlcle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	BOOL vaildImgPos(int x, int y);
	void UpdateDisplay();
	void findXpoint();
	void findYpoint();

	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	void drawCircle(int x, int y);
	void drawCircle(int x, int y, bool check);
	void InitImage(int x, int y);
	void InitPoint(int sx, int sy, int ex, int ey);
	
	void SaveImage(CString filePath);
	void ImageLoad(CString filePath);
	int findPoint(bool check);
	void drawCross(int x, int);
};
