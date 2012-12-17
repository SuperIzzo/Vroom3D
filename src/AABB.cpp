#include "AABB.h"


VROOM_BEGIN


//=================================================================
//	AABB::AABB
//---------------------------------------
AABB::AABB( const Vector3 &point1,	const Vector3 &point2)
{
	mMinPoint << min( point1.x(), point2.x() ),
				 min( point1.y(), point2.y() ),
				 min( point1.z(), point2.z() );

	mMaxPoint << max( point1.x(), point2.x() ),
				 max( point1.y(), point2.y() ),
				 max( point1.z(), point2.z() );
}





//=================================================================
//	AABB::GetMinPoint
//---------------------------------------
const Vector3& AABB::GetMinPoint()
{
	return mMinPoint;
}





//=================================================================
//	AABB::GetMaxPoint
//---------------------------------------
const Vector3& AABB::GetMaxPoint()
{
	return mMaxPoint;
}


VROOM_END