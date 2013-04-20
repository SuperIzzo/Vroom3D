varying vec4 vTexCoord;
varying vec4 position;
uniform sampler3D texture1;
uniform sampler3D texture2;

uniform int lightModel;
uniform vec3 l;
uniform vec3 h;

void main (void)
{
	vec3 texCoord = vTexCoord.xyz;
	vec4 tex = texture3D(texture1, texCoord);

	vec4 n = (texture3D(texture2, texCoord) - vec4(0.5, 0.5, 0.5, 0.0));
	vec3 v = vec3( position );

	float lnDot = l.x*n.x + l.y*n.y + l.z*n.z;	
	float hnDot = h.x*n.x + h.y*n.y + h.z*n.z;

	// we have to multiply the dot by 2 because n was halfsized
	lnDot = clamp(lnDot*2.0, -1.0, 1.0);
	hnDot = clamp(hnDot*2.0, -1.0, 1.0);	

	float k_s = 1;
	float I = lnDot + k_s * pow(hnDot,7)   + 0.2;
	
	vec4 finalCol;
	if( lightModel == 1 ) 
	{
		finalCol = vec4( I * tex.r, I * tex.g, I * tex.b, tex.a);
	} 
	else if( lightModel == 2 )
	{
		finalCol = vec4( lnDot * lnDot * tex.r, lnDot * lnDot * tex.g, lnDot * lnDot * tex.b, tex.a);
	}
	else if( lightModel == 3 )
	{
		if( lnDot > 0.7 ) 
		{ 
			finalCol = tex; 
		}
		else if( lnDot > 0.3 ) 
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