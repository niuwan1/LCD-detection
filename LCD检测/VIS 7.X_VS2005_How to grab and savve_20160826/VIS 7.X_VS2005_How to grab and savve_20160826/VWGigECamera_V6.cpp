#include "stdafx.h"
#include "VWGigECamera_V6.h"
#include "VwResourceType.h"

/******************************************************************************
* FUNCTION		ConvertMonoPackedToBGR8()
* DESCRIPTION:  Mono 8,12 packed -> BHR8 for display
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CVWGigECamera::ConvertMonoPackedToBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst )
{
	for(DWORD i = 0; i < cbSrc; i += 3)
	{
		*pbDst++ = *pbSrc;
		*pbDst++ = *pbSrc;
		*pbDst++ = *pbSrc;
		pbSrc += 2;
		*pbDst++ = *pbSrc;
		*pbDst++ = *pbSrc;
		*pbDst++ = *pbSrc; 
		pbSrc++;
	}
}

/******************************************************************************
* FUNCTION		ConvertMono12PackedToMono16bit()
* DESCRIPTION:  Mono12 packed -> Mono 16bit
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CVWGigECamera::ConvertMono12PackedToMono16bit( const BYTE* pbSrc, UINT widht, UINT height, BYTE* pbDst )
{
	BYTE data = 0;
	int count = 1;

	//Upper 4bit -> Zero.
	for(int i=0;i < widht*height*1.5 ;i=i+3)				
	{
		pbDst[count + i]	  = (pbSrc[i  ] & 0xF0) >> 4;
		data				  =  pbSrc[i+1] & 0x0F;
		pbDst[count + i - 1]  =  data; 
		data				  = (pbSrc[i  ] & 0x0F) << 4;
		pbDst[count + i - 1]  =  pbDst[count+i-1   ] | data;

		pbDst[count + i + 2]  = (pbSrc[i+2] & 0xF0) >> 4;
		data				  = (pbSrc[i+1] & 0xF0) >> 4;
		pbDst[count + i + 1]  =  data; 
		data				  = (pbSrc[i+2] & 0x0F) << 4;
		pbDst[count + i + 1]  =  pbDst[count+i+1   ] | data;

		count++;
	}
}

/******************************************************************************
* FUNCTION		ConvertMono12PackedToMono16bit1()
* DESCRIPTION:  Mono12 packed -> Mono 16bit
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CVWGigECamera::ConvertMono12PackedToMono16bit1( const BYTE* pbSrc, UINT widht, UINT height, BYTE* pbDst )
{
	BYTE data = 0;
	int count = 1;

	//Lower 4bit -> Zero.
	for(int i=0;i < widht*height*1.5 ;i=i+3)				
	{
		pbDst[count + i]	  =  pbSrc[i  ];
		data				  = (pbSrc[i+1] & 0x0F)<< 4;
		pbDst[count + i - 1]  =  data; 

		pbDst[count + i + 2]  =  pbSrc[i+2];
		pbDst[count + i + 1]  =  pbSrc[i+1] & 0xF0;

		count++;
	}
}

/******************************************************************************
* FUNCTION		ConvertMono12PackedToMono8bit()
* DESCRIPTION:  Mono12 packed -> Mono 8
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CVWGigECamera::ConvertMono12PackedToMono8bit  ( const BYTE* pbSrc, UINT widht,  UINT height, BYTE* pbDst  )
{
	for(int i=0;i < widht*height*1.5 ;i=i+3)				
	{
		pbDst[i-i/3  ]  =  pbSrc[i  ];
		pbDst[i-i/3+1]  =  pbSrc[i+2];
	}
}

/******************************************************************************
* FUNCTION		ConvertMono10PackedToMono16bit()
* DESCRIPTION:  Mono10 packed -> Mono 16bit
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CVWGigECamera::ConvertMono10PackedToMono16bit( const BYTE* pbSrc, UINT widht, UINT height, BYTE* pbDst )
{
	BYTE data = 0;
	int count = 1;

	//Upper 6bit -> Zero.
	for(int i=0;i < widht*height*1.5 ;i=i+3)				
	{
		pbDst[count + i]	 = (pbSrc[i  ] & 0xC0) >> 6;
		data				 =  pbSrc[i+1] & 0x03;
		pbDst[count + i - 1] =  data; 
		data				 = (pbSrc[i  ] & 0x3F) << 2;
		pbDst[count + i - 1] =  pbDst[count+i-1   ] | data;

		pbDst[count + i + 2] = (pbSrc[i+2] & 0xC0) >> 6;
		data				 = (pbSrc[i+1] & 0x30) >> 4;
		pbDst[count + i + 1] =  data; 
		data				 = (pbSrc[i+2] & 0x3F) << 2;
		pbDst[count + i + 1] =  pbDst[count+i+1   ] | data;

		count++;
	}	
}

/******************************************************************************
* FUNCTION		ConvertMono10PackedToMono16bit()
* DESCRIPTION:  Mono10 packed -> Mono 16bit
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CVWGigECamera::ConvertMono10PackedToMono16bit1( const BYTE* pbSrc, UINT widht, UINT height, BYTE* pbDst )
{
	BYTE data = 0;
	int count = 1;

	//Lower 6bit -> Zero.
	for(int i=0;i < widht*height*1.5 ;i=i+3)				
	{
		pbDst[count + i]	  =  pbSrc[i  ];
		data				  = (pbSrc[i+1] & 0x03) << 6;
		pbDst[count + i - 1]  =  data; 

		pbDst[count + i + 2]  =  pbSrc[i+2];
		pbDst[count + i + 1]  =  pbSrc[i+1] & 0xC0;

		count++;
	}
}

/******************************************************************************
* FUNCTION		ConvertMono10PackedToMono8bit()
* DESCRIPTION:  Mono10 packed -> Mono 8
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CVWGigECamera::ConvertMono10PackedToMono8bit  ( const BYTE* pbSrc, UINT widht,  UINT height, BYTE* pbDst  )
{
	for(int i=0;i < widht*height*1.5 ;i=i+3)				
	{
		pbDst[i-i/3  ]  =  pbSrc[i  ];
		pbDst[i-i/3+1]  =  pbSrc[i+2];
	}
}

/******************************************************************************
* FUNCTION		ConvertMono8ToMono16bit()
* DESCRIPTION:  Mono8 -> Mono 16bit
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CVWGigECamera::ConvertMono8ToMono16bit( const BYTE* pbSrc, UINT widht, UINT height, BYTE* pbDst )
{
	//Upper 1byte -> zero
	for(UINT i=0;i < widht*height ;i++)						
	{
		pbDst[i*2	 ] = pbSrc[i];
		pbDst[i*2 + 1] = 0;
	}
}

/******************************************************************************
* FUNCTION		ConvertMono8ToMono16bit1()
* DESCRIPTION:  Mono8 -> Mono 16bit
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CVWGigECamera::ConvertMono8ToMono16bit1( const BYTE* pbSrc, UINT widht, UINT height, BYTE* pbDst )
{
	//Lower 1byte -> zero
	for(UINT i=0;i < widht*height ;i++)						
	{
		pbDst[i*2 + 1] = pbSrc[i];
		pbDst[i*2    ] = 0;
	}
}

#define SELF			BYTE(*pbSrc)
#define RIGHT			BYTE(*(pbSrc+1))
#define LEFT			BYTE(*(pbSrc-1))
#define ABOVE			BYTE(*(pbSrc-width))
#define BELOW			BYTE(*(pbSrc+width))
#define ABOVELEFT		BYTE(*(pbSrc-width-1))
#define ABOVERIGHT		BYTE(*(pbSrc-width+1))
#define BELOWLEFT		BYTE(*(pbSrc+width-1))
#define BELOWRIGHT		BYTE(*(pbSrc+width+1))
#define AVG2(a,b)		((BYTE)((DWORD(a)+DWORD(b))/2))
#define AVG3(a,b,c)		((BYTE)((DWORD(a)+DWORD(b)+DWORD(c))/3))
#define AVG4(a,b,c,d)	((BYTE)((DWORD(a)+DWORD(b)+DWORD(c)+DWORD(d))/4))

/******************************************************************************
* FUNCTION		ConvertBAYRG8ToBGR8()
* DESCRIPTION:  
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CVWGigECamera::ConvertBAYRG8ToBGR8(const BYTE* pbSrc, BYTE* pbDst, DWORD width, DWORD height)
{
	//BYTE* pbDst = pbDst + (height - 1) * width * 3;
	*pbDst++ = BELOWRIGHT;
	*pbDst++ = AVG2(RIGHT,BELOW);
	*pbDst++ = SELF;
	pbSrc++;

	DWORD x = 1;
	for( x = 1; x < width-1; x += 2)
	{
		*pbDst++ = BELOW;
		*pbDst++ = SELF;
		*pbDst++ = AVG2(LEFT,RIGHT);
		pbSrc++;
		*pbDst++ = AVG2(BELOWLEFT,BELOWRIGHT);
		*pbDst++ = AVG3(LEFT,RIGHT,BELOW);
		*pbDst++ = SELF;
		pbSrc++;
	}
	*pbDst++ = BELOW;
	*pbDst++ = SELF;
	*pbDst++ = LEFT;
	pbSrc++;
	for(DWORD y = 1; y < height-1; y += 2)
	{
		//pbDst = pbDst + (height - y - 1) * width * 3;
		*pbDst++ = RIGHT;
		*pbDst++ = SELF;
		*pbDst++ = AVG2(ABOVE,BELOW);
		pbSrc++;
		for(x = 1; x < width-1; x += 2)
		{
			*pbDst++ = SELF;
			*pbDst++ = AVG4(ABOVE,BELOW,LEFT,RIGHT);
			*pbDst++ = AVG4(ABOVELEFT,ABOVERIGHT,BELOWLEFT,BELOWRIGHT);
			pbSrc++;
			*pbDst++ = AVG2(LEFT,RIGHT);
			*pbDst++ = SELF;
			*pbDst++ = AVG2(ABOVE,BELOW);
			pbSrc++;
		}
		*pbDst++ = SELF;
		*pbDst++ = AVG2(ABOVE,BELOW);
		*pbDst++ = AVG2(ABOVELEFT,BELOWLEFT);
		pbSrc++;
		//pbDst = pbDst + (height - y - 2) * width * 3;
		*pbDst++ = AVG2(ABOVERIGHT,BELOWRIGHT);
		*pbDst++ = AVG3(ABOVE,RIGHT,BELOW);
		*pbDst++ = SELF;
		pbSrc++;

		for(x = 1; x < width-1; x += 2)
		{
			*pbDst++ = AVG2(ABOVE,BELOW);
			*pbDst++ = SELF;
			*pbDst++ = AVG2(LEFT,RIGHT);
			pbSrc++;
			*pbDst++ = AVG4(ABOVELEFT,ABOVERIGHT,BELOWLEFT,BELOWRIGHT);
			*pbDst++ = AVG4(ABOVE,BELOW,LEFT,RIGHT);
			*pbDst++ = SELF;
			pbSrc++;
		}
		*pbDst++ = AVG2(ABOVE,BELOW);
		*pbDst++ = SELF;
		*pbDst++ = LEFT;
		pbSrc++;
	}
	pbDst = pbDst;
	*pbDst++ = RIGHT;
	*pbDst++ = SELF;
	*pbDst++ = ABOVE;
	pbSrc++;

	for(x = 1; x < width-1; x += 2)
	{
		*pbDst++ = SELF;
		*pbDst++ = AVG3(ABOVE,LEFT,RIGHT);
		*pbDst++ = AVG2(ABOVELEFT,ABOVERIGHT);
		pbSrc++;
		*pbDst++ = AVG2(LEFT,RIGHT);
		*pbDst++ = SELF;
		*pbDst++ = ABOVE;
		pbSrc++;
	}
	*pbDst++ = SELF;
	*pbDst++ = AVG2(ABOVE,LEFT);
	*pbDst++ = ABOVELEFT;
	pbSrc++;
}

/******************************************************************************
* FUNCTION		ConvertBAYGR8ToBGR8()
* DESCRIPTION:  
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CVWGigECamera::ConvertBAYGR8ToBGR8(const BYTE* pbSrc, BYTE* pbDst, DWORD width, DWORD height)
{
	//BYTE* pbDst = pbDst + (height - 1) * width * 3;
	*pbDst++ = BELOW;
	*pbDst++ = SELF;
	*pbDst++ = RIGHT;
	pbSrc++;

	DWORD x = 1;
	for( x = 1; x < width-1; x += 2)
	{
		*pbDst++ = AVG2(BELOWLEFT,BELOWRIGHT);
		*pbDst++ = AVG3(LEFT,RIGHT,BELOW);
		*pbDst++ = SELF;
		pbSrc++;
		*pbDst++ = BELOW;
		*pbDst++ = SELF;
		*pbDst++ = AVG2(LEFT,RIGHT);
		pbSrc++;
	}
	*pbDst++ = BELOWLEFT;
	*pbDst++ = AVG2(LEFT,BELOW);;
	*pbDst++ = SELF;
	pbSrc++;
	for(DWORD y = 1; y < height-1; y += 2)
	{
		//pbDst = pbDst + (height - y - 1) * width * 3;
		*pbDst++ = SELF;
		*pbDst++ = AVG3(ABOVE,RIGHT,BELOW);
		*pbDst++ = AVG2(ABOVERIGHT,BELOWRIGHT);
		pbSrc++;

		for(x = 1; x < width-1; x += 2)
		{
			*pbDst++ = AVG2(LEFT,RIGHT);
			*pbDst++ = SELF;
			*pbDst++ = AVG2(ABOVE,BELOW);	
			pbSrc++;
			*pbDst++ = SELF;
			*pbDst++ = AVG4(ABOVE,BELOW,LEFT,RIGHT);
			*pbDst++ = AVG4(ABOVELEFT,ABOVERIGHT,BELOWLEFT,BELOWRIGHT);
			pbSrc++;
		}
		*pbDst++ = LEFT;
		*pbDst++ = SELF;
		*pbDst++ = AVG2(ABOVE,BELOW);
		pbSrc++;
		//pbDst = pbDst + (height - y - 2) * width * 3;
		*pbDst++ = AVG2(ABOVE,BELOW);
		*pbDst++ = SELF;
		*pbDst++ = RIGHT;
		pbSrc++;

		for(x = 1; x < width-1; x += 2)
		{
			*pbDst++ = AVG4(ABOVELEFT,ABOVERIGHT,BELOWLEFT,BELOWRIGHT);
			*pbDst++ = AVG4(ABOVE,BELOW,LEFT,RIGHT);
			*pbDst++ = SELF;
			pbSrc++;
			*pbDst++ = AVG2(ABOVE,BELOW);
			*pbDst++ = SELF;
			*pbDst++ = AVG2(LEFT,RIGHT);
			pbSrc++;
		}
		*pbDst++ = AVG2(BELOWLEFT,ABOVELEFT);
		*pbDst++ = AVG3(ABOVE,BELOW,LEFT);
		*pbDst++ = SELF;
		pbSrc++;
	}
	pbDst = pbDst;
	*pbDst++ = SELF;
	*pbDst++ = AVG2(ABOVE,RIGHT);;
	*pbDst++ = ABOVERIGHT;
	pbSrc++;

	for(x = 1; x < width-1; x += 2)
	{
		*pbDst++ = AVG2(LEFT,RIGHT);
		*pbDst++ = SELF;
		*pbDst++ = ABOVE;
		pbSrc++;
		*pbDst++ = SELF;
		*pbDst++ = AVG3(ABOVE,LEFT,RIGHT);
		*pbDst++ = AVG2(ABOVELEFT,ABOVERIGHT);
		pbSrc++;
	}
	*pbDst++ = LEFT;
	*pbDst++ = SELF;
	*pbDst++ = ABOVE;
	pbSrc++;
}

#undef SELF
#undef RIGHT
#undef LEFT
#undef ABOVE
#undef BELOW
#undef ABOVELEFT
#undef ABOVERIGHT
#undef BELOWLEFT
#undef BELOWRIGHT

#define SELF		BYTE(*pbSrc>>2)
#define RIGHT		BYTE(*(pbSrc+1)>>2)
#define LEFT		BYTE(*(pbSrc-1)>>2)
#define ABOVE		BYTE(*(pbSrc-width)>>2)
#define BELOW		BYTE(*(pbSrc+width)>>2)
#define ABOVELEFT	BYTE(*(pbSrc-width-1)>>2)
#define ABOVERIGHT	BYTE(*(pbSrc-width+1)>>2)
#define BELOWLEFT	BYTE(*(pbSrc+width-1)>>2)
#define BELOWRIGHT	BYTE(*(pbSrc+width+1)>>2)
/******************************************************************************
* FUNCTION		ConvertRG10ToBGR8()
* DESCRIPTION:  
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CVWGigECamera::ConvertRG10ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height)
{
	*pbDst++ = BELOWRIGHT;
	*pbDst++ = AVG2(RIGHT,BELOW);
	*pbDst++ = SELF;
	pbSrc++;

	DWORD x = 1;
	for( x = 1; x < width-1; x += 2)
	{
		*pbDst++ = BELOW;
		*pbDst++ = SELF;
		*pbDst++ = AVG2(LEFT,RIGHT);
		pbSrc++;
		*pbDst++ = AVG2(BELOWLEFT,BELOWRIGHT);
		*pbDst++ = AVG3(LEFT,RIGHT,BELOW);
		*pbDst++ = SELF;
		pbSrc++;
	}

	*pbDst++ = BELOW;
	*pbDst++ = SELF;
	*pbDst++ = LEFT;
	pbSrc++;

	for(DWORD y = 1; y < height-1; y += 2)
	{
		*pbDst++ = RIGHT;
		*pbDst++ = SELF;
		*pbDst++ = AVG2(ABOVE,BELOW);
		pbSrc++;

		for(x = 1; x < width-1; x += 2)
		{
			*pbDst++ = SELF;
			*pbDst++ = AVG4(ABOVE,BELOW,LEFT,RIGHT);
			*pbDst++ = AVG4(ABOVELEFT,ABOVERIGHT,BELOWLEFT,BELOWRIGHT);
			pbSrc++;
			*pbDst++ = AVG2(LEFT,RIGHT);
			*pbDst++ = SELF;
			*pbDst++ = AVG2(ABOVE,BELOW);
			pbSrc++;
		}

		*pbDst++ = SELF;
		*pbDst++ = AVG2(ABOVE,BELOW);
		*pbDst++ = AVG2(ABOVELEFT,BELOWLEFT);
		pbSrc++;

		*pbDst++ = AVG2(ABOVERIGHT,BELOWRIGHT);
		*pbDst++ = AVG3(ABOVE,RIGHT,BELOW);
		*pbDst++ = SELF;
		pbSrc++;

		for(x = 1; x < width-1; x += 2)
		{
			*pbDst++ = AVG2(ABOVE,BELOW);
			*pbDst++ = SELF;
			*pbDst++ = AVG2(LEFT,RIGHT);
			pbSrc++;
			*pbDst++ = AVG4(ABOVELEFT,ABOVERIGHT,BELOWLEFT,BELOWRIGHT);
			*pbDst++ = AVG4(ABOVE,BELOW,LEFT,RIGHT);
			*pbDst++ = SELF;
			pbSrc++;
		}

		*pbDst++ = AVG2(ABOVE,BELOW);
		*pbDst++ = SELF;
		*pbDst++ = LEFT;
		pbSrc++;
	}

/*
RGRGRGRG
GBGBGBGB
RGRGRGRG
GBGBGBGB
RGRGRGRG
GBGBGBGB
*/

	*pbDst++ = RIGHT;
	*pbDst++ = SELF;
	*pbDst++ = ABOVE;
	pbSrc++;

	for(x = 1; x < width-1; x += 2)
	{
		*pbDst++ = SELF;
		*pbDst++ = AVG3(ABOVE,LEFT,RIGHT);
		*pbDst++ = AVG2(ABOVELEFT,ABOVERIGHT);
		pbSrc++;
		*pbDst++ = AVG2(LEFT,RIGHT);
		*pbDst++ = SELF;
		*pbDst++ = ABOVE;
		pbSrc++;
	}

	*pbDst++ = SELF;
	*pbDst++ = AVG2(ABOVE,LEFT);
	*pbDst++ = ABOVELEFT;
	pbSrc++;
}

