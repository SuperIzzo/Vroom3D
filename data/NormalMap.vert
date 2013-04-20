varying vec4 texCoord;

void main(void)
{
	texCoord = gl_MultiTexCoord0;
	gl_Position = gl_Vertex;
}