#pragma once

#include "VwGigE.API.h"
using namespace VWSDK;
class CVWGigECamera
{
public:
	CVWGigECamera(void);
	~CVWGigECamera(void);

	// MEMBER DATA---------------------------------------------------------------------------------------
private:
	HINTERFACE				   m_pInterface;
	VWGIGE_HANDLE			   m_pvwGigE;
	UINT					   m_nCamIndex;
	HCAMERA					   m_pCamera;
	OBJECT_INFO*			   m_pObjectInfo;
	BYTE*					   m_pUnpackedImage;
	UINT					   m_imagebuffernumber;
	PVOID					   m_pcapturedpBase;

private:
	void					   MakeUnPackedBuffer();

public:
	BOOL 					   InitDevice(void*			pInterfaceHanlde,		//Interface Handle
										  VWGIGE_HANDLE pvwGigE,				//GigE Handle.
										  UINT			nCamIndex,				//Camera index
										  void		   *pParent,				//Parent Pointer
							   			  UINT			nBufferNum,				//Buffer Number
										  UINT			packetsize,				//Pixel format
										  void		   *pFnCallback1,			//Image captured callback function	
										  void		   *pFnCallback2			//Disconnection callback function
										  );	

	BOOL 					   CloseDevice();									//Close device
	BOOL					   Start();											//Start to grab image					          
	BOOL					   Stop();											//Stop to grab image
	BOOL					   SetPixelFormat(PIXEL_FORMAT format);				//Set Pixel Format
	void					   SetRawBufferData(void *pbuffer);					//Set raw image data
	BOOL					   SetTriggerMode(CHAR* strvalue);					//Off, On
	BOOL				       SetTriggerSource(CHAR* strvalue);				//External, Software
	BOOL					   SetExposureMode(CHAR* strvalue);					//Timed, Triggerwidth
	BOOL					   SetExposureTime(CHAR* strvaluee);				//Set exposure time - us
	BOOL					   SetGain(CHAR* strvalue);							//Set Gain
	BOOL					   SendSoftwareTrigger(VOID);						//Send software trigger. Software trigger only works with Timed mode.
	BOOL					   SetInterpacketDelay(CHAR* strvalue);				//Set inter-packet delay (Unit - Tick)
	BOOL					   SetTestImageSelector(CHAR* strvalue);			//SetTestImageSelector(0,1,2,3)
	BOOL  					   SetStreamHold(CHAR* strvalue);					//Set StreamHold enable or disable
	BOOL					   SetBinningHorizontal(CHAR* strvalue);			//Binning Horizontal : 1,2,3,4,8
	BOOL					   SetBinningVertical(CHAR* strvalue);				//Binning Vertical   : 1,2,3,4,8
	BOOL					   SetAOISize(CHAR* OffsetX,CHAR* OffsetY,CHAR* width,CHAR* height); //Set AOI size
	BOOL					   SetEventSelector(CHAR* strvalue);				//EventSelector : ExposureEnd
	BOOL					   SetEventNotification(CHAR* strvalue);			//EventNotification control : Off,On
	BOOL					   SetDevSetEventControl(const char* sEventName,	//Event  Callback
													 size_t	     szEventName, 
													 void*	     pEventCallback );
	BOOL					   SetCustomCommand(CHAR* nodename,CHAR* value);	//Set node value.

	UINT  					   GetFrameCapacity(VOID);							//Get frame number to be saved.
	void*					   GetRawBufferData();								//Get raw image data
	PIXEL_FORMAT			   GetPixelFormat();								//Get pixel format : 8(8bit) , 10(10bit) , 12(12bit) , RG8 , GR8 ( From buffer )
	void*					   GetDeviceHandle(void) { return m_pCamera; }		//Get device handle
	void*					   GetBufferDataForDisplay(UINT width,UINT height,PIXEL_FORMAT pixelFormat,void *pbuffer); //Get Image data (BGR8 Format)
	UINT					   GetCameraWidth();								//Get Buffer Width
	UINT					   GetCameraHeight();								//Get Buffer Height
	UINT 					   GetTestImageSelector(VOID);						//GetTestImageSelector(0,1,2,3)
	UINT					   GetMaxImageWidth();								//Get Image width (Full resolution image)
	UINT					   GetMaxImageHeight();								//Get image height(Full resolution image)
	UINT					   GetInterpacketDelay(VOID);						//Get inter-packet delay (Unit - Tick)
	BOOL					   GetCustomCommand(CHAR* nodename,CHAR* returnstr);//Get node value	
	BOOL					   GetCustomCommandMin(CHAR* nodename, CHAR* returnstr);//Get MIN value
	BOOL					   GetCustomCommandMax(CHAR* nodename, CHAR* returnstr);//Get MAX value

	void					   ConvertMonoPackedToBGR8	      ( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst			      );
	void					   ConvertMono12PackedToMono16bit ( const BYTE* pbSrc, UINT widht,  UINT height, BYTE* pbDst  );
	void					   ConvertMono12PackedToMono16bit1( const BYTE* pbSrc, UINT widht,  UINT height, BYTE* pbDst  );
	void					   ConvertMono12PackedToMono8bit  ( const BYTE* pbSrc, UINT widht,  UINT height, BYTE* pbDst  );
	void					   ConvertMono10PackedToMono16bit ( const BYTE* pbSrc, UINT widht,  UINT height, BYTE* pbDst  );
	void					   ConvertMono10PackedToMono16bit1( const BYTE* pbSrc, UINT widht,  UINT height, BYTE* pbDst  );
	void					   ConvertMono10PackedToMono8bit  ( const BYTE* pbSrc, UINT widht,  UINT height, BYTE* pbDst  );
	void					   ConvertMono8ToMono16bit	      ( const BYTE* pbSrc, UINT widht,  UINT height, BYTE* pbDst  );
	void					   ConvertMono8ToMono16bit1	      ( const BYTE* pbSrc, UINT widht,  UINT height, BYTE* pbDst  );	
	void					   ConvertBAYRG8ToBGR8		      ( const BYTE* pbSrc, BYTE* pbDst, DWORD width, DWORD height );
	void					   ConvertBAYGR8ToBGR8		      ( const BYTE* pbSrc, BYTE* pbDst, DWORD width, DWORD height );
	void					   ConvertRG10ToBGR8			  ( const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height );
	void					   ConvertGR10ToBGR8			  ( const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height );
	void					   ConvertRG12ToBGR8			  ( const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height );
	void					   ConvertGR12ToBGR8			  ( const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height );
};
