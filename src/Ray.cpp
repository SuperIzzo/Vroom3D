#include "Ray.h"

#include <SFML/OpenGL.hpp>


void Ray::Draw()
{
	glBegin( GL_LINES );
		glVertex3f( origin.x(), origin.y(), origin.z() );
		glVertex3f( origin.x() + 100*direction.x(),
					origin.y() + 100*direction.y(),
					origin.z() + 100*direction.z() );
	glEnd();
}



void Ray::DrawSeg( float t1, float t2 )
{
		Eigen::Vector3f p1 = origin + t1*direction;
		Eigen::Vector3f p2 = origin + t2*direction;

		glBegin( GL_LINES );

		if( t1 > 0 )
		{
			glColor3f( 1, 1, 1 );
			glVertex3f( origin.x(), origin.y(), origin.z() );
			glVertex3f( p1.x(),	p1.y(), p1.z() );
		}
		else
		{
			p1 = origin;
		}

		// Colored section
		glColor3f( 1, 0, 0 );
		glVertex3f( p1.x(),	p1.y(), p1.z() );
		glVertex3f( p2.x(),	p2.y(), p2.z() );

		glColor3f( 1, 1, 1 );
		glVertex3f( p2.x(),	p2.y(), p2.z() );
		glVertex3f( origin.x() + 10 * direction.x(),
					origin.y() + 10 * direction.y(),
					origin.z() + 10 * direction.z() );
		glEnd();
}