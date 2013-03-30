varying vec4 vTexCoord;
varying vec4 position;
uniform sampler3D texture1;
uniform sampler3D texture2;

uniform int lightModel;
uniform vec3 l;

void main (void)
{
	vec3 texCoord = vTexCoord.xyz;
	vec4 tex = texture3D(texture1, texCoord);

	vec4 n = (texture3D(texture2, texCoord) - vec4(0.5, 0.5, 0.5, 0.0));
	vec3 v = vec3( position );

	float lDot = l.x*n.x + l.y*n.y + l.z*n.z;
		  lDot = lDot * 2.2 + 0.2;
	
	vec4 finalCol;
	if( lightModel == 1 ) 
	{
		finalCol = vec4( lDot * tex.r, lDot * tex.g, lDot * tex.b, tex.a);
	} 
	else if( lightModel == 2 )
	{
		finalCol = vec4( lDot * lDot * tex.r, lDot * lDot * tex.g, lDot * lDot * tex.b, tex.a);
	}
	else if( lightModel == 3 )
	{
		if( lDot > 0.7 ) 
		{ 
			finalCol = tex; 
		}
		else if( lDot > 0.3 ) 
		{ 
			finalCol = vec4( tex.r * 0.7, tex.g * 0.7, tex.b * 0.7, tex.a ); 
		}
		else 
		{ 
			finalCol = vec4( tex.r * 0.3, tex.g * 0.3, tex.b * 0.3, tex.a ); 
		}
	}

	finalCol = clamp(finalCol, 0.0, 1.0);
	gl_FragColor = finalCol;
}