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

#include <UnitTest++.h>
#include <cstdio>

#include <VolumeRenderer.h>
#include <RenderNode.h>
#include <ShaderProgram.h>

#include <gl/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <fstream>
#include <iostream>

#include <XMLDocument.h>

using namespace Vroom;




void LoadVolumeFromFile( VolumeData &vol, const char *fname )
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



void LoadHead( VolumeData &vol )
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




String ReadFile( String fname )
{
	String			theResult = "";
	std::ifstream	theFile;
	
	theFile.open(fname);	
	if( theFile.is_open() ) 
	{
		while( !theFile.eof() ) 
		{
			std::string line;
			std::getline(theFile, line);

			theResult += line + "\n";
		}
	}
	theFile.close();

	return theResult;
}





ShaderProgram myShader;
void ShaderTest()
{		
	ShaderPtr vertShader	= new Shader();
	ShaderPtr fragShader	= new Shader();

	String vertShaderSrc = ReadFile( "../../data/Lighting.vert");
	String fragShaderSrc = ReadFile( "../../data/Lighting.frag");

	vertShader->CompileString( Shader::ST_VERTEX,	vertShaderSrc );
	fragShader->CompileString( Shader::ST_FRAGMENT,	fragShaderSrc );


	if( !vertShader->CompileString( Shader::ST_VERTEX,	vertShaderSrc ) )
	{
		std::cout << vertShader->GetInfoLog() << std::endl;
	}

	if( !fragShader->CompileString( Shader::ST_FRAGMENT,	fragShaderSrc ) )
	{
		std::cout << fragShader->GetInfoLog() << std::endl;
	};


	myShader.AttachShader( vertShader );
	myShader.AttachShader( fragShader );

	myShader.Link();
}

ShaderProgram myNormalShader;
void NormalTest()
{		
	ShaderPtr vertShader	= new Shader();
	ShaderPtr fragShader	= new Shader();

	String vertShaderSrc = ReadFile( "../../data/NormalMap.vert");
	String fragShaderSrc = ReadFile( "../../data/NormalMap.frag");

	if( !vertShader->CompileString( Shader::ST_VERTEX,	vertShaderSrc ) )
	{
		std::cout << vertShader->GetInfoLog() << std::endl;
	}

	if( !fragShader->CompileString( Shader::ST_FRAGMENT,	fragShaderSrc ) )
	{
		std::cout << fragShader->GetInfoLog() << std::endl;
	};


	myNormalShader.AttachShader( vertShader );
	myNormalShader.AttachShader( fragShader );

	myNormalShader.Link();
}






void GenerateBricks( VolumeData &vol )
{
	const UInt32 FILL_INSET = 2;
	vol.Create( 32, 32, 32 );

	Color brickColor( 180, 0, 0 );
	Color fillColor( 120, 120, 120 );

	for( UInt32 x = 0; x < vol.GetWidth(); x++ )
	{
		for( UInt32 y = 0; y < vol.GetHeight(); y++ )
		{
			for( UInt32 z = 0; z < vol.GetDepth(); z++ )
			{
				Color &col = vol.GetVoxel(x,y,z);

				int inset = (y/4 % 2 ^ z/4 % 2)*4;

				srand( (x-inset)/8 + y/4*vol.GetWidth() + z/4*vol.GetWidth()*vol.GetHeight() );
				brickColor = Color( 120 + rand()%30, rand()%70, rand()%20 );
				
				if( x % 8 == inset || y % 4 == 0 || z % 4 == 0 )
				{
					col = fillColor;

					if(		x<FILL_INSET || x>=vol.GetWidth()-FILL_INSET 
						||	y<FILL_INSET || y>=vol.GetHeight()-FILL_INSET 
						||	z<FILL_INSET || z>=vol.GetDepth()-FILL_INSET )
						col.alpha = 0;					
				}
				else
				{
					col = brickColor;
					col.red+= (5 - rand()%10)*2;
					col.green+= rand()%10;
					col.blue+= rand()%10;
				}
			}
		}
	}
}


VolumeRenderer *renderer;


void UpdateCamera()
{	 
	static double angle = 0;
	angle += 0.1;
	//double angle = 100;

	Eigen::Transform<float,3, Eigen::Affine> transf;
			
	transf =	
		(
		Eigen::Translation3f( 0,0, -5 )
					*
		Eigen::AngleAxisf( (angle*0.002+30)/180.f*3.14f, Eigen::Vector3f(1,0,0) )
					*	
		Eigen::AngleAxisf( angle*10/180.f, Eigen::Vector3f(0,1,0) )
					*
		Eigen::Translation3f( -0.5, -0.5, -0.5)
		);

	renderer->GetCamera()->SetView( transf );
}




Eigen::Vector4f lightPos;


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
		renderer = new VolumeRenderer();

		renderer->GetCamera()->SetOrthographicProjection(-1, 1, -1, 1, 0, 100);

		glewInit();

		// Print something useful 
		printGLStats();

		ShaderTest();
		NormalTest();

		VolumeData vol[3];

		GenerateBricks( vol[0] );
		LoadVolumeFromFile(vol[1], "../../data/test.png");
		LoadHead( vol[2] );
		int modelId = 0;


		RenderNode * texNode = renderer->GetRootNode();

		texNode->SetVolumeData( vol[0] );
		

		texNode->showNorm = 0;

		
		sf::Clock clock;
		clock.restart();

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
								^ RenderNode::DBG_DRAW_SLICES;

							texNode->SetDebugFlags( debugFlags );
						}
						if( theEvent.key.code == sf::Keyboard::B ) 
						{
							int debugFlags = texNode->GetDebugFlags()
								^ RenderNode::DBG_DRAW_BBOX;

							texNode->SetDebugFlags( debugFlags );
						}
						if( theEvent.key.code == sf::Keyboard::L )
						{
							bool light = texNode->GetLighting();
							texNode->SetLighting( !light );
						}
						if( theEvent.key.code == sf::Keyboard::M )
						{
							modelId++;
							modelId%=3;
							
							texNode->SetVolumeData( vol[modelId] );
						}
						if( theEvent.key.code == sf::Keyboard::N )
						{
							texNode->showNorm++;
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



			static float a = 0;
			a += 0.01;
			lightPos = Eigen::Vector4f( 100*sin(a), 180*cos(a), 34*sin(a), 0 );
			lightPos.normalize();
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos.data() );



			// Clear the screen
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			UpdateCamera();

			renderer->Render();
		
			theWindow.display();


			// FPS stuff
			{
				sf::Time frameTime = clock.restart();
				float fps = 1/frameTime.asSeconds();
				std::cout << "FPS: " << fps << std::endl;
			}
		}

		delete renderer;

		return 0;
	}
}
