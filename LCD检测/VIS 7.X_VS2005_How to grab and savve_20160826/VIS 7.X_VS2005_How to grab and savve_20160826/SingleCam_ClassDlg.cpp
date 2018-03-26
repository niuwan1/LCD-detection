// SingleCam_ClassDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SingleCam_Class.h"
#include "SingleCam_ClassDlg.h"
#include "SerialPort.h"
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//For OpenCV
#ifdef WIN64
#pragma comment(lib,".\\OpenCV\\x64\\vc10\\lib\\opencv_core248.lib")	
#pragma comment(lib,".\\OpenCV\\x64\\vc10\\lib\\opencv_highgui248.lib")	
#else
#pragma comment(lib,".\\OpenCV\\x86\\vc10\\lib\\opencv_core248.lib")	
#pragma comment(lib,".\\OpenCV\\x86\\vc10\\lib\\opencv_highgui248.lib")	
#endif
//For OpenCV

// CSingleCam_ClassDlg dialog

/////////////////////////////////////////////////////////////////////////////
// CSingleCam_ClassDlg dialog

CSingleCam_ClassDlg::CSingleCam_ClassDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSingleCam_ClassDlg::IDD, pParent)
{
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon		= AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pvgcam					 = NULL;
	m_pvwGigE		             = NULL;

	//For selected interface and device.
	m_pSelectedIFhandle			 = NULL; 
	m_nSeletecDeviceIndex		 = -1;
}

CSingleCam_ClassDlg::~CSingleCam_ClassDlg()
{

}

void CSingleCam_ClassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_DEVICE_LIST,		      m_deviceListTree);
}

