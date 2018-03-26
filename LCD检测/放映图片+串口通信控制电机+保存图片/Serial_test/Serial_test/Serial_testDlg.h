
// Serial_testDlg.h : ͷ�ļ�
//

#pragma once
#include "SerialPort.h"

// CSerial_testDlg �Ի���
class CSerial_testDlg : public CDialogEx
{
// ����
public:
	CSerial_testDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SERIAL_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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