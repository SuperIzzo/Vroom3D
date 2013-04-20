//=================================================================
//	Inlude
//---------------------------------------
#include "Node.h"


VROOM_BEGIN


//=================================================================
//	Node::Node
//---------------------------------------
Node::Node() :
	mVolume( 0 )
{
	mTransform =  Matrix4::Identity();
}





//=================================================================
//	Node::~Node
//---------------------------------------
Node::~Node()
{
}





//=================================================================
//	Node::GetVolumeData
//---------------------------------------
VolumeData * Node::GetVolumeData()
{
	return mVolume;
}





//=================================================================
//	Node::SetVolumeData
//---------------------------------------
void Node::SetVolumeData( VolumeData *volume )
{
	mVolume = volume;
}





//=================================================================
//	Node::GetTransform
//---------------------------------------
Matrix4 Node::GetTransform() const
{
	return mTransform;
}





//=================================================================
//	Node::SetTransform
//---------------------------------------
void Node::SetTransform( const Matrix4 &transform )
{
	mTransform = transform;
}


VROOM_END