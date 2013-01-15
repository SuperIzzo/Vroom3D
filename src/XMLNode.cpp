#include <XMLNode.h>


VROOM_BEGIN


//=================================================================
//	XMLNode::XMLNode
//---------------------------------------
XMLNode::XMLNode( rapidxml::xml_node<> *nodePtr )
{
	mXMLNode = nodePtr;
}





//=================================================================
//	XMLNode::IsValid
//---------------------------------------
bool XMLNode::IsValid()
{
	return (bool)mXMLNode;
}





//=================================================================
//	XMLNode::GetName
//---------------------------------------
String XMLNode::GetName()
{
	if( IsValid() )
	{
		return mXMLNode->name();
	}
	else
	{
		return "";
	}
}





//=================================================================
//	XMLNode::GetValue
//---------------------------------------
String XMLNode::GetValue()
{
	if( IsValid() )
	{
		return mXMLNode->value();
	}
	else
	{
		return "";
	}
}

	



//=================================================================
//	XMLNode::GetChildren
//---------------------------------------
XMLNodeList XMLNode::GetChildren(String name)
{
	XMLNodeList nodeList;

	if( IsValid() )
	{
		const char *cstrName = 0;
		if( !name.empty() )
		{
			cstrName = name.c_str();
		}

		rapidxml::xml_node<> *nodePtr = mXMLNode->first_node(cstrName);
		for( ; nodePtr != 0; nodePtr = nodePtr->next_sibling(cstrName) )
		{
			nodeList.push_back( XMLNode(nodePtr) );
		}
	}

	return nodeList;
}

VROOM_END
