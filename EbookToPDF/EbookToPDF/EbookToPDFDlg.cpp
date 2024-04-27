
// EbookToPDFDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "EbookToPDF.h"
#include "EbookToPDFDlg.h"
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


// CEbookToPDFDlg 대화 상자



CEbookToPDFDlg::CEbookToPDFDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EBOOKTOPDF_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEbookToPDFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SELECTED_MONITOR, m_comboSelectedMonitor);
	DDX_Control(pDX, IDC_STATIC_PICTURE_CONTROL, m_pictureTemp);
	DDX_Control(pDX, IDC_EDIT_CURRENT_COUNT, m_editCurrentCount);
}

BEGIN_MESSAGE_MAP(CEbookToPDFDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_SELECTED_MONITOR, &CEbookToPDFDlg::OnCbnSelchangeComboSelectedMonitor)
	ON_BN_CLICKED(IDC_BUTTON_CAPUTRE, &CEbookToPDFDlg::OnBnClickedButtonCaputre)
	ON_BN_CLICKED(IDC_BUTTON_SET_REGION, &CEbookToPDFDlg::OnBnClickedButtonSetRegion)
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE_START, &CEbookToPDFDlg::OnBnClickedButtonCaptureStart)
END_MESSAGE_MAP()


// CEbookToPDFDlg 메시지 처리기

BOOL CEbookToPDFDlg::OnInitDialog()
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
	InitDlg();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CEbookToPDFDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEbookToPDFDlg::OnPaint()
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
HCURSOR CEbookToPDFDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



CString CEbookToPDFDlg::InitDlg()
{
	SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);

	SetLayeredWindowAttributes(0, 255, LWA_ALPHA);

	InitControls();
	InitParams();

	CheckMonitor();

	return CString();
}

CString CEbookToPDFDlg::InitControls(int iOffsetX, int iOffsetY)
{
	if (iOffsetX == 0 && iOffsetY == 0)
	{
		this->MoveWindow(500, 20, 1000, 500);
	}

	GetDlgItem(IDC_STATIC_MONITOR_SELECT)->MoveWindow(iOffsetX + 100, iOffsetY + 100, 100, 30);
	GetDlgItem(IDC_COMBO_SELECTED_MONITOR)->MoveWindow(iOffsetX + 100, iOffsetY + 130, 100, 30);
	m_pictureTemp.MoveWindow(iOffsetX + 65, iOffsetY + 125, 30, 30);

	GetDlgItem(IDC_STATIC_MONITOR_WIDTH)->MoveWindow(iOffsetX + 250, iOffsetY + 100, 100, 30);
	GetDlgItem(IDC_EDIT_MONITOR_WIDTH)->MoveWindow(iOffsetX + 250, iOffsetY + 130, 100, 30);
	GetDlgItem(IDC_STATIC_MONITOR_HEIGHT)->MoveWindow(iOffsetX + 400, iOffsetY + 100, 100, 30);
	GetDlgItem(IDC_EDIT_MONITOR_HEIGHT)->MoveWindow(iOffsetX + 400, iOffsetY + 130, 100, 30);

	GetDlgItem(IDC_BUTTON_SET_REGION)->MoveWindow(iOffsetX + 400, iOffsetY + 230, 100, 30);
	GetDlgItem(IDC_BUTTON_CAPUTRE)->MoveWindow(iOffsetX + 400, iOffsetY + 330, 100, 30);
	
	GetDlgItem(IDC_STATIC_SELECT_REGION_START_X)->MoveWindow(iOffsetX + 100, iOffsetY + 200, 100, 30);
	GetDlgItem(IDC_EDIT_SELECT_REGION_START_X)->MoveWindow(iOffsetX + 100, iOffsetY + 230, 100, 30);
	GetDlgItem(IDC_STATIC_SELECT_REGION_START_Y)->MoveWindow(iOffsetX + 250, iOffsetY + 200, 100, 30);
	GetDlgItem(IDC_EDIT_SELECT_REGION_START_Y)->MoveWindow(iOffsetX + 250, iOffsetY + 230, 100, 30);

	GetDlgItem(IDC_STATIC_SELECT_REGION_END_X)->MoveWindow(iOffsetX + 100, iOffsetY + 300, 100, 30);
	GetDlgItem(IDC_EDIT_SELECT_REGION_END_X)->MoveWindow(iOffsetX + 100, iOffsetY + 330, 100, 30);
	GetDlgItem(IDC_STATIC_SELECT_REGION_END_Y)->MoveWindow(iOffsetX + 250, iOffsetY + 300, 100, 30);
	GetDlgItem(IDC_EDIT_SELECT_REGION_END_Y)->MoveWindow(iOffsetX + 250, iOffsetY + 330, 100, 30);
	
	
	GetDlgItem(IDC_STATIC_CAPTURE_DELAY)->MoveWindow(iOffsetX + 600, iOffsetY + 20, 100, 30);
	GetDlgItem(IDC_EDIT_CAPTURE_DELAY)->MoveWindow(iOffsetX + 600, iOffsetY + 50, 100, 30);

	GetDlgItem(IDC_BUTTON_CAPTURE_START)->MoveWindow(iOffsetX + 750, iOffsetY + 50, 100, 30);

	GetDlgItem(IDC_STATIC_CURRENT_COUNT)->MoveWindow(iOffsetX + 600, iOffsetY + 100, 100, 30);
	GetDlgItem(IDC_EDIT_CURRENT_COUNT)->MoveWindow(iOffsetX + 600, iOffsetY + 130, 100, 30);

	GetDlgItem(IDC_STATIC_MAX_COUNT)->MoveWindow(iOffsetX + 750, iOffsetY + 100, 100, 30);
	GetDlgItem(IDC_EDIT_MAX_COUNT)->MoveWindow(iOffsetX + 750, iOffsetY + 130, 100, 30);
	
	GetDlgItem(IDC_STATIC_MAKE_DIR_NAME)->MoveWindow(iOffsetX + 600, iOffsetY + 200, 200, 30);
	GetDlgItem(IDC_EDIT_MAKE_DIR_NAME)->MoveWindow(iOffsetX + 600, iOffsetY + 230, 200, 30);

	//m_pictureTemp.ShowWindow(SW_HIDE);
	CString strTemp;
	GetDlgItemText(IDC_EDIT_MAKE_DIR_NAME, strTemp);
	if (strTemp.IsEmpty())
	{
		SetDlgItemText(IDC_EDIT_MAKE_DIR_NAME, CString(_T("Image")));
	}
	

	return CString();
}

