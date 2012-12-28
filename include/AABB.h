#ifndef __VROOM_AABB_H__
#define __VROOM_AABB_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <Polygon.h>


VROOM_BEGIN


class AABB
{
public:
							AABB(	const Vector3 &point1 = Vector3(0,0,0),
									const Vector3 &point2 = Vector3(0,0,0) );
							
	const Vector3		  &	GetMinCorner();
	const Vector3		  &	GetMaxCorner();

	Vector3					GetSize();

	void					_GetNearAndFarCornersForDirection( Vector3 inDirection,	Vector3 &outNear, Vector3 &outFar);
	Polygon					SliceByPercentage( Vector3 inPlaneDir, Real inLocalPerc );

private:
	Vector3					mMinCorner;
	Vector3					mMaxCorner;
};


VROOM_END


#endif
