
// Serial_testDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Serial_test.h"
#include "Serial_testDlg.h"
#include "afxdialogex.h"
#include<CString>
#include"ImageDeal.h"
#include <direct.h>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	//DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

//BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//END_MESSAGE_MAP()


// CSerial_testDlg 对话框



CSerial_testDlg::CSerial_testDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSerial_testDlg::IDD, pParent)
	, m_EditReceive(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSerial_testDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, ID_EDIT_Rec, m_EditReceive);
}

BEGIN_MESSAGE_MAP(CSerial_testDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_snap, &CSerial_testDlg::OnBnClickedButtonsnap)
	ON_MESSAGE(WM_COMM_RXCHAR, OnComm)
	ON_EN_CHANGE(IDC_EDIT1, &CSerial_testDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON10, &CSerial_testDlg::OnBnClickedButton10)
END_MESSAGE_MAP()


// CSerial_testDlg 消息处理程序

BOOL CSerial_testDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	m_SerialPort.InitPort(this, 3, 9600,'n', 8, 1);

	if (m_SerialPort.InitPort(this, 3, 9600,'n', 8, 1))
	{
		m_SerialPort.StartMonitoring();
		m_bSerialPortOpened = TRUE;
	}
	else
	{
		MessageBox("串口初始化失败!");
		
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSerial_testDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSerial_testDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSerial_testDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CSerial_testDlg::OnBnClickedButtonsnap()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str1 = "0x31";
	CString str2 = "0x32";
	CString str3 = "0x33";
	CString str4 = "0x34";
	char *str5 = "0x31";
	CString str6 = "1";
	//byte* buf;
	byte buffer1[] = { 0x31 };     //0x31,前进
	byte buffer2[] = { 0x32 };     //0x32,向左
	byte buffer3[] = { 0x33 };     //0x33,后退
	byte buffer4[] = { 0x34 };     //0x34,向右

	
	//m_SerialPort.WriteToPort((LPCTSTR)str2);
	//m_SerialPort.WriteToPort((LPCTSTR)str2, 4);
	m_SerialPort.WriteToPort((LPCTSTR)str6);

	//MessageBox("发送数据成功！");
	return ;

}




//static long rxdatacount = 0;  //该变量用于接收字符计数
//LONG CSerial_testDlg::OnCommunication(WPARAM ch, LPARAM port)
//{
//	if (port <= 0 || port > 16)
//		return -1;
//	rxdatacount++;   //接收的字节计数
//	CString strTemp;
//	strTemp.Format("%ld", rxdatacount);
//	strTemp = "RX:" + strTemp;
//
//
//	//byte RecevieData[1000];
//	//	unsigned short int i;
//
//	if (m_bStopDispRXData)   //如果选择了“停止显示”接收数据，则返回
//		return -1;          //注意，这种情况下，计数仍在继续，只是不显示
//	//若设置了“自动清空”，则达到50行后，自动清空接收编辑框中显示的数据
//	if ((m_ctrlAutoClear.GetCheck()) && (m_ctrlReceiveData.GetLineCount() >= 50))
//	{
//		m_ReceiveData.Empty();
//		UpdateData(FALSE);
//	}
//	//如果没有“自动清空”，数据行达到400后，也自动清空
//	//因为数据过多，影响接收速度，显示是最费CPU时间的操作
//	if (m_ctrlReceiveData.GetLineCount() > 400)
//	{
//		m_ReceiveData.Empty();
//		m_ReceiveData = "***The Length of the Text is too long, Emptied Automaticly!!!***\r\n";
//		UpdateData(FALSE);
//	}
//
//	//如果选择了"十六进制显示"，则显示十六进制值
//	CString str;
//	if (m_ctrlHexReceieve.GetCheck())
//		str.Format("%02X ", ch);
//	else
//		str.Format("%c", ch);
//	//以下是将接收的字符加在字符串的最后，这里费时很多
//	//但考虑到数据需要保存成文件，所以没有用List Control
//	int nLen = m_ctrlReceiveData.GetWindowTextLength();
//	m_ctrlReceiveData.SetSel(nLen, nLen);
//	m_ctrlReceiveData.ReplaceSel(str);
//	nLen += str.GetLength();
//	m_ReceiveData += str;
//	return0;
//}



