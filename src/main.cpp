#include <UnitTest++.h>
#include <iostream>

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "AABB.h"
#include "Ray.h"



void glDrawAABB( const AABB &box )
{
	box.Draw();
}


void glDrawRay( const Ray &ray )
{
	ray.Draw();
}


void glDrawRaySeg( const Ray &ray, float t1, float t2 )
{
	ray.DrawSeg( t1, t2 );
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


void GetCloseAndFarAABBPointForRay( Eigen::Vector3f &dir, AABB &aabb, 
										Eigen::Vector3f &closePoint,
										Eigen::Vector3f &farPoint )
{
	for( int axis=0; axis<3; axis++ )
	{

		if( dir[axis] >= 0 )
		{
			closePoint[axis] = aabb.min[axis];
			farPoint[axis]   = aabb.max[axis];
		}
		else
		{
			closePoint[axis] = aabb.max[axis];
			farPoint[axis]   = aabb.min[axis];
		}
	}
}


int t = 800;
void glDrawSlices( Ray &ray, AABB &aabb )
{
	float maxT = (aabb.max - aabb.min).norm();
	printf( "maxT %f\n", maxT );
	for( float t=0; t< 0.6; t+=0.04 )
	{
	Eigen::Vector3f closePoint;
	Eigen::Vector3f farPoint;

	GetCloseAndFarAABBPointForRay( ray.direction, aabb,  closePoint, farPoint );

	Eigen::Vector3f points[6];
	
	for(int axis= 0; axis< 3; axis++)
	{
		int a = axis*2; 
		int b = a+1;
		points[a] = closePoint;
		points[b] = closePoint;

		points[a][axis] += t/ray.direction[axis];

		if( abs(points[a][axis]-closePoint[axis]) > abs(farPoint[axis]-closePoint[axis]) )
		{
			float diff = abs(points[a][axis]-farPoint[axis]);

			int bAxis = (axis + 1)%3;
			int aAxis = (axis + 2)%3;
			points[a][aAxis] += diff/ray.direction[aAxis]*ray.direction[axis];
			points[b][bAxis] += diff/ray.direction[bAxis]*ray.direction[axis];
			points[a][axis] = farPoint[axis];
			points[b][axis] = farPoint[axis];

			if( abs(points[a][aAxis]-closePoint[aAxis]) > abs(farPoint[aAxis]-closePoint[aAxis]) )
			{
				float diff = abs(points[a][aAxis]-farPoint[aAxis]);

				points[a][bAxis] += diff/ray.direction[bAxis]*ray.direction[aAxis];
				points[a][aAxis] = farPoint[aAxis];
			}

			if( abs(points[b][bAxis]-closePoint[bAxis]) > abs(farPoint[bAxis]-closePoint[bAxis]) )
			{
				float diff = abs(points[b][bAxis]-farPoint[bAxis]);

				points[b][aAxis] += diff/ray.direction[aAxis]*ray.direction[bAxis];
				points[b][bAxis] = farPoint[bAxis];
			}
		}
		else
		{
			points[b][axis] = points[a][axis];
		}
	}

	for( int i=0; i<6; i++)
	{
		glColor3f( 1-i%2, i%2, 0 );
		glBegin( GL_TRIANGLES );
			glVertex3f( points[i].x()-0.01, points[i].y()+0.01, points[i].z()      );
			glVertex3f( points[i].x()     , points[i].y()-0.01, points[i].z()+0.01 );
			glVertex3f( points[i].x()+0.01, points[i].y()     , points[i].z()-0.01 );
		glEnd();


		int j = i+1;
			
		if( j>= 6 )
			j -=6;

		glBegin( GL_LINES );
			glVertex3f( points[i].x(), points[i].y() , points[i].z() );
			glVertex3f( points[j].x(), points[j].y() , points[j].z() );
		glEnd();
	}

	glColor3f( 0, 1, 1 );
	glBegin( GL_LINES );
		glVertex3f( closePoint.x(), closePoint.y(), closePoint.z() );
		glVertex3f( closePoint.x() + ray.direction.x()*10, 
					closePoint.y() + ray.direction.y()*10,
					closePoint.z() + ray.direction.z()*10 );
	glEnd();

	}
	/*
	for(int i=0; i<10; i++)
	{
		point1.x()+= 1/ray.direction.x() * 0.02 *i;
		point2.y()+= 1/ray.direction.y() * 0.02 *i;
		point3.z()+= 1/ray.direction.z() * 0.02 *i;

		Eigen::Vector3f point1b = point1;
		Eigen::Vector3f point2b = point2;
		Eigen::Vector3f point3b = point3;

		if( point1.x() > farPoint.x() )
		{
			float diff = point1.x() - farPoint.x();

			point1.x() = farPoint.x();
			point1.y() = diff*ray.direction.y();

			point1b.x() = farPoint.x();
			point1b.z() = diff*ray.direction.z();
		};

		if( point2.y() > farPoint.y() )
		{
			float diff = point1.y() - farPoint.y();

			point2.y() = farPoint.y();
			point2.z() = diff*ray.direction.z();

			point2b.y() = farPoint.y();
			point2b.x() = diff*ray.direction.x();
		};

		if( point3.z() > farPoint.z() )
		{
			float diff = point3.z() - farPoint.z();

			point3.z() = farPoint.z();
			point3.x() = diff*ray.direction.x();

			point3b.z() = farPoint.z();
			point3b.y() = diff*ray.direction.y();
		};

		glBegin( GL_LINES );
			glVertex3f( point1.x(), point1.y(), point1.z() );
			glVertex3f( point1b.x(), point1b.y(), point1b.z() );

			glVertex3f( point1b.x(), point1b.y(), point1b.z() );
			glVertex3f( point2.x(), point2.y(), point2.z() );

			glVertex3f( point2.x(), point2.y(), point2.z() );
			glVertex3f( point2b.x(), point2b.y(), point2b.z() );

			glVertex3f( point2b.x(), point2b.y(), point2b.z() );
			glVertex3f( point3.x(), point3.y(), point3.z() );

			glVertex3f( point3.x(), point3.y(), point3.z() );
			glVertex3f( point3b.x(), point3b.y(), point3b.z() );

			glVertex3f( point3b.x(), point3b.y(), point3b.z() );
			glVertex3f( point1.x(), point1.y(), point1.z() );
		glEnd();
	}
	*/

	glColor3f( 1, 1, 1 );
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
		aabb.min		<< -0.2, -0.2, -0.2;
		aabb.max		<<  0.2,  0.2,  0.2;

		Ray ray;
		ray.origin		<< 0.5,    0,    0;
		ray.direction	<<    1,    0.4,	  0.2;

		ray.direction.normalize();

		// For rotation animation
		float angle = 0;

		
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

			// Clear the screen
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			// Do view transformations here...
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-1, 1, -1, 1, 0, 100);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			angle += 0.01;
			glTranslatef( 0, 0, -5 );
			glRotatef( 30 , 1.0, 0.0, 0.0);
			glRotatef( angle*2 , 0.0, 1.0, 0.0);
			


			// Draw Our AABB
			glDrawAABB( aabb );


			//ray.origin		<< 0 - 0.5f,    0,    0;
			ray.direction	<<  angle/700,    0.4,	  0.2;

			ray.direction.normalize();

			float t1, t2;

			if( GetRayAABBIntersectionPoints( ray, aabb, t1, t2 ) && t1>0 && t2>0)
			{
				glDrawRaySeg( ray, t1, t2 );
			}
			else
			{
				glDrawRay( ray );
			}


			glDrawSlices( ray, aabb );


			// Flip buffers
			theWindow.display();
		}

		return 0;
	}
}