#ifndef __VROOM_NODE_H__
#define __VROOM_NODE_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <AABB.h>
#include <Volume.h>
#include <Eigen/Dense>



VROOM_BEGIN


//=================================================================
//	Class Node
//---------------------------------------
class Node
{
public:
	typedef Eigen::Matrix<Real,4,4>	TransformType;

public:
									Node();
	virtual							~Node();

	virtual void					SetVolume( Volume *volume );
	virtual Volume				  *	GetVolume();

	TransformType					GetTransform() const;
	void							SetTransform( const TransformType &transf);

	// Eigen alignment operator
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

private:
	TransformType					mTransform;

	Node						  * mParent;
	Volume						  * mVolume; 
};


VROOM_END


#endif