/******************************************************************************
* FUNCTION		ConvertGR10ToBGR8()
* DESCRIPTION:  
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CVWGigECamera::ConvertGR10ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height)
{
	//BYTE* pbDst = pbDst + (height - 1) * width * 3;
	*pbDst++ = BELOW;
	*pbDst++ = SELF;
	*pbDst++ = RIGHT;
	pbSrc++;

	DWORD x = 1;
	for(  x = 1; x < width-1; x += 2)
	{
		*pbDst++ = AVG2(BELOWLEFT,BELOWRIGHT);
		*pbDst++ = AVG3(LEFT,RIGHT,BELOW);
		*pbDst++ = SELF;
		pbSrc++;
		*pbDst++ = BELOW;
		*pbDst++ = SELF;
		*pbDst++ = AVG2(LEFT,RIGHT);
		pbSrc++;
	}
	*pbDst++ = BELOWLEFT;
	*pbDst++ = AVG2(LEFT,BELOW);;
	*pbDst++ = SELF;
	pbSrc++;
	for(DWORD y = 1; y < height-1; y += 2)
	{
		//pbDst = pbDst + (height - y - 1) * width * 3;
		*pbDst++ = SELF;
		*pbDst++ = AVG3(ABOVE,RIGHT,BELOW);
		*pbDst++ = AVG2(ABOVERIGHT,BELOWRIGHT);
		pbSrc++;

		for(x = 1; x < width-1; x += 2)
		{
			*pbDst++ = AVG2(LEFT,RIGHT);
			*pbDst++ = SELF;
			*pbDst++ = AVG2(ABOVE,BELOW);	
			pbSrc++;
			*pbDst++ = SELF;
			*pbDst++ = AVG4(ABOVE,BELOW,LEFT,RIGHT);
			*pbDst++ = AVG4(ABOVELEFT,ABOVERIGHT,BELOWLEFT,BELOWRIGHT);
			pbSrc++;
		}
		*pbDst++ = LEFT;
		*pbDst++ = SELF;
		*pbDst++ = AVG2(ABOVE,BELOW);
		pbSrc++;
		//pbDst = pbDst + (height - y - 2) * width * 3;
		*pbDst++ = AVG2(ABOVE,BELOW);
		*pbDst++ = SELF;
		*pbDst++ = RIGHT;
		pbSrc++;

		for(x = 1; x < width-1; x += 2)
		{
			*pbDst++ = AVG4(ABOVELEFT,ABOVERIGHT,BELOWLEFT,BELOWRIGHT);
			*pbDst++ = AVG4(ABOVE,BELOW,LEFT,RIGHT);
			*pbDst++ = SELF;
			pbSrc++;
			*pbDst++ = AVG2(ABOVE,BELOW);
			*pbDst++ = SELF;
			*pbDst++ = AVG2(LEFT,RIGHT);
			pbSrc++;
		}
		*pbDst++ = AVG2(BELOWLEFT,ABOVELEFT);
		*pbDst++ = AVG3(ABOVE,BELOW,LEFT);
		*pbDst++ = SELF;
		pbSrc++;
	}
	pbDst = pbDst;
	*pbDst++ = SELF;
	*pbDst++ = AVG2(ABOVE,RIGHT);;
	*pbDst++ = ABOVERIGHT;
	pbSrc++;

	for(x = 1; x < width-1; x += 2)
	{
		*pbDst++ = AVG2(LEFT,RIGHT);
		*pbDst++ = SELF;
		*pbDst++ = ABOVE;
		pbSrc++;
		*pbDst++ = SELF;
		*pbDst++ = AVG3(ABOVE,LEFT,RIGHT);
		*pbDst++ = AVG2(ABOVELEFT,ABOVERIGHT);
		pbSrc++;
	}
	*pbDst++ = LEFT;
	*pbDst++ = SELF;
	*pbDst++ = ABOVE;
	pbSrc++;
}

#undef SELF
#undef RIGHT
#undef LEFT
#undef ABOVE
#undef BELOW
#undef ABOVELEFT
#undef ABOVERIGHT
#undef BELOWLEFT
#undef BELOWRIGHT

#define SELF		BYTE(*pbSrc>>4)
#define RIGHT		BYTE(*(pbSrc+1)>>4)
#define LEFT		BYTE(*(pbSrc-1)>>4)
#define ABOVE		BYTE(*(pbSrc-width)>>4)
#define BELOW		BYTE(*(pbSrc+width)>>4)
#define ABOVELEFT	BYTE(*(pbSrc-width-1)>>4)
#define ABOVERIGHT	BYTE(*(pbSrc-width+1)>>4)
#define BELOWLEFT	BYTE(*(pbSrc+width-1)>>4)
#define BELOWRIGHT	BYTE(*(pbSrc+width+1)>>4)
/******************************************************************************
* FUNCTION		ConvertRG12ToBGR8()
* DESCRIPTION:  
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CVWGigECamera::ConvertRG12ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height)
{
	*pbDst++ = BELOWRIGHT;
	*pbDst++ = AVG2(RIGHT,BELOW);
	*pbDst++ = SELF;
	pbSrc++;

	DWORD x = 1;
	for( x = 1; x < width-1; x += 2)
	{
		*pbDst++ = BELOW;
		*pbDst++ = SELF;
		*pbDst++ = AVG2(LEFT,RIGHT);
		pbSrc++;
		*pbDst++ = AVG2(BELOWLEFT,BELOWRIGHT);
		*pbDst++ = AVG3(LEFT,RIGHT,BELOW);
		*pbDst++ = SELF;
		pbSrc++;
	}

	*pbDst++ = BELOW;
	*pbDst++ = SELF;
	*pbDst++ = LEFT;
	pbSrc++;

	for(DWORD y = 1; y < height-1; y += 2)
	{
		*pbDst++ = RIGHT;
		*pbDst++ = SELF;
		*pbDst++ = AVG2(ABOVE,BELOW);
		pbSrc++;

		for(x = 1; x < width-1; x += 2)
		{
			*pbDst++ = SELF;
			*pbDst++ = AVG4(ABOVE,BELOW,LEFT,RIGHT);
			*pbDst++ = AVG4(ABOVELEFT,ABOVERIGHT,BELOWLEFT,BELOWRIGHT);
			pbSrc++;
			*pbDst++ = AVG2(LEFT,RIGHT);
			*pbDst++ = SELF;
			*pbDst++ = AVG2(ABOVE,BELOW);
			pbSrc++;
		}

		*pbDst++ = SELF;
		*pbDst++ = AVG2(ABOVE,BELOW);
		*pbDst++ = AVG2(ABOVELEFT,BELOWLEFT);
		pbSrc++;

		*pbDst++ = AVG2(ABOVERIGHT,BELOWRIGHT);
		*pbDst++ = AVG3(ABOVE,RIGHT,BELOW);
		*pbDst++ = SELF;
		pbSrc++;

		for(x = 1; x < width-1; x += 2)
		{
			*pbDst++ = AVG2(ABOVE,BELOW);
			*pbDst++ = SELF;
			*pbDst++ = AVG2(LEFT,RIGHT);
			pbSrc++;
			*pbDst++ = AVG4(ABOVELEFT,ABOVERIGHT,BELOWLEFT,BELOWRIGHT);
			*pbDst++ = AVG4(ABOVE,BELOW,LEFT,RIGHT);
			*pbDst++ = SELF;
			pbSrc++;
		}

		*pbDst++ = AVG2(ABOVE,BELOW);
		*pbDst++ = SELF;
		*pbDst++ = LEFT;
		pbSrc++;
	}

/*
RGRGRGRG
GBGBGBGB
RGRGRGRG
GBGBGBGB
RGRGRGRG
GBGBGBGB
*/

	*pbDst++ = RIGHT;
	*pbDst++ = SELF;
	*pbDst++ = ABOVE;
	pbSrc++;

	for(x = 1; x < width-1; x += 2)
	{
		*pbDst++ = SELF;
		*pbDst++ = AVG3(ABOVE,LEFT,RIGHT);
		*pbDst++ = AVG2(ABOVELEFT,ABOVERIGHT);
		pbSrc++;
		*pbDst++ = AVG2(LEFT,RIGHT);
		*pbDst++ = SELF;
		*pbDst++ = ABOVE;
		pbSrc++;
	}

	*pbDst++ = SELF;
	*pbDst++ = AVG2(ABOVE,LEFT);
	*pbDst++ = ABOVELEFT;
	pbSrc++;
}

