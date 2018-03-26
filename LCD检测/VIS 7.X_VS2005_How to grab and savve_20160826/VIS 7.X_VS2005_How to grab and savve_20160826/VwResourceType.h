#pragma once

#include "vwgige.Global.h"
using namespace VWSDK;

class CVwResourceType
{
	// constructor
	CVwResourceType();

	// destructor
	~CVwResourceType();

public:
	static CString GetPixelFormatName( PIXEL_FORMAT ePixelFormat );
	static BOOL ConvertPixelFormat( PIXEL_FORMAT ePixelFormat, BYTE* pDest, BYTE* pSource, int nWidth, int nHeight );
	static int GetPixelBitCount( PIXEL_FORMAT ePixelFormat );
};
