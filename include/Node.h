#ifndef __VROOM_NODE_H__
#define __VROOM_NODE_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <AABB.h>
#include <VolumeData.h>
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

	virtual void					SetVolumeData( VolumeData *volume );
	virtual VolumeData			  *	GetVolumeData();

	TransformType					GetTransform() const;
	void							SetTransform( const TransformType &transf);

	// Eigen alignment operator
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

private:
	TransformType					mTransform;

	Node						  * mParent;
	VolumeData					  * mVolume; 
};


VROOM_END


#endif
