#ifndef __VROOM_XMLDOCUMENT_H__
#define __VROOM_XMLDOCUMENT_H__





//=================================================================
//	Inlude
//---------------------------------------
#include <XMLNode.h>


VROOM_BEGIN


class XMLDocument
{
public:
								XMLDocument();
								~XMLDocument();

	void						ParseFile(const char *fname);
	void						ParseString(const char *text);

	XMLNode						GetRootNode();

private:
	void						Parse();
	void						LoadFromFile(const char *fname);
	void						CopyXMLString(const char *text);
	void						ClearData();

private:
	typedef rapidxml::xml_document<char>	XMLDocType;

	XMLDocType					mXMLDoc;
	char *						mXMLString;
};


VROOM_END


#endif