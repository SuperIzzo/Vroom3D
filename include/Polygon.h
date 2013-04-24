#ifndef __VROOM_POLYGON_H__
#define __VROOM_POLYGON_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <MathCommon.h>
#include <vector>


VROOM_BEGIN


//=================================================================
//	Class Polygon
//---------------------------------------
class Polygon
{
public:
							Polygon();
							
	void					AddVertex( Vector3 &vert );
	void					RemoveVertex( UInt32 index );

	UInt32					GetVertexCount() const;
	Vector3					GetVertex( UInt32 index ) const;

private:
	std::vector<Vector3>	mVertices;
};





//=================================================================
//	Type PolygonList
//---------------------------------------
typedef std::vector<Polygon>	PolygonList;


VROOM_END


#endif
