#include <UnitTest++.h>
#include <MoreUnitTest++.h>
#include <Volume.h>

#include <IndexOutOfBoundsException.h>


using namespace Vroom;


SUITE( Volume )
{
	struct FIXTURE_EmptyVolume
	{
		FIXTURE_EmptyVolume()
		{
			volume.Create( 32, 64, 16 );

			voxelData = volume.GetData();
			voxelColorData = (Color*) voxelData;
		}

		Volume volume;
		UInt8 *voxelData;
		Color *voxelColorData;
	};



	TEST( TEST_default_volume_has_no_data_and_zeroed_dimensions )
	{
		Volume volume;

		CHECK_NULL( volume.GetData() );
		CHECK_EQUAL( 0,		volume.GetWidth()	);
		CHECK_EQUAL( 0,		volume.GetHeight()	);
		CHECK_EQUAL( 0,		volume.GetDepth()	);
	}



	TEST( TEST_default_volume_reports_zero_size )
	{
		Volume volume;

		CHECK_EQUAL( 0,		volume.GetDataSize()	);
	}



	TEST_FIXTURE( FIXTURE_EmptyVolume,	TEST_created_volume_has_correct_dimensions )
	{
		CHECK_EQUAL( 32,		volume.GetWidth()	);
		CHECK_EQUAL( 64,		volume.GetHeight()	);
		CHECK_EQUAL( 16,		volume.GetDepth()	);
	}



	TEST_FIXTURE( FIXTURE_EmptyVolume,	TEST_created_volume_reports_correct_size )
	{
		const UInt32 expectedDataSize = 32*64*16 * 4;

		CHECK_EQUAL( expectedDataSize,		volume.GetDataSize() );
	} 



	TEST_FIXTURE( FIXTURE_EmptyVolume,	TEST_created_volume_has_non_null_data )
	{
		CHECK_NOT_NULL( volume.GetData() );
	}



	TEST_FIXTURE( FIXTURE_EmptyVolume,	TEST_created_volume_data_can_be_modified )
	{
		UInt8 *voxData = volume.GetData();
		*(voxData + 10) = 123;

		CHECK_EQUAL( 123,		*(volume.GetData()+10) );
	}



	TEST_FIXTURE( FIXTURE_EmptyVolume,	TEST_first_byte_of_created_volume_data_can_be_modified )
	{
		UInt8 *voxData = volume.GetData();
		*voxData = 123;

		CHECK_EQUAL( 123,		*volume.GetData() );
	}



	TEST_FIXTURE( FIXTURE_EmptyVolume,	TEST_last_byte_of_created_volume_data_can_be_modified )
	{
		UInt8 *voxData = volume.GetData();

		UInt32 lastByteOffset = volume.GetDataSize() - 1;
		*(voxData + lastByteOffset) = 123;

		CHECK_EQUAL( 123,		*(volume.GetData() + lastByteOffset) );
	}



	TEST_FIXTURE( FIXTURE_EmptyVolume,	TEST_volume_data_can_be_mapped_to_color_object )
	{
		Color color( 10, 220, 49, 130 );

		UInt32 voxelIndex = 10;
		voxelColorData[voxelIndex] = color;

		CHECK_EQUAL( 10,	*( voxelData + voxelIndex*4 + 0) );
		CHECK_EQUAL( 220,	*( voxelData + voxelIndex*4 + 1) );
		CHECK_EQUAL( 49,	*( voxelData + voxelIndex*4 + 2) );
		CHECK_EQUAL( 130,	*( voxelData + voxelIndex*4 + 3) );

		CHECK_EQUAL( color.red,		*( voxelData + voxelIndex*4 + 0) );
		CHECK_EQUAL( color.green,	*( voxelData + voxelIndex*4 + 1) );
		CHECK_EQUAL( color.blue,	*( voxelData + voxelIndex*4 + 2) );
		CHECK_EQUAL( color.alpha,	*( voxelData + voxelIndex*4 + 3) );
	}



	TEST_FIXTURE( FIXTURE_EmptyVolume,	TEST_set_voxel_modifies_correct_place_in_memory )
	{
		Color color( 0, 10, 30 );
		UInt32 x = 12;
		UInt32 y = 10;
		UInt32 z = 4;
		UInt32 voxelIndex = (z*volume.GetHeight() + y)*volume.GetWidth() + x; 

		volume.SetVoxel( x, y, z, color );

		CHECK_EQUAL( 0,		*(voxelData + voxelIndex*4 + 0) );
		CHECK_EQUAL( 10,	*(voxelData + voxelIndex*4 + 1) );
		CHECK_EQUAL( 30,	*(voxelData + voxelIndex*4 + 2) );
		CHECK_EQUAL( 255,	*(voxelData + voxelIndex*4 + 3) );
	}



	TEST_FIXTURE( FIXTURE_EmptyVolume,	TEST_set_reports_incorrect_voxel_indexing )
	{
		Color color( 0, 10, 30 );

		// x index exceeds the width
		CHECK_THROW( volume.SetVoxel( 32, 10, 4, color ),  IndexOutOfBoundsException );

		// y index exceeds the height
		CHECK_THROW( volume.SetVoxel( 0, 64, 4, color ),  IndexOutOfBoundsException );

		// z index exceeds the depth
		CHECK_THROW( volume.SetVoxel( 0, 10, 17, color ),  IndexOutOfBoundsException );
	}
}
