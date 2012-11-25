#ifndef __AABB_H__
#define __AABB_H__

#include <Eigen/Dense>



class AABB
{
public:
	Eigen::Vector3f min;
	Eigen::Vector3f max;

	void Draw() const;
};





#endif