/******************************************************************************
* FUNCTION		ConvertGR12ToBGR8()
* DESCRIPTION:  
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CVWGigECamera::ConvertGR12ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height)
{
	//BYTE* pbDst = pbDst + (height - 1) * width * 3;
	*pbDst++ = BELOW;
	*pbDst++ = SELF;
	*pbDst++ = RIGHT;
	pbSrc++;

	DWORD x = 1;
	for( x = 1; x < width-1; x += 2)
	{
		*pbDst++ = AVG2(BELOWLEFT,BELOWRIGHT);
		*pbDst++ = AVG3(LEFT,RIGHT,BELOW);
		*pbDst++ = SELF;
		pbSrc++;
		*pbDst++ = BELOW;
		*pbDst++ = SELF;
		*pbDst++ = AVG2(LEFT,RIGHT);
		pbSrc++;
	}
	*pbDst++ = BELOWLEFT;
	*pbDst++ = AVG2(LEFT,BELOW);;
	*pbDst++ = SELF;
	pbSrc++;
	for(DWORD y = 1; y < height-1; y += 2)
	{
		//pbDst = pbDst + (height - y - 1) * width * 3;
		*pbDst++ = SELF;
		*pbDst++ = AVG3(ABOVE,RIGHT,BELOW);
		*pbDst++ = AVG2(ABOVERIGHT,BELOWRIGHT);
		pbSrc++;

		for(x = 1; x < width-1; x += 2)
		{
			*pbDst++ = AVG2(LEFT,RIGHT);
			*pbDst++ = SELF;
			*pbDst++ = AVG2(ABOVE,BELOW);	
			pbSrc++;
			*pbDst++ = SELF;
			*pbDst++ = AVG4(ABOVE,BELOW,LEFT,RIGHT);
			*pbDst++ = AVG4(ABOVELEFT,ABOVERIGHT,BELOWLEFT,BELOWRIGHT);
			pbSrc++;
		}
		*pbDst++ = LEFT;
		*pbDst++ = SELF;
		*pbDst++ = AVG2(ABOVE,BELOW);
		pbSrc++;
		//pbDst = pbDst + (height - y - 2) * width * 3;
		*pbDst++ = AVG2(ABOVE,BELOW);
		*pbDst++ = SELF;
		*pbDst++ = RIGHT;
		pbSrc++;

		for(x = 1; x < width-1; x += 2)
		{
			*pbDst++ = AVG4(ABOVELEFT,ABOVERIGHT,BELOWLEFT,BELOWRIGHT);
			*pbDst++ = AVG4(ABOVE,BELOW,LEFT,RIGHT);
			*pbDst++ = SELF;
			pbSrc++;
			*pbDst++ = AVG2(ABOVE,BELOW);
			*pbDst++ = SELF;
			*pbDst++ = AVG2(LEFT,RIGHT);
			pbSrc++;
		}
		*pbDst++ = AVG2(BELOWLEFT,ABOVELEFT);
		*pbDst++ = AVG3(ABOVE,BELOW,LEFT);
		*pbDst++ = SELF;
		pbSrc++;
	}
	pbDst = pbDst;
	*pbDst++ = SELF;
	*pbDst++ = AVG2(ABOVE,RIGHT);;
	*pbDst++ = ABOVERIGHT;
	pbSrc++;

	for(x = 1; x < width-1; x += 2)
	{
		*pbDst++ = AVG2(LEFT,RIGHT);
		*pbDst++ = SELF;
		*pbDst++ = ABOVE;
		pbSrc++;
		*pbDst++ = SELF;
		*pbDst++ = AVG3(ABOVE,LEFT,RIGHT);
		*pbDst++ = AVG2(ABOVELEFT,ABOVERIGHT);
		pbSrc++;
	}
	*pbDst++ = LEFT;
	*pbDst++ = SELF;
	*pbDst++ = ABOVE;
	pbSrc++;
}

/******************************************************************************
* FUNCTION		CVWGigECamera()
* DESCRIPTION:  
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
CVWGigECamera::CVWGigECamera(void)
{
	m_nCamIndex					= 0;
	m_pvwGigE					= NULL;
	m_pCamera					= NULL;
	m_pObjectInfo				= NULL;
	m_pInterface				= NULL;
	m_imagebuffernumber			= 1;
	m_pcapturedpBase			= NULL;
	m_pUnpackedImage			= NULL;
}

/******************************************************************************
* FUNCTION		~CVWGigECamera()
* DESCRIPTION:  
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
CVWGigECamera::~CVWGigECamera(void)
{

}

/******************************************************************************
* FUNCTION		InitDevice()
* DESCRIPTION:  
* PARAMETERS:
* RETURNS:
* NOTES:		You should open the device with full resolution.
*******************************************************************************
*/
BOOL CVWGigECamera::	   InitDevice(void*			pInterfaceHanlde,		//Interface Handle
									  VWGIGE_HANDLE pvwGigE,				//GigE Handle.
									  UINT			nCamIndex,				//Camera index
									  void		   *pParent,				//Parent Pointer
									  UINT			nBufferNum,				//Buffer Number
									  UINT			packetsize,				//Pixel format
									  void		   *pFnCallback1,			//Image captured callback function	
									  void		   *pFnCallback2			//Disconnection callback function
									  )	
{
	RESULT ret					= RESULT_SUCCESS;

	m_pvwGigE					= pvwGigE;
	m_nCamIndex					= nCamIndex;
	m_pInterface				= pInterfaceHanlde;
	m_pObjectInfo				= new OBJECT_INFO;
	m_imagebuffernumber			= nBufferNum;


	ret = VwOpenCameraByIndex(m_pvwGigE, m_nCamIndex, &m_pCamera, m_imagebuffernumber, 0/*Width*/, 0/*Height*/, 0, m_pObjectInfo, 
							 (ImageCallbackFn*)pFnCallback1,(DisconnectCallbackFn*)pFnCallback2 );
	if ( RESULT_SUCCESS != ret )
	{

	}		

	m_pObjectInfo->pUserPointer = pParent;
	m_pObjectInfo->pVwCamera    = (void *)m_pCamera; 

	// Set acquisition timeout
	// 0xFFFFFFFF means INFINITE
	ret = CameraSetAcquisitionTimeOut(m_pCamera,0xFFFFFFFF);
	if ( RESULT_SUCCESS != ret )
	{

	}	

	// Prepare the buffer for display
	MakeUnPackedBuffer();

	return TRUE;
}

