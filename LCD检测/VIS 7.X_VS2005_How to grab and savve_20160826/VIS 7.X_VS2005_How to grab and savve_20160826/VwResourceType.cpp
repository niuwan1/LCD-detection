#include "stdafx.h"
#include "VwResourceType.h"
#include "VwGigE.API.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Constructor
CVwResourceType::CVwResourceType()
{

}

// Destructor
CVwResourceType::~CVwResourceType()
{
}

CString CVwResourceType::GetPixelFormatName( PIXEL_FORMAT ePixelFormat )
{
	CString strTmp;

	switch( ePixelFormat )
	{
	case PIXEL_FORMAT_MONO8:
		strTmp = _T("Mono8");
		break;
	case PIXEL_FORMAT_MONO8_SIGNED:
		strTmp = _T("Mono8signed");
		break;
	case PIXEL_FORMAT_MONO10:
		strTmp = _T("Mono10");
		break;
	case PIXEL_FORMAT_MONO10_PACKED:
		strTmp = _T("Mono10Packed");
		break;
	case PIXEL_FORMAT_MONO12:
		strTmp = _T("Mono12");
		break;
	case PIXEL_FORMAT_MONO12_PACKED:
		strTmp = _T("Mono12Packed");
		break;
	case PIXEL_FORMAT_MONO16:
		strTmp = _T("Mono16");
		break;
	case PIXEL_FORMAT_BAYGR8:
		strTmp = _T("BayerGR8");
		break;
	case PIXEL_FORMAT_BAYRG8:
		strTmp = _T("BayerRG8");
		break;
	case PIXEL_FORMAT_BAYGB8:
		strTmp = _T("BayerGB8");
		break;
	case PIXEL_FORMAT_BAYBG8:
		strTmp = _T("BayerBG8");
		break;
	case PIXEL_FORMAT_BAYGR10:
		strTmp = _T("BayerGR10");
		break;
	case PIXEL_FORMAT_BAYRG10:
		strTmp = _T("BayerRG10");
		break;
	case PIXEL_FORMAT_BAYGB10:
		strTmp = _T("BayerGB10");
		break;
	case PIXEL_FORMAT_BAYBG10:
		strTmp = _T("BayerBG10");
		break;
	case PIXEL_FORMAT_BAYGR10_PACKED:
		strTmp = _T("BayerGR10Packed");
		break;
	case PIXEL_FORMAT_BAYRG10_PACKED:
		strTmp = _T("BayerRG10Packed");
		break;
	case PIXEL_FORMAT_BAYGR12:
		strTmp = _T("BayerGR12");
		break;
	case PIXEL_FORMAT_BAYRG12:
		strTmp = _T("BayerRG12");
		break;
	case PIXEL_FORMAT_BAYGB12:
		strTmp = _T("BayerGB12");
		break;
	case PIXEL_FORMAT_BAYBG12:
		strTmp = _T("BayerBG12");
		break;
	case PIXEL_FORMAT_BAYRG12_PACKED:
		strTmp = _T("BayerRG12Packed");
		break;
	case PIXEL_FORMAT_BAYGR12_PACKED:
		strTmp = _T("BayerGR12Packed");
		break;	
	case PIXEL_FORMAT_RGB8_PACKED:
		strTmp = _T("RGB8Packed");
		break;
	case PIXEL_FORMAT_BGR8_PACKED:
		strTmp = _T("BGR8Packed");
		break;
	case PIXEL_FORMAT_YUV422_UYVY:
		strTmp = _T("YUV422Packed");
		break;
	case PIXEL_FORMAT_YUV422_YUYV:
		strTmp = _T("YUV422YUVYPacked");
		break;
	case PIXEL_FORMAT_YUV422_10_PACKED:
		strTmp = _T("YUV42210Packed");
		break;
	case PIXEL_FORMAT_YUV422_12_PACKED:
		strTmp = _T("YUV42212Packed");
		break;
	case PIXEL_FORMAT_YUV411:
		strTmp = _T("YUV411");
		break;
	case PIXEL_FORMAT_YUV411_10_PACKED:
		strTmp = _T("YUV41110Packed");
		break;
	case PIXEL_FORMAT_YUV411_12_PACKED:
		strTmp = _T("YUV41112Packed");
		break;
	case PIXEL_FORMAT_BGR10V1_PACKED:
		strTmp = _T("BGR10V1Packed");
		break;
	case PIXEL_FORMAT_BGR10V2_PACKED:
		strTmp = _T("BGR10V2Packed");
		break;
	case PIXEL_FORMAT_RGB12_PACKED:
		strTmp = _T("RGB12Packed");
		break;
	case PIXEL_FORMAT_BGR12_PACKED:
		strTmp = _T("BGR12Packed");
		break;
	case PIXEL_FORMAT_YUV444:
		strTmp = _T("YUV444");
		break;
	case PIXEL_FORMAT_PAL_INTERLACED:
		strTmp = _T("PALInterlaced");
		break;
	case PIXEL_FORMAT_NTSC_INTERLACED:
		strTmp = _T("NTSCInterlaced");
		break;
	default:
		strTmp = _T("Unrecognized pixel format\n");
	}

	return strTmp;
}

