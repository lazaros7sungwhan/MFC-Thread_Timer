
// MFC_Thread_Test_1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFC_Thread_Test_1.h"
#include "MFC_Thread_Test_1Dlg.h"
#include "afxdialogex.h"
//#include <WinUser.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define USER_TIMER 1000

// CMFCThreadTest1Dlg 대화 상자


CMFCThreadTest1Dlg::CMFCThreadTest1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_THREAD_TEST_1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCThreadTest1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCThreadTest1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(THREADTEST0, thread_contents)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCThreadTest1Dlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCThreadTest1Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()

//Thread_1 1. updateforthread, thread_contents..

//////////////////Thread 관련////////////////////////
UINT updateforthread(LPVOID param)
{
	CMFCThreadTest1Dlg* pMain = (CMFCThreadTest1Dlg*)param;
	while (pMain->thread_state_0)
	{
		Sleep(1);
		PostMessage(pMain->m_hWnd, THREADTEST0, NULL, NULL);
	}
	return 0;
}
LRESULT CMFCThreadTest1Dlg::thread_contents(WPARAM wParam, LPARAM lParam)
{
	CString Data_text;
	Data_text.Format(_T("%0.f"), test_data_0++);
	SetDlgItemText(IDC_EDIT1,Data_text);
	return 0;
}
//////////////////Thread 관련////////////////////////

// CMFCThreadTest1Dlg 메시지 처리기

BOOL CMFCThreadTest1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCThreadTest1Dlg::OnPaint()
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
HCURSOR CMFCThreadTest1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////Thread 관련////////////////////////
void CMFCThreadTest1Dlg::OnBnClickedButton1()
{
	CString editcaption;
	GetDlgItemText(IDC_BUTTON1, editcaption);

	if (editcaption == _T("connect")){
		
		thread_state_0= TRUE;

		thread_0 = AfxBeginThread(updateforthread, this);

		SetDlgItemText(IDC_BUTTON1, _T("disconnect"));
	}
	else {
		thread_state_0 = FALSE;
		//AfxMessageBox(_T("ok"));
		WaitForSingleObject(thread_0->m_hThread, 500);
		SetDlgItemText(IDC_BUTTON1, _T("connect"));
	}
}
//////////////////Thread 관련////////////////////////
//////////////////Timer 관련////////////////////////
void CMFCThreadTest1Dlg::OnBnClickedButton2()
{
	CString caption_2;

	GetDlgItemText(IDC_BUTTON2, caption_2);
	if (caption_2 == _T("connect"))
	{
		timer_state = TRUE;
		SetDlgItemText(IDC_BUTTON2, _T("disconnect"));
		SetTimer(1, 200, NULL);
	}
	else {
		timer_state = FALSE;
		SetDlgItemText(IDC_BUTTON2, _T("connect"));
		KillTimer(1);
	}

}

void CMFCThreadTest1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	CString test_data;
	test_data.Format(_T("%0.f"), test_data_1++);
	SetDlgItemText(IDC_EDIT2, test_data);
	CDialogEx::OnTimer(nIDEvent);
}
//////////////////Timer 관련////////////////////////
