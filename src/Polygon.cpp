#include "Polygon.h"


VROOM_BEGIN
	

//=================================================================
//	Polygon::Polygon
//---------------------------------------
Polygon::Polygon()
{
}





//=================================================================
//	Polygon::AddVertex
//---------------------------------------
void Polygon::AddVertex( Vector3 &vert )
{
	mVertices.push_back( vert );
}





//=================================================================
//	Polygon::RemoveVertex
//---------------------------------------
void Polygon::RemoveVertex( UInt32 index )
{
	mVertices.erase( mVertices.begin() + index );
}





//=================================================================
//	Polygon::GetVertexCount
//---------------------------------------
UInt32 Polygon::GetVertexCount() const
{
	return mVertices.size();
}





//=================================================================
//	Polygon::GetVertex
//---------------------------------------
Vector3 Polygon::GetVertex( UInt32 index ) const
{
	return mVertices.at(index);
}


VROOM_END