BOOL CVwResourceType::ConvertPixelFormat( PIXEL_FORMAT ePixelFormat, BYTE* pDest, BYTE* pSource, int nWidth, int nHeight )
{
	if ( NULL == pDest ||
		 NULL == pSource )
	{
		return FALSE;
	}
	
	if ( 0 == nWidth || 0 == nHeight )
	{
		return FALSE;
	}

	BOOL bRet				   = TRUE;
	BYTE* bpConvertPixelFormat = NULL;

	switch( ePixelFormat )
	{
		//-----------------------------------------------------------------
		// about MONO Pixel Format Series ---------------------------------
		//-----------------------------------------------------------------
	case PIXEL_FORMAT_MONO8:
		memcpy( pDest, pSource, nWidth * nHeight );
		break;
	case PIXEL_FORMAT_MONO10:
		ConvertMono10ToBGR8(PBYTE(pSource), nWidth*nHeight*2, pDest);
		break;
	case PIXEL_FORMAT_MONO12:
		ConvertMono12ToBGR8(PBYTE(pSource), nWidth*nHeight*2, pDest);
		break;
	case PIXEL_FORMAT_MONO10_PACKED:
	case PIXEL_FORMAT_MONO12_PACKED:
		ConvertMonoPackedToBGR8( pSource,
												UINT(1.5*nWidth*nHeight),
												pDest );
		break;
	case PIXEL_FORMAT_MONO16:
		ConvertMono16PackedToBGR8( pSource,
												UINT(2*nWidth*nHeight),
												pDest );
		break;
		//-----------------------------------------------------------------
		// about BAYER Pixel Format Series --------------------------------
		//-----------------------------------------------------------------
	case PIXEL_FORMAT_BAYGR8:
		ConvertBAYGR8ToBGR8( pSource,
											pDest,
											nWidth,
											nHeight );
		break;
	case PIXEL_FORMAT_BAYRG8:
		ConvertBAYRG8ToBGR8( pSource,
											pDest,
											nWidth,
											nHeight );
		break;
	case PIXEL_FORMAT_BAYGR10:
		ConvertBAYGR10ToBGR8( (WORD*)(pSource),
											pDest,
											nWidth,
											nHeight );
		break;
	case PIXEL_FORMAT_BAYRG10:
		ConvertBAYRG10ToBGR8( (WORD*)(pSource),
											pDest,
											nWidth,
											nHeight );
		break;
	case PIXEL_FORMAT_BAYGR12:
		ConvertBAYGR12ToBGR8( (WORD*)(pSource),
											pDest,
											nWidth,
											nHeight );
		break;
	case PIXEL_FORMAT_BAYRG12:
		ConvertBAYRG12ToBGR8( (WORD*)(pSource),
											pDest,
											nWidth,
											nHeight );
		break;
	case PIXEL_FORMAT_BAYGR10_PACKED:
		bpConvertPixelFormat =	new BYTE[ nWidth * nHeight * 2 ];
		ConvertMono10PackedToMono16bit( (PBYTE)pSource,
														nWidth,
														nHeight,
														bpConvertPixelFormat );
		ConvertBAYGR10ToBGR8( (WORD*)bpConvertPixelFormat,
												pDest,
												nWidth,
												nHeight );
		break;
	case PIXEL_FORMAT_BAYRG10_PACKED:
		bpConvertPixelFormat =	new BYTE[ nWidth * nHeight * 2 ];
		ConvertMono10PackedToMono16bit( (PBYTE)pSource,
														nWidth,
														nHeight,
														bpConvertPixelFormat );
		ConvertBAYRG10ToBGR8( (WORD*)bpConvertPixelFormat,
												pDest,
												nWidth,
												nHeight );
		break;
	case PIXEL_FORMAT_BAYGR12_PACKED:
		bpConvertPixelFormat =	new BYTE[ nWidth * nHeight * 2 ];
		ConvertMono12PackedToMono16bit( (PBYTE)pSource,
														nWidth,
														nHeight,
														bpConvertPixelFormat );
		ConvertBAYGR12ToBGR8( (WORD*)bpConvertPixelFormat,
												pDest,
												nWidth,
												nHeight );
		break;
	case PIXEL_FORMAT_BAYRG12_PACKED:
		bpConvertPixelFormat =	new BYTE[ nWidth * nHeight * 2 ];
		ConvertMono12PackedToMono16bit( (PBYTE)pSource,
														nWidth,
														nHeight,
														bpConvertPixelFormat );
		ConvertBAYRG12ToBGR8( (WORD*)bpConvertPixelFormat,
													pDest,
													nWidth,
													nHeight );
		break;
	case PIXEL_FORMAT_RGB8_PACKED:
		ConvertRGB8toBGR8( (PBYTE)pSource,
											UINT(3*nWidth*nHeight),
											pDest );
		break;
	case PIXEL_FORMAT_BGR8_PACKED:
		bRet = FALSE;
		break;
	case PIXEL_FORMAT_RGB12_PACKED:
		ConvertRGB12PackedtoBGR8( (PBYTE)pSource,
												UINT(6*nWidth*nHeight),
												pDest );
		break;
	case PIXEL_FORMAT_BGR12_PACKED:
		bRet = FALSE;
		break;
	case PIXEL_FORMAT_YUV411:
		ConvertYUV411toBGR8( (PBYTE)pSource,
											UINT(1.5*nWidth*nHeight),
											pDest );
		break;
	case PIXEL_FORMAT_YUV422_UYVY:
		ConvertYUV422_UYVYtoBGR8( (PBYTE)pSource,
												nWidth,
												nHeight,
												pDest );
		break;
	case PIXEL_FORMAT_YUV422_YUYV:
		ConvertYUV422_YUYVtoBGR8( (PBYTE)pSource,
												nWidth,
												nHeight,
												pDest );
		break;
	case PIXEL_FORMAT_YUV444:
		ConvertYUV444toBGR8( (PBYTE)pSource,
											UINT(1.5*nWidth*nHeight),
											pDest );
		break;
	case PIXEL_FORMAT_BGR10V1_PACKED:
		bRet = FALSE;
		break;
	case PIXEL_FORMAT_YUV411_10_PACKED:
	case PIXEL_FORMAT_YUV411_12_PACKED:
		ConvertYUV411PackedtoBGR8( (PBYTE)pSource,
													UINT(2.25*nWidth*nHeight),
													pDest );
		break;
	case PIXEL_FORMAT_YUV422_10_PACKED:
	case PIXEL_FORMAT_YUV422_12_PACKED:
		ConvertYUV422PackedtoBGR8( (PBYTE)pSource,
													UINT(3*nWidth*nHeight),
													pDest );
		break;
	case PIXEL_FORMAT_PAL_INTERLACED:
	case PIXEL_FORMAT_NTSC_INTERLACED:
		break;
	default:
		{
			bRet = FALSE;
		}
	}

	if ( NULL != bpConvertPixelFormat )
	{
		delete [] bpConvertPixelFormat;
	}
	
	return bRet;
}

