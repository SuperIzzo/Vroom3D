#include <UnitTest++.h>
#include <iostream>

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class AABB
{
public:
	Eigen::Vector3f min;
	Eigen::Vector3f max;
};



class Ray
{
public:
	Eigen::Vector3f origin;
	Eigen::Vector3f direction;
};


void glDrawAABB( const AABB &box )
{
	glBegin( GL_LINES );
		glVertex3f( box.min.x(),  box.min.y(),	box.min.z() );
		glVertex3f( box.max.x(),  box.min.y(),	box.min.z() );

		glVertex3f( box.min.x(),  box.min.y(),	box.min.z() );
		glVertex3f( box.min.x(),  box.max.y(),	box.min.z() );

		glVertex3f( box.min.x(),  box.min.y(),	box.min.z() );
		glVertex3f( box.min.x(),  box.min.y(),	box.max.z() );


		glVertex3f( box.max.x(),  box.min.y(),	box.min.z() );
		glVertex3f( box.max.x(),  box.max.y(),	box.min.z() );

		glVertex3f( box.max.x(),  box.min.y(),	box.min.z() );
		glVertex3f( box.max.x(),  box.min.y(),	box.max.z() );

		
		glVertex3f( box.min.x(),  box.max.y(),	box.min.z() );
		glVertex3f( box.max.x(),  box.max.y(),	box.min.z() );

		glVertex3f( box.min.x(),  box.max.y(),	box.min.z() );
		glVertex3f( box.min.x(),  box.max.y(),	box.max.z() );


		glVertex3f( box.min.x(),  box.min.y(),	box.max.z() );
		glVertex3f( box.max.x(),  box.min.y(),	box.max.z() );

		glVertex3f( box.min.x(),  box.min.y(),	box.max.z() );
		glVertex3f( box.min.x(),  box.max.y(),	box.max.z() );


		glVertex3f( box.max.x(),  box.max.y(),	box.max.z() );
		glVertex3f( box.max.x(),  box.max.y(),	box.min.z() );

		glVertex3f( box.max.x(),  box.max.y(),	box.max.z() );
		glVertex3f( box.max.x(),  box.min.y(),	box.max.z() );

		glVertex3f( box.max.x(),  box.max.y(),	box.max.z() );
		glVertex3f( box.min.x(),  box.max.y(),	box.max.z() );
	glEnd();
}


void glDrawRay( const Ray &ray )
{
	glBegin( GL_LINES );
		glVertex3f( ray.origin.x(), ray.origin.y(), ray.origin.z() );
		glVertex3f( ray.origin.x() + 100*ray.direction.x(), 
					ray.origin.y() + 100*ray.direction.y(), 
					ray.origin.z() + 100*ray.direction.z() );
	glEnd();
}


void glDrawRaySeg( const Ray &ray, float t1, float t2 )
{
	Eigen::Vector3f p1 = ray.origin + t1*ray.direction;
	Eigen::Vector3f p2 = ray.origin + t2*ray.direction;

	glBegin( GL_LINES );

		if( t1 > 0 )
		{
			glColor3f( 1, 1, 1 );
			glVertex3f( ray.origin.x(), ray.origin.y(), ray.origin.z() );
			glVertex3f( p1.x(),	p1.y(), p1.z() );
		}
		else
		{
			p1 = ray.origin;
		}

		// Colored section
		glColor3f( 1, 0, 0 );
		glVertex3f( p1.x(),	p1.y(), p1.z() );
		glVertex3f( p2.x(),	p2.y(), p2.z() );

		glColor3f( 1, 1, 1 );
		glVertex3f( p2.x(),	p2.y(), p2.z() );
		glVertex3f( ray.origin.x() + 10*ray.direction.x(), 
					ray.origin.y() + 10*ray.direction.y(), 
					ray.origin.z() + 10*ray.direction.z() );
	glEnd();
}




class Volume
{
public:
	unsigned char * data;

	Volume();
	~Volume();

	void LoadImageXZImage( const char * imgFile, int width );

	int GetWidth() const;
	int GetHeight() const;
	int GetDepth() const;

	sf::Color GetVoxel(int x, int y, int z) const;

private:
	void Clear();

	int  mWidth;
	int  mHeight;
	int  mDepth;
};


Volume::Volume()
	: data( 0 )
{
	Clear();
}


