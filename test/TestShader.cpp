#include <Shader.h>
#include "GraphicsFixture.h"

#include <UnitTest++.h>
#include <MoreUnitTest++.h>
#include <iostream>


using namespace Vroom;


const String WORKING_VertexShader =  
"	void main() {														\n"
"		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;			\n"
"   }																	\n";

const String WORKING_FragmentShader =  
"	void main() {														\n"
"		gl_FragColor = vec4 (0.0, 1.0, 0.0, 1.0);						\n"
"   }																	\n";


const String BROKEN_VertexShader =  
"	void main() 	&*%^&												\n"
"		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;			\n"
"   }																	\n";

const String BROKEN_FragmentShader =  
"	void main() 	&*%^&												\n"
"		gl_FragColor = vec4 (0.0, 1.0, 0.0, 1.0);						\n"
"   }																	\n";


SUITE( Shader )
{
	TEST_FIXTURE( GraphicsFixture, TEST_shader_should_initialize_to_invalid )
	{
		Shader theShader;

		CHECK_NOT( theShader.IsValid() );
	}


	TEST_FIXTURE( GraphicsFixture, TEST_compiling_shader_code_validates_the_shader )
	{
		// VERTEX SHADER
		if( Shader::IsSupported(Shader::ST_VERTEX) )
		{			
			Shader theShader;
			bool compiles = false;

			compiles = theShader.CompileString( Shader::ST_VERTEX, WORKING_VertexShader );

			CHECK( compiles );
			CHECK( theShader.IsValid() );
		}
		else
		{			
			std::cout << "Vertex shaders not supported. Skipping in \"" << m_details.testName << "\"" << std::endl;
		}

		// FRAGMENT SHADER
		if( Shader::IsSupported(Shader::ST_FRAGMENT) )
		{			
			Shader theShader;
			bool compiles = false;

			compiles = theShader.CompileString( Shader::ST_FRAGMENT, WORKING_FragmentShader );

			CHECK( compiles );
			CHECK( theShader.IsValid() );
		}
		else
		{			
			std::cout << "Fragment shaders not supported. Skipping in \"" << m_details.testName << "\"" << std::endl;
		}
	}


	TEST_FIXTURE( GraphicsFixture, TEST_compiling_broken_vertex_shader_code_fails_to_validates_the_shader )
	{
		// VERTEX SHADER
		if( Shader::IsSupported(Shader::ST_VERTEX) )
		{
			Shader theShader;
			bool compiles = false;

			compiles = theShader.CompileString( Shader::ST_VERTEX, BROKEN_VertexShader );

			CHECK_NOT( compiles );
			CHECK_NOT( theShader.IsValid() );
		}
		else
		{			
			std::cout << "Vertex shaders not supported. Skipping in \"" << m_details.testName << "\"" << std::endl;
		}

		// FRAGMENT SHADER
		if( Shader::IsSupported(Shader::ST_FRAGMENT) )
		{
			Shader theShader;
			bool compiles = false;

			compiles = theShader.CompileString( Shader::ST_FRAGMENT, BROKEN_FragmentShader );

			CHECK_NOT( compiles );
			CHECK_NOT( theShader.IsValid() );
		}
		else
		{			
			std::cout << "Fragment shaders not supported. Skipping in \"" << m_details.testName << "\"" << std::endl;
		}
	}


	TEST_FIXTURE( GraphicsFixture, TEST_destroying_a_valid_shader_shout_invalidate_it )
	{
		// VERTEX SHADER
		if( Shader::IsSupported(Shader::ST_VERTEX) )
		{
			Shader theShader;
			bool compiles = false;

			compiles = theShader.CompileString( Shader::ST_VERTEX, WORKING_VertexShader );
			theShader.Destroy();

			CHECK( compiles );
			CHECK_NOT( theShader.IsValid() );
		}
		else
		{			
			std::cout << "Vertex shaders not supported. Skipping in \"" << m_details.testName << "\"" << std::endl;
		}

		// FRAGMENT SHADER
		if( Shader::IsSupported(Shader::ST_FRAGMENT) )
		{
			Shader theShader;
			bool compiles = false;

			compiles = theShader.CompileString( Shader::ST_FRAGMENT, WORKING_FragmentShader );
			theShader.Destroy();

			CHECK( compiles );
			CHECK_NOT( theShader.IsValid() );
		}
		else
		{			
			std::cout << "Vertex shaders not supported. Skipping in \"" << m_details.testName << "\"" << std::endl;
		}
	}
}