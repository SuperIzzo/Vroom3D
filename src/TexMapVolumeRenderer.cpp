//=================================================================
//	Inlude
//---------------------------------------
#include "TexMapVolumeRenderer.h"
#include "TexMapVolumeRendererNode.h"
#include "AABB.h"

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

VROOM_BEGIN


//=================================================================
//	TexMapVolumeRenderer::TexMapVolumeRenderer
//---------------------------------------
TexMapVolumeRenderer::TexMapVolumeRenderer() :
	mRootNode(0)
{
}





//=================================================================
//	TexMapVolumeRenderer::~TexMapVolumeRenderer
//---------------------------------------
TexMapVolumeRenderer::~TexMapVolumeRenderer()
{
	delete mRootNode;
}





//=================================================================
//	TexMapVolumeRenderer::GetRootNode
//---------------------------------------
Node * TexMapVolumeRenderer::GetRootNode()
{
	if( !mRootNode )
	{
		mRootNode = new TexMapVolumeRendererNode();
	}

	return mRootNode;
}





//=================================================================
//	TexMapVolumeRenderer::SetupRenderingState
//---------------------------------------
void TexMapVolumeRenderer::SetupRenderingState()
{
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	glEnable( GL_DEPTH_TEST );
}



typedef Eigen::Matrix<Real, 4, 4>	Matrix4;
Matrix4 OrthographicProjection( Real l, Real r, 
								Real b, Real t,
								Real n, Real f)
{
	// http://en.wikipedia.org/wiki/Orthographic_projection_(geometry)

	Matrix4 mat;
	
	mat <<	2/(r - l), 0, 0, -(r+l)/(r-l),
			0, 2/(t - b), 0, -(t+b)/(t-b),
			0, 0, -2/(f - n), -(f+n)/(f-n),
			0, 0, 0, 1;

	return mat;
}


static Eigen::Vector3f cameraDir;

void SetCamera()
{
	static double angle = 0;
	angle += 0.1;

	Eigen::Transform<float,3, Eigen::Projective> transf;
			
	transf =	
		(
		Eigen::Translation3f( 0,0, -5 )
					*
		Eigen::AngleAxisf( (angle*0.002+30)/180.f*3.14f, Eigen::Vector3f(1,0,0) )
					*	
		Eigen::AngleAxisf( angle*10/180.f, Eigen::Vector3f(0,1,0) )
					*
		Eigen::Translation3f( -0.5, -0.5, -0.5)
		);

	transf = OrthographicProjection(-1, 1, -1, 1, 0, 100) * transf;

	// Camera forward vector
	Eigen::Vector4f homogenCamDir = transf.inverse() * Eigen::Vector4f(0,0, 1, 1);

	cameraDir <<	homogenCamDir.x() / homogenCamDir.w(),
					homogenCamDir.y() / homogenCamDir.w(),
					homogenCamDir.z() / homogenCamDir.w();


	// Do view transformations here...
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( transf.data() );
}


void Translate(float x, float y, float z)
{
	Eigen::Transform<float,3, Eigen::Affine> transf;
	transf = Eigen::Translation3f( x, y, z);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf( transf.data() );
}

//=================================================================
//	TexMapVolumeRenderer::Render
//---------------------------------------
void TexMapVolumeRenderer::Render()
{
	// Setup the rendering state
	SetupRenderingState();

	// Setup camera
	SetCamera();

	Translate(0,0,0);
	// Draw nodes
	mRootNode->Draw(cameraDir);


	Translate(0.2,0, -1);
	// Draw nodes
	mRootNode->Draw(cameraDir);
}



VROOM_END