BEGIN_MESSAGE_MAP(CSingleCam_ClassDlg, CDialog)
	//{{AFX_MSG_MAP(CSingleCam_ClassDlg)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK,								OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_DEVICE,			OnBnClickedButtonSearch)	
	ON_BN_CLICKED(IDC_BUTTON_OPEN1,					OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_PLAY1,					OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP1,					OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE1,				OnBnClickedButtonClose)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_DEVICE_LIST, OnTvnSelchangedTreeDeviceList)
	ON_BN_CLICKED(IDC_BUTTON_SOFTWARE_TRIGGER,		OnBnClickedButtonSoftwareTrigger)
	ON_MESSAGE(UM_CALLBACKMSG1,						OnMycallbackImageMessage)
	ON_BN_CLICKED(IDC_BUTTON_WRITE_COMMAND,			OnBnClickedButtonWriteCommand)
	ON_BN_CLICKED(IDC_BUTTON_READ_COMMAND,			OnBnClickedButtonReadCommand)

	ON_MESSAGE(WM_COMM_RXCHAR, OnComm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSingleCam_ClassDlg message handlers
/******************************************************************************
* FUNCTION		 OnInitDialog()
* DESCRIPTION:  
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CSingleCam_ClassDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog. The framework does this automatically
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

	CString tempdebug;
	QueryPerformanceFrequency(&freq);

	GetDlgItem(IDC_EDIT_COMMAND)->SetWindowText("TriggerMode");

	m_capturedImageNumber = 0;


	m_SerialPort.InitPort(this, 9, 9600, 'n', 8, 1);

	if (m_SerialPort.InitPort(this, 9, 9600, 'n', 8, 1))
	{
		m_SerialPort.StartMonitoring();
		m_bSerialPortOpened = TRUE;
	}
	else
	{
		MessageBox("串口初始化失败!");

	}

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

/******************************************************************************
* FUNCTION		 OnPaint()
* DESCRIPTION:  
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CSingleCam_ClassDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

/******************************************************************************
* FUNCTION		 OnQueryDragIcon()
* DESCRIPTION:  
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
HCURSOR CSingleCam_ClassDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/******************************************************************************
* FUNCTION		 GetDisconnectionEvent()
* DESCRIPTION:   When the connection is disconnected between PC and Camera, a user can receive disconnection Event.
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CSingleCam_ClassDlg::GetDisconnectionEvent(OBJECT_INFO* pObjectInfo,DISCONNECT_INFO tDisconnect)
{
	CSingleCam_ClassDlg *dlg = (CSingleCam_ClassDlg *)pObjectInfo->pUserPointer;	

	if( dlg == NULL )
		return;

	dlg->GetDlgItem(IDC_STATIC_CAPTURED)->SetWindowText("GetDisconnectionEvent");
}

/******************************************************************************
* FUNCTION		 GetImageEvent1()
* DESCRIPTION:   Display image
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CSingleCam_ClassDlg::GetImageEvent(OBJECT_INFO* pObjectInfo,IMAGE_INFO* pImageInfo)
{
    CSingleCam_ClassDlg *dlg = (CSingleCam_ClassDlg *)pObjectInfo->pUserPointer;	;

	if( pObjectInfo == NULL || pImageInfo == NULL )
	{
		return;
	}

	memcpy(&dlg->m_pObjctInfo, pObjectInfo,sizeof(OBJECT_INFO));
	memcpy(&dlg->m_pgImageInfo,pImageInfo, sizeof(IMAGE_INFO));

	//We call PostMessage function. Because any job should not interrupt callback function.
	dlg->PostMessage(UM_CALLBACKMSG1, (WPARAM)&dlg->m_pObjctInfo, (LPARAM)&dlg->m_pgImageInfo);
}

//Display image
LRESULT CSingleCam_ClassDlg::OnMycallbackImageMessage (WPARAM wParam, LPARAM lParam)
{
	OBJECT_INFO* pObjectInfo = (OBJECT_INFO*)wParam;
	IMAGE_INFO* pImageInfo	 = (IMAGE_INFO* )lParam;

	if( pImageInfo == NULL || pObjectInfo == NULL)
	{
		return 0;
	}

	CSingleCam_ClassDlg *dlg = (CSingleCam_ClassDlg *)pObjectInfo->pUserPointer;	

	//This is an image buffer as raw data.
	dlg->m_pDisplayImage	 = dlg->m_pvgcam->GetBufferDataForDisplay(pImageInfo->width,pImageInfo->height,pImageInfo->pixelFormat,pImageInfo->pImage);
	pImageInfo->pImage;

	dlg->m_capturedImageNumber++;
	CString debugmsg;
	debugmsg.Format("Capture the image : %d",dlg->m_capturedImageNumber);
	GetDlgItem(IDC_STATIC_CAPTURED)->SetWindowText(debugmsg);
	//OutputDebugString("Grabbed the image raw data");

	dlg->SaveImagetoFile();

	return 0;
}

void CSingleCam_ClassDlg::SaveImagetoFile()
{
	CString tempfilefullname    = "";
	UINT    nSelectedFileformat = 0;

	if( m_pgImageInfo.pixelFormat	== PIXEL_FORMAT_BAYGR8  ||
		m_pgImageInfo.pixelFormat	== PIXEL_FORMAT_BAYRG8   )
	{
		BYTE * tempOriginalPointer = NULL ;

		//Get the image data for display.
		tempOriginalPointer		  = (BYTE *)m_pDisplayImage;

		int nBitsPerPixel  = 8;													
		int nStep		   = m_pgImageInfo.width * 3;	
		IplImage* pcvImage = cvCreateImageHeader(cvSize(m_pgImageInfo.width, m_pgImageInfo.height), nBitsPerPixel, 3);

		cvSetImageData( pcvImage, (void*)tempOriginalPointer, nStep );

		if(  nSelectedFileformat == 0 )
		{
			tempfilefullname.Format(".\\image%05d.bmp",m_capturedImageNumber);
		}
		else if(  nSelectedFileformat == 1 )
		{
			tempfilefullname.Format(".\\image%05d.tiff",m_capturedImageNumber);	
		}
		else if(  nSelectedFileformat == 2 )
		{
			tempfilefullname.Format(".\\image%05d.jpg",m_capturedImageNumber);	
		}
		else if(  nSelectedFileformat == 3 )
		{
			tempfilefullname.Format(".\\image%05d.png",m_capturedImageNumber);	
		}

		//char savepath[100];
		//char savename[100];
		//char FolderName[100];
		//sprintf(FolderName, "D:\\Save\\%d", zu);
		//int state = mkdir(FolderName);
		//sprintf(savename, "%d.bmp", num);
		//strcat(FolderName, "\\");
		//strcat(FolderName, savename);

		//cvSaveImage(FolderName, pcvImage);
		cvSaveImage(tempfilefullname, pcvImage);
		cvReleaseImageHeader(&pcvImage);
	}
	else
	{
		CFile   file;
		BYTE*   tempbuffer		      = NULL;
		BYTE*   tempOriginalPointer   = NULL;
		tempbuffer	    			  = new BYTE[m_pgImageInfo.width,m_pgImageInfo.height*1];

		if( tempbuffer == NULL )
		{
			return;  
		}

		//convert image as 8bit depth
		ZeroMemory(tempbuffer, sizeof(tempbuffer));
		tempOriginalPointer = (BYTE *)m_pgImageInfo.pImage;

		//12packed 
		if(m_pgImageInfo.pixelFormat		== PIXEL_FORMAT_MONO12_PACKED )
		{
			m_pvgcam->ConvertMono12PackedToMono8bit(tempOriginalPointer,m_pgImageInfo.width,m_pgImageInfo.height,tempbuffer);
		}
		//10packed 
		else if(m_pgImageInfo.pixelFormat  == PIXEL_FORMAT_MONO10_PACKED ) 
		{
			m_pvgcam->ConvertMono10PackedToMono8bit(tempOriginalPointer,m_pgImageInfo.width,m_pgImageInfo.height,tempbuffer);				
		}
		//Mono 8bit
		else
		{

		}

		int nBitsPerPixel = 8;												
		int nStep = m_pgImageInfo.width * 1;					
		IplImage* pImage = cvCreateImageHeader(cvSize(m_pgImageInfo.width, m_pgImageInfo.height),nBitsPerPixel, 1);

		if( m_pgImageInfo.pixelFormat  == PIXEL_FORMAT_MONO12_PACKED||
			m_pgImageInfo.pixelFormat  == PIXEL_FORMAT_MONO10_PACKED)
		{		
			cvSetImageData( pImage, (void*)tempbuffer, nStep );
		}
		else
		{
			cvSetImageData( pImage,(void*)tempOriginalPointer, nStep );
		}

		if(  nSelectedFileformat == 0 )
		{
			tempfilefullname.Format(".\\image%05d.bmp",m_capturedImageNumber);
		}
		else if(  nSelectedFileformat == 1 )
		{
			tempfilefullname.Format(".\\image%05d.tiff",m_capturedImageNumber);	
		}
		else if(  nSelectedFileformat == 2 )
		{
			tempfilefullname.Format(".\\image%05d.jpg",m_capturedImageNumber);	
		}
		else if(  nSelectedFileformat == 3 )
		{
			tempfilefullname.Format(".\\image%05d.png",m_capturedImageNumber);	
		}


		//if (FolderName!=NULL)
		//{
		cvSaveImage(FolderName, pImage);
		
		//}

		//cvSaveImage(tempfilefullname, pImage);

		cvReleaseImageHeader(&pImage);

		delete tempbuffer;
	}	

	GetDlgItem(IDC_STATIC_CAPTURED)->SetWindowText(tempfilefullname);
}

/******************************************************************************
* FUNCTION		 OnBnClickedButtonSearch()
* DESCRIPTION:   Search NIC 
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CSingleCam_ClassDlg::OnBnClickedButtonSearch()
{
	RESULT ret = RESULT_SUCCESS;

	if( m_pvwGigE != NULL )
	{
		CloseVwGigE(m_pvwGigE);
		m_pvwGigE = NULL;
	}

	m_deviceListTree.DeleteAllItems();
	m_deviceListTree.RedrawWindow();

	//Open VIS library
	ret = OpenVwGigE ( &m_pvwGigE );
	if ( RESULT_SUCCESS != ret )
	{
		return;
	}

	//Discovery the connected cameras
	ret = VwDiscovery( m_pvwGigE  );
	if ( RESULT_SUCCESS != ret )
	{
		return;
	}

	UINT nInterfaceNum = 0;

	//Get NIC handle(Lan card)
	ret = VwGetNumInterfaces( m_pvwGigE, &nInterfaceNum);
	if ( RESULT_SUCCESS != ret )
	{
		return;
	}

	HTREEITEM hSub;
	HTREEITEM hSubSub;

	// Enumerate interface which having a camera.
	{	
		for(UINT i=0;i<nInterfaceNum;i++)
		{
			UINT				  nconnectedCamindex=0;	
			HINTERFACE			  phInterface;
			INTERFACE_INFO_STRUCT InterfaceInfo;
			UINT				  DeviceNum = 0;

			//Open NIC interface
			ret = VwOpenInterfaceByIndex  (m_pvwGigE, i, &phInterface);
			if ( RESULT_SUCCESS != ret )
			{

			}

			//Get NIC information
			ret = VwDiscoveryInterfaceInfo(m_pvwGigE, i, &InterfaceInfo);
			if ( RESULT_SUCCESS != ret )
			{

			}

			//Get the connected camera number 
			ret = InterfaceGetNumCameras( phInterface, &DeviceNum );
			if ( RESULT_SUCCESS != ret )
			{

			}

			//This is just for displaying NIC name
			hSub          = m_deviceListTree.InsertItem(InterfaceInfo.name,1,1);

			//In order to open the camera, we save NIC handle here.
			m_deviceListTree.SetItemData(hSub,(unsigned long)phInterface);

			for(UINT j=0;j<DeviceNum;j++)
			{
				CHAR chDevName[1024] = {0,};
				size_t sizeDevName   = sizeof( chDevName );
				//Get Camera Name
				ret = InterfaceGetCameraName( phInterface, j, chDevName, &sizeDevName );
				if ( RESULT_SUCCESS != ret )
				{

				}

				//This is just for displaying the camera name.
				hSubSub = m_deviceListTree.InsertItem(chDevName,2,2,hSub);

				//In order to open the camera, we save the connected camera index here
				m_deviceListTree.SetItemData(hSubSub,nconnectedCamindex);

				nconnectedCamindex++;
			}

			m_deviceListTree.Expand(hSub, TVE_EXPAND);
		}
	}

	return;
}

/******************************************************************************
* FUNCTION		 OnBnClickedButtonOpen1()
* DESCRIPTION:   Camera open
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CSingleCam_ClassDlg::OnBnClickedButtonOpen()
{
	if( m_pvgcam != NULL )
	{
		return;
	}	

	if( m_pSelectedIFhandle == NULL || m_nSeletecDeviceIndex == -1 )
	{
		GetDlgItem(IDC_STATIC_LOG)->SetWindowText(_T("Please select the device you want to open."));
		return;
	}

	m_pvgcam		  = new CVWGigECamera;

	if( m_pvgcam == NULL )
	{
		GetDlgItem(IDC_STATIC_CAPTURED)->SetWindowText("new CVWGigECamera - Bad");
		return;
	}

	UINT bufferNumber = 10; //We recommend the current frame rate / 2 number. For example, the current frame rate 30
							//The good buffer number is 15(30 / 2)
	UINT packetsize   = 0;  //If it is ZERO, it means that it does not change the current packet size.

	if( m_pvgcam != NULL )
	{
		if( m_pvgcam->InitDevice((void *)m_pSelectedIFhandle,m_pvwGigE,m_nSeletecDeviceIndex,
								   this,bufferNumber,packetsize,GetImageEvent,GetDisconnectionEvent) == TRUE )
		{
			// We change the following modes
			m_pvgcam->SetCustomCommand("TriggerMode",	"On"			 );
			m_pvgcam->SetCustomCommand("TriggerSource",	"Software"		 );

			GetDlgItem(IDC_STATIC_CAPTURED)->SetWindowText("Open - Good");
			OnBnClickedButtonPlay();
			//CString str1 = "1";
			//m_SerialPort.WriteToPort((LPCTSTR)str1);
		}
		else
		{
			GetDlgItem(IDC_STATIC_CAPTURED)->SetWindowText("Open - Bad");
		}
	}
}

/******************************************************************************
* FUNCTION		 OnBnClickedButtonPlay1()
* DESCRIPTION:   Start to grab image
				 In the trigger Mode, Start(Grab function) just changes 
				 this software to "Standby" state in order to grab the image.
				 When you create a trigger, the image will be grabbed.
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CSingleCam_ClassDlg::OnBnClickedButtonPlay()
{
	if( m_pvgcam != NULL && m_pvgcam->GetDeviceHandle() != NULL )
	{
		if( m_pvgcam->Start() == TRUE )
		{
			GetDlgItem(IDC_STATIC_CAPTURED)->SetWindowText("Play - Good");

		}
		else
		{
			GetDlgItem(IDC_STATIC_CAPTURED)->SetWindowText("Play - Bad");
		}


	}
}

/******************************************************************************
* FUNCTION		 OnBnClickedButtonStop1()
* DESCRIPTION:   Stop to grab image				 
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CSingleCam_ClassDlg::OnBnClickedButtonStop()
{
	if( m_pvgcam != NULL && m_pvgcam->GetDeviceHandle() != NULL )
	{
		if( m_pvgcam->Stop() == TRUE )
		{
			GetDlgItem(IDC_STATIC_CAPTURED)->SetWindowText("Stop - Good");
		}
		else
		{
			GetDlgItem(IDC_STATIC_CAPTURED)->SetWindowText("Bad - Good");			
		}
	}

	m_capturedImageNumber = 0;
}

/******************************************************************************
* FUNCTION		 OnBnClickedButtonClose1()
* DESCRIPTION:   Close camera
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CSingleCam_ClassDlg::OnBnClickedButtonClose()
{
	//Close device
	if( m_pvgcam != NULL && m_pvgcam->GetDeviceHandle() != NULL )
	{		
		m_pvgcam->Stop();
				
		if( m_pvgcam->CloseDevice() == TRUE )
		{
			GetDlgItem(IDC_STATIC_CAPTURED)->SetWindowText("Close - Good");
		}
		else
		{
			GetDlgItem(IDC_STATIC_CAPTURED)->SetWindowText("Close - Bad");		
		}
	}

	//Delete the object
	if( m_pvgcam != NULL )
	{
		delete m_pvgcam;
		m_pvgcam = NULL;
	}
}

/******************************************************************************
* FUNCTION		 OnBnClickedOk()
* DESCRIPTION:   Close application
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CSingleCam_ClassDlg::OnBnClickedOk()
{
	if( m_pvgcam != NULL )
	{
		AfxMessageBox(_T("Frist, Close device\n"));
		return;
	}

	if( m_pvwGigE != NULL )
	{
		CloseVwGigE(m_pvwGigE);
		m_pvwGigE = NULL;
	}

	DestroyWindow();
}

/******************************************************************************
* FUNCTION		 OnTvnSelchangedTreeDeviceList()
* DESCRIPTION:   Get selected interface handle and Device.
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CSingleCam_ClassDlg::OnTvnSelchangedTreeDeviceList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	*pResult = 0;

	HTREEITEM parentNode  = m_deviceListTree.GetParentItem(pNMTreeView->itemNew.hItem);
	if( parentNode == NULL )
	{
		m_pSelectedIFhandle   =  0;
		m_nSeletecDeviceIndex = -1;
		return;
	}

	//This is NIC handle
	m_pSelectedIFhandle   = m_deviceListTree.GetItemData(parentNode);
	//This is the camera index
	//Because one NIC can have a lot of cameras.
	m_nSeletecDeviceIndex = (INT)m_deviceListTree.GetItemData(pNMTreeView->itemNew.hItem);
}

/******************************************************************************
* FUNCTION		 PreTranslateMessage()
* DESCRIPTION:   Exception - Return , Escape , Space key
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CSingleCam_ClassDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

/******************************************************************************
* FUNCTION		 OnBnClickedButtonSoftwareTrigger()
* DESCRIPTION:   
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CSingleCam_ClassDlg::OnBnClickedButtonSoftwareTrigger()
{
	if( m_pvgcam != NULL && m_pvgcam->GetDeviceHandle() != NULL )
	{
		if( m_pvgcam->SendSoftwareTrigger() == TRUE )
		{
			GetDlgItem(IDC_STATIC_CAPTURED)->SetWindowText("S/W Trigger - Good");
		}
		else
		{
			GetDlgItem(IDC_STATIC_CAPTURED)->SetWindowText("S/W Trigger - Bad");
		}
	}
}

/******************************************************************************
* FUNCTION		 OnBnClickedButtonWriteCommand()
* DESCRIPTION:   
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CSingleCam_ClassDlg::OnBnClickedButtonWriteCommand()
{
	CString strvalue1;
	CString strvalue2;

	GetDlgItem(IDC_EDIT_COMMAND)->GetWindowText(strvalue1);
	GetDlgItem(IDC_EDIT_VALUE  )->GetWindowText(strvalue2);

	if( m_pvgcam != NULL && m_pvgcam->GetDeviceHandle() != NULL )
	{
		if( m_pvgcam->SetCustomCommand(strvalue1.GetBuffer(),strvalue2.GetBuffer()) == TRUE )
		{

		}
		else
		{
			GetDlgItem(IDC_EDIT_COMMAND)->SetWindowText(_T("0"));
		}
	}
}

/******************************************************************************
* FUNCTION		 OnBnClickedButtonReadCommand()
* DESCRIPTION:   
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CSingleCam_ClassDlg::OnBnClickedButtonReadCommand()
{
	CString strvalue1;
	CString strvalue2;

	GetDlgItem(IDC_EDIT_COMMAND)->GetWindowText(strvalue1);

	if( m_pvgcam != NULL && m_pvgcam->GetDeviceHandle() != NULL )
	{
		CHAR returnstr[256] = {0,};
		if( m_pvgcam->GetCustomCommand(strvalue1.GetBuffer(),returnstr) == TRUE )
		{
			strvalue2.Format(_T("%s"),returnstr);
			GetDlgItem(IDC_EDIT_VALUE)->SetWindowText(strvalue2);
		}
		else
		{
			GetDlgItem(IDC_EDIT_VALUE)->SetWindowText(_T("0"));
		}
	}
}



LRESULT CSingleCam_ClassDlg::OnComm(WPARAM ch, LPARAM port)
{
	CString str;
	str.Format(_T("%c"), ch);

	if (str == "1")
	{
		//MessageBox("接收数据1成功！");
		//CString str3 = "3";
		//m_SerialPort.WriteToPort((LPCTSTR)str3);

		//cvWaitKey(5000);
		//int num = atoi(str);
		//ImageShow(num);

		zu++;

		int num = 1;

		while (num != 6)
		{
			char filename[100];

			sprintf(filename, "红绿蓝黑白\\%d.jpg", num);// 将图片以数字命名：例如1.jpg 2.jpg等，放入D:/test/文件夹下

			IplImage* src = cvLoadImage(filename, 1);//导入图片
			if (!src)
			{
				MessageBox("读取图片出错！");
			}

			cvNamedWindow("src", CV_WND_PROP_FULLSCREEN);
			cvSetWindowProperty("src", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
			cvShowImage("src", src);
			ShowCursor(FALSE);//隐藏原来的光标


			char savepath[100];
			char savename[100];
			//char FolderName[100];
			sprintf(FolderName, "D:\\Save\\%d", zu);
			int state = mkdir(FolderName);
			sprintf(savename, "%d.bmp", num);
			strcat(FolderName, "\\");
			strcat(FolderName, savename);

			

			//cvSaveImage(FolderName, pcvImage);

			//cvSaveImage(FolderName, src);
			cvWaitKey(2000);
			//OnBnClickedButtonPlay();
			//cvWaitKey(2000);
			//OnBnClickedButtonStop();
			OnBnClickedButtonSoftwareTrigger();
			cvWaitKey(1000);
			//OnBnClickedButtonStop();

			cvReleaseImage(&src);
			cvDestroyWindow("src");
			ShowCursor(TRUE);//显示新的光标
			num++;
		}


		//MessageBox("该组照片拍摄完毕，请更换显示屏继续下一组拍摄！");
		CString str2 = "2";
		m_SerialPort.WriteToPort((LPCTSTR)str2);

	}
	/*if (str == "3")
	{
	MessageBox("接收数据3成功！");
	}*/
	//cvWaitKey(100);

	//if (str == "3")
	//{
	//	MessageBox("接收数据3成功！");
	//}
	return 0;
}