//BEGIN_MESSAGE_MAP(CSerial_testDlg, CDialog)
//	//{{AFX_MSG_MAP(CAboutDlg) 
//	ON_MESSAGE(WM_COMM_RXCHAR, OnComm)
//	//   No   message   handlers 
//	//}}AFX_MSG_MAP 
//END_MESSAGE_MAP()



long CSerial_testDlg::OnComm(WPARAM ch, LPARAM port)
{
	CString str;  
	str.Format(_T("%c"), ch);



	if (str == "1")
	{
		//MessageBox("接收数据1成功！");
		/*str = "NULL";*/
		//CString str3 = "3";
		//m_SerialPort.WriteToPort((LPCTSTR)str3);
		//int num = atoi(str);
		//ImageShow(num);
		zu++;
		
		int num = 1;
		while (num!=6)
		{
			char filename[100];
			
			char savepath[100];
			char savename[100];

			sprintf(filename, "红绿蓝黑白\\%d.jpg", num);// 将图片以数字命名：例如1.jpg 2.jpg等，放入D:/test/文件夹下

			
			//sprintf(savepath, "Picture_Save\\%d\\", zu);	
			char FolderName[100];
			sprintf(FolderName, "D:\\Save\\%d", zu);
			int state = mkdir(FolderName);
			//system("md D:\\");//创建一个文件夹 
			sprintf(savename, "%d.jpg", num);
			strcat(FolderName, "\\");
			strcat(FolderName, savename);
			IplImage* src = cvLoadImage(filename, 1);//导入图片
			if (!src)
			{
				MessageBox("读取图片出错！");
			}

			cvNamedWindow("src", CV_WND_PROP_FULLSCREEN);
			cvSetWindowProperty("src", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
			cvShowImage("src", src);
			ShowCursor(FALSE);//隐藏原来的光标

			cvSaveImage(FolderName, src);
			
			cvWaitKey(3000);
			cvReleaseImage(&src);
			cvDestroyWindow("src");
			ShowCursor(TRUE);//显示新的光标
			num++;
		}
		//MessageBox("该组照片拍摄完毕，请更换显示屏继续下一组拍摄！");

		CString str2 = "2";
		m_SerialPort.WriteToPort((LPCTSTR)str2); 

	}



	//do
	//{
	//	CString str2 = "2";
	//	m_SerialPort.WriteToPort((LPCTSTR)str2);
	//	cvWaitKey(10);
	//}while (str != "2");
	
	/*else if (str != "2")
	{
		CString str2 = "2";
		cvWaitKey(10);
		m_SerialPort.WriteToPort((LPCTSTR)str2);

	}*/
	/*if (str == "2")
	{
		MessageBox("接收数据2成功！");
	}*/

	
	

	//while (str)
	//{
	//	MessageBox("接收数据成功！");
	//	return 0;
	//}


	//if (str == "0")
	//{
	//	MessageBox("接收数据0成功！");

	//}
	//if (str == "x")
	//{
	//	MessageBox("接收数据x成功！");
	//}
	//if (str == "3")
	//{
	//	MessageBox("接收数据3成功！");
	//	/*int num = atoi(str);
	//	ImageShow(num);*/
	//}
	//if (str == "2")
	//{
	//	MessageBox("接收数据2成功！");
	//}


	//if (str == "0x32")
	//{
	//	MessageBox("接收数据0x32成功！");
	//}
	//else
	//{

	//	MessageBox("接收数据失败！");
	//}


	//m_EditReceive+=str;

	//UpdateData(FALSE);//将接收到的字符显示在接受编辑框中 
	return 0;
}



void CSerial_testDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CSerial_testDlg::OnBnClickedButton10()
{
	// TODO:  在此添加控件通知处理程序代码
}
