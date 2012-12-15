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



void traverseAndDrawBoxes(const Ray &ray, const AABB &aabb, int numBoxes)
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

		std::cout << "Ray is in voxel: " << point1.x() << ", " << point1.y() << ", " << point1.z() << std::endl;
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
		aabb.min		<< -0.2, -0.2, -0.2;
		aabb.max		<<  0.2,  0.2,  0.2;

		Ray ray;
		ray.origin		<< 0.5,    0,    0;
		ray.direction	<<    1,    0.4,	  0.2;

		ray.direction.normalize();

		// For rotation animation
		float angle = 0;


		std::vector<AABB> subBoxes;
		int numBoxes = 3;

		// And some fictional voxels
		{	
			Eigen::Vector3f sbSize = (aabb.max - aabb.min)/numBoxes;

			for( int z = 0; z< numBoxes; z++)
			{
				for( int y = 0; y< numBoxes; y++)
				{
					for( int x = 0; x< numBoxes; x++)
					{
						AABB subBox;
						subBox.min.x() = sbSize.x() * x			+ aabb.min.x();
						subBox.max.x() = sbSize.x() * (x+1)		+ aabb.min.x();

						subBox.min.y() = sbSize.y() * y			+ aabb.min.y();
						subBox.max.y() = sbSize.y() * (y+1)		+ aabb.min.y();

						subBox.min.z() = sbSize.z() * z			+ aabb.min.z();
						subBox.max.z() = sbSize.z() * (z+1)		+ aabb.min.z();
						subBoxes.push_back(subBox);
					}
				}
			}
		}


		
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
			angle += 0.1;
			glTranslatef( 0, 0, -5 );
			glRotatef( 30 , 1.0, 0.0, 0.0);
			glRotatef( angle*2 , 0.0, 1.0, 0.0);
			


			// Draw Our AABB
			glDrawAABB( aabb );


			for( int i=0; i< subBoxes.size(); i++ )
			{
			//	glDrawAABB( subBoxes[i] );
			}



			ray.origin		<< angle/700 - 0.5f,    0,    0;
			ray.direction	<<    1,    0.4,	  0.2;

			ray.direction.normalize();


			traverseAndDrawBoxes( ray, aabb, numBoxes );

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