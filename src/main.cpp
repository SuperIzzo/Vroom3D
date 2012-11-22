#include <UnitTest++.h>
#include <iostream>

#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GLX/glext.h>

#include <vector>

class AABB
{
public:
	Eigen::Vector3f min;
	Eigen::Vector3f max;
};


class SliceBox
{
public:
	AABB box;

	void draw(Eigen::Vector3f view);
};

/*
{
	for( int i=0; i< xSliceNum; i++ )
	{
		float xTex = i/(float)xSliceNum;
		float xCoord = box.min.x() + (box.max.x() - box.min.x()) * xTex;

		glBegin( GL_TRIANGLE_FAN );

			glTexCoord3d(xTex, 0, 0);
			glVertex3d(xCoord, box.min.y(), box.min.z());

			glTexCoord3d(xTex, 0, 1);
			glVertex3d(xCoord, box.min.y(), box.max.z());

			glTexCoord3d(xTex, 1, 1);
			glVertex3d(xCoord, box.max.y(), box.max.z());

			glTexCoord3d(xTex, 1, 0);
			glVertex3d(xCoord, box.max.y(), box.min.z());

		glEnd();
	}

	for( int i=0; i< zSliceNum; i++ )
	{
		float zTex = i/(float)zSliceNum;
		float zCoord = box.min.z() + (box.max.z() - box.min.z()) * zTex;

		glBegin( GL_TRIANGLE_FAN );

			glTexCoord3d(0, 0, zTex);
			glVertex3d(box.min.x(), box.min.y(), zCoord );

			glTexCoord3d(0, 1, zTex);
			glVertex3d(box.min.x(), box.max.y(), zCoord );

			glTexCoord3d(1, 1, zTex);
			glVertex3d(box.max.x(), box.max.y(), zCoord );

			glTexCoord3d(1, 0, zTex);
			glVertex3d(box.max.x(), box.min.y(), zCoord );

		glEnd();
	}
}
*/

void SliceBox::draw(Eigen::Vector3f view)
{
	Eigen::Vector3f xDir(1,0,0);
	Eigen::Vector3f yDir(0,1,0);
	Eigen::Vector3f zDir(0,0,1);

	int sliceNum = 100;

	// We can do with an inverse view vectr (because the cosine doesn't change :)
	float xcos = view.dot( xDir );
	float ycos = view.dot( yDir );
	float zcos = view.dot( zDir );

	// The sum of xcos^2 + ycos^2 + zcos^2 = 1
	float xcos_sq = xcos * xcos;
	float ycos_sq = ycos * ycos;
	float zcos_sq = zcos * zcos;

	// The sign of the cosine tells us the order of the
	// planes -1 is back to front; 1 is front to back
	int x_sign = xcos>0 ? 1 : -1;
	int y_sign = ycos>0 ? 1 : -1;
	int z_sign = zcos>0 ? 1 : -1;

	float xStep = 1;//xcos_sq; //abs(xcos) > abs(ycos) && abs(xcos) >= abs(zcos);
	float yStep = 1;//ycos_sq; //abs(ycos) > abs(zcos) && abs(ycos) >= abs(xcos);
	float zStep = 1;//zcos_sq; //abs(zcos) > abs(xcos) && abs(zcos) >= abs(ycos);

	float stepLen = xStep + yStep + zStep;
	xStep /= stepLen;
	yStep /= stepLen;
	zStep /= stepLen;

	float x_accum = 0;
	float y_accum = 0;
	float z_accum = 0;

	for( int i=0; i< sliceNum; i++ )
	{
		x_accum+= xStep;
		y_accum+= yStep;
		z_accum+= zStep;

		if( x_accum >= 1)
		{
			x_accum-=1;

			float xTex;
			if( x_sign < 0 )
				xTex = (sliceNum - (i+0.5))/(float)sliceNum;
			else
				xTex = (i+0.5)/(float)sliceNum;
			float xCoord = box.min.x() + (box.max.x() - box.min.x()) * xTex;

			glBegin( GL_TRIANGLE_FAN );

				glTexCoord3d(xTex, 0, 0);
				glVertex3d(xCoord, box.min.y(), box.min.z());

				glTexCoord3d(xTex, 0, 1);
				glVertex3d(xCoord, box.min.y(), box.max.z());

				glTexCoord3d(xTex, 1, 1);
				glVertex3d(xCoord, box.max.y(), box.max.z());

				glTexCoord3d(xTex, 1, 0);
				glVertex3d(xCoord, box.max.y(), box.min.z());

			glEnd();
		}

		if( y_accum >= 1)
		{
			y_accum-=1;

			float yTex;
			if( y_sign < 0 )
				yTex = (sliceNum - (i+0.5))/(float)sliceNum;
			else
				yTex = (i+0.5)/(float)sliceNum;
			float yCoord = box.min.y() + (box.max.y() - box.min.y()) * yTex;

			glBegin( GL_TRIANGLE_FAN );

				glTexCoord3d(0, yTex, 0);
				glVertex3d(box.min.x(), yCoord, box.min.y());

				glTexCoord3d(1, yTex, 0);
				glVertex3d(box.max.x(), yCoord, box.min.z());

				glTexCoord3d(1, yTex, 1);
				glVertex3d(box.max.x(), yCoord, box.max.z());

				glTexCoord3d(0, yTex, 1);
				glVertex3d(box.min.x(), yCoord, box.max.z());

			glEnd();
		}

		if( z_accum >= 1)
		{
			z_accum-=1;

			float zTex;
			if( z_sign < 0 )
				zTex = (sliceNum - (i+0.5))/(float)sliceNum;
			else
				zTex = (i+0.5)/(float)sliceNum;
			float zCoord = box.min.z() + (box.max.z() - box.min.z()) * zTex;

			glBegin( GL_TRIANGLE_FAN );

				glTexCoord3d(0, 0, zTex);
				glVertex3d(box.min.x(), box.min.y(), zCoord );

				glTexCoord3d(0, 1, zTex);
				glVertex3d(box.min.x(), box.max.y(), zCoord );

				glTexCoord3d(1, 1, zTex);
				glVertex3d(box.max.x(), box.max.y(), zCoord );

				glTexCoord3d(1, 0, zTex);
				glVertex3d(box.max.x(), box.min.y(), zCoord );

			glEnd();
		}
	}
}


