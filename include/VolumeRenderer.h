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
#ifndef __VROOM_TEXMAP_VOLUME_RENDERER_H__
#define __VROOM_TEXMAP_VOLUME_RENDERER_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <RenderNode.h>
#include <ShaderProgram.h>
#include <Camera.h>
#include <map>


VROOM_BEGIN


//=================================================================
//	Class VolumeRenderer
//---------------------------------------
class VolumeRenderer
{
public:
							VolumeRenderer();
	virtual					~VolumeRenderer();

	virtual RenderNodePtr	CreateNode(const String &name);
	virtual void			RemoveNode(const String &name);
	virtual RenderNodePtr	GetNode(const String &name);

	virtual void			Render();

	void					SetShaderProgram( ShaderProgramPtr shader );
	ShaderProgramPtr		GetShaderProgram();

	CameraPtr				GetCamera();					

private:
	typedef std::map<String, RenderNodePtr>		NodeMap;

	void					SetupRenderingState();
	void					SetupLighting();
	void					SetupCamera();
	void					DebugDrawNode( RenderNode *node );
	void					DrawNode( RenderNode *node );			

private:		
	NodeMap					mNodes;	
	ShaderProgramPtr		mShaderProgram;
	bool					mLightingEnabled;
	CameraPtr				mCamera;
};


VROOM_END


#endif
