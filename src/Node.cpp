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
}





//=================================================================
//	Node::~Node
//---------------------------------------
Node::~Node()
{
}





//=================================================================
//	Node::GetVolume
//---------------------------------------
Volume * Node::GetVolume()
{
	return mVolume;
}





//=================================================================
//	Node::SetVolume
//---------------------------------------
void Node::SetVolume( Volume *volume )
{
	mVolume = volume;
}


VROOM_END