#version 330 core

// Interpolated values from the vertex shaders
in vec4 emissiveColor;
in vec3 texCoord3d;
in vec3 translateToOrigin;
// Ouput data
out vec4 color;
uniform sampler3D VolumeTex;
uniform sampler1D TransferFunction;
uniform mat4 T;

void main(){

	// Output color = color specified in the vertex shader, 
	// interpolated between all 3 surrounding vertices
	//color = vec4(1,0,0,1);
/* 	vec3 originalUVW = texCoord3d.xyz;
	//vec3 translateToOrigin = vec3(0.5, 0, totalSlices);	
	vec3 uvwAtOrigin = originalUVW - translateToOrigin;
	
	vec4 transformedTexCoord = T * vec4(uvwAtOrigin.xyz,1);
	vec3 actualTexCoord3D = transformedTexCoord.xyz + translateToOrigin; */
	
	float value = texture(VolumeTex, texCoord3d).r;
	color = texture(TransferFunction , value);
	
	// if(r > 0.1)
		// color = vec4(r,r,r,1);
	// else
		// color = vec4(r,r,r,0);  // Read 3D data texture
	//color =  emissiveColor * a.x;           // Multiply color by opacityvec4(1,0,0,1);

}