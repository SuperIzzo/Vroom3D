#include <UnitTest++.h>
#include <AABB.h>

using namespace Vroom;

SUITE( AABB )
{
	TEST( TEST_default_contruction_of_AABB_makes_a_0_box )
	{
		AABB aabb;
		Vector3 zeroVector(0,0,0);

		Vector3 point1 = aabb.GetMinPoint();
		Vector3 point2 = aabb.GetMaxPoint();

		CHECK_EQUAL( zeroVector,	point1 );
		CHECK_EQUAL( zeroVector,	point2 );
	}



	TEST( TEST_AABB_correctly_identifies_min_and_max_point_coordinates )
	{
		Vector3 point1( 0, 10, 5 );
		Vector3 point2( 10, 5, 0 );

		AABB aabb( point1, point2 );

		Vector3 minPoint( 0, 5, 0 );
		Vector3 maxPoint( 10, 10, 5 );

		CHECK_EQUAL( minPoint,	aabb.GetMinPoint() );
		CHECK_EQUAL( maxPoint,	aabb.GetMaxPoint() );
	}
}