Volume::~Volume()
{
	Clear();
}


void Volume::Clear()
{
	if( data )
	{
		delete[] data;
	}

	mWidth = 0;
	mHeight = 0;
	mDepth = 0;
}

int Volume::GetWidth() const
{
	return mWidth;
}

int Volume::GetHeight() const
{
	return mHeight;
}

int Volume::GetDepth() const
{
	return mDepth;
}

sf::Color Volume::GetVoxel(int x, int y, int z) const
{
	sf::Color col;

	int idx = (x + y*mWidth + z*mWidth*mHeight) *4;

	col.r = data[ idx +0 ];
	col.g = data[ idx +1 ];
	col.b = data[ idx +2 ];
	col.a = data[ idx +3 ];

	return col;
}

void Volume::LoadImageXZImage( const char * imgFile, int width )
{
	sf::Image the3DImage;

	the3DImage.loadFromFile( imgFile );

	int W = width;
	int H = the3DImage.getSize().y;
	int D = the3DImage.getSize().x / width;

	Clear();
	data = new unsigned char[ W*H*D * 4 ];

	unsigned char	*volPointer = data;
	const sf::Uint8 *texPointer = the3DImage.getPixelsPtr();

	for( int z=0; z< D; z++ )
	{
		for( int y=0; y< H; y++ )
		{
			texPointer = the3DImage.getPixelsPtr() + y*the3DImage.getSize().x + z*W;

			for( int x=0; x< W; x++ )
			{
				sf::Color col = the3DImage.getPixel(x + z*W, y);

				*(volPointer++) = col.r;
				*(volPointer++) = col.g;
				*(volPointer++) = col.b;
				*(volPointer++) = col.a;

				/*
				*(volPointer++) = *(texPointer++);	// Copy red, move forward
				*(volPointer++) = *(texPointer++);	// Copy green, move forward
				*(volPointer++) = *(texPointer++);	// Copy blue, move forward
				*(volPointer++) = *(texPointer++);	// Copy alpha, move forward
				*/
			}
		}
	}

	mWidth  = W;
	mHeight = H;
	mDepth  = D;
}




bool GetRayAABBIntersectionPoints( const Ray &ray, const AABB &aabb, float &outTMin, float &outTMax )
{
	float epsilon = FLT_EPSILON;

	float tMin = -FLT_MAX;
	float tMax = FLT_MAX;

	for( int i=0; i < 3; i++ )
	{
		float planeMin = aabb.min[i];
		float planeMax = aabb.max[i];

		if( ray.direction[i] < epsilon && ray.direction[i] > -epsilon )
		{
			// If the ray is paralel to the planes then it's origin must be between
			// them (otherwise it's a miss);
			if(  ray.origin[i] > planeMax || ray.origin[i] < planeMin )
				return false;
			else
				continue;
		}

		// PlanePoint = ray.origin + ray.direction * t
		// => t = (planePint - ray.origin) / ray.direction
		float min;
		float max;

		if( ray.direction[i] > 0 )
		{
			min = (planeMin - ray.origin[i]) / ray.direction[i];
			max = (planeMax - ray.origin[i]) / ray.direction[i];
		}
		else
		{
			max = (planeMin - ray.origin[i]) / ray.direction[i];
			min = (planeMax - ray.origin[i]) / ray.direction[i];
		}

		if( min > tMin )
			tMin = min;

		if( max < tMax )
			tMax = max;

		if( tMax < tMin )
			return false;
	}

	outTMin = tMin;
	outTMax = tMax;

	return true;
}



void traverseAndDrawBoxes(const Ray &ray, const AABB &aabb, const std::vector<AABB> *subBoxes, int numBoxes)
{
	float t1, t2;
	if(	GetRayAABBIntersectionPoints( ray, aabb, t1, t2 ) )
	{
		// Initialization
		// We need to pin the ray to the first voxel it hits in the grid
		// 

		// Get the entrance point in box coord space
		Eigen::Vector3f point1 = ray.origin + ray.direction * t1 - aabb.min;

		std::cout << "Ray hits volume at: " << point1.x() << ", " << point1.y() << ", " << point1.z() << std::endl;

		point1.x() /= (aabb.max.x() - aabb.min.x())/numBoxes;
		point1.y() /= (aabb.max.y() - aabb.min.y())/numBoxes;
		point1.z() /= (aabb.max.z() - aabb.min.z())/numBoxes;

		//point1.x() = floor( point1.x() );
		//point1.y() = floor( point1.y() );
		//point1.z() = floor( point1.z() );

		std::cout << "Ray is in voxel: " << point1.x() << ", " << point1.y() << ", " << point1.z() << std::endl;

		//Eigen::Vector3f point2 = ray.origin + ray.direction * t2 - aabb.min;		
	}
}


