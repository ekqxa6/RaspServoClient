
// RaspServoClientDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CRaspServoClientDlg dialog
class CRaspServoClientDlg : public CDialog
{
// Construction
public:
	CRaspServoClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RASPSERVOCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedChkConnectSts();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClickedBtnConnect();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

private:
	DWORD m_dwIP;
	CSliderCtrl m_SCtl_V;
	CSliderCtrl m_SCtl_H;
	CButton m_Btn_Connect;
	CButton m_Chk_Connect_Sts;
	CSocket m_sock;
	void	Connect();
	void	Disconnect();
	void	Send();
	CString m_St_Ed_V;
	CString m_St_Ed_H;
	CString GetIPAddress(DWORD dwIP);
	BOOL m_bSocketReady;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