/******************************************************************************
* FUNCTION		 CloseDevice()
* DESCRIPTION:   
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::CloseDevice()
{
	if ( m_pObjectInfo != NULL )
	{
		delete m_pObjectInfo;
		m_pObjectInfo = NULL;
	}

	if ( m_pUnpackedImage )
	{
		delete [] m_pUnpackedImage;
		m_pUnpackedImage = NULL;
	}

	if ( CameraClose( m_pCamera ) == RESULT_SUCCESS )
	{
		m_pCamera = NULL;

		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
* FUNCTION		 Start()
* DESCRIPTION:   
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL	CVWGigECamera::Start() 
{
	RESULT ret	     = RESULT_SUCCESS;

	BOOL bGrabbing = FALSE;
	CameraGetGrabCondition( m_pCamera, bGrabbing );
	if ( bGrabbing == TRUE )
	{
		return TRUE;
	}

	ret = CameraGrab( m_pCamera );
	if ( RESULT_SUCCESS != ret )
	{
		return FALSE;
	}

	ret = CameraSetCustomCommand(m_pCamera,"TLParamsLocked","1");		

	return TRUE;
}    

/******************************************************************************
* FUNCTION		 Stop()
* DESCRIPTION:   
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL	CVWGigECamera::Stop()
{
	RESULT ret	     = RESULT_SUCCESS;

	BOOL bGrabbing = FALSE;
	CameraGetGrabCondition( m_pCamera, bGrabbing );

	if ( bGrabbing == TRUE )
	{
		ret = CameraAbort( m_pCamera );
		if ( RESULT_SUCCESS != ret )
		{
			return FALSE;
		}
	}

	ret = CameraSetCustomCommand(m_pCamera,"TLParamsLocked","0");		

	return TRUE;
}

/******************************************************************************
* FUNCTION		 GetCameraWidth()
* DESCRIPTION:   
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
UINT CVWGigECamera::GetCameraWidth()						
{
	BOOL ret	     = FALSE;

	char strValue[256] = {0,};
	ret = GetCustomCommand("Width",strValue);

	if ( TRUE != ret )
	{

	}

	return atoi(strValue);
}

/******************************************************************************
* FUNCTION		 GetCameraHeight()
* DESCRIPTION:   Get camera Height
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
UINT CVWGigECamera::GetCameraHeight()						
{
	BOOL ret	     = FALSE;

	char strValue[256] = {0,};
	ret = GetCustomCommand("Height",strValue);

	if ( TRUE != ret )
	{

	}

	return atoi(strValue);
}

/******************************************************************************
* FUNCTION		 GetPixelFormat()
* DESCRIPTION:   
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
PIXEL_FORMAT CVWGigECamera::GetPixelFormat()
{
	RESULT		 ret	     = RESULT_SUCCESS;
	PIXEL_FORMAT pixelFormat = PIXEL_FORMAT_MONO8;

	ret = CameraGetPixelFormat( m_pCamera, &pixelFormat );
	if ( RESULT_SUCCESS != ret )
	{

	}

	return pixelFormat;
}

/******************************************************************************
* FUNCTION		 GetBufferDataForDisplay()
* DESCRIPTION:   Get Image data for display(BGR8 Format)
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void* CVWGigECamera::GetBufferDataForDisplay(UINT width,UINT height,PIXEL_FORMAT pixelFormat,void *pbuffer)				
{
	BOOL bRet = CVwResourceType::ConvertPixelFormat( pixelFormat, m_pUnpackedImage, (BYTE*)pbuffer, width, height);
	if ( TRUE != bRet )
	{

	}

	return m_pUnpackedImage;
}

/******************************************************************************
* FUNCTION		 SetPixelFormat()
* DESCRIPTION:   Set Pixel Format		
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::SetPixelFormat(PIXEL_FORMAT format)
{	
	RESULT  nRet         = RESULT_SUCCESS;

	PROPERTY pProperty;
	CameraGetPropertyInfo( m_pCamera, "PixelFormat", &pProperty );

	if( pProperty.eAccessMode == READ_ONLY )
	{
		return FALSE;
	}

	switch (format)
	{
	case PIXEL_FORMAT_MONO8:
		nRet = CameraSetCustomCommand(m_pCamera, "PixelFormat","Mono8");
		break;
	case PIXEL_FORMAT_MONO10_PACKED:
		nRet = CameraSetCustomCommand(m_pCamera, "PixelFormat","Mono10Packed");
		break;
	case PIXEL_FORMAT_MONO12_PACKED:
		nRet = CameraSetCustomCommand(m_pCamera, "PixelFormat","Mono12Packed");
		break;
	case PIXEL_FORMAT_BAYGR8: 
		nRet = CameraSetCustomCommand(m_pCamera, "PixelFormat","BayerGR8");
		break;
	case PIXEL_FORMAT_BAYRG8:
		nRet = CameraSetCustomCommand(m_pCamera, "PixelFormat","BayerRG8");
		break;
	case PIXEL_FORMAT_BAYRG12_PACKED:
		nRet = CameraSetCustomCommand(m_pCamera, "PixelFormat","BayerRG12Packed");
		break;		
	}
	MakeUnPackedBuffer();

	if ( RESULT_SUCCESS != nRet )
	{
		return FALSE;
	}

	return TRUE;
}

/******************************************************************************
* FUNCTION		 GetFrameCapacity
* DESCRIPTION:   Get frame number to be saved.
* PARAMETERS:    
* RETURNS:
* NOTES:
*******************************************************************************
*/
UINT CVWGigECamera::GetFrameCapacity(VOID)	
{
	RESULT  nRet         = RESULT_SUCCESS;
	CHAR    caArg1[256]  = {0,};
	size_t  nArgSize1    = 256;

	CHAR*   cpCommand    = "FrameCapacity";

	int nCmdType = GET_CUSTOM_COMMAND_VALUE;

	nRet = CameraGetCustomCommand(m_pCamera, cpCommand,caArg1, &nArgSize1,nCmdType);

	if( nRet == RESULT_SUCCESS )
	{
		return atoi(caArg1);
	}

	return 0;
}

