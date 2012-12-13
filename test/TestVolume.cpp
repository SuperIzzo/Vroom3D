#include <UnitTest++.h>
#include <MoreUnitTest++.h>
#include <Volume.h>

#include <IndexOutOfBoundsException.h>



SUITE( Volume )
{
	struct FIXTURE_EmptyVolume
	{
		FIXTURE_EmptyVolume()
		{
			volume.Create( 32, 64, 16 );
		}

		Volume volume;
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
		UInt8 *voxData = volume.GetData();
		Color *voxColorData = (Color*) voxData;
		Color color( 10, 220, 49, 130 );

		UInt32 voxelIndex = 10;
		voxColorData[voxelIndex] = color;

		CHECK_EQUAL( 10,	*( voxData + voxelIndex*4 + 0) );
		CHECK_EQUAL( 220,	*( voxData + voxelIndex*4 + 1) );
		CHECK_EQUAL( 49,	*( voxData + voxelIndex*4 + 2) );
		CHECK_EQUAL( 130,	*( voxData + voxelIndex*4 + 3) );

		CHECK_EQUAL( color.red,		*( voxData + voxelIndex*4 + 0) );
		CHECK_EQUAL( color.green,	*( voxData + voxelIndex*4 + 1) );
		CHECK_EQUAL( color.blue,	*( voxData + voxelIndex*4 + 2) );
		CHECK_EQUAL( color.alpha,	*( voxData + voxelIndex*4 + 3) );
	}



	TEST_FIXTURE( FIXTURE_EmptyVolume,	TEST_set_voxel_modifies_correct_place_in_memory )
	{
		UInt8 *voxData = volume.GetData();
		Color color( 0, 10, 30 );
		UInt32 x = 12;
		UInt32 y = 10;
		UInt32 z = 4;
		UInt32 voxelIndex = (z*volume.GetHeight() + y)*volume.GetWidth() + x; 

		volume.SetVoxel( x, y, z, color );

		CHECK_EQUAL( 0,		*(voxData + voxelIndex*4 + 0) );
		CHECK_EQUAL( 10,	*(voxData + voxelIndex*4 + 1) );
		CHECK_EQUAL( 30,	*(voxData + voxelIndex*4 + 2) );
		CHECK_EQUAL( 255,	*(voxData + voxelIndex*4 + 3) );
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