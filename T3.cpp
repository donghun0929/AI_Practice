
// T3.cpp: 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "T3.h"
#include "T3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CT3App

BEGIN_MESSAGE_MAP(CT3App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CT3App 생성

CT3App::CT3App()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CT3App 개체입니다.

CT3App theApp;


// CT3App 초기화

BOOL CT3App::InitInstance()
{

	CWinApp::InitInstance();

	CT3Dlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

