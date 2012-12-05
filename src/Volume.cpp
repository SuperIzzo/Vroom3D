//=================================================================
//	Inlude
//---------------------------------------
#include "Volume.h"





//=================================================================
//	Volume::Volume
//---------------------------------------
Volume::Volume() :
	mWidth( 0 ),
	mHeight( 0 ),
	mDepth( 0 ),
	mData( 0 )
{
}





//=================================================================
//	Volume::~Volume
//---------------------------------------
Volume::~Volume()
{
	delete[] mData;
	mData = 0;
}





//=================================================================
//	Volume::GetData
//---------------------------------------
UInt8 * Volume::GetData()
{
	return mData;
}





//=================================================================
//	Volume::GetDataSize
//---------------------------------------
UInt32 Volume::GetDataSize()
{
	static const UInt32 BYTES_PER_VOXEL = 4;

	return mWidth*mHeight*mDepth * BYTES_PER_VOXEL;
}





//=================================================================
//	Volume::GetWidth
//---------------------------------------
UInt32 Volume::GetWidth()
{
	return mWidth;
}





//=================================================================
//	Volume::GetHeight
//---------------------------------------
UInt32 Volume::GetHeight()
{
	return mHeight;
}





//=================================================================
//	Volume::GetDepth
//---------------------------------------
UInt32 Volume::GetDepth()
{
	return mDepth;
}





//=================================================================
//	Volume::Create
//---------------------------------------
void Volume::Create( UInt32 inWidth, UInt32 inHeight, UInt32 inDepth )
{
	mWidth	= inWidth;
	mHeight = inHeight;
	mDepth	= inDepth;

	UInt32 dataSize = GetDataSize();
	mData = new UInt8[ dataSize ];
}