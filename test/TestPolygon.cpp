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
#include <Polygon.h>

using namespace Vroom;

SUITE( Polygon )
{
	struct FIXTURE_DefaultPolygon
	{
		FIXTURE_DefaultPolygon()
		{
			point1 << 0, 10, 13;
			point2 << 12, 90, 1;
			point3 << 3, 13, 26;
		}

		Polygon polygon;
		Vector3 point1;
		Vector3 point2;
		Vector3 point3;
	};


	TEST_FIXTURE( FIXTURE_DefaultPolygon, 
		TEST_adding_vertices_to_a_polygon_changes_its_vert_count )
	{
		CHECK_EQUAL( 0,		polygon.GetVertexCount() );

		polygon.AddVertex( point1 );
		CHECK_EQUAL( 1,		polygon.GetVertexCount() );

		polygon.AddVertex( point2 );
		CHECK_EQUAL( 2,		polygon.GetVertexCount() );

		polygon.AddVertex( point2 );
		CHECK_EQUAL( 3,		polygon.GetVertexCount() );

		polygon.AddVertex( point1 );
		CHECK_EQUAL( 4,		polygon.GetVertexCount() );
	}


	TEST_FIXTURE( FIXTURE_DefaultPolygon,
		TEST_added_vertices_can_be_retrieved_from_the_polygon )
	{
		polygon.AddVertex( point1 );
		polygon.AddVertex( point2 );
		polygon.AddVertex( point3 );
		polygon.AddVertex( point1 );

		CHECK_EQUAL( point1,	polygon.GetVertex(0) );
		CHECK_EQUAL( point2,	polygon.GetVertex(1) );
		CHECK_EQUAL( point3,	polygon.GetVertex(2) );
		CHECK_EQUAL( point1,	polygon.GetVertex(3) );
	}


	TEST_FIXTURE( FIXTURE_DefaultPolygon,
		TEST_added_vertices_can_be_removed_from_polygons )
	{
		polygon.AddVertex( point1 );
		polygon.AddVertex( point2 );
		polygon.AddVertex( point3 );
		polygon.AddVertex( point1 );

		polygon.RemoveVertex( 2 );
		CHECK_EQUAL( 3,			polygon.GetVertexCount() );
		CHECK_EQUAL( point1,		polygon.GetVertex(2) );

		polygon.RemoveVertex( 0 );
		CHECK_EQUAL( 2,			polygon.GetVertexCount() );
		CHECK_EQUAL( point1,		polygon.GetVertex(1) );

		polygon.RemoveVertex( 1 );
		CHECK_EQUAL( 1,			polygon.GetVertexCount() );
		CHECK_EQUAL( point2,		polygon.GetVertex(0) );
	}
}