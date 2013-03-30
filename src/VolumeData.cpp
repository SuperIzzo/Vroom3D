//=================================================================
//	Inlude
//---------------------------------------
#include "VolumeData.h"
#include "IndexOutOfBoundsException.h"


VROOM_BEGIN


//=================================================================
//	Volume::BYTES_PER_VOXEL
//---------------------------------------
const UInt32 VolumeData::BYTES_PER_VOXEL = 4;





//=================================================================
//	VolumeData::VolumeData
//---------------------------------------
VolumeData::VolumeData() :
	mWidth( 0 ),
	mHeight( 0 ),
	mDepth( 0 ),
	mData( 0 )
{
}





//=================================================================
//	VolumeData::~VolumeData
//---------------------------------------
VolumeData::~VolumeData()
{
	Destroy();
}





//=================================================================
//	VolumeData::GetData
//---------------------------------------
UInt8 * VolumeData::GetData()
{
	return mData;
}





//=================================================================
//	VolumeData::GetData
//---------------------------------------
const UInt8 * VolumeData::GetData() const
{
	return mData;
}





//=================================================================
//	VolumeData::GetDataSize
//---------------------------------------
UInt32 VolumeData::GetDataSize()	const
{
	return mWidth*mHeight*mDepth * BYTES_PER_VOXEL;
}





//=================================================================
//	VolumeData::GetWidth
//---------------------------------------
UInt32 VolumeData::GetWidth()	const
{
	return mWidth;
}





//=================================================================
//	VolumeData::GetHeight
//---------------------------------------
UInt32 VolumeData::GetHeight()	const
{
	return mHeight;
}





//=================================================================
//	Volume::GetDepth
//---------------------------------------
UInt32 VolumeData::GetDepth()	const
{
	return mDepth;
}





//=================================================================
//	VolumeData::SetVoxel
//---------------------------------------
void VolumeData::SetVoxel( UInt32 x, UInt32 y, UInt32 z, const Color &col )
{
	CheckInRange(x,y,z);

	Color *colorData	= (Color*)mData;
	UInt32 voxelIdx		= x + (y + z*mHeight)*mWidth;

	colorData[ voxelIdx ] = col;
}





//=================================================================
//	VolumeData::GetVoxel
//---------------------------------------
Color& VolumeData::GetVoxel( UInt32 x, UInt32 y, UInt32 z )
{
	CheckInRange(x,y,z);

	Color *colorData	= (Color*)mData;
	UInt32 voxelIdx		= x + (y + z*mHeight)*mWidth;

	return colorData[ voxelIdx ];
}





//=================================================================
//	VolumeData::GetVoxel
//---------------------------------------
Color VolumeData::GetVoxel( UInt32 x, UInt32 y, UInt32 z ) const
{
	CheckInRange(x,y,z);

	Color *colorData	= (Color*)mData;
	UInt32 voxelIdx		= x + (y + z*mHeight)*mWidth;

	return colorData[ voxelIdx ];
}





//=================================================================
//	VolumeData::Create
//---------------------------------------
void VolumeData::Create( UInt32 inWidth, UInt32 inHeight, UInt32 inDepth )
{
	Destroy();

	mWidth	= inWidth;
	mHeight = inHeight;
	mDepth	= inDepth;

	UInt32 dataSize = GetDataSize();
	mData = new UInt8[ dataSize ];

	// Clear the memory
	memset( mData, 0, dataSize*sizeof(UInt8) );
}





//=================================================================
//	VolumeData::Destroy
//---------------------------------------
void VolumeData::Destroy()
{
	delete[] mData;
	mData = 0;

	mWidth	= 0;
	mHeight	= 0;
	mDepth	= 0;
}





//=================================================================
//	VolumeData::CheckInRange
//---------------------------------------
void VolumeData::CheckInRange(UInt32 x, UInt32 y, UInt32 z) const
{
	if( x >= mWidth || y >= mHeight || z >= mDepth )
	{
		throw IndexOutOfBoundsException();
	}
}


VROOM_END
