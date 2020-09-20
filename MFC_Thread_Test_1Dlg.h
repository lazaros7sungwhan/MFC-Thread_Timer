
// MFC_Thread_Test_1Dlg.h: 헤더 파일
//

#pragma once
#define THREADTEST0 WM_USER


// CMFCThreadTest1Dlg 대화 상자
class CMFCThreadTest1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CWinThread *thread_0, *therad_1;
	bool thread_state_0, thread_state_1, timer_state;
	double test_data_0, test_data_1;
	CMFCThreadTest1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	LRESULT thread_contents(WPARAM wParam, LPARAM lParam);

// 대화 상자 데이터입니다.wkfgo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_THREAD_TEST_1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton2();
};
