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
		ray.direction	<<    1,    0,	  0;

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
			glDrawRay( ray );


			// Flip buffers
			theWindow.display();
		}

		return 0;
	}
}