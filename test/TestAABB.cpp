#include <UnitTest++.h>
#include <AABB.h>

using namespace Vroom;

SUITE( AABB )
{
	struct BoxPercentSlice
	{
		BoxPercentSlice( AABB &aabb ) :
			aabbRef( aabb ),
			sliceDecimalPrecision( 0.01 )
		{
		}

		void CheckPercentSlicing(Vector3 direction, Real percent)
		{
			// Function under test here
			Polygon result = aabbRef.SliceByPercentage( direction, percent );

			// Check for correct number of points
			CHECK_EQUAL( expectedNumberOfPoints,	result.GetVertexCount() );

			// Check for correctness of the results
			for( int pointIdx=0; pointIdx<expectedNumberOfPoints; pointIdx++ )
			{
				CHECK_ARRAY_CLOSE( 
					expectedPoints[pointIdx],	
					result.GetVertex( pointIdx ),  
					3,
					sliceDecimalPrecision
				);
			}
		}

		Vector3 expectedPoints[6];
		int		expectedNumberOfPoints;
		Real	sliceDecimalPrecision;

	private:
		AABB	& aabbRef;
	};


	struct AABBCommon
	{
		AABBCommon()
		{
		}

		AABBCommon( Vector3 point1, Vector3 point2 ) :
			aabbPoint1( point1 ),
			aabbPoint2( point2 ),
			aabb( aabbPoint1, aabbPoint2 )
		{
		}

		Vector3 aabbPoint1;
		Vector3 aabbPoint2;
		AABB	aabb;
	};


	struct FIXTURE_UnitBox : public AABBCommon
	{
		FIXTURE_UnitBox() :
			AABBCommon(
				Vector3( 0,0,0 ),
				Vector3( 1,1,1 )
			)			
		{
		}
	};


	struct FIXTURE_GeneralBox : public AABBCommon
	{
		FIXTURE_GeneralBox() :
			AABBCommon(
				Vector3( 0,10,5 ),
				Vector3( 10,5,0 )
			)			
		{
		}
	};


	struct FIXTURE_UnitBoxPercentSlice : 
		public FIXTURE_UnitBox, public BoxPercentSlice
	{
		FIXTURE_UnitBoxPercentSlice()
			: BoxPercentSlice( aabb )
		{
		}
	};


	struct FIXTURE_GeneralBoxPercentSlice : 
		public FIXTURE_GeneralBox, public BoxPercentSlice
	{
		FIXTURE_GeneralBoxPercentSlice()
			: BoxPercentSlice( aabb )
		{
		}
	};


	TEST( TEST_default_contruction_of_AABB_makes_a_0_box )
	{
		AABB aabb;
		Vector3 zeroVector(0,0,0);

		Vector3 point1 = aabb.GetMinCorner();
		Vector3 point2 = aabb.GetMaxCorner();

		CHECK_EQUAL( zeroVector,	point1 );
		CHECK_EQUAL( zeroVector,	point2 );
	}



	TEST_FIXTURE( FIXTURE_GeneralBox, 
		TEST_AABB_correctly_identifies_min_and_max_point_coordinates )
	{
		Vector3 minPoint( 0, 5, 0 );
		Vector3 maxPoint( 10, 10, 5 );

		CHECK_EQUAL( minPoint,	aabb.GetMinCorner() );
		CHECK_EQUAL( maxPoint,	aabb.GetMaxCorner() );
	}


	TEST_FIXTURE( FIXTURE_GeneralBox,
		TEST_AABB_size_returns_correct_dimensions )
	{
		Vector3 expectedSize( 10, 5, 5 );

		CHECK_EQUAL( expectedSize, aabb.GetSize() );
	}


	TEST_FIXTURE( FIXTURE_GeneralBox, 
		TEST_AABB_closest_and_furhtest_point_for_direction )
	{
		// Direction 1
		Vector3 direction( 1, 1, 1 );
		direction.normalize();

		Vector3 near;
		Vector3 far;
		aabb.__GetNearAndFarCornersForDirection( direction, near, far );

		CHECK_EQUAL( Vector3( 0,5,0 ),		near );
		CHECK_EQUAL( Vector3( 10,10,5 ),	far  );

		// Direction 2
		direction << -1, 1, -1;
		direction.normalize();

		aabb.__GetNearAndFarCornersForDirection( direction, near, far );

		CHECK_EQUAL( Vector3( 10,5,5 ),		near );
		CHECK_EQUAL( Vector3( 0,10,0 ),		far  );
	}


	TEST_FIXTURE( FIXTURE_UnitBoxPercentSlice, 
		TEST_AABB_percentage_cut_edge_and_corner_at_0_and_1 )
	{
		Vector3 planeDirectionCorner(1,1,1);
		Vector3 planeDirectionEdge(1,1,0);

		planeDirectionCorner.normalize();
		planeDirectionEdge.normalize();

		expectedNumberOfPoints = 0;

		CheckPercentSlicing( planeDirectionCorner, 0 );
		CheckPercentSlicing( planeDirectionCorner, 1 );
		CheckPercentSlicing( planeDirectionEdge, 0 );
		CheckPercentSlicing( planeDirectionEdge, 1 );
	}


	TEST_FIXTURE( FIXTURE_UnitBoxPercentSlice, 
		TEST_AABB_percentage_cut_corner )
	{
		Vector3 planeDirection1( 1, 1, 1);
		Vector3 planeDirection2(-1,-1, 1);
		Vector3 planeDirection3( 1,-1,-1);
		planeDirection1.normalize();
		planeDirection2.normalize();
		planeDirection3.normalize();


		// Direction 1, percentage = 0.3
		expectedNumberOfPoints = 3;
		expectedPoints[0] << 0.9, 0, 0;
		expectedPoints[1] << 0, 0.9, 0;
		expectedPoints[2] << 0, 0, 0.9;

		CheckPercentSlicing( planeDirection1, 0.3 );


		// Direction 2, percentage = 0.5
		expectedNumberOfPoints = 6;
		expectedPoints[0] << 0,   1,   0.5;
		expectedPoints[1] << 0,   0.5, 0;
		expectedPoints[2] << 0.5, 0,   0;
		expectedPoints[3] << 1,   0,   0.5;
		expectedPoints[4] << 1,   0.5, 1;
		expectedPoints[5] << 0.5, 1,   1;

		CheckPercentSlicing( planeDirection2, 0.5 );


		// Direction 3, percentage = 0.6
		expectedNumberOfPoints = 6;
		expectedPoints[0] << 1,   1,   0.2;
		expectedPoints[1] << 1,   0.2, 1;
		expectedPoints[2] << 0.8, 0,   1;
		expectedPoints[3] << 0,   0,   0.2;
		expectedPoints[4] << 0,   0.2, 0;
		expectedPoints[5] << 0.8, 1,   0;

		CheckPercentSlicing( planeDirection3, 0.6 );
	}


	TEST_FIXTURE( FIXTURE_UnitBoxPercentSlice, 
		TEST_AABB_percentage_cut_edge )
	{
		Vector3 planeDirection1( 1, 1, 0);
		Vector3 planeDirection2(-1, 0, 1);
		Vector3 planeDirection3( 0,-1,-1);

		// For all tests
		expectedNumberOfPoints = 4;


		// Direction 1, percentage = 0.3
		expectedPoints[0] << 0.6, 0, 0;
		expectedPoints[1] << 0, 0.6, 0;
		expectedPoints[2] << 0, 0.6, 1;
		expectedPoints[3] << 0.6, 0, 1;

		CheckPercentSlicing( planeDirection1, 0.3 );


		// Direction 2, percentage = 0.6
		expectedPoints[0] << 0,   0, 0.2;
		expectedPoints[1] << 0,   1, 0.2;
		expectedPoints[2] << 0.8, 1, 1;
		expectedPoints[3] << 0.8, 0, 1;

		CheckPercentSlicing( planeDirection2, 0.6 );


		// Direction 3, percentage = 0.73
		expectedPoints[0] << 1, 0.54, 0;
		expectedPoints[1] << 1, 0, 0.54;
		expectedPoints[2] << 0, 0, 0.54;
		expectedPoints[3] << 0, 0.54, 0;

		CheckPercentSlicing( planeDirection3, 0.73 );
	}


	TEST_FIXTURE( FIXTURE_UnitBoxPercentSlice, 
		TEST_AABB_percentage_cut_side )
	{
		Vector3 planeDirection1( 1, 0,  0);
		Vector3 planeDirection2( 0, -1, 0);
		Vector3 planeDirection3( 0, 0,  1);

		// For all tests
		expectedNumberOfPoints = 4;


		// Direction 1, percentage = 0.3
		expectedPoints[0] << 0.3, 0, 0;
		expectedPoints[1] << 0.3, 1, 0;
		expectedPoints[2] << 0.3, 1, 1;
		expectedPoints[3] << 0.3, 0, 1;

		CheckPercentSlicing( planeDirection1, 0.3 );


		// Direction 2, percentage = 0.6
		expectedPoints[0] << 1, 0.4, 1;
		expectedPoints[1] << 1, 0.4, 0;
		expectedPoints[2] << 0, 0.4, 0;
		expectedPoints[3] << 0, 0.4, 1;

		CheckPercentSlicing( planeDirection2, 0.6 );


		// Direction 3, percentage = 0.73
		expectedPoints[0] << 1, 0, 0.73;
		expectedPoints[1] << 1, 1, 0.73;
		expectedPoints[2] << 0, 1, 0.73;
		expectedPoints[3] << 0, 0, 0.73;

		CheckPercentSlicing( planeDirection3, 0.73 );
	}


	TEST_FIXTURE( FIXTURE_GeneralBoxPercentSlice, 
		TEST_general_AABB_percentage_cut )
	{
		Vector3 planeDirection1( 1, -0.3, 0.4 );
		Vector3 planeDirection2( 0.2, 1, -0.8 );

		planeDirection1.normalize();
		planeDirection2.normalize();

		// Direction 1, percentage = 0.5
		expectedNumberOfPoints = 4;
		expectedPoints[0] << 6.75, 10, 0;
		expectedPoints[1] << 5.25, 5, 0;
		expectedPoints[2] << 3.25, 5, 5;
		expectedPoints[3] << 4.75, 10, 5;

		CheckPercentSlicing( planeDirection1, 0.5 );


		// Direction 2, percentage = 0.5
		expectedNumberOfPoints = 6;
		expectedPoints[0] << 10,  5,   0.625;
		expectedPoints[1] << 10,  8.5, 5;
		expectedPoints[2] << 2.5, 10,  5;
		expectedPoints[3] << 0,   10,  4.375;
		expectedPoints[4] << 0,   6.5, 0;
		expectedPoints[5] << 7.5, 5,   0;

		CheckPercentSlicing( planeDirection2, 0.5 );
	}
}