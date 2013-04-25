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


//=================================================================
//	Include
//---------------------------------------
#include "Camera.h"


VROOM_BEGIN


//=================================================================
//	Camera::GetView
//---------------------------------------
AffineTransform Camera::GetView()
{
	return mView;
}





//=================================================================
//	Camera::SetView
//---------------------------------------
void Camera::SetView( const AffineTransform &view )
{
	mView = view;
}





//=================================================================
//	Camera::GetProjection
//---------------------------------------
ProjectiveTransform Camera::GetProjection()
{
	return mProjection;
}





//=================================================================
//	Camera::SetProjection
//---------------------------------------
void Camera::SetProjection( const ProjectiveTransform &projection )
{
	mProjection = projection;
}





//=================================================================
//	Camera::SetOrthographicProjection
//---------------------------------------
/// Sets orthographic projection, the code is based on 
///	http://en.wikipedia.org/wiki/Orthographic_projection_(geometry)
void Camera::SetOrthographicProjection( Real l, Real r, 
										Real b, Real t,
										Real n, Real f)
{
	Matrix4 mat;
	
	mat <<	2/(r - l),	0,			0,			-(r+l)/(r-l),
			0,			2/(t - b),	0,			-(t+b)/(t-b),
			0,			0,			-2/(f - n),	-(f+n)/(f-n),
			0,			0,			0,			1;

	mProjection = mat;
}





//=================================================================
//	Camera::GetForward
//---------------------------------------
Vector3 Camera::GetForward()
{
	Vector3	cameraDir;

	// Camera forward vector
	Vector4 origin			= Vector4(0, 0, 0, 1);
	Vector4	forwardDir		= Vector4(0, 0, 1, 1);

	Vector4 newForwardDir	= mView.inverse() * forwardDir;
	Vector4 newOrigin		= mView.inverse() * origin;

	newForwardDir		   /= newForwardDir.w();
	newOrigin			   /= newOrigin.w();

	cameraDir <<	newForwardDir.x() - newOrigin.x(),
					newForwardDir.y() - newOrigin.y(),
					newForwardDir.z() - newOrigin.z();

	cameraDir.normalize();

	return -cameraDir;

	// TODO
	// Fix the direction
	// Shader stuff in the renderer - currently things are in Node
	// Move matrices to shaders
}


VROOM_END