
// RaspServoClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RaspServoClient.h"
#include "RaspServoClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CRaspServoClientDlg dialog



CRaspServoClientDlg::CRaspServoClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_RASPSERVOCLIENT_DIALOG, pParent)
	, m_dwIP(0)
	, m_St_Ed_V(_T(""))
	, m_St_Ed_H(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRaspServoClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_IPAddress(pDX, IDC_IPADDRESS1, m_dwIP);
	//  DDX_Control(pDX, IDC_SLIDER1, m_SCtl_1);
	DDX_Control(pDX, IDC_SLIDER2, m_SCtl_V);
	DDX_Control(pDX, IDC_SLIDER1, m_SCtl_H);
	//  DDX_Control(pDX, IDC_BTN_CONNECT, m_);
	DDX_Control(pDX, IDC_BTN_CONNECT, m_Btn_Connect);
	DDX_Control(pDX, IDC_CHK_CONNECT_STS, m_Chk_Connect_Sts);
	DDX_Text(pDX, IDC_EDIT1, m_St_Ed_V);
	DDX_Text(pDX, IDC_EDIT2, m_St_Ed_H);
}

BEGIN_MESSAGE_MAP(CRaspServoClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHK_CONNECT_STS, &CRaspServoClientDlg::OnBnClickedChkConnectSts)
	ON_BN_CLICKED(IDOK, &CRaspServoClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CRaspServoClientDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CRaspServoClientDlg::OnClickedBtnConnect)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, &CRaspServoClientDlg::OnBnClickedButton1)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CRaspServoClientDlg message handlers

BOOL CRaspServoClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_SCtl_V.SetRange(-180, 180, TRUE);
	m_SCtl_V.SetPos(0);
	m_SCtl_H.SetRange(-180, 180, TRUE);
	m_SCtl_H.SetPos(0);
	m_St_Ed_H.Format(_T("%d"), 0);
	m_St_Ed_V.Format(_T("%d"), 0);
	m_SCtl_V.SetPageSize(10);
	m_SCtl_H.SetPageSize(10);
	m_dwIP = 0xc0a80174;	// 192.168.1.116
	m_bSocketReady = FALSE;
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRaspServoClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRaspServoClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRaspServoClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRaspServoClientDlg::OnBnClickedChkConnectSts()
{
	// TODO: Add your control notification handler code here
}


void CRaspServoClientDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialog::OnOK();
}


void CRaspServoClientDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	Disconnect();
	CDialog::OnCancel();
}


void CRaspServoClientDlg::OnClickedBtnConnect()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_bSocketReady == FALSE)
	{
		Connect();
	}
	else
	{
		Disconnect();
	}
}

////////////////////////////////////////
// 接続
void CRaspServoClientDlg::Connect()
{
	UpdateData(TRUE);
	int err = 0;
	if (!m_sock.Create())
	{
		err = 1;
	}
	if (!err)
	{
		if (!m_sock.Connect(GetIPAddress(m_dwIP), 5000))
			err = 1;
	}

	if (err)
	{
		LPVOID        lpMsgBuf = NULL;

		::FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, m_sock.GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf, 0, NULL);

		//	m_xvEditLog += _T("Error : ");
		//	m_xvEditLog += static_cast<LPTSTR>(lpMsgBuf);
		UpdateData(FALSE);
		LocalFree(lpMsgBuf);
		return;
	}
	m_bSocketReady = TRUE;
	m_Btn_Connect.SetWindowTextW(_T("Connect"));//			MessageBox("ソケットを削除出来ません",NULL,MB_OK| MB_ICONEXCLAMATION);
	m_Chk_Connect_Sts.SetCheck(BST_CHECKED);
	UpdateData(FALSE);

}
////////////////////////////////////////
// 接続を切る
void CRaspServoClientDlg::Disconnect()
{

	if (m_bSocketReady == TRUE)
	{
		m_sock.Close();
		m_Btn_Connect.SetWindowTextW(_T("Connect"));//			MessageBox("ソケットを削除出来ません",NULL,MB_OK| MB_ICONEXCLAMATION);
		m_Chk_Connect_Sts.SetCheck(BST_UNCHECKED);
		UpdateData(FALSE);
		m_bSocketReady = FALSE;
	}
}