/******************************************************************************
* FUNCTION		 MakeUnPackedBuffer()
* DESCRIPTION:   	
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void CVWGigECamera::MakeUnPackedBuffer()
{
	if ( NULL == m_pCamera )
	{
		return;
	}

	if ( m_pUnpackedImage )
	{
		delete [] m_pUnpackedImage;
		m_pUnpackedImage = NULL;
	}

	//Get image width,height 
	UINT nWidth				 = 0;
	UINT nHeight			 = 0;
	PIXEL_FORMAT pixelFormat = PIXEL_FORMAT_MONO8;

	char strValue[256] = {0,};
	GetCustomCommand("Width", strValue); nWidth = atoi(strValue);
	GetCustomCommand("Height",strValue); nHeight = atoi(strValue);

	CameraGetPixelFormat( m_pCamera, &pixelFormat );

	switch( pixelFormat )
	{
	case PIXEL_FORMAT_MONO8:
		m_pUnpackedImage = new BYTE[nWidth*nHeight];
		break;
	case PIXEL_FORMAT_MONO10_PACKED:
	case PIXEL_FORMAT_MONO12_PACKED:
	case PIXEL_FORMAT_MONO16:
		m_pUnpackedImage = new BYTE[nWidth*nHeight*3]; //8bit : 3band for display
		break;
	case PIXEL_FORMAT_BAYGR8:
	case PIXEL_FORMAT_BAYRG8:
		m_pUnpackedImage = new BYTE[nWidth*nHeight*3]; //8bit : 3band for display
		break;
	case PIXEL_FORMAT_BAYRG12:
	case PIXEL_FORMAT_BAYGR10_PACKED:
		m_pUnpackedImage = new BYTE[nWidth*nHeight*3]; //8bit : 3band for display
		break;
	default:
		m_pUnpackedImage = new BYTE[nWidth*nHeight*3]; //8bit : 3band for display
		break;
	}
	CameraChangeBufferFormat( m_pCamera, m_imagebuffernumber, nWidth, nHeight, pixelFormat );
}

/******************************************************************************
* FUNCTION		 GetRawBufferData()
* DESCRIPTION:   Get raw data
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void* CVWGigECamera::GetRawBufferData()
{
	return m_pcapturedpBase;
}

/******************************************************************************
* FUNCTION		 SetRawBufferData()
* DESCRIPTION:   
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
void  CVWGigECamera::SetRawBufferData(void *pbuffer)
{
	m_pcapturedpBase = pbuffer;
}

/******************************************************************************
* FUNCTION		 SetTriggerMode()
* DESCRIPTION:  
* PARAMETERS:    FALSE ; Off, TRUE : On
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::SetTriggerMode(CHAR* strvalue)	
{
	RESULT ret	     = RESULT_SUCCESS;

	ret = CameraSetCustomCommand(m_pCamera,"TriggerMode",strvalue);
	if ( RESULT_SUCCESS == ret )
	{
		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
* FUNCTION		 SetTriggerSource()
* DESCRIPTION:  
* PARAMETERS:    2 ; external, 3 : software
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::SetTriggerSource(CHAR* strvalue)			
{
	RESULT ret	     = RESULT_SUCCESS;

	ret = CameraSetCustomCommand(m_pCamera,"TriggerSource",strvalue);		
	if ( RESULT_SUCCESS == ret )
	{
		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
* FUNCTION		 SetExposureMode()
* DESCRIPTION:  
* PARAMETERS:   0 ; Timed, 1 : Trigger width
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::SetExposureMode(CHAR* strvalue)		
{
	RESULT ret	     = RESULT_SUCCESS;

	ret = CameraSetCustomCommand(m_pCamera,"ExposureMode",strvalue);		
	if ( RESULT_SUCCESS == ret )
	{
		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
* FUNCTION		 SetExposureTime()
* DESCRIPTION:  
* PARAMETERS:    Set exposure time - us
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::SetExposureTime(CHAR* strvalue)			
{
	RESULT ret	     = RESULT_SUCCESS;

	ret = CameraSetCustomCommand(m_pCamera,"ExposureTime",strvalue);		
	if ( RESULT_SUCCESS == ret )
	{
		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
* FUNCTION		 SetGain()
* DESCRIPTION:   Set Gain
* PARAMETERS:    
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::SetGain(CHAR* strvalue)			
{
	RESULT ret	     = RESULT_SUCCESS;

	ret = CameraSetCustomCommand(m_pCamera,"Gain",strvalue);		
	if ( RESULT_SUCCESS == ret )
	{
		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
* FUNCTION		 SendSoftwareTrigger()
* DESCRIPTION:  
* PARAMETERS:    Send software trigger. Software trigger only works with Timed mode.
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::SendSoftwareTrigger(VOID)
{
	RESULT ret	     = RESULT_SUCCESS;

	ret = CameraSetCustomCommand(m_pCamera,"TriggerSoftware",NULL);		
	if ( RESULT_SUCCESS == ret )
	{
		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
* FUNCTION		 SetInterpacketDelay
* DESCRIPTION:   Set inter packet delay (Unit - Tick)
* PARAMETERS:    
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::SetInterpacketDelay(CHAR* strvalue)
{
	RESULT ret	     = RESULT_SUCCESS;

	ret = CameraSetCustomCommand(m_pCamera,"GevSCPD",strvalue);		
	if ( RESULT_SUCCESS == ret )
	{
		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
* FUNCTION		 SetTestImageSelector
* DESCRIPTION:   Set test image pattern(0,1,2,3)
				 0 : Off
				 1 : GreyHorizontalRamp
				 2 : GreyDiagonalRamp
				 3 : GreyDiagonalRampMoving
* PARAMETERS:    
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::SetTestImageSelector(CHAR* strvalue)	
{
	RESULT ret	     = RESULT_SUCCESS;

	ret = CameraSetCustomCommand(m_pCamera,"TestImageSelector",strvalue);		
	if ( RESULT_SUCCESS == ret )
	{
		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
* FUNCTION		 SetStreamHold
* DESCRIPTION:   Set StreamHold enable or disable
* PARAMETERS:    
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::SetStreamHold(CHAR* strvalue)	
{
	RESULT ret	     = RESULT_SUCCESS;

	ret = CameraSetCustomCommand(m_pCamera,"StreamHold",strvalue);		
	if ( RESULT_SUCCESS == ret )
	{
		return TRUE;
	}

	return FALSE;
}


/******************************************************************************
* FUNCTION		 SetBinningHorizontal
* DESCRIPTION:   Binning Horizontal : 1,2,3,4,8
* PARAMETERS:    
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::SetBinningHorizontal(CHAR* strvalue)
{
	RESULT ret	     = RESULT_SUCCESS;

	PROPERTY pProperty;
	CameraGetPropertyInfo( m_pCamera, "BinningHorizontal", &pProperty );

	if( pProperty.eAccessMode == READ_ONLY )
	{
		return FALSE;
	}

	ret = CameraSetCustomCommand(m_pCamera,"BinningHorizontal",strvalue);		
	MakeUnPackedBuffer();
	if ( RESULT_SUCCESS == ret )
	{
		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
* FUNCTION		 SetBinningVertical
* DESCRIPTION:   Binning Vertical   : 1,2,3,4,8
* PARAMETERS:    
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::SetBinningVertical(CHAR* strvalue)
{
	RESULT ret	     = RESULT_SUCCESS;

	PROPERTY pProperty;
	ret = CameraGetPropertyInfo( m_pCamera, "BinningVertical", &pProperty );

	if( pProperty.eAccessMode == READ_ONLY )
	{
		return FALSE;
	}

	ret = CameraSetCustomCommand(m_pCamera,"BinningVertical",strvalue);		
	MakeUnPackedBuffer();
	if ( RESULT_SUCCESS == ret )
	{
		return TRUE;
	}

	return FALSE;
}


/******************************************************************************
* FUNCTION		 SetAOISize()
* DESCRIPTION:   	
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::SetAOISize(CHAR* OffsetX,CHAR* OffsetY,CHAR* width,CHAR* height)
{
	RESULT ret			 = RESULT_SUCCESS;

	PROPERTY pProperty;
	CameraGetPropertyInfo( m_pCamera, "Width", &pProperty );

	if( pProperty.eAccessMode == READ_ONLY )
	{
		return FALSE;
	}

	UINT nOffsetX		 = atoi(OffsetX);
	UINT nwidth			 = atoi(width);
	UINT nOffsetY		 = atoi(OffsetY);
	UINT nheight		 = atoi(height);

	UINT nImageMaxWidth  = 0;
	UINT nImageMaxHeight = 0;
	UINT nImageCurWidth  = 0;
	UINT nImageCurHeight = 0;

	CHAR    caArg1[256]  = {0,};
	size_t  nArgSize1    = 256;
	CHAR*   cpCommand    = "WidthMax";
	int nCmdType		 = GET_CUSTOM_COMMAND_VALUE;
	ret					 = CameraGetCustomCommand(m_pCamera, cpCommand,caArg1, &nArgSize1,nCmdType);
	if ( RESULT_SUCCESS != ret )
	{
		return FALSE;
	}
	nImageMaxWidth		 = atoi(caArg1);

	nArgSize1			 = 256;
	cpCommand			 = "HeightMax";
	ret					 = CameraGetCustomCommand(m_pCamera, cpCommand,caArg1, &nArgSize1,nCmdType);
	if ( RESULT_SUCCESS != ret )
	{
		return FALSE;
	}
	nImageMaxHeight		 = atoi(caArg1);

	if( nOffsetX + nwidth  > nImageMaxWidth )
	{
		return FALSE;
	}

	if( nOffsetY + nheight > nImageMaxHeight )
	{
		return FALSE;
	}

	ret = CameraSetCustomCommand(m_pCamera,"Width",  width);		
	if ( RESULT_SUCCESS != ret )
	{
		return FALSE;
	}

	ret = CameraSetCustomCommand(m_pCamera,"OffsetX",OffsetX);		
	if ( RESULT_SUCCESS != ret )
	{
		return FALSE;
	}

	ret = CameraSetCustomCommand(m_pCamera,"Height", height);		
	if ( RESULT_SUCCESS != ret )
	{
		return FALSE;
	}

	ret = CameraSetCustomCommand(m_pCamera,"OffsetY",OffsetY);		
	if ( RESULT_SUCCESS != ret )
	{
		return FALSE;
	}
	MakeUnPackedBuffer();

	return TRUE;
}

/******************************************************************************
* FUNCTION		 GetInterpacketDelay
* DESCRIPTION:   Get inter packet delay (Unit - Tick)
* PARAMETERS:    
* RETURNS:
* NOTES:
*******************************************************************************
*/
UINT CVWGigECamera::GetInterpacketDelay(VOID)				
{
	RESULT  nRet         = RESULT_SUCCESS;
	CHAR    caArg1[256]  = {0,};
	size_t  nArgSize1    = 256;
	CHAR*   cpCommand    = "GevSCPD";
	int nCmdType		 = GET_CUSTOM_COMMAND_VALUE;

	nRet = CameraGetCustomCommand(m_pCamera, cpCommand,caArg1, &nArgSize1,nCmdType);
	if ( RESULT_SUCCESS == nRet )
	{
		return atoi(caArg1);
	}

	return 0;
}

