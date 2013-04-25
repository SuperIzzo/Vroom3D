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
#ifndef __VROOM_MATHCOMMON_H__
#define __VROOM_MATHCOMMON_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <Platform.h>
#include <Eigen\Dense>


VROOM_BEGIN


//=================================================================
//	Pulbic Definitions
//---------------------------------------
typedef Eigen::Matrix<Real, 3,1,0,3,1>					Vector3;
typedef Eigen::Matrix<Real, 4,1,0,4,1>					Vector4;
typedef Eigen::Matrix<Real, 4,4,0,4,4>					Matrix4;
typedef	Eigen::Transform<Real, 3, Eigen::Projective>	ProjectiveTransform;
typedef	Eigen::Transform<Real, 3, Eigen::Affine>		AffineTransform;





//=================================================================
//	min(a,b) : returns the smaller of a and b
//---------------------------------------
template<typename Type>
inline Type min(Type a, Type b)
{
	return (a < b) ? a : b;
}





//=================================================================
//	max(a,b) : returns the larger of a and b
//---------------------------------------
template<typename Type>
inline Type max(Type a, Type b)
{
	return (a > b) ? a : b;
}


VROOM_END


#endif
