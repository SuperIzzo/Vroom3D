#ifndef __VROOM_PLATFORM_H__
#define __VROOM_PLATFORM_H__





//=================================================================
// Include
//---------------------------------------
#include <string>





//=================================================================
// Define namespace maros
//---------------------------------------
#define VROOM_BEGIN		namespace Vroom {
#define VROOM_END		};
#define Vroom			Vroom



VROOM_BEGIN


//=================================================================
// Types
//---------------------------------------
typedef unsigned char				UInt8;
typedef signed char					SInt8;
typedef unsigned short				UInt16;
typedef signed short				SInt16;
typedef unsigned int				UInt32;
typedef signed int					SInt32;
typedef unsigned long long int		UInt64;
typedef signed long long int		SInt64;

typedef float						Real;
typedef std::string					String;


VROOM_END


#endif
