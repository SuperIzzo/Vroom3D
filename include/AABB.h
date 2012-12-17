#ifndef __VROOM_AABB_H__
#define __VROOM_AABB_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <MathCommon.h>


VROOM_BEGIN


class AABB
{
public:
							AABB(	const Vector3 &point1 = Vector3(0,0,0),
									const Vector3 &point2 = Vector3(0,0,0) );
							
	const Vector3		  &	GetMinPoint();
	const Vector3		  &	GetMaxPoint();

private:
	Vector3					mMinPoint;
	Vector3					mMaxPoint;
};


VROOM_END


#endif
