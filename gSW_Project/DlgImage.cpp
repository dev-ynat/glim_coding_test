// DlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "gSW_Project.h"
#include "afxdialogex.h"
#include "DlgImage.h"


// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgImage, pParent)
{

}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CDlgImage::InitImage(int x, int y) 
{
	m_nWidth = x;
	m_nHeight = y;
	int nBpp = 8;
	m_image.Create(m_nWidth, -m_nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	memset(fm, 0xff, m_nWidth * m_nHeight);
}

void CDlgImage::InitPoint(int sx, int sy, int ex, int ey)
{
	m_nStartX = sx;
	m_nStartY = sy;
	m_nEndX = ex;
	m_nEndY = ey;
	if (!m_bAction) {
		processCircle();
	}
}

void CDlgImage::processCircle()
{
	m_nRadius = rand() % 100 + 10;
	std::cout << m_nRadius << std::endl;
	drawCircle(m_nStartX, m_nStartY);
}

void CDlgImage::drawCircle(int x, int y)
{
	int nCenterX = x - m_nRadius;
	int nCenterY = y - m_nRadius;

	int nPitch = m_image.GetPitch();

	unsigned char* fm = (unsigned char*)m_image.GetBits();
	memset(fm, 0xff, m_nWidth * m_nHeight);
	for (int i = nCenterX; i < x + m_nRadius * 2; i++) {
		for (int j = nCenterY; j < y + m_nRadius * 2; j++) {
			if (initCirlcle(i, j, x, y, m_nRadius)) {
				if(vaildImgPos(i, j))
					fm[j * nPitch + i] = m_nGray;
			}
		}
	}
	UpdateDisplay();
}

void CDlgImage::drawCircle(int x, int y, bool check)
{
	int nCenterX = x - m_nRadius;
	int nCenterY = y - m_nRadius;

	int nPitch = m_image.GetPitch();

	unsigned char* fm = (unsigned char*)m_image.GetBits();
	memset(fm, 0xff, m_nWidth * m_nHeight);
	for (int i = nCenterX; i < x + m_nRadius * 2; i++) {
		for (int j = nCenterY; j < y + m_nRadius * 2; j++) {
			if (initCirlcle(i, j, x, y, m_nRadius)) {
				if (vaildImgPos(i, j))
					fm[j * nPitch + i] = m_nGray;
			}
		}
	}
	UpdateDisplay();
}

BOOL CDlgImage::vaildImgPos(int x, int y)
{
	CRect rect(0, 0, m_nWidth, m_nHeight);
	return rect.PtInRect(CPoint(x, y));
}

bool CDlgImage::initCirlcle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;
	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) {
		bRet = true;
	}
	return bRet;
}


void CDlgImage::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}


void CDlgImage::SaveImage(CString filePath)
{
	m_image.Save(filePath);
}

void CDlgImage::ImageLoad(CString filePath)
{
	if (m_image != NULL) {
		m_image.Destroy();
	}
	m_image.Load(filePath);
	UpdateDisplay();
}

int CDlgImage::findPoint(bool check)
{
	findXpoint();
	findYpoint();
	if (check) {
		if (m_nX1 == 0 || m_nX2 == 0) {
			return m_nX1 == 0 ? m_nX1 : m_nX2;
		}
		else if ((m_nX1 != 0 || m_nX2 != 0) && abs(m_nX1 - m_nX2) != abs(m_nY1 - m_nY2)) {
			int ndistance = abs(m_nX1 - m_nX2) > abs(m_nY1 - m_nY2) ? abs(m_nX1 - m_nX2) : abs(m_nY1 - m_nY2);
			return m_nX1 < m_nX2 ? m_nX1 + ndistance/2 : m_nX2 + ndistance/2;
		}
		else if (m_nX1 == m_nX2) {
			return m_nX1;
		}
		else {
			return m_nX1 > m_nX2 ? m_nX1 - abs(m_nX1 - m_nX2) / 2 : m_nX2 - abs(m_nX1 - m_nX2) / 2;
		}
	}
	else {
		if (m_nY1 == 0 || m_nY2 == 0) {
			return m_nY1 == 0 ? m_nY1 : m_nY2;
		}
		// 여기가 문제인듯
		else if ((m_nY1 != 0 || m_nY2 != 0) && abs(m_nX1 - m_nX2) != abs(m_nY1 - m_nY2)) {
			int ndistance = abs(m_nX1 - m_nX2) > abs(m_nY1 - m_nY2) ? abs(m_nX1 - m_nX2) : abs(m_nY1 - m_nY2);
			return m_nY1 < m_nY2 ? m_nY1 + ndistance/2 : m_nX2 + ndistance/2;
		}
		else if (m_nY1 == m_nY2) {
			return m_nY1;
		}
		else {
			return m_nY1 > m_nY2 ? m_nY1 - abs(m_nY1 - m_nY2) / 2 : m_nY2 - abs(m_nY1 - m_nY2) / 2;
		}
	}
}


void CDlgImage::findYpoint()
{
	int nLength = 0;
	int nResult = 0;
	int nPitch = m_image.GetPitch();

	int nY1 = 0, nY2 = NULL;
	int i, j;
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	for (i = 0; i < m_nHeight; i++) {
		for (j = 0; j < m_nWidth; j++) {
			if (fm[i * nPitch + j] == m_nGray)
				nLength++;
		}
		if (nResult < nLength) {
			nResult = nLength;
			m_nY1 = nY1 = i;
		}
		else if (nResult == nLength) {
			m_nY2 = nY2 = i;
		}
		nLength = 0;
	}
}

void CDlgImage::findXpoint()
{
	int nLength = 0;
	int nResult = 0;
	int nPitch = m_image.GetPitch();

	int nX1 = 0;
	int nX2 = NULL;
	int i, j;
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	for (i = 0; i < m_nWidth; i++) {
		for (j = 0; j < m_nHeight; j++) {
			if (fm[j * nPitch + i] == m_nGray)
				nLength++;
		}
		if (nResult < nLength) {
			nResult = nLength;
			m_nX1 = nX1 = i;
		}
		else if (nResult == nLength) {
			m_nX2 = nX2 = i;
		}
		nLength = 0;
	}
}


void CDlgImage::drawCross(int x, int y)
{
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	for (int i = 0; i < 7; i++) {
		if ((y + i - 3) < 0 || (x + i - 3) < 0 ) {
			continue;
		}
		int nPoint = (y + i - 3) * nPitch + (x + i - 3);
		fm[nPoint] = 0xff;
	}
	for (int i = 0; i < 7; i++) {
		if ((y + i - 3) < 0 || (x - i + 3) < 0) {
			continue;
		}
		int nPoint = (y + i - 3) * nPitch + (x - i + 3);
		fm[nPoint] = 0xff;
	}
	UpdateDisplay();
}


void CDlgImage::OnPaint()
{
	CPaintDC dc(this);
	if (m_image) {
		m_image.Draw(dc, 0, 0);
	}
}
