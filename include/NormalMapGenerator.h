#ifndef __VROOM_NORMAL_MAP_GENERATOR_H__
#define __VROOM_NORMAL_MAP_GENERATOR_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <Texture3D.h>



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
	static Texture3DPtr		Generate( Texture3D &volume, UInt32 flags = 0 );

private:
	static VolumeDataPtr	GenerateSWOpaque( VolumeData &volume,
											  NMQualityEnum quality);

	static Texture3DPtr		GenerateHWOpaque( Texture3D &texture, 
											  NMQualityEnum quality);
};


VROOM_END


#endif