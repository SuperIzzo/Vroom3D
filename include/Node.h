#ifndef __VROOM_NODE_H__
#define __VROOM_NODE_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <VolumeData.h>
#include <MathCommon.h>



VROOM_BEGIN


//=================================================================
//	Class Node
//---------------------------------------
class Node
{
public:

public:
									Node();
	virtual							~Node();

	virtual void					SetVolumeData( VolumeData *volume );
	virtual VolumeData			  *	GetVolumeData();

	Matrix4							GetTransform() const;
	void							SetTransform( const Matrix4 &transf);

	// Eigen alignment operator
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

private:
	Matrix4							mTransform;

	Node						  * mParent;
	VolumeData					  * mVolume; 
};


VROOM_END


#endif
