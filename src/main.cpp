#include <UnitTest++.h>
#include <cstdio>

#include <TexMapVolumeRenderer.h>
#include <TexMapVolumeRendererNode.h>
#include <Node.h>

#include <gl/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <fstream>
#include <iostream>

//#include <GLX/glext.h>

#include <XMLDocument.h>

using namespace Vroom;



void LoadVolumeFromFile( Volume &vol, const char *fname )
{	
	sf::Image the3DImage;
	the3DImage.loadFromFile( fname );

	Vroom::String filname = fname;

	Vroom::XMLDocument doc;
	doc.ParseFile( filname + ".meta" ); 

	Vroom::XMLNode node = doc.GetRootNode();
	int volWidth  = node.GetChildren( "volWidth" )[0].GetIntValue();
	int volHeight = node.GetChildren( "volHeight" )[0].GetIntValue();
	int volDepth  = node.GetChildren( "volDepth" )[0].GetIntValue();

	vol.Create(volWidth, volHeight, volDepth);
	UInt8 *v = vol.GetData();

	for(int i=0; i< volWidth; i++)
	{
		for(int j=0; j< volHeight; j++)
		{
			for(int k=0; k< volDepth; k++)
			{
				sf::Color c = the3DImage.getPixel(i + k*volWidth, volHeight-j-1);
				*(v++) = c.r;
				*(v++) = c.g;
				*(v++) = c.b;
				*(v++) = c.a;
			}
		}
	}

}



void LoadHead( Volume &vol )
{
	vol.Create(128, 128, 128);

	UInt8 *v = vol.GetData();

	for( int i=1; i<=255; i+=2 )
	{		
		std::stringstream name;
		
		name << "../../data/HumanHead/a_vm1";

		if( i < 10 )
		{
			name << "00";
		}
		else if( i < 100 )
		{
			name << "0";
		}


		name << i;
		name << "-m.jpg";

		sf::Image theSlice;
		theSlice.loadFromFile( name.str() );

		for( int x =0; x< theSlice.getSize().x; x++ )
		{
			for( int z=0; z< theSlice.getSize().y; z++ )
			{
				sf::Color c = theSlice.getPixel(x, z);

				double alpha = (c.r+c.g+c.b)*0.4;

				if( alpha > 255 )
					alpha = 255;

				vol.SetVoxel(x, 127-i/2, z, Color(c.r,c.g,c.b, (UInt8)alpha ) );
			}
		}
	}
}


const char *glErrorName( GLenum err )
{
	switch( err ) 
	{
		case GL_INVALID_ENUM:
			return "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			return "GL_INVALID_VALUE";
			break;

		case GL_INVALID_OPERATION:
			return "GL_INVALID_OPERATION";
			break;
		case GL_STACK_OVERFLOW:
			return "GL_STACK_OVERFLOW";
			break;
		case GL_STACK_UNDERFLOW:
			return "GL_STACK_UNDERFLOW";
			break;
		case GL_OUT_OF_MEMORY:
			return "GL_OUT_OF_MEMORY";
			break;
	}
}





void printGLStats()
{
	GLint maxTextureSize = 0;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);

	std::cout << "GL_MAX_TEXTURE_SIZE - " << maxTextureSize << std::endl;

	maxTextureSize = 0;
	glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &maxTextureSize);

	std::cout << "GL_MAX_3D_TEXTURE_SIZE - " << maxTextureSize << std::endl;

	GLenum err = glGetError();

	if( err )
		std::cout << "GL error - " << glErrorName(err)<< std::endl;

	if( GLEW_ARB_vertex_program )
		std::cout << "Vertex program supported!" << std::endl;
	else
		std::cout << "!! Vertex program NOT supported!" << std::endl;

	if( GLEW_ARB_fragment_program )
		std::cout << "Fragment program supported!" << std::endl;
	else
		std::cout << "!! Fragment program NOT supported!" << std::endl;
}


//#include "Shaders.shd"

const GLcharARB * VertShaderSrc = 
"varying vec4 vTexCoord;"
"varying vec4 position;"

"void main(void)"
"{"
"	position = gl_Vertex;"
"	vTexCoord = gl_MultiTexCoord0;"
"   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
"} ";

const GLcharARB * FragShaderSrc = 
"varying vec4 vTexCoord;"
"varying vec4 position;"
"uniform sampler3D texture1;"
"uniform sampler3D texture2;"
" "
"void main (void)"
"{"
"	vec3 texCoord = vTexCoord.xyz;"
"	vec4 tex = texture3D(texture1, texCoord);"

"	vec4 n = (texture3D(texture2, texCoord) - vec4(0.5, 0.5, 0.5, 0.0));"
"	vec3 v = vec3( position );"
"   vec3 Lp = vec3( gl_ModelViewMatrix * vec4(5, 10,-10, 1) );"
"	vec3 l = normalize( Lp - v );"

"	float lDot = l.x*n.x + l.y*n.y + l.z*n.z;"
"		  lDot = lDot * 2.2 + 0.2;"

