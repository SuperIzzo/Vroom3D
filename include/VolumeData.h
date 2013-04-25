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
#ifndef __VROOM_VOLUMEDATA_H__
#define __VROOM_VOLUMEDATA_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <Color.h>
#include <SharedPointer.h>


VROOM_BEGIN


//=================================================================
//	Class VolumeData
//---------------------------------------
class VolumeData
{
public:
	static const UInt32		BYTES_PER_VOXEL;

public:
	// Constructors
							VolumeData();
							~VolumeData();

	// Getters
	UInt8				  *	GetData();
	const UInt8			  *	GetData()		const;
	UInt32					GetDataSize()	const;
	UInt32					GetWidth()		const;
	UInt32					GetHeight()		const;
	UInt32					GetDepth()		const;

	void					SetVoxel( UInt32 x, UInt32 y, UInt32 z, const Color &col );
	Color&					GetVoxel( UInt32 x, UInt32 y, UInt32 z);
	Color					GetVoxel( UInt32 x, UInt32 y, UInt32 z) const;

	void					Create( UInt32 inWidth, UInt32 inHeight, UInt32 inDepth );

private:
	void					CheckInRange(UInt32 x, UInt32 y, UInt32 z) const;
	void					Destroy();

private:
	UInt32					mWidth;
	UInt32					mHeight;
	UInt32					mDepth;

	UInt8				  *	mData;
};





//=================================================================
//	Type VolumeDataPtr
//---------------------------------------
typedef SharedPointer<VolumeData>::Type			VolumeDataPtr;


VROOM_END


#endif
