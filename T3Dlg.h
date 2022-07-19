#pragma once
#include "janggiai.h"

#define MAX_COUNT 15
#define MAX_X_COUNT 9
#define MAX_Y_COUNT 10
extern int janggi[MAX_Y_COUNT][MAX_X_COUNT] ;

// CT3Dlg 대화 상자
class CT3Dlg : public CDialogEx
{
// 생성입니다.
private:

	CImage unit[MAX_COUNT];
	char unit_value[MAX_COUNT];
	char attack = 1;
	int used = 0;
	CImage m_png_image;
	CImage m_png_image2;
	CImage clicked;
	CImageList clickedimg;
public:
	CT3Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	/*
	int janggi[MAX_Y_COUNT][MAX_X_COUNT] = { 13,12,11,14,0,14,11,12,13,
					  0,0,0,0,17,0,0,0,0,
					   0,15,0,0,0,0,0,15,0,
					   16,0,16,0,16,0,16,0,16,
					   0,0,0,0,0,0,0,0,0,
					   0,0,0,0,0,0,0,0,0,
					   6,0,6,0,6,0,6,0,6,
					   0,5,0,0,0,0,0,5,0,
					   0,0,0,0,7,0,0,0,0,
					   3,2,1,4,0,4,1,2,3 };*/


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_T3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedCancel();
};
