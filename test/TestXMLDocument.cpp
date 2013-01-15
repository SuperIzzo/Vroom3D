#include <UnitTest++.h>
#include <XMLDocument.h>

using namespace Vroom;


// Generic random test data
const char * testXML1 = 
	"<rootNode>											\n"
	"	<item1>1</item1>								\n"
	"	<item2> 2  </item2>								\n"
	"	<item3>value3</item3>							\n"
	"	<item4> and 4 </item4>							\n"
	"</rootNode>										\n";

// More real world like for the purpose of the parser
const char * testXML2 = 
	"<volume>											\n"
	"	<width>128</width>								\n"
	"	<height>256</height>							\n"
	"	<depth>512</depth>								\n"
	"</volume>											\n";


SUITE( XMLDocument )
{
	TEST( TEST_empty_XML_document_has_no_valid_nodes )
	{
		XMLDocument doc;

		XMLNode root = doc.GetRootNode();
		CHECK( ! root.IsValid() );
		CHECK_EQUAL( "", root.GetName() );
		CHECK_EQUAL( "", root.GetValue() );


		XMLNodeList children = root.GetChildren();

		CHECK_EQUAL( 0,		children.size() );
	}


	TEST( TEST_simple_XML1_parses_nodes_correctly )
	{
		XMLDocument doc;

		doc.ParseString( testXML1 );

		XMLNode root = doc.GetRootNode();
		
		// Test root
		CHECK( root.IsValid() );
		CHECK_EQUAL( "rootNode", root.GetName() );

		// Test general children
		XMLNodeList children = root.GetChildren();

		CHECK_EQUAL( 4,			children.size()		  );
		CHECK_EQUAL( "item1",	children[0].GetName() );
		CHECK_EQUAL( "item2",	children[1].GetName() );
		CHECK_EQUAL( "item3",	children[2].GetName() );
		CHECK_EQUAL( "item4",	children[3].GetName() );

		CHECK_EQUAL( "1",	children[0].GetValue() );
		CHECK_EQUAL( " 2  ",	children[1].GetValue() );
		CHECK_EQUAL( "value3",	children[2].GetValue() );
		CHECK_EQUAL( " and 4 ",	children[3].GetValue() );

		// Test specific children
		children = root.GetChildren("item3");

		CHECK_EQUAL( 1,			children.size()		  );
		CHECK_EQUAL( "item3",	children[0].GetName() );
	}


	TEST( TEST_simple_XML2_parses_nodes_correctly )
	{
		XMLDocument doc;

		doc.ParseString( testXML2 );

		XMLNode root = doc.GetRootNode();
		
		// Test root
		CHECK( root.IsValid() );
		CHECK_EQUAL( "volume", root.GetName() );

		// Test general children
		XMLNodeList children = root.GetChildren();

		CHECK_EQUAL( 3,			children.size()		  );
		CHECK_EQUAL( "width",	children[0].GetName() );
		CHECK_EQUAL( "height",	children[1].GetName() );
		CHECK_EQUAL( "depth",	children[2].GetName() );

		CHECK_EQUAL( "128",		children[0].GetValue() );
		CHECK_EQUAL( "256",		children[1].GetValue() );
		CHECK_EQUAL( "512",		children[2].GetValue() );

		// Test specific children
		children = root.GetChildren("height");

		CHECK_EQUAL( 1,			children.size()		  );
		CHECK_EQUAL( "height",	children[0].GetName() );
	}
}