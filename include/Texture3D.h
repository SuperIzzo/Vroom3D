#ifndef __VROOM_TEXTURE_3D_H__
#define __VROOM_TEXTURE_3D_H__



//=================================================================
//	Inlude
//---------------------------------------
#include <Volume.h>


VROOM_BEGIN


//=================================================================
//	Class Texture3D
//---------------------------------------
class Texture3D
{
public:
	enum ScalingFilter
	{
		SF_LINEAR,
		SF_NEAREST
	};

public:
							Texture3D();
							Texture3D( const Volume &volume );

	void					CreateFromVolume( const Volume &volume );

	void					Destroy();

	void					SetScalingFilter( ScalingFilter magFilter );
	void					SetScalingFilter( ScalingFilter magFilter, ScalingFilter minFilter );

	bool					Bind( UInt8 unit = 0 );
	bool					Unbind( UInt8 unit = 0 );

private:
	void					SetWrapFunction( int func );

private:
	UInt32					mTextureID;
};


VROOM_END


#endif