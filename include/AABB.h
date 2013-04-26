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
#ifndef __VROOM_AABB_H__
#define __VROOM_AABB_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <Polygon.h>


VROOM_BEGIN


//=================================================================
//	Class AABB
//---------------------------------------
class AABB
{
public:
						AABB(	const Vector3 &point1 = Vector3(0,0,0),
								const Vector3 &point2 = Vector3(0,0,0) );
							
	const Vector3	  &	GetMinCorner();
	const Vector3	  &	GetMaxCorner();

	Vector3				GetSize() const;

	Polygon				SliceByPercentage( Vector3 inPlaneDir, Real inLocalPerc ) const;

	void				__GetNearAndFarCornersForDirection( 
														Vector3 inDirection,
														Vector3 &outNear,
														Vector3 &outFar	) const;	

private:
	Vector3				mMinCorner;
	Vector3				mMaxCorner;
};


VROOM_END


#endif
