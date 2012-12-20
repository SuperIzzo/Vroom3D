#include <TexMapVolumeRenderer.h>
#include <UnitTest++.h>
#include <MoreUnitTest++.h>


using namespace Vroom;


SUITE( TexMapVolumeRenderer )
{
	TEST( TEST_texmap_renderer_can_create_a_rendering_node )
	{
		TexMapVolumeRenderer renderer;

		Node *node = renderer.CreateNode();

		CHECK_NOT_NULL( node );
	}

	TEST( TEST_volume_data_can_be_attached_to_texmap_node )
	{

	}



	TEST( TEST_renderer_can_render_opaque_objects_correctly )
	{

	}
}
