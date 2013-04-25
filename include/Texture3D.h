#ifndef __VROOM_TEXTURE_3D_H__
#define __VROOM_TEXTURE_3D_H__



//=================================================================
//	Inlude
//---------------------------------------
#include <VolumeData.h>
#include <GraphicsHardwareException.h>
#include <InvalidStateException.h>


VROOM_BEGIN


//=================================================================
//	Class Texture3D
//---------------------------------------
class Texture3D
{
public:
							Texture3D();
							Texture3D( const VolumeData &volume );
							~Texture3D();

	void					Create( const VolumeData &volume );
	void					Create( UInt32 width, 
									UInt32 height,
									UInt32 depth );
	void					Destroy();

	bool					Bind( UInt8 unit = 0 ) const;
	bool					Unbind( UInt8 unit = 0 ) const;

	bool					IsValid() const;

	void					SetSmooth( bool smooth );
	bool					IsSmooth() const;

	UInt32					GetWidth() const;
	UInt32					GetHeight() const;
	UInt32					GetDepth() const;

	void					GetVolumeData( VolumeData &volume ) const;

	UInt32					__GetTextureID() const;

private:
	void					CreateFromData( UInt32 width, 
											UInt32 height, 
											UInt32 depth, 
											void *data);

	void					SetWrapFunction( int func );

private:
	UInt32					mTextureID;
};





//=================================================================
//	Type Texture3DPtr
//---------------------------------------
typedef SharedPointer<Texture3D>::Type		Texture3DPtr;


VROOM_END


#endif