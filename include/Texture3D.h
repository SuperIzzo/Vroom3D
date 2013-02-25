#ifndef __VROOM_TEXTURE_3D_H__
#define __VROOM_TEXTURE_3D_H__



//=================================================================
//	Inlude
//---------------------------------------
#include <VolumeData.h>
#include <SharedPointer.h>


VROOM_BEGIN


//=================================================================
//	Class Texture3D
//---------------------------------------
class Texture3D
{
public:
							Texture3D();
							Texture3D( const VolumeData &volume );

	void					CreateFromVolume( const VolumeData &volume );
	void					Destroy();

	bool					Bind( UInt8 unit = 0 );
	bool					Unbind( UInt8 unit = 0 );

	bool					IsValid() const;

	void					SetSmooth( bool smooth );
	bool					IsSmooth() const;

private:
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