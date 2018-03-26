// SingleCam_ClassDlg.h : header file
//

#if !defined(AFX_SINGLECAM_CLASSDLG_H__8B8AE451_FBBF_41A0_BBE8_E4D312EA1A68__INCLUDED_)
#define AFX_SINGLECAM_CLASSDLG_H__8B8AE451_FBBF_41A0_BBE8_E4D312EA1A68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSingleCam_ClassDlg dialog

#include "VWGigECamera_V6.h"
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "SerialPort.h"

using namespace VWSDK;

#define   UM_CALLBACKMSG1       WM_USER + 1

class CSingleCam_ClassDlg : public CDialog
{
// Construction
public:
	CSingleCam_ClassDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CSingleCam_ClassDlg();

// Dialog Data
	//{{AFX_DATA(CSingleCam_ClassDlg)
	enum { IDD = IDD_SINGLECAM_CLASS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSingleCam_ClassDlg)
	protected:
	virtual void			   DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	static void				   GetImageEvent		 (OBJECT_INFO* pObjectInfo, IMAGE_INFO* pImageInfo     );	//Image capture event
	static void				   GetDisconnectionEvent (OBJECT_INFO* pObjectInfo, DISCONNECT_INFO tDisconnect);	//Disconnection event

	VWGIGE_HANDLE			   m_pvwGigE;																//Library object
	CVWGigECamera*			   m_pvgcam;
	VOID*					   m_pDisplayImage;
	//Camera object 

	IMAGE_INFO				   m_pgImageInfo;
	OBJECT_INFO				   m_pObjctInfo;

	CTreeCtrl				   m_deviceListTree;
	DWORD    				   m_pSelectedIFhandle; 
	INT						   m_nSeletecDeviceIndex;
	LARGE_INTEGER			   initial , freq , counter;

	UINT					   m_capturedImageNumber;
	void					   SaveImagetoFile();


	CSerialPort				   m_SerialPort;
	BOOL                       m_bSerialPortOpened;
	int                        zu = 0;
	char                       FolderName[100];

// Implementation
protected:
	HICON					   m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSingleCam_ClassDlg)
	virtual BOOL			   PreTranslateMessage(MSG* pMsg);
	virtual BOOL			   OnInitDialog();
	afx_msg void			   OnPaint();
	afx_msg HCURSOR			   OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void			   OnBnClickedOk();
	afx_msg void			   OnBnClickedButtonSearch();
	afx_msg void			   OnBnClickedButtonOpen();
	afx_msg void			   OnBnClickedButtonPlay();
	afx_msg void			   OnBnClickedButtonStop();
	afx_msg void			   OnBnClickedButtonClose();
	afx_msg void			   OnBnClickedButtonSoftwareTrigger();
	afx_msg LRESULT			   OnMycallbackImageMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void			   OnTvnSelchangedTreeDeviceList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void			   OnBnClickedButtonWriteCommand();
	afx_msg void			   OnBnClickedButtonReadCommand();
	afx_msg LRESULT               OnComm(WPARAM ch, LPARAM port);
};

#endif
