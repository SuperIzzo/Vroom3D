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
#ifndef __VROOM_TEXMAP_VOLUME_RENDERER_NODE_H__
#define __VROOM_TEXMAP_VOLUME_RENDERER_NODE_H__



//=================================================================
//	Inlude
//---------------------------------------
#include <VolumeData.h>
#include <MathCommon.h>
#include <Texture3D.h>

#include <vector>


VROOM_BEGIN


//=================================================================
//	Class RenderNode
//---------------------------------------
class RenderNode
{
public:
	friend class VolumeRenderer;

	enum DebugFlags {
			DBG_DRAW_BBOX		= 0x0001,
			DBG_DRAW_SLICES		= 0x0002
	};

public:
	void					SetNumberOfSlices( UInt32 numSlices );
	UInt32					GetNumberOfSlices();

	void					SetSliceSpacingExponent( Real exponent ); 
	Real					GetSliceSpacingExponent();

	void					SetDebugFlags(UInt32 debugFlags);
	UInt32					GetDebugFlags();

	void					SetLighting( bool enable );
	bool					GetLighting();

	void					SetVolumeData( VolumeData &volume );

	Texture3DPtr			GetNormalMap( bool generate = false );

	Matrix4					GetTransform() const;
	void					SetTransform( const Matrix4 &transf);

	char					showNorm;

protected:
							RenderNode();
	void					Draw(const Vector3 &cameraDir);

private:
	void					BindTexture();

	void					SetTransformMatrix();
	void					UnsetTransformMatrix();

	void					SetLightingMode(const Vector3 &cameraDir);
	void					UnsetLightingMode();

	// Eigen alignment operator
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

private:
	UInt32					mDebugFlags;
	Texture3DPtr		  	mTexture;
	Texture3DPtr			mNormalMap;

	UInt32					mNumSlices;
	Real					mSpacingExponent;
	Matrix4					mTransform;

	bool					mLighting;
};


VROOM_END


#endif