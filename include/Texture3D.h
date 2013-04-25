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