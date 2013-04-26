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
#ifndef __VROOM_NORMAL_MAP_GENERATOR_H__
#define __VROOM_NORMAL_MAP_GENERATOR_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <Texture3D.h>
#include <ShaderProgram.h>



VROOM_BEGIN


enum NMImplementationEnum
{		
	NM_SOFTWARE			= 0x0,
	NM_HARDWARE			= 0x1
};

enum NMTransparencyEnum
{		
	NM_OPAQUE			= 0x0,
	NM_TRANSPARENT		= 0x10
};

enum NMQualityEnum
{		
	NM_QUALITY_POOR		= 0x0,
	NM_QUALITY_GOOD		= 0x100
};




	
//=================================================================
//	Class NormalMapGenerator
//---------------------------------------
class NormalMapGenerator
{
public:	
	static Texture3DPtr			Generate( Texture3D &volume, UInt32 flags =0 );
	static void					SetShader( ShaderProgramPtr shader );

private:
	static VolumeDataPtr		GenerateSWOpaque( VolumeData &volume,
											  NMQualityEnum quality);

	static Texture3DPtr			GenerateHWOpaque( Texture3D &texture, 
											  NMQualityEnum quality);

private:
	static ShaderProgramPtr		mNormalShader;
};


VROOM_END


#endif