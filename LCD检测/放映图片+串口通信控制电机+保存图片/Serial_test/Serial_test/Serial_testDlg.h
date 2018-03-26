
// Serial_testDlg.h : 头文件
//

#pragma once
#include "SerialPort.h"

// CSerial_testDlg 对话框
class CSerial_testDlg : public CDialogEx
{
// 构造
public:
	CSerial_testDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SERIAL_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnBnClickedButtonsnap();
	//Generated message map funnctions  
	//{{AFX_MSG(CSCportTestView)   
	afx_msg long OnComm(WPARAM ch, LPARAM port);  
	//}}AFX_MSG

public:
	CSerialPort m_SerialPort;
	BOOL m_bSerialPortOpened;
	CString m_EditReceive;
	int zu=0;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton10();
};
//BEGIN_MESSAGE_MAP(CSerial_testDlg, CDialogEx)
//	ON_WM_SYSCOMMAND()
//	ON_WM_PAINT()
//	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BUTTON_snap, &CSerial_testDlg::OnBnClickedButtonsnap)
//	ON_MESSAGE(WM_COMM_RXCHAR, OnComm)
//END_MESSAGE_MAP()