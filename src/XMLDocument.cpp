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
#include "XMLDocument.h"
#include <fstream>
#include <string>


VROOM_BEGIN
	

//=================================================================
//	XMLDocument::XMLDocument
//---------------------------------------
XMLDocument::XMLDocument() :
	mXMLString( 0 )
{
}





//=================================================================
//	XMLDocument::~XMLDocument
//---------------------------------------
XMLDocument::~XMLDocument()
{
	ClearData();
}





//=================================================================
//	XMLDocument::ParseFile
//---------------------------------------
void XMLDocument::ParseFile(const String &fname)
{
	LoadFromFile( fname );
	Parse();
}





//=================================================================
//	XMLDocument::ParseString
//---------------------------------------
void XMLDocument::ParseString(const String &text)
{
	CopyXMLString( text.c_str() );
	Parse();
}





//=================================================================
//	XMLDocument::Parse
//---------------------------------------
void XMLDocument::Parse()
{
	mXMLDoc.parse<0>( mXMLString );
}





//=================================================================
//	XMLDocument::LoadFromFile
//---------------------------------------
void XMLDocument::LoadFromFile( const String &fname )
{
	std::ifstream fileIn;
	std::string line, docContent;

	ClearData();

	fileIn.open( fname , std::ifstream::in );

	while( std::getline(fileIn, line) )
	{
		docContent += line + "\n";
	}

	CopyXMLString( docContent.c_str() );
}





//=================================================================
//	XMLDocument::CopyXMLString
//---------------------------------------
void XMLDocument::CopyXMLString( const char *text)
{
	UInt32 length = strlen(text);
	mXMLString = new char[ length+1 ];
	strcpy(mXMLString, text);
}





//=================================================================
//	XMLDocument::GetRootNode
//---------------------------------------
XMLNode XMLDocument::GetRootNode()
{
	if( mXMLString )
	{
		return XMLNode( mXMLDoc.first_node() );
	}
	else
	{
		return XMLNode( 0 );
	}
}





//=================================================================
//	XMLDocument::ClearData
//---------------------------------------
void XMLDocument::ClearData()
{
	if( mXMLString )
	{
		mXMLDoc.clear();

		delete[] mXMLString;
		mXMLString = 0;
	}
}


VROOM_END