/******************************************************************************
* FUNCTION		 GetTestImageSelector
* DESCRIPTION:   Get test image pattern(0,1,2,3)
				 0 : Off
				 1 : GreyHorizontalRamp
				 2 : GreyDiagonalRamp
				 3 : GreyDiagonalRampMoving
* PARAMETERS:    
* RETURNS:
* NOTES:
*******************************************************************************
*/
UINT CVWGigECamera::GetTestImageSelector(VOID)	
{
	RESULT  nRet         = RESULT_SUCCESS;
	CHAR    caArg1[256]  = {0,};
	size_t  nArgSize1    = 256;
	CHAR*   cpCommand    = "TestImageSelector";
	int		nCmdType	 = GET_CUSTOM_COMMAND_VALUE;
	UINT    nreturn      = 0;

	nRet = CameraGetCustomCommand(m_pCamera, cpCommand,caArg1, &nArgSize1,nCmdType);
	if ( RESULT_SUCCESS == nRet )
	{
		if( strcmp( caArg1, "Off" )					   == 0)
		{
			nreturn = 0;
		}
		else if( strcmp( caArg1, "GreyHorizontalRamp" )== 0)
		{
			nreturn = 1;
		}
		else if( strcmp( caArg1, "GreyDiagonalRamp" )  == 0)
		{
			nreturn = 2;
		}
		else 
		{
			nreturn = 3;
		}

		return nreturn;
	}

	return 0;
}

