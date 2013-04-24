varying vec4 texCoord;

uniform sampler3D texture1;
uniform vec3 res;

vec3 voxNormal(in sampler3D texture, in vec3 texCoord, in vec3 res)
{
	vec4 voxel = texture3D(texture, texCoord);
		
	vec3 normalDir = vec3(0.0, 0.0, 0.0);

	for(float i= -1.0; i<=1.0; i+= 2.0)
	{
		vec3 newTexCoordX = vec3( texCoord.x + i*res.x, texCoord.y, texCoord.z );
		vec3 newTexCoordY = vec3( texCoord.x, texCoord.y + i*res.y, texCoord.z );
		vec3 newTexCoordZ = vec3( texCoord.x, texCoord.y, texCoord.z + i*res.z );

		normalDir.x += i * texture3D(texture, newTexCoordX).a;
		normalDir.y += i * texture3D(texture, newTexCoordY).a;
		normalDir.z += i * texture3D(texture, newTexCoordZ).a;
	}

	float normLen = length(normalDir);
	if( normLen > 0.0 )
	{
		normalDir /= normLen;
	}

	normalDir *= 0.5;
	normalDir += vec3(0.5, 0.5, 0.5);

	return normalDir;
}


void main(void)
{
	vec4 tex = texture3D(texture1, texCoord.xyz);

	gl_FragColor.xyz = voxNormal(texture1, texCoord.xyz, res);
	gl_FragColor.a = tex.a;
}