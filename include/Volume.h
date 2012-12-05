#ifndef __VROOM_VOLUME_H__
#define __VROOM_VOLUME_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <Platform.h>





//=================================================================
//	Class Volume
//---------------------------------------
class Volume
{
public:
	// Constructors
						Volume();
					   ~Volume();

	// Getters
	UInt8			  *	GetData();
	UInt32				GetDataSize();
	UInt32				GetWidth();
	UInt32				GetHeight();
	UInt32				GetDepth();

	void				Create( UInt32 inWidth, UInt32 inHeight, UInt32 inDepth );

private:
	UInt32				mWidth;
	UInt32				mHeight;
	UInt32				mDepth;

	UInt8			  *	mData;
};





#endif