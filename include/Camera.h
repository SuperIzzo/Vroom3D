#ifndef __VROOM_CAMERA_H__
#define __VROOM_CAMERA_H__



//=================================================================
//	Inlude
//---------------------------------------
#include <MathCommon.h>
#include <SharedPointer.h>


VROOM_BEGIN


//=================================================================
//	Class Camera
//---------------------------------------
class Camera
{
public:
	AffineTransform			GetView();
	void					SetView( const AffineTransform &view );

	ProjectiveTransform		GetProjection();
	void					SetProjection( const ProjectiveTransform &projection );


	void					SetOrthographicProjection( Real left,	Real right, 
													   Real bottom, Real top,
													   Real near,	Real far);

	Vector3					GetForward();

	// Eigen alignment operator
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

private:
	AffineTransform			mView;
	ProjectiveTransform		mProjection;
};





//=================================================================
//	Type CameraPtr
//---------------------------------------
typedef SharedPointer<Camera>::Type		CameraPtr;


VROOM_END


#endif