#include "stdafx.h"
#include "T3.h"
#include "T3Dlg.h"
#include "afxdialogex.h"
#include "janggiai.h"


#include "iostream"

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int send_i, send_j,new_i,new_j;
int janggi[MAX_Y_COUNT][MAX_X_COUNT] = { 13,12,11,14,0,14,11,12,13,
				  0,0,0,0,17,0,0,0,0,
				   0,15,0,0,0,0,0,15,0,
				   16,0,16,0,16,0,16,0,16,
				   0,0,0,0,0,0,0,0,0,
				   0,0,0,0,0,0,0,0,0,
				   6,0,6,0,6,0,6,0,6,
				   0,5,0,0,0,0,0,5,0,
				   0,0,0,0,7,0,0,0,0,
				   3,2,1,4,0,4,1,2,3 };
//int janggi[MAX_Y_COUNT][MAX_X_COUNT];


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


// CT3Dlg 대화 상자



CT3Dlg::CT3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_T3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CT3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CT3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDCANCEL, &CT3Dlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CT3Dlg 메시지 처리기

BOOL CT3Dlg::OnInitDialog()
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
	CString str;
	const wchar_t *p_string = str;
	for (int i = 0; i < MAX_COUNT; i++) {
		str.Format(L"오목눈이\\%d.png",i);
		//str.Format(L"C:\\Users\\donghoon\\Desktop\\오목눈이\\%d.png",i);
		unit[i].Load(str);
	}


	m_png_image.Load(L"장기판.jpg");
	//m_png_image2.Load(L"알.png");
	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CT3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CT3Dlg::OnPaint()
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



		CPaintDC dc(this);
		m_png_image.Draw(dc, 5, 5);
		//m_png_image2.Draw(dc, 10, 100);
		for (int j = 0; j < MAX_Y_COUNT; j++) {
			for (int i = 0; i < MAX_X_COUNT; i++) {
				if (janggi[j][i] > 10) {
					if (janggi[j][i] % 10 == 1)
						unit[6].Draw(dc, i * 80, j * 60);
					if (janggi[j][i] % 10 == 2)
						unit[8].Draw(dc, i * 80, j * 60);
					if (janggi[j][i] % 10 == 3)
						unit[2].Draw(dc, i * 80, j * 60);
					if (janggi[j][i] % 10 == 4)
						unit[10].Draw(dc, i * 80, j * 60);
					if (janggi[j][i] % 10 == 5)
						unit[4].Draw(dc, i * 80, j * 60);
					if (janggi[j][i] % 10 == 6)
						unit[12].Draw(dc, i * 80, j * 60);
					if (janggi[j][i] % 10 == 7)
						unit[0].Draw(dc, i * 80, j * 60);
				}
				else if(janggi[j][i] > 0 && janggi[j][i] < 10) {
					if (janggi[j][i] % 10 == 1)
						unit[7].Draw(dc,  i * 80, j * 60);
					if (janggi[j][i] % 10 == 2)
						unit[9].Draw(dc,  i * 80,  j * 60);
					if (janggi[j][i] % 10 == 3)
						unit[3].Draw(dc,   i * 80,   j * 60);
					if (janggi[j][i] % 10 == 4)
						unit[11].Draw(dc,  i * 80,   j * 60);
					if (janggi[j][i] % 10 == 5)
						unit[5].Draw(dc,   i * 80,   j * 60);
					if (janggi[j][i] % 10 == 6)
						unit[13].Draw(dc,  i * 80,  j * 60);
					if (janggi[j][i] % 10 == 7)
						unit[1].Draw(dc,   i * 80,   j * 60);
				}
				if (unit_move[j][i] == 1)
					unit[14].Draw(dc, i * 80, j * 60);
			}
		}
		
		/*if (attack == 1) {
			for (int i = 0; i < MAX_COUNT; i++) {

				unit[i].Draw(dc, i * 60, 0);
			}
		}
		else
		 {
				for (int i = 0; i < MAX_COUNT; i++) {
					if (i == 7)
						continue;
					unit[i].Draw(dc, i * 60, 50);
				}
			}*/
		//else if(attack == 0) {
		//	unit[7].Destroy();
		//}
		//UpdateDate(FALSE);
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CT3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CT3Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	janggiai a;
	if (used == 0) {

		int x = point.x / 80;
		int y = point.y / 60;
		x = (x) * 80;// +30;
		y = (y) * 60;// +35;

		if (point.x % 80 > 80 / 2)
			x = x + 80;

		if (point.y % 60 > 60 / 2)
			y = y + 60;

		if (janggi[y / 60][x / 80] > 0 && janggi[y / 60][x / 80] < 10) {
			send_j = y / 60;
			send_i = x / 80;
			a.movee(send_j, send_i);
			//power[3][3];
			//janggiai.movee(send_i, send_j);
			/*
			cout << send_i << " .. " << send_j<<"\n";
			
			for (size_t i = 0; i < 10; i++)
			{
				cout << "\n";
				for (int j = 0; j < 9; j++) {
					cout << unit_move[i][j]<<" ";

				}
			}*/	
		}

		attack = 0;
		used = 1;
		//unit[7].Destroy();
		Invalidate(FALSE);

	}
	else if (used == 1) {
		//cout << send_i << " : " << send_j << "\n";

		int x = point.x / 80;
		int y = point.y / 60;
		x = (x) * 80;// +30;
		y = (y) * 60;// +35;
		if (point.x % 80 > 80 / 2)
			x = x + 80;

		if (point.y % 60 > 60 / 2)
			y = y + 60;
		if (unit_move[y / 60][x / 80] == 1) {
			new_j = y / 60;
			new_i = x / 80;
			janggi[new_j][new_i] = janggi[send_j][send_i];
			janggi[send_j][send_i] = 0;
			for (size_t i = 0; i < 10; i++)
			{
				for (int j = 0; j < 9; j++) {
					unit_move[i][j] = 0;
				}
			}
			Invalidate();
			a.ai();
			janggi[next_y][next_x] = janggi[now_y][now_x];
			janggi[now_y][now_x] = 0;
			next_x = 0; next_y = 0; now_x = 0; now_y = 0;
			int pcwin = 0;
			int userwin = 0;
			for (size_t i = 0; i < MAX_Y_COUNT; i++)
			{
				for (int j = 0; j < MAX_X_COUNT; j++) {
					if (janggi[i][j] == 17)
						pcwin = 1;
					if (janggi[i][j] == 7)
						userwin = 1;
			}
			}
			if (pcwin == 1)
				pcwin = 0;
			else
				MessageBox(TEXT("USER 승"));
			if (userwin == 1)
				userwin = 0;
			else
				MessageBox(TEXT("PC 승"));
			//MessageBox(TEXT("안뇽"));
		}
		/*if (janggi[y / 60][x / 80] == 0 || janggi[y / 60][x / 80] > 10) {
			new_j = y / 60;
			new_i = x / 80;
			cout << new_i << " mm " << new_j << "\n";
			janggi[new_j][new_i] = janggi[send_j][send_i];
			janggi[send_j][send_i] = 0;
		}*/
		
		used = 0;
		Invalidate();
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CT3Dlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