inline float max(float a, float b)
{
	return a>b ? a : b;
}

inline float min(float a, float b)
{
	return a<b ? a : b;
}

sf::Color RayTraceColor(const Ray &ray, const AABB &aabb, const Volume &volume)
{
	sf::Color col(0,0,0,0);

	float t1, t2;
	if(	GetRayAABBIntersectionPoints( ray, aabb, t1, t2 ) )
	{
		Eigen::Vector3f floatPoint = ray.origin + ray.direction * t1 - aabb.min;		
		floatPoint.x() /= (aabb.max.x() - aabb.min.x())/ volume.GetWidth();
		floatPoint.y() /= (aabb.max.y() - aabb.min.y())/ volume.GetHeight();
		floatPoint.z() /= (aabb.max.z() - aabb.min.z())/ volume.GetDepth();

		float &fx = floatPoint.x();
		float &fy = floatPoint.y();
		float &fz = floatPoint.z();

		fx = min( max( fx, 0 ), volume.GetWidth() );
		fy = min( max( fy, 0 ), volume.GetHeight() );
		fz = min( max( fz, 0 ), volume.GetDepth() );


		float deltaStep = 0.5f;
		float dx = ray.direction.x() * deltaStep;
		float dy = ray.direction.y() * deltaStep;
		float dz = ray.direction.z() * deltaStep;


		float maxCoord, *curCoord;

		// Determine the coordinate that changes the most
		// And calculate it's value at t2
		if( dx>dy )
		{
			if( dx>dz )
			{
				curCoord = &fx;
				maxCoord = (ray.origin.x() + ray.direction.x() * t2 - aabb.min.x()) 
						   / ((aabb.max.x() - aabb.min.x())/ volume.GetWidth());				
			}
			else
			{
				curCoord = &fz;
				maxCoord = (ray.origin.z() + ray.direction.z() * t2 - aabb.min.z()) 
						   / ((aabb.max.z() - aabb.min.z())/ volume.GetDepth());
			}
		}
		else
		{
			if( dy>dz )
			{
				curCoord = &fy;
				maxCoord = (ray.origin.y() + ray.direction.y() * t2 - aabb.min.y()) 
						   / ((aabb.max.y() - aabb.min.y())/ volume.GetHeight());				
			}
			else
			{
				curCoord = &fz;
				maxCoord = (ray.origin.z() + ray.direction.z() * t2 - aabb.min.z()) 
						   / ((aabb.max.z() - aabb.min.z())/ volume.GetDepth());
			}
		}

		int displY = volume.GetWidth();
		int displZ = volume.GetWidth() * volume.GetDepth();

		while( (col.a<240) && (*curCoord < maxCoord))
		{
			int floor_x = (int) floor( fx );
			int floor_y = (int) floor( fy );
			int floor_z = (int) floor( fz );

			int floor_idx = floor_x + floor_y*displY + floor_z*displZ;
			/*			

			float sx = fx - floor_x;
			float sy = fy - floor_y;
			float sz = fz - floor_z;

			float rsx = 1 - sx;
			float rsy = 1 - sy;
			float rsz = 1 - sz;

			unsigned char *vox = &volume.data[ floor_idx * 4 ];
			sf::Color c1( ((*vox)++) * sx,
						  ((*vox)++) * sx,
			*/

			col.r = volume.data[ floor_idx * 4 +0 ];
			col.g = volume.data[ floor_idx * 4 +1 ];
			col.b = volume.data[ floor_idx * 4 +2 ];
			col.a = volume.data[ floor_idx * 4 +3 ];

			fx += dx;
			fy += dy;
			fz += dz;
		}
	}

	return col;
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
		sf::RenderWindow theWindow( sf::VideoMode(640, 480), "The window" ); 
		sf::Image theBuffer;


		theBuffer.create(640, 480, sf::Color::Black );


		sf::Texture theBufferTexture;
		theBufferTexture.loadFromImage(theBuffer);

		sf::Sprite theBufferSprite;
		theBufferSprite.setTexture(theBufferTexture);

		Volume volume;

		volume.LoadImageXZImage( "../../../data/test.png", 32 );

		// Set color and depth clear value
		//glClearDepth(1.f);
		//glClearColor(0.f, 0.f, 0.f, 0.f);

		// Enable Z-buffer read and write
		//glEnable(GL_DEPTH_TEST);
		//glDepthMask(GL_TRUE);


		// Our AABB
		AABB aabb;
		aabb.min		<< -0.2, -0.2, -0.2;
		aabb.max		<<  0.2,  0.2,  0.2;

		Ray ray;
		ray.origin		<< 0.5,    0,    -1;
		ray.direction	<<   0,    0,	  1;

		ray.direction.normalize();

		float angle = 30;
		
		while( theWindow.isOpen() )
		{
			sf::Event theEvent;
			while( theWindow.pollEvent(theEvent) )
			{
				switch( theEvent.type )
				{
					case sf::Event::Closed :
						theWindow.close();
					break;
				}
			}



			Eigen::Transform<float,3, Eigen::Affine> transf;

			angle += 0.1;
			transf =
				Eigen::Translation3f( 0,0, -5 )
				*
				Eigen::AngleAxisf( 30/180.f*3.14f, Eigen::Vector3f(1,0,0) )
				*
				Eigen::AngleAxisf( angle*2/180.f, Eigen::Vector3f(0,1,0) );

			Eigen::Transform<float,3, Eigen::Affine> transfInv = transf.inverse();


			sf::Clock rayProf;
			sf::Clock allProf;

			// Raytracing 
			int rayTm = 0;
			for( int x=0; x<640; x++ )
			{
				for( int y=0; y<480; y++ )
				{
					ray.origin.x() = x/320.0f - 1;
					ray.origin.y() = y/240.0f - 1;

					Ray viewRay;
					viewRay.direction = transfInv * ray.direction;
					viewRay.origin = transfInv * ray.origin;

					viewRay.direction.normalize();

					// PROFILE
					rayProf.restart();

					sf::Color col = RayTraceColor(viewRay, aabb, volume);

					rayTm += rayProf.getElapsedTime().asMicroseconds();
					// PROFILE END

					//col.a = 255;
					theBuffer.setPixel(x, y, col );
				}
			}

			std::cout << "Avg. time per ray: " << rayTm/(640*480) << "mcs." << std::endl;
			std::cout << "Time for all rays: " << rayTm << "mcs." << std::endl;
			std::cout << "Time for the entire rendering: " << allProf.getElapsedTime().asMicroseconds() << "mcs." << std::endl;

			//Debug Volume
			/*
			static float a = 0;
			a+=0.1;

			if( a>= volume.GetDepth())
				a = 0;

			for( int x=0; x<volume.GetWidth(); x++ )
			{
				for( int y=0; y<volume.GetHeight(); y++ )
				{					
					theBuffer.setPixel(x+100, y+100, volume.GetVoxel(x, y, (int)a) );
				}
			}
			*/


			theBufferTexture.loadFromImage( theBuffer );




			theWindow.clear();			

			theWindow.draw( theBufferSprite );

			theWindow.display();

		}
	}
}



/*
			// Clear the screen
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			// Do view transformations here...
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-1, 1, -1, 1, 0, 100);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			angle += 0.1;
			glTranslatef( 0, 0, -5 );
			glRotatef( 30 , 1.0, 0.0, 0.0);
			glRotatef( angle*2 , 0.0, 1.0, 0.0);
			


			// Draw Our AABB
			glDrawAABB( aabb );



			ray.origin		<< angle/700 - 0.5f,    0,    0;
			ray.direction	<<    1,    0.4,	  0.2;

			ray.direction.normalize();


			//traverseAndDrawBoxes( ray, aabb, numBoxes );

			float t1, t2;

			if( GetRayAABBIntersectionPoints( ray, aabb, t1, t2 ) && t1>0 && t2>0)
			{
				glDrawRaySeg( ray, t1, t2 );
			}
			else
			{
				glDrawRay( ray );
			}


			// Flip buffers
			theWindow.display();
		}

		return 0;
	}
}

*/