////////////////////////////////////////
// 文字列送信
VOID CRaspServoClientDlg::Send()
{
	static BOOL bSending = FALSE;
	UpdateData(TRUE);
	DWORD dwMaxSend;
	DWORD dwSentSum;
	DWORD dwSent;
	char chSendStr[256];
	LPCSTR          byteCP = NULL;

	CString sendStr;
	sendStr.Format(L"%s,%s", m_St_Ed_H, m_St_Ed_V);

	if (bSending == TRUE)
		return;
	if (m_bSocketReady == TRUE)
	{
		bSending = TRUE;
		strcpy_s(chSendStr, CT2CA(sendStr));
		dwSentSum = 0;
		dwMaxSend = sendStr.GetLength();
		while (dwSentSum < dwMaxSend)
		{
			byteCP = (LPCSTR)(chSendStr + dwSentSum);
			dwSent = m_sock.Send(byteCP, dwMaxSend - dwSentSum);
			if (dwSent == SOCKET_ERROR)
				return;
			dwSentSum += dwSent;
		}
	}
	bSending = FALSE;
}


void CRaspServoClientDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	int        pageSize;
	int        min, max;
	int		nUpdatePos;
	BOOL	bUpdate = FALSE;
	if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK)
	{
		nUpdatePos = nPos;
		bUpdate = TRUE;
	}
	else if (nSBCode == SB_PAGELEFT)
	{
		pageSize = m_SCtl_H.GetPageSize();
		m_SCtl_H.GetRange(min, max);
		nUpdatePos = (m_SCtl_H.GetPos() - pageSize > min) ? m_SCtl_H.GetPos() - pageSize : min;
		bUpdate = TRUE;
	}
	else if( nSBCode == SB_PAGERIGHT)
	{
		pageSize = m_SCtl_H.GetPageSize();
		m_SCtl_H.GetRange(min, max);
		nUpdatePos = (m_SCtl_H.GetPos() + pageSize < max) ? m_SCtl_H.GetPos() + pageSize : max;
		bUpdate = TRUE;
	}
	else
	{
		;
	}

	if (bUpdate)
	{
		m_SCtl_H.SetPos(nUpdatePos);
		m_St_Ed_H.Format(_T("%d"), nUpdatePos);
		UpdateData(FALSE);
	}


	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CRaspServoClientDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	int        pageSize;
	int        min, max;
	int		nUpdatePos;
	BOOL	bUpdate = FALSE;
	if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK)
	{
		nUpdatePos = nPos;
		bUpdate = TRUE;
	}
	else if (nSBCode == SB_PAGELEFT)
	{
		pageSize = m_SCtl_V.GetPageSize();
		m_SCtl_V.GetRange(min, max);
		nUpdatePos = (m_SCtl_V.GetPos() - pageSize > min) ? m_SCtl_V.GetPos() - pageSize : min;
		bUpdate = TRUE;
	}
	else if (nSBCode == SB_PAGERIGHT)
	{
		pageSize = m_SCtl_V.GetPageSize();
		m_SCtl_V.GetRange(min, max);
		nUpdatePos = (m_SCtl_V.GetPos() + pageSize < max) ? m_SCtl_V.GetPos() + pageSize : max;
		bUpdate = TRUE;
	}
	else
	{
		;
	}

	if (bUpdate)
	{
		m_SCtl_V.SetPos(nUpdatePos);
		m_St_Ed_V.Format(_T("%d"), nUpdatePos);
		UpdateData(FALSE);
	}
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

CString CRaspServoClientDlg::GetIPAddress(DWORD dwIP)
{
	CString str;
	str.Format(_T("%d.%d.%d.%d"), (dwIP & 0xFF000000) >> 24,
		(dwIP & 0x00FF0000) >> 16, (dwIP & 0x0000FF00) >> 8,
		(dwIP & 0x000000FF));
	return str;
}


void CRaspServoClientDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	Send();
}


void CRaspServoClientDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
/*	under construction
	int minV, maxV, minH, maxH;
	m_SCtl_H.GetRange(minH, maxH);
	m_SCtl_V.GetRange(minV, maxV);
	RECT rcH, rcV;
	m_SCtl_H.GetWindowRect(&rcH);
	m_SCtl_V.GetWindowRect(&rcV);

	int shiftX = -60 -minH;
	int shiftY = -30 -minV;
	point.Offset(shiftX, shiftY);

	if (minH <= point.x && point.x <= maxH )
	{
		if (minV <= point.y && point.y <= maxV)
		{
			m_SCtl_H.SetPos(point.x - shiftX);
			m_SCtl_V.SetPos(point.y - shiftY);
			m_St_Ed_H.Format(_T("%d"), point.x - shiftX);
			m_St_Ed_V.Format(_T("%d"), point.y - shiftY);
			UpdateData(FALSE);
			; // Draw Point
		}
	}
	*/
	CDialog::OnLButtonDown(nFlags, point);
}
