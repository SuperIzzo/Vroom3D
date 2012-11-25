#include "AABB.h"



#include <SFML/OpenGL.hpp>


void AABB::Draw()
{
	glBegin( GL_LINES );
	glVertex3f( min.x(), min.y(),	min.z() );
	glVertex3f( max.x(), min.y(),	min.z() );

	glVertex3f( min.x(), min.y(),	min.z() );
	glVertex3f( min.x(), max.y(),	min.z() );

	glVertex3f( min.x(), min.y(),	min.z() );
	glVertex3f( min.x(), min.y(),	max.z() );


	glVertex3f( max.x(), min.y(),	min.z() );
	glVertex3f( max.x(), max.y(),	min.z() );

	glVertex3f( max.x(), min.y(),	min.z() );
	glVertex3f( max.x(), min.y(),	max.z() );


	glVertex3f( min.x(), max.y(),	min.z() );
	glVertex3f( max.x(), max.y(),	min.z() );

	glVertex3f( min.x(), max.y(),	min.z() );
	glVertex3f( min.x(), max.y(),	max.z() );


	glVertex3f( min.x(), min.y(),	max.z() );
	glVertex3f( max.x(), min.y(),	max.z() );

	glVertex3f( min.x(), min.y(),	max.z() );
	glVertex3f( min.x(), max.y(),	max.z() );


	glVertex3f( max.x(), max.y(),	max.z() );
	glVertex3f( max.x(), max.y(),	min.z() );

	glVertex3f( max.x(), max.y(),	max.z() );
	glVertex3f( max.x(), min.y(),	max.z() );

	glVertex3f( max.x(), max.y(),	max.z() );
	glVertex3f( min.x(), max.y(),	max.z() );
	glEnd();
}