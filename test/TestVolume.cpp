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
#include <UnitTest++.h>
#include <MoreUnitTest++.h>
#include <VolumeData.h>

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

		VolumeData volume;
		UInt8 *voxelData;
		Color *voxelColorData;
	};



	TEST( TEST_default_volume_has_no_data_and_zeroed_dimensions )
	{
		VolumeData volume;

		CHECK_NULL( volume.GetData() );
		CHECK_EQUAL( 0,		volume.GetWidth()	);
		CHECK_EQUAL( 0,		volume.GetHeight()	);
		CHECK_EQUAL( 0,		volume.GetDepth()	);
	}



	TEST( TEST_default_volume_reports_zero_size )
	{
		VolumeData volume;

		CHECK_EQUAL( 0,		volume.GetDataSize()	);
	}



	TEST_FIXTURE( FIXTURE_EmptyVolume,	TEST_created_volume_has_correct_dimensions )
	{
		CHECK_EQUAL( 32,		volume.GetWidth()	);
		CHECK_EQUAL( 64,		volume.GetHeight()	);
		CHECK_EQUAL( 16,		volume.GetDepth()	);
	}



	TEST_FIXTURE( FIXTURE_EmptyVolume,	TEST_created_volume_has_clear_0_data )
	{		
		for( int attempt=0; attempt <20; attempt++ )
		{
			UInt32 byteIdx = (UInt32) rand() % volume.GetDataSize();

			CHECK_EQUAL( 0,		voxelData[byteIdx]	);
		}
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