CString CEbookToPDFDlg::InitParams()
{
	m_vtMonitorData.clear();

	m_vtMonitorData = GetMonitorData();
	if ((int)m_vtMonitorData.size() != 0)
	{
		m_comboSelectedMonitor.ResetContent();

		for (auto& monitorData : m_vtMonitorData)
		{
			CString strTeemp(monitorData.wcharMonitorName);

			m_comboSelectedMonitor.AddString(strTeemp);
		}

		m_iSelected = 0;
		m_comboSelectedMonitor.SetCurSel(m_iSelected);
		SetComboSel(m_iSelected);
	}
	else
	{
		return DStrError;
	}

	return DStrSuccess;
}

std::vector<TMonitorData> CEbookToPDFDlg::GetMonitorData()
{
	std::vector<TMonitorData> vtTemp;

	// Graphic Divice
	DISPLAY_DEVICE G_device;
	ZeroMemory(&G_device, sizeof(G_device));
	G_device.cb = sizeof(DISPLAY_DEVICE);
	DWORD deviceNum = 0;

	while (EnumDisplayDevices(NULL, deviceNum, &G_device, 0)) {
		// Monitor Divice
		DISPLAY_DEVICE M_device;
		ZeroMemory(&M_device, sizeof(M_device));
		M_device.cb = sizeof(DISPLAY_DEVICE);
		DWORD monitorNum = 0;

		while (EnumDisplayDevices(G_device.DeviceName, monitorNum, &M_device, 0))
		{
			// Current Monitor Info
			DEVMODE devmode{};
			devmode.dmSize = sizeof(DEVMODE);
			EnumDisplaySettings(G_device.DeviceName, ENUM_CURRENT_SETTINGS, &devmode);

			CString strTemp = M_device.DeviceID;
			CString strName = strTemp.Mid(8, 7); // 모니터 이름

			TMonitorData tTemp;
			memcpy(tTemp.wcharMonitorName, strName.GetBuffer(), DStringBufferSize);
			tTemp.iStartX = devmode.dmPosition.x;
			tTemp.iStartY = devmode.dmPosition.y;

			tTemp.iMonitorWidth = devmode.dmPelsWidth;
			tTemp.iMonitorHeight = devmode.dmPelsHeight;

			vtTemp.emplace_back(tTemp);

			devmode; // <- 모니터의 각종 정보
			monitorNum++;
		}
		deviceNum++;
	}

	return vtTemp;
}

