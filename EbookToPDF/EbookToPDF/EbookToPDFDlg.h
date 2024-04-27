
// EbookToPDFDlg.h: 헤더 파일
//

#pragma once


// CEbookToPDFDlg 대화 상자
class CEbookToPDFDlg : public CDialogEx
{
// 생성입니다.
public:
	CEbookToPDFDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EBOOKTOPDF_DIALOG };
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

	//// Member Variables
private:
	CComboBox m_comboSelectedMonitor;
	CStatic m_pictureTemp;
	CEdit m_editCurrentCount;

	std::vector<TMonitorData> m_vtMonitorData;
	int m_iSelected;

	bool m_bSetRegion;
	bool m_bMouseClickStart;

	int m_iRegionStartX;
	int m_iRegionStartY;
	int m_iRegionEndX;
	int m_iRegionEndY;

	LONG m_lCurrentMousePosX;
	LONG m_lCurrentMousePosY;

	float m_fCaptureDelay;

	int m_nMaxCount;

public:

	//// Member Functions	
private:
	CString InitDlg();
	CString InitControls(int iOffsetX = 0, int iOffsetY = 0);
	CString InitParams();

	std::vector<TMonitorData> GetMonitorData();

	void UpdateStartPos(int x, int y);
	void UpdateEndPos(int x, int y);

	void CheckMonitor();

	CString ImageCaputre(std::string dirName, int iCount);

public:
	CString SetComboSel(int iSel);
	CString ImageCaputre();
	


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboSelectedMonitor();
	afx_msg void OnBnClickedButtonCaputre();
	afx_msg void OnBnClickedButtonSetRegion();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonCaptureStart();
};