"   vec4 finalCol = vec4( lDot * tex.r, lDot * tex.g, lDot * tex.b, tex.a);"
"	finalCol = clamp(finalCol, 0.0, 1.0);"

"	gl_FragColor = finalCol; "
"}";


GLuint myShader = 0;

void ShaderTest()
{		
	GLint compiled;
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	GLint vshadlen = strlen(VertShaderSrc);
	GLint fshadlen = strlen(FragShaderSrc);

	glShaderSourceARB(vertShader, 1, &VertShaderSrc, &vshadlen );
	glShaderSourceARB(fragShader, 1, &FragShaderSrc, &fshadlen );

	glCompileShaderARB(vertShader);
	glCompileShaderARB(fragShader);

	glGetObjectParameterivARB(vertShader, GL_COMPILE_STATUS, &compiled);
	if(! compiled)
	{
		std::cout << "Failed to compile vert shader." << std::endl;
		
		GLint blen = 0;	
		GLsizei slen = 0;

		glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH , &blen);       
		if (blen > 1)
		{
			GLchar* compiler_log = (GLchar*)malloc(blen);
			glGetInfoLogARB(vertShader, blen, &slen, compiler_log);
			std::cout << "compiler_log:\n" << compiler_log;
			free (compiler_log);
		}
	}

	glGetObjectParameterivARB(fragShader, GL_COMPILE_STATUS, &compiled);
	if(! compiled)
	{
		std::cout << "Failed to compile frag shader." << std::endl;

		GLint blen = 0;	
		GLsizei slen = 0;

		glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH , &blen);       
		if (blen > 1)
		{
			GLchar* compiler_log = (GLchar*)malloc(blen);
			glGetInfoLogARB(fragShader, blen, &slen, compiler_log);
			std::cout << "compiler_log:\n" << compiler_log;
			free (compiler_log);
		}
	}


	myShader = glCreateProgram();

	glAttachShader(myShader, vertShader);
	glAttachShader(myShader, fragShader);

	glLinkProgram(myShader);
}


int main(int argc, char* args[])
{
	if ( argc > 1   &&   strcmp("-test", args[1])==0 )
	{
		int result = 0;

		printf("\n--=-=-=-=== = Test = ===-=-=-=--\n");
		result = UnitTest::RunAllTests();
		printf(  "--=-=-=-== == ==== == ==-=-=-=--\n\n");

		return result;
	}
	else
	{		
		sf::RenderWindow theWindow( sf::VideoMode(640, 480), "Graphix Window" );
		TexMapVolumeRenderer *renderer = new TexMapVolumeRenderer();

		glewInit();

		// Print something useful 
		printGLStats();

		ShaderTest();

		Volume vol;

		LoadVolumeFromFile(vol, "../../data/test.png");
		//LoadHead( vol );

		Node * volumeNode = renderer->GetRootNode();

		TexMapVolumeRendererNode* texNode = 
			(TexMapVolumeRendererNode*) volumeNode;

		volumeNode->SetVolume( &vol );

		//texNode->SetLighting( true );

		while( theWindow.isOpen() )
		{
			sf::Event theEvent;
			while( theWindow.pollEvent(theEvent) )
			{
				switch( theEvent.type )
				{
					case sf::Event::Closed :
						theWindow.close();
					break;

					case sf::Event::Resized :
						glViewport (0, 0, 
							(GLsizei) theWindow.getSize().x, 
							(GLsizei) theWindow.getSize().y );
					break;

					case sf::Event::KeyReleased :
						if( theEvent.key.code == sf::Keyboard::S ) 
						{
							int debugFlags = texNode->GetDebugFlags()
								^ TexMapVolumeRendererNode::DBG_DRAW_SLICES;

							texNode->SetDebugFlags( debugFlags );
						}
						if( theEvent.key.code == sf::Keyboard::B ) 
						{
							int debugFlags = texNode->GetDebugFlags()
								^ TexMapVolumeRendererNode::DBG_DRAW_BBOX;

							texNode->SetDebugFlags( debugFlags );
						}
						if( theEvent.key.code == sf::Keyboard::L )
						{
							bool light = texNode->GetLighting();
							texNode->SetLighting( !light );
						}
					break;
				}
			}


			if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
			{
				UInt32 numSlices = texNode->GetNumberOfSlices();

				if( numSlices > 1 )
					texNode->SetNumberOfSlices(numSlices-1);
			}

			if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
			{
				UInt32 numSlices = texNode->GetNumberOfSlices();
				texNode->SetNumberOfSlices(numSlices+1);
			}

			if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
			{
				Real exp = texNode->GetSliceSpacingExponent();

				if( exp > 1.01 )
					texNode->SetSliceSpacingExponent(exp-0.01);
			}
			
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
			{
				Real exp = texNode->GetSliceSpacingExponent();
				texNode->SetSliceSpacingExponent(exp+0.01);
			}


			// Clear the screen
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//glUseProgram( myShader );
			renderer->Render();
		
			theWindow.display();
		}

//Undel
//		delete renderer;

		return 0;
	}
}