/******************************************************************************
* FUNCTION		 GetMaxImageWidth()
* DESCRIPTION:   
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
UINT CVWGigECamera::GetMaxImageWidth()
{
	RESULT  nRet         = RESULT_SUCCESS;
	CHAR    caArg1[256]  = {0,};
	size_t  nArgSize1    = 256;
	CHAR*   cpCommand    = "WidthMax";
	int nCmdType		 = GET_CUSTOM_COMMAND_VALUE;

	nRet = CameraGetCustomCommand(m_pCamera, cpCommand,caArg1, &nArgSize1,nCmdType);
	if ( RESULT_SUCCESS == nRet )
	{
		return atoi(caArg1);
	}

	return 0;
}

/******************************************************************************
* FUNCTION		 GetMaxImageHeight()
* DESCRIPTION:   
* PARAMETERS:
* RETURNS:
* NOTES:
*******************************************************************************
*/
UINT CVWGigECamera::GetMaxImageHeight()
{
	RESULT  nRet         = RESULT_SUCCESS;
	CHAR    caArg1[256]  = {0,};
	size_t  nArgSize1    = 256;
	CHAR*   cpCommand    = "HeightMax";
	int nCmdType		 = GET_CUSTOM_COMMAND_VALUE;

	nRet = CameraGetCustomCommand(m_pCamera, cpCommand,caArg1, &nArgSize1,nCmdType);
	if ( RESULT_SUCCESS == nRet )
	{
		return atoi(caArg1);
	}

	return 0;
}

