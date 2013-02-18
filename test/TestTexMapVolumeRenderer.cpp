#include <TexMapVolumeRenderer.h>
#include <UnitTest++.h>
#include <MoreUnitTest++.h>


using namespace Vroom;


SUITE( TexMapVolumeRenderer )
{
	TEST( TEST_texmap_renderer_returns_the_root_rendering_node )
	{
		TexMapVolumeRenderer renderer;

		Node *node1 = renderer.GetRootNode();
		Node *node2 = renderer.GetRootNode();

		CHECK_NOT_NULL( node1 );
		CHECK_EQUAL( node1, node2 );
	}


	TEST( TEST_volume_data_can_be_attached_to_texmap_node )
	{

	}
}