int CVwResourceType::GetPixelBitCount( PIXEL_FORMAT ePixelFormat )
{
	int nRet = 0;
	switch( ePixelFormat )
	{
		//-----------------------------------------------------------------
		// about MONO Pixel Format Series ---------------------------------
		//-----------------------------------------------------------------
	case PIXEL_FORMAT_MONO8:
		nRet	=	8;
		break;
	case PIXEL_FORMAT_MONO10:
	case PIXEL_FORMAT_MONO12:
	case PIXEL_FORMAT_MONO10_PACKED:
	case PIXEL_FORMAT_MONO12_PACKED:
	case PIXEL_FORMAT_MONO16:
		nRet	=	24;
		break;
		//-----------------------------------------------------------------
		// about BAYER Pixel Format Series --------------------------------
		//-----------------------------------------------------------------
	case PIXEL_FORMAT_BAYGR8:
	case PIXEL_FORMAT_BAYRG8:
	case PIXEL_FORMAT_BAYGR10:
	case PIXEL_FORMAT_BAYRG10:
	case PIXEL_FORMAT_BAYGR12:
	case PIXEL_FORMAT_BAYRG12:
	case PIXEL_FORMAT_BAYGR10_PACKED:
	case PIXEL_FORMAT_BAYRG10_PACKED:
	case PIXEL_FORMAT_BAYGR12_PACKED:
	case PIXEL_FORMAT_BAYRG12_PACKED:
		nRet	=	24;
		break;
	case PIXEL_FORMAT_RGB8_PACKED:
	case PIXEL_FORMAT_BGR8_PACKED:
	case PIXEL_FORMAT_RGB12_PACKED:
	case PIXEL_FORMAT_BGR12_PACKED:
		nRet	=	24;
		break;
	case PIXEL_FORMAT_BGR10V2_PACKED:
		nRet	=	24;
		break;
	case PIXEL_FORMAT_YUV411:
	case PIXEL_FORMAT_YUV422_UYVY:
	case PIXEL_FORMAT_YUV422_YUYV:
	case PIXEL_FORMAT_YUV444:
		nRet	=	24;
		break;
	case PIXEL_FORMAT_BGR10V1_PACKED:
		nRet	=	32;
		break;
	case PIXEL_FORMAT_YUV411_10_PACKED:
	case PIXEL_FORMAT_YUV411_12_PACKED:
	case PIXEL_FORMAT_YUV422_10_PACKED:
	case PIXEL_FORMAT_YUV422_12_PACKED:
		nRet	=	24;
		break;
	case PIXEL_FORMAT_PAL_INTERLACED:
	case PIXEL_FORMAT_NTSC_INTERLACED:
		nRet	=	24;
		break;
	default:
		{
		}
	}

	return nRet;
}