#ifndef __RAY_H__
#define __RAY_H__

#include <Eigen/Dense>




class Ray
{
public:
	Eigen::Vector3f origin;
	Eigen::Vector3f direction;

	void Draw();
	void DrawSeg( float t1, float t2 );
};



#endif