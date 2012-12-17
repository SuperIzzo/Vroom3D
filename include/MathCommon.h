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
typedef Eigen::Vector3f		Vector3;





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
