#include <Node.h>
#include <UnitTest++.h>
#include <MoreUnitTest++.h>


using namespace Vroom;


SUITE( Node )
{
	TEST( TEST_node_has_no_volume_attached_by_default )
	{
		Node node;

		CHECK_NULL( node.GetVolume() );
	}


	TEST( TEST_node_has_a_volume_after_attaching_and_doesnt_after_detaching )
	{
		Node node;

		Volume volume;
		node.SetVolume( &volume );

		CHECK_NOT_NULL( node.GetVolume() );

		node.SetVolume( 0 );

		CHECK_NULL( node.GetVolume() );
	}
}