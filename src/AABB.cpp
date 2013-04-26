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


//=================================================================
//	Inlude
//---------------------------------------
#include "AABB.h"


VROOM_BEGIN


//=================================================================
//	AABB::AABB
//---------------------------------------
AABB::AABB( const Vector3 &point1,	const Vector3 &point2)
{
	mMinCorner << min( point1.x(), point2.x() ),
				  min( point1.y(), point2.y() ),
				  min( point1.z(), point2.z() );

	mMaxCorner << max( point1.x(), point2.x() ),
				  max( point1.y(), point2.y() ),
				  max( point1.z(), point2.z() );
}





//=================================================================
//	AABB::GetMinCorner
//---------------------------------------
const Vector3& AABB::GetMinCorner()
{
	return mMinCorner;
}





//=================================================================
//	AABB::GetMaxCorner
//---------------------------------------
const Vector3& AABB::GetMaxCorner()
{
	return mMaxCorner;
}





//=================================================================
//	AABB::GetSize
//---------------------------------------
Vector3 AABB::GetSize() const
{
	return mMaxCorner - mMinCorner;
}





//=================================================================
//	AABB::PlaneCutByPercentage
//---------------------------------------
Polygon AABB::SliceByPercentage( Vector3 planeDir, Real percent ) const
{
	Polygon slice;

	if( percent > 0 && percent < 1 )
	{
		Vector3 closeBoxVertex, farBoxVertex;
		__GetNearAndFarCornersForDirection( planeDir, closeBoxVertex, farBoxVertex );

		Vector3 aabbSize = GetSize();

		// The slice ray is ray that goes trough all slices,
		// its direction is the plane normal
		// It's origin is the closest box point
		// It's length is the projection of the diagonal onto that normal, i.e. it is such that
		// The first slice (0) goes trough close point 
		// and the last slice (1) goes trough the far point
		float sliceRayLength = planeDir.dot( farBoxVertex - closeBoxVertex );
		Real step = sliceRayLength * percent;

		Vector3 points[6];
				points[0] = closeBoxVertex;
				points[1] = closeBoxVertex;
				points[2] = closeBoxVertex;
				points[3] = closeBoxVertex;
				points[4] = closeBoxVertex;
				points[5] = closeBoxVertex;

		for(int axis= 0; axis< 3; axis++)
		{
			// We have 6 vertices, main vertices (vertexA) and split Verices (vertexB)
			int vertexA = axis*2; 
			int vertexB = vertexA+1;

			points[vertexA][axis] += step/planeDir[axis];

			// If the point grows beyond it's initial axis segment 
			if( abs(points[vertexA][axis]-closeBoxVertex[axis]) >= aabbSize[axis] )
			{
				int nextAxis = (axis + 1)%3;
				int prevAxis = (axis + 2)%3;				

				// Then split the two vertices and bend their trajectories
				// to the other two axes
				if( planeDir[axis] != 0 )
				{
					float diff = points[vertexA][axis]-farBoxVertex[axis];

					points[vertexA][prevAxis] += diff/planeDir[prevAxis]*planeDir[axis];
					points[vertexB][nextAxis] += diff/planeDir[nextAxis]*planeDir[axis];
				}
				else
				{
					points[vertexA][prevAxis] += step/planeDir[prevAxis];
					points[vertexB][nextAxis] += step/planeDir[nextAxis];
				}

				points[vertexA][axis] = farBoxVertex[axis];
				points[vertexB][axis] = farBoxVertex[axis];


				if( abs(points[vertexA][prevAxis]-closeBoxVertex[prevAxis]) >= aabbSize[prevAxis] )
				{
					if( planeDir[prevAxis] != 0 )
					{
						float diff = points[vertexA][prevAxis]-farBoxVertex[prevAxis];

						points[vertexA][nextAxis] += diff/planeDir[nextAxis]*planeDir[prevAxis];
					}
					else
					{
						// Duplicate Point
						points[vertexA][nextAxis] = points[vertexB][nextAxis];
					}

					points[vertexA][prevAxis] = farBoxVertex[prevAxis];
				}

				if( abs(points[vertexB][nextAxis]-closeBoxVertex[nextAxis]) >= aabbSize[nextAxis] )
				{
					if( planeDir[nextAxis] != 0 )
					{
						float diff = points[vertexB][nextAxis]-farBoxVertex[nextAxis];

						points[vertexB][prevAxis] += diff/planeDir[prevAxis]*planeDir[nextAxis];
					}
					else
					{
						// Duplicate Point
						points[vertexB][prevAxis] = points[vertexA][prevAxis];
					}

					points[vertexB][nextAxis] = farBoxVertex[nextAxis];
				}
			}
			else
			{
				// Duplicate Point
				points[vertexB][axis] = points[vertexA][axis];
			}
		}


		for( int i=0; i< 6; i++)
		{
			int j = i+1;
			
			if( j>= 6 )
				j -=6;

			if( (points[i] - points[j]).norm() > 0.01 )
			{
				slice.AddVertex( points[i] );		
			}
		}
	}

	return slice;
}





//=================================================================
//	AABB::_GetNearAndFarDirectionCorners
//---------------------------------------
void AABB::__GetNearAndFarCornersForDirection(	Vector3 inDirection,
												Vector3 &outNear,
												Vector3 &outFar ) const
{
	for( int axis=0; axis<3; axis++ )
	{

		if( inDirection[axis] >= 0 )
		{
			outNear[axis]	= mMinCorner[axis];
			outFar[axis]	= mMaxCorner[axis];
		}
		else
		{
			outNear[axis]	= mMaxCorner[axis];
			outFar[axis]	= mMinCorner[axis];
		}
	}
}


VROOM_END