/******************************************************************************
* FUNCTION		 SetEventSelector
* DESCRIPTION:   "ExposureEnd"
* PARAMETERS:    
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::SetEventSelector(CHAR* strvalue)
{
	RESULT ret	     = RESULT_SUCCESS;

	ret = CameraSetCustomCommand(m_pCamera,"EventSelector",strvalue);		
	if ( RESULT_SUCCESS == ret )
	{
		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
* FUNCTION		 SetEventNotification
* DESCRIPTION:   0ff, On
* PARAMETERS:    
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::SetEventNotification(CHAR* strvalue)
{
	RESULT ret	     = RESULT_SUCCESS;

	ret = CameraSetCustomCommand(m_pCamera,"EventNotification",strvalue);		
	if ( RESULT_SUCCESS == ret )
	{
		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
* FUNCTION		 SetDevSetEventControl
* DESCRIPTION:   "ExposureEnd¡±
* PARAMETERS:    
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::SetDevSetEventControl(const char*  sEventName, 
										  size_t       szEventName, 
										  void*		   pEventCallback )
{	
	RESULT ret	     = RESULT_SUCCESS;

	//ret = CameraSetEventControl( m_pCamera, sEventName,szEventName, (EventControlCallbackFn*)pEventCallback );
	if ( RESULT_SUCCESS == ret )
	{
		return TRUE;
	}
	
	return FALSE;
}

/******************************************************************************
* FUNCTION		 SetCustomCommand
* DESCRIPTION:   Set node value.
* PARAMETERS:    
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::SetCustomCommand(CHAR* nodename,CHAR* pValue)
{
	RESULT  ret			 = RESULT_SUCCESS;

	PROPERTY pProperty;
	CameraGetPropertyInfo( m_pCamera, nodename, &pProperty );

	if( pProperty.eAccessMode == READ_ONLY )
	{
		return FALSE;
	}

	ret = CameraSetCustomCommand(m_pCamera,nodename,pValue);		
	if ( RESULT_SUCCESS == ret )
	{
		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
* FUNCTION		 GetCustomCommand
* DESCRIPTION:   Get node value
* PARAMETERS:    
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::GetCustomCommand(CHAR* nodename, CHAR* returnstr)
{
	RESULT  nRet         = RESULT_SUCCESS;
	CHAR    caArg1[256]  = {0,};
	size_t  nArgSize1    = 256;
	int nCmdType		 = GET_CUSTOM_COMMAND_VALUE;

	nRet = CameraGetCustomCommand(m_pCamera, nodename,caArg1, &nArgSize1,nCmdType);
	if ( RESULT_SUCCESS == nRet )
	{
		strcpy(returnstr,caArg1);
		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
* FUNCTION		 GetCustomCommandMin
* DESCRIPTION:   Get node value
* PARAMETERS:    
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::GetCustomCommandMin(CHAR* nodename, CHAR* returnstr)
{
	RESULT  nRet         = RESULT_SUCCESS;
	CHAR    caArg1[256]  = {0,};
	size_t  nArgSize1    = 256;
	int nCmdType		 = GET_CUSTOM_COMMAND_MIN;

	nRet = CameraGetCustomCommand(m_pCamera, nodename,caArg1, &nArgSize1,nCmdType);
	if ( RESULT_SUCCESS == nRet )
	{
		strcpy(returnstr,caArg1);
		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
* FUNCTION		 GetCustomCommandMax
* DESCRIPTION:   Get node value
* PARAMETERS:    
* RETURNS:
* NOTES:
*******************************************************************************
*/
BOOL CVWGigECamera::GetCustomCommandMax(CHAR* nodename, CHAR* returnstr)
{
	RESULT  nRet         = RESULT_SUCCESS;
	CHAR    caArg1[256]  = {0,};
	size_t  nArgSize1    = 256;
	int nCmdType		 = GET_CUSTOM_COMMAND_MAX;

	nRet = CameraGetCustomCommand(m_pCamera, nodename,caArg1, &nArgSize1,nCmdType);
	if ( RESULT_SUCCESS == nRet )
	{
		strcpy(returnstr,caArg1);
		return TRUE;
	}

	return FALSE;
}