int main(int argc, char* args[])
{
	if ( argc > 1   &&   strcmp("-test", args[1])==0 )
	{
		int result = 0;

		std::cout << "\n--=-=-=-=== = Test = ===-=-=-=--\n" << std::endl;
		result = UnitTest::RunAllTests();
		std::cout << "--=-=-=-== == ==== == ==-=-=-=--\n\n" << std::endl;

		return result;
	}
	else
	{
		sf::Window theWindow( sf::VideoMode(640, 480), "The window" ); 

		// Set color and depth clear value
		glClearDepth(1.f);
		glClearColor(0.f, 0.f, 0.f, 0.f);

		// Enable Z-buffer read and write
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);


		// Our AABB
		AABB aabb;
		aabb.min		<< -0.7, -0.7, -0.7;
		aabb.max		<<  0.7,  0.7,  0.7;


		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		// 3D Texture nitialization
		glEnable(GL_TEXTURE_3D);

		PFNGLTEXIMAGE3DPROC glTexImage3D;
		glTexImage3D = (PFNGLTEXIMAGE3DPROC) wglGetProcAddress("glTexImage3D");


		sf::Image the3DImage;
		the3DImage.loadFromFile("../../../data/test.png");


		//(generate texel code omitted)
		GLvoid *voxels = new char[32*32*32 * 4];
		char * v = (char*) voxels; 

		for(int i=0; i<32; i++)
			for(int j=0; j<32; j++)
				for(int k=0; k<32; k++)
				{
					sf::Color c = the3DImage.getPixel(i + k*32, 31-j);
					*(v++) = c.r;
					*(v++) = c.g;
					*(v++) = c.b;
					*(v++) = c.a;
				}


		unsigned int texID;
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_3D, texID);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA8, 32, 32, 32, 0, GL_RGBA, 
			GL_UNSIGNED_BYTE, voxels );

		SliceBox sliceBox;
		sliceBox.box = aabb;

		float angle = 0;

		while( theWindow.isOpen() )
		{
			sf::Event theEvent; 
			while( theWindow.pollEvent(theEvent) )
			{
				if( theEvent.type == sf::Event::Closed )
				{
					theWindow.close();
				}
			}

			
			// Clear the screen
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Do view transformations here...
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-1, 1, -1, 1, 0, 100);

			glMatrixMode(GL_MODELVIEW);
			//glLoadIdentity();
			angle += 0.1;

			/*
			glTranslatef( 0, 0, -5 );
			glRotatef( 30 , 1.0, 0.0, 0.0);
			glRotatef( angle*2 , 0.0, 1.0, 0.0);
			*/

			Eigen::Transform<float,3, Eigen::Affine> transf;
			transf =	Eigen::Translation3f( 0,0, -5 )
						*
						Eigen::AngleAxisf( 30/180.f*3.14f, Eigen::Vector3f(1,0,0) )
						*
						Eigen::AngleAxisf( angle*2/180.f, Eigen::Vector3f(0,1,0) );

			glLoadMatrixf( transf.data() );

			Eigen::Vector3f origView(0,0,-1);
			Eigen::Vector3f camView = transf.inverse() * origView;


			static double a = 0;
			a+= 0.0001;

			if( a> 1 )
				a = 0;

			glBindTexture( GL_TEXTURE_3D, texID );
			sliceBox.draw( camView.normalized() );

			/*
			glBegin( GL_TRIANGLE_FAN );

				glTexCoord3d(1, 1, a);
				glVertex3d(-0.2, -0.2, -0.2);

				glTexCoord3d(0, 1, a);
				glVertex3d(0.2, -0.2, -0.2);

				glTexCoord3d(0, 0, a);
				glVertex3d(0.2, 0.2, -0.2);

				glTexCoord3d(1, 0, a);
				glVertex3d(-0.2, 0.2, -0.2);

			glEnd();
			*/

			theWindow.display();
		}
		return 0;
	}
}