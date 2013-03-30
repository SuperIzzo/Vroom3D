varying vec4 vTexCoord;
varying vec4 position;

void main(void)
{
	position = gl_Vertex;
	vTexCoord = gl_MultiTexCoord0;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}