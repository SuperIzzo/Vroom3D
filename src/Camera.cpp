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