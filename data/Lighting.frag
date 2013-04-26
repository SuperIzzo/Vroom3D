//=\\=//=\\=//=\\=//=\\=//=\\=//=\\=/// \\\=//=\\=//=\\=//=\\=//=\\=//=\\=//=\\
//                                                                           \\
//  Copyright (c) 2013   Hristoz S. Stefanov                                 \\
//                                                                           \\
//  Permission is hereby granted, free of charge, to any person              \\
//  obtaining a copy of this software and associated documentation files     \\
//  (the "Software"), to deal in the Software without restriction,           \\
//  including without limitation the rights to use, copy, modify, merge,     \\
//  publish, distribute, sublicense, and/or sell copies of the Software,     \\
//  and to permit persons to whom the Software is furnished to do so,        \\
//  subject to the following conditions:                                     \\
//                                                                           \\
//  The above copyright notice and this permission notice shall be included  \\
//  in all copies or substantial portions of the Software.                   \\
//                                                                           \\
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  \\
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               \\
//  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   \\
//  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     \\
//  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     \\
//  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        \\
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   \\
//                                                                           \\
//=\\=//=\\=//=\\=//=\\=//=\\=//=\\=\\\ ///=//=\\=//=\\=//=\\=//=\\=//=\\=//=\\

varying vec4 vTexCoord;
varying vec4 position;
uniform sampler3D volume;
uniform sampler3D normalMap;

uniform int shadingModel;
uniform vec3 l;
uniform vec3 h;

void main (void)
{
	vec3 texCoord = vTexCoord.xyz;
	vec4 tex = texture3D(volume, texCoord);

	if( shadingModel == 0 )
	{
		gl_FragColor = tex;
		return;
	}

	vec4 n = (texture3D(normalMap, texCoord) - vec4(0.5, 0.5, 0.5, 0.0));
	vec3 v = vec3( position );

	n = normalize(n);

	float lnDot = l.x*n.x + l.y*n.y + l.z*n.z;	
	float hnDot = h.x*n.x + h.y*n.y + h.z*n.z;

	// Clamp the results
	lnDot = clamp(lnDot, -1.0, 1.0);
	hnDot = clamp(hnDot, -1.0, 1.0);

	float k_s = 1.0;
	float I = lnDot + k_s * pow(-hnDot,3.0)   + 0.2;
	
	// Avoiding branches by doing some clever maths
	float cellShadingEnable = float( shadingModel==2 );
	float cells = 10002.0 - cellShadingEnable*10000.0;

	I = ceil( I*cells ) / cells;

	vec4 finalCol = vec4( I * tex.r, I * tex.g, I * tex.b, tex.a);


	finalCol = clamp(finalCol, 0.0, 1.0);
	gl_FragColor = finalCol;
}