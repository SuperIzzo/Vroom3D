//=================================================================
//	Inlude
//---------------------------------------
#include "Volume.h"
#include "IndexOutOfBoundsException.h"





//=================================================================
//	Volume::BYTES_PER_VOXEL
//---------------------------------------
const UInt32 Volume::BYTES_PER_VOXEL = 4;





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
UInt32 Volume::GetDataSize()	const
{
	return mWidth*mHeight*mDepth * BYTES_PER_VOXEL;
}





//=================================================================
//	Volume::GetWidth
//---------------------------------------
UInt32 Volume::GetWidth()	const
{
	return mWidth;
}





//=================================================================
//	Volume::GetHeight
//---------------------------------------
UInt32 Volume::GetHeight()	const
{
	return mHeight;
}





//=================================================================
//	Volume::GetDepth
//---------------------------------------
UInt32 Volume::GetDepth()	const
{
	return mDepth;
}





//=================================================================
//	Volume::SetVoxel
//---------------------------------------
void Volume::SetVoxel( UInt32 x, UInt32 y, UInt32 z, Color &col )
{
	CheckInRange(x,y,z);

	Color *colorData	= (Color*)mData;
	UInt32 voxelIdx		= x + (y + z*mHeight)*mWidth;

	colorData[ voxelIdx ] = col;
}





//=================================================================
//	Volume::Create
//---------------------------------------
void Volume::Create( UInt32 inWidth, UInt32 inHeight, UInt32 inDepth )
{
	delete[] mData;

	mWidth	= inWidth;
	mHeight = inHeight;
	mDepth	= inDepth;

	UInt32 dataSize = GetDataSize();
	mData = new UInt8[ dataSize ];
}





//=================================================================
//	Volume::CheckInRange
//---------------------------------------
void Volume::CheckInRange(UInt32 x, UInt32 y, UInt32 z) const
{
	if( x >= mWidth || y >= mHeight || z >= mDepth )
	{
		throw IndexOutOfBoundsException();
	}
}