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
	glBegin( GL_LINES );
		glColor3f( 1, 1, 1 );
		glVertex3f( ray.origin.x(), ray.origin.y(), ray.origin.z() );
		glVertex3f( ray.origin.x() + t1*ray.direction.x(),
					ray.origin.y() + t1*ray.direction.y(),
					ray.origin.z() + t1*ray.direction.z() );

		// Colored section
		glColor3f( 1, 0, 0 );
		glVertex3f( ray.origin.x() + t1*ray.direction.x(),
					ray.origin.y() + t1*ray.direction.y(),
					ray.origin.z() + t1*ray.direction.z() );
		glVertex3f( ray.origin.x() + t2*ray.direction.x(),
					ray.origin.y() + t2*ray.direction.y(),
					ray.origin.z() + t2*ray.direction.z() );

		glColor3f( 1, 1, 1 );
		glVertex3f( ray.origin.x() + t2*ray.direction.x(),
					ray.origin.y() + t2*ray.direction.y(),
					ray.origin.z() + t2*ray.direction.z() );
		glVertex3f( ray.origin.x() + 100*ray.direction.x(), 
					ray.origin.y() + 100*ray.direction.y(), 
					ray.origin.z() + 100*ray.direction.z() );
	glEnd();
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


		// Our AABB
		AABB aabb;
		aabb.min		<< -0.2, -0.2, -0.2;
		aabb.max		<<  0.2,  0.2,  0.2;

		Ray ray;
		ray.origin		<< -0.5,    0,    0;
		ray.direction	<<    1,    0.4,	  0;

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
			theWindow.clear();


			// Do view transformations here...
			glLoadIdentity();

			angle += 0.1;
			glRotatef( 30 , 1.0, 0.0, 0.0);
			glRotatef( angle , 0.0, 1.0, 0.0);


			// Do drawings
			glDrawAABB( aabb );


			float t1, t2;

			if( GetRayAABBIntersectionPoints( ray, aabb, t1, t2 ) )
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