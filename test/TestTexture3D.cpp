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

		CHECK_EQUAL( 0,	texture.GetWidth()	);
		CHECK_EQUAL( 0,	texture.GetHeight() );
		CHECK_EQUAL( 0,	texture.GetDepth()	);
	}


	TEST_FIXTURE( GraphicsFixture, TEST_creating_empty_texture_initializes_properly )
	{
		Texture3D texture;		

		texture.Create( 32, 16, 8 );

		CHECK( texture.IsValid() );
		CHECK_EQUAL( 32,	texture.GetWidth()	);
		CHECK_EQUAL( 16,	texture.GetHeight() );
		CHECK_EQUAL( 8,		texture.GetDepth()	);
	}


	TEST_FIXTURE( GraphicsFixture, TEST_recreating_empty_texture_initializes_properly )
	{
		Texture3D texture;

		texture.Create( 32, 16, 8 );
		texture.Create( 128, 256, 64 );

		CHECK( texture.IsValid() );
		CHECK_EQUAL( 128,	texture.GetWidth()	);
		CHECK_EQUAL( 256,	texture.GetHeight() );
		CHECK_EQUAL( 64,	texture.GetDepth()	);
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