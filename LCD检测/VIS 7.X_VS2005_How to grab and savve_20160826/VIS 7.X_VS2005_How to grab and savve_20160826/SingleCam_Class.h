// SingleCam_Class.h : main header file for the SINGLECAM_CLASS application
//

#if !defined(AFX_SINGLECAM_CLASS_H__B07FD2EA_3655_458C_AD4A_6102BF93B0F2__INCLUDED_)
#define AFX_SINGLECAM_CLASS_H__B07FD2EA_3655_458C_AD4A_6102BF93B0F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSingleCam_ClassApp:
// See SingleCam_Class.cpp for the implementation of this class
//

class CSingleCam_ClassApp : public CWinApp
{
public:
	CSingleCam_ClassApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSingleCam_ClassApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSingleCam_ClassApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SINGLECAM_CLASS_H__B07FD2EA_3655_458C_AD4A_6102BF93B0F2__INCLUDED_)
