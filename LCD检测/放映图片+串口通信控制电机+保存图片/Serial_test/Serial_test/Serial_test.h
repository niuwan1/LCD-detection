
// Serial_test.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSerial_testApp: 
// �йش����ʵ�֣������ Serial_test.cpp
//

class CSerial_testApp : public CWinApp
{
public:
	CSerial_testApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP() 
};

extern CSerial_testApp theApp;