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
void XMLDocument::ParseFile(const char *fname)
{
	LoadFromFile( fname );
	Parse();
}





//=================================================================
//	XMLDocument::ParseString
//---------------------------------------
void XMLDocument::ParseString(const char *text)
{
	CopyXMLString( text );
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
void XMLDocument::LoadFromFile(const char *fname)
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
void XMLDocument::CopyXMLString(const char *text)
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
