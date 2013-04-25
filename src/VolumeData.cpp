/*ZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZ*\
Z|                                                                           |Z
Z|  Copyright (c) 2013   Hristoz S. Stefanov                                 |Z
Z|                                                                           |Z
Z|  Permission is hereby granted, free of charge, to any person              |Z
Z|  obtaining a copy of this software and associated documentation files     |Z
Z|  (the "Software"), to deal in the Software without restriction,           |Z
Z|  including without limitation the rights to use, copy, modify, merge,     |Z
Z|  publish, distribute, sublicense, and/or sell copies of the Software,     |Z
Z|  and to permit persons to whom the Software is furnished to do so,        |Z
Z|  subject to the following conditions:                                     |Z
Z|                                                                           |Z
Z|  The above copyright notice and this permission notice shall be included  |Z
Z|  in all copies or substantial portions of the Software.                   |Z
Z|                                                                           |Z
Z|  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  |Z
Z|  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               |Z
Z|  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   |Z
Z|  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     |Z
Z|  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     |Z
Z|  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        |Z
Z|  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   |Z
Z|                                                                           |Z
\*ZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZ*/


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
