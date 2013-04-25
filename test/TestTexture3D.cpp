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
#include <Texture3D.h>
#include "GraphicsFixture.h"

#include <UnitTest++.h>
#include <MoreUnitTest++.h>
#include <iostream>


using namespace Vroom;



SUITE( Texture3D )
{
	TEST_FIXTURE( GraphicsFixture, TEST_unitialize_texture_ )
	{
		Texture3D texture;

		CHECK_NOT( texture.IsValid() );
		CHECK_EQUAL( 0,	glGetError() );

		CHECK_EQUAL( 0,	texture.GetWidth()	);
		CHECK_EQUAL( 0,	glGetError() );

		CHECK_EQUAL( 0,	texture.GetHeight() );
		CHECK_EQUAL( 0,	glGetError() );

		CHECK_EQUAL( 0,	texture.GetDepth()	);
		CHECK_EQUAL( 0,	glGetError() );
	}


	TEST_FIXTURE( GraphicsFixture, TEST_creating_empty_texture_initializes_properly )
	{
		Texture3D texture;		

		texture.Create( 32, 16, 8 );
		CHECK_EQUAL( 0,	glGetError() );

		CHECK( texture.IsValid() );
		CHECK_EQUAL( 0,	glGetError() );

		CHECK_EQUAL( 32,	texture.GetWidth()	);
		CHECK_EQUAL( 0,	glGetError() );

		CHECK_EQUAL( 16,	texture.GetHeight() );
		CHECK_EQUAL( 0,	glGetError() );

		CHECK_EQUAL( 8,		texture.GetDepth()	);
		CHECK_EQUAL( 0,	glGetError() );
	}


	TEST_FIXTURE( GraphicsFixture, TEST_recreating_empty_texture_initializes_properly )
	{
		Texture3D texture;


		texture.Create( 32, 16, 8 );		
		texture.Create( 128, 32, 64 );
		CHECK_EQUAL( 0,	glGetError() );


		CHECK( texture.IsValid() );
		CHECK_EQUAL( 0,	glGetError() );

		CHECK_EQUAL( 128,	texture.GetWidth()	);
		CHECK_EQUAL( 0,	glGetError() );

		CHECK_EQUAL( 32,	texture.GetHeight() );
		CHECK_EQUAL( 0,	glGetError() );

		CHECK_EQUAL( 64,	texture.GetDepth()	);
		CHECK_EQUAL( 0,	glGetError() );
	}


	TEST_FIXTURE( GraphicsFixture, TEST_creating_from_volume_initializes_properly )
	{		
		Texture3D texture;
		VolumeData volume;

		volume.Create( 32, 64, 16 );
		texture.Create( volume );

		CHECK( texture.IsValid() );
		CHECK_EQUAL( 32,	texture.GetWidth()	);
		CHECK_EQUAL( 64,	texture.GetHeight() );
		CHECK_EQUAL( 16,	texture.GetDepth()	);
	}


	TEST_FIXTURE( GraphicsFixture, TEST_invalidation_of_texture_on_destruction )
	{
		Texture3D texture;

		texture.Create( 32, 16, 8 );
		texture.Destroy();

		CHECK_NOT( texture.IsValid() );
	}


	TEST_FIXTURE( GraphicsFixture, TEST_volume_data_is_obtainable_from_texture )
	{
		const Color testColor1(128, 250, 120, 255);
		const Color testColor2(12, 56, 34, 255);

		Texture3D texture;
		VolumeData volume1;
		VolumeData volume2;

		// This should fail, because we never created the texture
		CHECK_THROW(texture.GetVolumeData(volume1), InvalidStateException );

		volume1.Create(32,16,8);
		volume1.SetVoxel( 2,3,6,	testColor1 );
		volume1.SetVoxel( 15,15,3,	testColor2 );

		// This should work, because we will create it now
		texture.Create( volume1 );
		texture.GetVolumeData( volume2 );

		CHECK( testColor1 == volume2.GetVoxel(2,3,6) );
		CHECK( testColor2 == volume2.GetVoxel(15,15,3) );
	}
}