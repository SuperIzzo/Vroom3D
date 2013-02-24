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
	mTransform =  TransformType::Identity();
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
Node::TransformType Node::GetTransform() const
{
	return mTransform;
}





//=================================================================
//	Node::SetTransform
//---------------------------------------
void Node::SetTransform( const TransformType &transform )
{
	mTransform = transform;
}


VROOM_END