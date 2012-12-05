#include <UnitTest++.h>
#include <MoreUnitTest++.h>
#include "Volume.h"

SUITE( Vector )
{
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



	TEST( TEST_created_volume_has_correct_dimensions )
	{
		Volume volume;

		volume.Create( 32, 64, 16 );

		CHECK_EQUAL( 32,		volume.GetWidth()	);
		CHECK_EQUAL( 64,		volume.GetHeight()	);
		CHECK_EQUAL( 16,		volume.GetDepth()	);
	}



	TEST( TEST_created_volume_reports_correct_size )
	{
		Volume volume;

		volume.Create( 32, 64, 16 );
		const UInt32 expectedDataSize = 32*64*16 * 4;

		CHECK_EQUAL( expectedDataSize,		volume.GetDataSize() );
	} 



	TEST( TEST_created_volume_has_non_null_data )
	{
		Volume volume;

		volume.Create( 32, 64, 16 );

		CHECK_NOT_NULL( volume.GetData() );
	}



	TEST( TEST_created_volume_data_can_be_modified )
	{
		Volume volume;

		volume.Create( 32, 64, 16 );
		UInt8 *voxData = volume.GetData();
		*(voxData + 10) = 123;

		CHECK_EQUAL( 123,		*(volume.GetData()+10) );
	}



	TEST( TEST_first_byte_of_created_volume_data_can_be_modified )
	{
		Volume volume;

		volume.Create( 32, 64, 16 );
		UInt8 *voxData = volume.GetData();
		*voxData = 123;

		CHECK_EQUAL( 123,		*volume.GetData() );
	}



	TEST( TEST_last_byte_of_created_volume_data_can_be_modified )
	{
		Volume volume;
		
		volume.Create( 32, 64, 16 );
		UInt8 *voxData = volume.GetData();

		UInt32 lastByteOffset = volume.GetDataSize() - 1;
		*(voxData + lastByteOffset) = 123;

		CHECK_EQUAL( 123,		*(volume.GetData() + lastByteOffset) );
	}
}