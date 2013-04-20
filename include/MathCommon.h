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