void CEbookToPDFDlg::UpdateStartPos(int x, int y)
{
	SetDlgItemInt(IDC_EDIT_SELECT_REGION_START_X, x);
	SetDlgItemInt(IDC_EDIT_SELECT_REGION_START_Y, y);
}

void CEbookToPDFDlg::UpdateEndPos(int x, int y)
{
	SetDlgItemInt(IDC_EDIT_SELECT_REGION_END_X, x);
	SetDlgItemInt(IDC_EDIT_SELECT_REGION_END_Y, y);
}

void CEbookToPDFDlg::CheckMonitor()
{
	CRect windowRect;
	this->GetWindowRect(windowRect);
	
	POINT ptTemp = windowRect.CenterPoint();

	CRect compareRect;
	compareRect.left = m_vtMonitorData[m_iSelected].iStartX;
	compareRect.top = m_vtMonitorData[m_iSelected].iStartY;
	compareRect.right = m_vtMonitorData[m_iSelected].iStartX + m_vtMonitorData[m_iSelected].iMonitorWidth;
	compareRect.bottom = m_vtMonitorData[m_iSelected].iStartY + m_vtMonitorData[m_iSelected].iMonitorHeight;

	bool bCheck = compareRect.PtInRect(ptTemp);

	CRect rect;
	CDC* pDc = m_pictureTemp.GetWindowDC();
	m_pictureTemp.GetWindowRect(rect);

	CImage image;
	int iImageWidth = 30;
	int iImageHeight = 30;

	image.Create(iImageWidth, iImageHeight, 32);
	unsigned char* pucTemp = (unsigned char*)image.GetBits();

	BYTE ucR = 0;
	BYTE ucG = 0;
	BYTE ucB = 0;

	if (bCheck)
	{
		ucR = 0;
		ucG = 255;
		ucB = 0;
	}
	else
	{
		ucR = 255;
		ucG = 0;
		ucB = 0;
	}

	for (int i = 0; i < iImageWidth; i++)
	{
		for (int j = 0; j < iImageHeight; j++)
		{
			image.SetPixelRGB(i, j, ucR, ucG, ucB);
		}
	}

	image.StretchBlt(pDc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정

	ReleaseDC(pDc);
}

CString CEbookToPDFDlg::ImageCaputre(std::string dirName,int iCount)
{
	// 스크린 전체를 캡쳐하기 위해서 CWindowDC 형식으로 DC를 얻는다.
	// GetDC의 파라메터에 특정 윈도우 핸들을 넣지 않고 NULL을 넣으면
	// CWindowDC 형식으로 DC를 얻게 된다.
	HDC h_screen_dc = ::GetDC(NULL);

	//int iStartX = m_vtMonitorData[m_iSelected].iStartX;
	//int iStartY = m_vtMonitorData[m_iSelected].iStartY;
	//int iWidth = m_vtMonitorData[m_iSelected].iMonitorWidth;
	//int iHeight = m_vtMonitorData[m_iSelected].iMonitorHeight;

	CString strData;
	GetDlgItem(IDC_EDIT_SELECT_REGION_START_X)->GetWindowTextW(strData);
	int iStartX = _ttoi(strData);
	GetDlgItem(IDC_EDIT_SELECT_REGION_START_Y)->GetWindowTextW(strData);
	int iStartY = _ttoi(strData);
	GetDlgItem(IDC_EDIT_SELECT_REGION_END_X)->GetWindowTextW(strData);
	int iWidth = _ttoi(strData) - iStartX;
	GetDlgItem(IDC_EDIT_SELECT_REGION_END_Y)->GetWindowTextW(strData);
	int iHeight = _ttoi(strData) - iStartY;

	// DIB의 형식을 정의한다.
	BITMAPINFO dib_define;
	dib_define.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	dib_define.bmiHeader.biWidth = iWidth;
	dib_define.bmiHeader.biHeight = iHeight;
	dib_define.bmiHeader.biPlanes = 1;
	dib_define.bmiHeader.biBitCount = 24;
	dib_define.bmiHeader.biCompression = BI_RGB;
	dib_define.bmiHeader.biSizeImage = (((iWidth * 24 + 31) & ~31) >> 3) * iHeight;
	dib_define.bmiHeader.biXPelsPerMeter = 0;
	dib_define.bmiHeader.biYPelsPerMeter = 0;
	dib_define.bmiHeader.biClrImportant = 0;
	dib_define.bmiHeader.biClrUsed = 0;

	// DIB의 내부 이미지 비트 패턴을 참조할 포인터 변수
	BYTE* p_image_data = NULL;

	// dib_define에 정의된 내용으로 DIB를 생성한다.
	HBITMAP h_bitmap = ::CreateDIBSection(h_screen_dc, &dib_define, DIB_RGB_COLORS, (void**)&p_image_data, 0, 0);

	// 이미지를 추출하기 위해서 가상 DC를 생성한다. 메인 DC에서는 직접적으로 비트맵에 접근하여
	// 이미지 패턴을 얻을 수 없기 때문이다.
	HDC h_memory_dc = ::CreateCompatibleDC(h_screen_dc);

	// 가상 DC에 이미지를 추출할 비트맵을 연결한다.
	HBITMAP h_old_bitmap = (HBITMAP)::SelectObject(h_memory_dc, h_bitmap);

	// 현재 스크린 화면을 캡쳐한다.
	::BitBlt(h_memory_dc, 0, 0, iWidth, iHeight, h_screen_dc, iStartX, iStartY, SRCCOPY);

	// 본래의 비트맵으로 복구한다.
	::SelectObject(h_memory_dc, h_old_bitmap);

	// 가상 DC를 제거한다.
	DeleteDC(h_memory_dc);

	// DIB 파일의 헤더 내용을 구성한다.
	BITMAPFILEHEADER dib_format_layout;
	ZeroMemory(&dib_format_layout, sizeof(BITMAPFILEHEADER));
	dib_format_layout.bfType = *(WORD*)"BM";
	dib_format_layout.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dib_define.bmiHeader.biSizeImage;
	dib_format_layout.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	CString strDirName(dirName.c_str());
	strDirName += _T("\\");
	::CreateDirectory(strDirName, nullptr);

	CString strFileName;
	strFileName.Format(_T("image%04d.bmp"), iCount);

	// DIB 파일을 생성한다.
	FILE* p_file;

	std::string strFilePath = dirName + "\\" + std::string((CT2CA)strFileName);
	fopen_s(&p_file, strFilePath.c_str(), "wb");

	if (p_file != NULL) {
		fwrite(&dib_format_layout, 1, sizeof(BITMAPFILEHEADER), p_file);
		fwrite(&dib_define, 1, sizeof(BITMAPINFOHEADER), p_file);
		fwrite(p_image_data, 1, dib_define.bmiHeader.biSizeImage, p_file);
		fclose(p_file);
	}
	else
	{
		return DStrError;
	}

	// 사용했던 비트맵과 DC 를 해제한다.
	if (NULL != h_bitmap)
	{
		DeleteObject(h_bitmap);
	}
	else
	{
		return DStrError;
	}

	if (NULL != h_screen_dc)
	{
		::ReleaseDC(NULL, h_screen_dc);
	}
	else
	{
		return DStrError;
	}

	return DStrSuccess;
}

CString CEbookToPDFDlg::SetComboSel(int iSel)
{
	if (m_vtMonitorData.size() >= iSel && iSel >= 0)
	{
		CString strSetData;
		strSetData.Format((L"%d"), m_vtMonitorData[iSel].iMonitorWidth);
		GetDlgItem(IDC_EDIT_MONITOR_WIDTH)->SetWindowTextW(strSetData);
		strSetData.Format((L"%d"), m_vtMonitorData[iSel].iMonitorHeight);
		GetDlgItem(IDC_EDIT_MONITOR_HEIGHT)->SetWindowTextW(strSetData);

		return DStrSuccess;
	}
	else
	{
		return DStrError;
	}
}

CString CEbookToPDFDlg::ImageCaputre()
{
	// 캡쳐를 하기 위해서 화면에서 현재 프로그램을 감춘다.
	ShowWindow(SW_HIDE);

	CString strTemp;
	GetDlgItemText(IDC_EDIT_MAKE_DIR_NAME, strTemp);

	std::string strDirName = (CT2CA)strTemp;
	ImageCaputre(strDirName, 0);

	// 캡쳐를 하기 위해서 감춘 화면을 다시 보여준다.
	ShowWindow(SW_SHOW);

	return DStrSuccess;
}

void CEbookToPDFDlg::OnCbnSelchangeComboSelectedMonitor()
{
	m_iSelected = m_comboSelectedMonitor.GetCurSel();
	SetComboSel(m_comboSelectedMonitor.GetCurSel());

	CheckMonitor();
}


void CEbookToPDFDlg::OnBnClickedButtonCaputre()
{
	CString strErr;
	strErr = ImageCaputre();
	if (strErr != DStrSuccess)
	{
		AfxMessageBox(strErr);
	}
}


void CEbookToPDFDlg::OnBnClickedButtonSetRegion()
{
	m_bSetRegion = true;

	int iSize = (int)m_vtMonitorData.size();

	if (iSize > 0)
	{
		int iWidthSum = 0;
		int iHeightSum = 0;

		for (auto& tData : m_vtMonitorData)
		{
			iWidthSum += tData.iMonitorWidth;
			iHeightSum += tData.iMonitorHeight;
		}

		this->MoveWindow(m_vtMonitorData[0].iStartX, m_vtMonitorData[0].iStartY, iWidthSum, iHeightSum);

		InitControls(m_vtMonitorData[0].iMonitorWidth, 0);

		SetLayeredWindowAttributes(0, 125, LWA_ALPHA);
	}
}


BOOL CEbookToPDFDlg::PreTranslateMessage(MSG* pMsg)
{
	if (m_bSetRegion)
	{
		if (pMsg->message == WM_LBUTTONDOWN)
		{
			m_iRegionStartX = pMsg->pt.x;
			m_iRegionStartY = pMsg->pt.y;

			UpdateStartPos(m_iRegionStartX, m_iRegionStartY);
		}
		else if (pMsg->message == WM_LBUTTONUP)
		{
			m_bSetRegion = false;

			m_iRegionEndX = pMsg->pt.x;
			m_iRegionEndY = pMsg->pt.y;

			UpdateEndPos(m_iRegionEndX, m_iRegionEndY);

			SetLayeredWindowAttributes(0, 255, LWA_ALPHA);
			this->MoveWindow(500, 20, 1000, 1000);
			InitControls();
		}
	}
	else
	{
		if (pMsg->message == WM_LBUTTONUP)
		{
			CheckMonitor();
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CEbookToPDFDlg::OnBnClickedButtonCaptureStart()
{
	CString strTemp;
	GetDlgItemText(IDC_EDIT_CAPTURE_DELAY, strTemp);
	m_fCaptureDelay = (float)_ttof(strTemp);

	m_nMaxCount = GetDlgItemInt(IDC_EDIT_MAX_COUNT);

	GetDlgItemText(IDC_EDIT_MAKE_DIR_NAME, strTemp);

	std::string strDirName = (CT2CA)strTemp;
	
	for (int i = 0; i <= m_nMaxCount; i++)
	{
		// 페이지 이동 필요
		keybd_event(VK_RIGHT, 0, 0, 0);

		clock_t start = clock();

		// 딜레이 기능 필요
		while (1)
		{
			clock_t end = clock();
			double time = double(end - start) / CLOCKS_PER_SEC; //초단위 변환

			if (time > m_fCaptureDelay)
				break;
		}

		ImageCaputre(strDirName, i);
	}

	// 완료.
}
