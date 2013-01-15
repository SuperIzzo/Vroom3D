#ifndef __VROOM_XMLNODE_H__
#define __VROOM_XMLNODE_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <Platform.h>
#include <rapidxml.hpp>
#include <vector>


VROOM_BEGIN


//=================================================================
//	Public Types
//---------------------------------------
class XMLNode;
typedef std::vector<XMLNode>	XMLNodeList;





//=================================================================
//	Class XMLNode
//---------------------------------------
class XMLNode
{
public:
						XMLNode( rapidxml::xml_node<> *nodePtr );

	bool				IsValid();
	String				GetName();
	String				GetValue();

	XMLNodeList			GetChildren( String name="" );

private:
	rapidxml::xml_node<>	*mXMLNode;
};


VROOM_END


#endif