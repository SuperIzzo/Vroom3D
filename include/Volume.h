#ifndef __VROOM_VOLUME_H__
#define __VROOM_VOLUME_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <Platform.h>
#include <Color.h>





//=================================================================
//	Class Volume
//---------------------------------------
class Volume
{
public:
	static const UInt32		BYTES_PER_VOXEL;

public:
	// Constructors
							Volume();
							~Volume();

	// Getters
	UInt8				  *	GetData();
	UInt32					GetDataSize()	const;
	UInt32					GetWidth()		const;
	UInt32					GetHeight()		const;
	UInt32					GetDepth()		const;

	void					SetVoxel( UInt32 x, UInt32 y, UInt32 z, Color &col );

	void					Create( UInt32 inWidth, UInt32 inHeight, UInt32 inDepth );

private:
	void					CheckInRange(UInt32 x, UInt32 y, UInt32 z) const;

private:
	UInt32					mWidth;
	UInt32					mHeight;
	UInt32					mDepth;

	UInt8				  *	mData;
};





#endif