#include <Node.h>
#include <UnitTest++.h>
#include <MoreUnitTest++.h>


using namespace Vroom;


SUITE( Node )
{
	TEST( TEST_node_has_no_volume_attached_by_default )
	{
		Node node;

		CHECK_NULL( node.GetVolumeData() );
	}


	TEST( TEST_node_has_a_volume_after_attaching_and_doesnt_after_detaching )
	{
		Node node;

		VolumeData volume;
		node.SetVolumeData( &volume );

		CHECK_NOT_NULL( node.GetVolumeData() );

		node.SetVolumeData( 0 );

		CHECK_NULL( node.GetVolumeData() );
	}
}