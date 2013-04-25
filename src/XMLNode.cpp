/*ZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZ*\
Z|                                                                           |Z
Z|  Copyright (c) 2013   Hristoz S. Stefanov                                 |Z
Z|                                                                           |Z
Z|  Permission is hereby granted, free of charge, to any person              |Z
Z|  obtaining a copy of this software and associated documentation files     |Z
Z|  (the "Software"), to deal in the Software without restriction,           |Z
Z|  including without limitation the rights to use, copy, modify, merge,     |Z
Z|  publish, distribute, sublicense, and/or sell copies of the Software,     |Z
Z|  and to permit persons to whom the Software is furnished to do so,        |Z
Z|  subject to the following conditions:                                     |Z
Z|                                                                           |Z
Z|  The above copyright notice and this permission notice shall be included  |Z
Z|  in all copies or substantial portions of the Software.                   |Z
Z|                                                                           |Z
Z|  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  |Z
Z|  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               |Z
Z|  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   |Z
Z|  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     |Z
Z|  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     |Z
Z|  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        |Z
Z|  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   |Z
Z|                                                                           |Z
\*ZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZNZ*/


//=================================================================
//	Inlude
//---------------------------------------
#include <XMLNode.h>
#include <sstream>


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
//	XMLNode::GetIntValue
//---------------------------------------
SInt32 XMLNode::GetIntValue()
{
	SInt32 theResult = 0;
	std::istringstream( GetValue() ) >> theResult;
	return theResult;
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
