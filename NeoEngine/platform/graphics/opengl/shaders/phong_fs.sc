$version 400

in vec3 normal;
in vec3 position;
in vec2 texcoord;
in vec3 tangent;
in vec3 bitangent;
in vec3 worldPosition;
in mat3 worldToTangent;

uniform mat4 ModelMatrix;
uniform vec3 CameraPosition;

uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;
uniform sampler2D SpecularTexture;
uniform sampler2D HeightTexture;

uniform int HasDiffuse = 0;
uniform int HasNormal = 0;
uniform int HasSpecular = 0;
uniform int HasHeight = 0;

uniform int NumTextures;

uniform vec3 Diffuse;
uniform vec3 Specular;
uniform vec3 Emit;
uniform float Opacity;
uniform float Shininess;

uniform int NumLights;

#include "ShaderLight.h"
layout (std140) uniform Lights
{
	ShaderLight lights;
};

#include "cook_torrance.sc"

vec3 removeGamma(vec3 color)
{
	return vec3(pow(color.x, 2.2f),
			pow(color.y, 2.2f),
			pow(color.z, 2.2f));
}

vec3 applyGamma(vec3 color)
{
	return vec3(pow(color.x, 1.0f/2.2f),
			pow(color.y, 1.0f/2.2f),
			pow(color.z, 1.0f/2.2f));
}

void main()
{
	vec3 Normal = normal;
	float Roughness = 0.4f / Shininess;
	vec3 v = normalize(-position);
	
	if(HasDiffuse == 1)
	{
		vec2 TexCoord = texcoord;
		if(HasHeight == 1)
		{	
			vec3 vdir = normalize(vec3(dot(v, tangent), dot(v, bitangent), dot(v, normal)));
			float height = texture2D(HeightTexture, texcoord).x * 0.025 - 0.015;
			vec2 offset = vdir.xy / vdir.z * height;

			offset = vdir.xy * height;
			TexCoord += offset;
		}
		
		if(HasNormal == 1)
		{
			vec3 bump = texture2D(NormalTexture, TexCoord).xyz * 2.0 - 1.0;
			Normal = vec3(normalize(tangent*bump.x + bitangent*bump.y + normal*bump.z));
		}
		
		if(HasSpecular == 1)
		{
			vec3 spec = texture2D(SpecularTexture, TexCoord).rgb;
			Roughness = ((spec.r + spec.b + spec.g) * Shininess);
		}
		
		gl_FragColor = texture2D(DiffuseTexture, TexCoord);
	}
	else
	{
		gl_FragColor = vec4(Diffuse, Opacity);
	}

	gl_FragColor.rgb = removeGamma(gl_FragColor.rgb);
	vec3 accumulator = Emit.rgb; // = Ambient + Emissive;

	for(int i = 0; i < NumLights; i++)
	{
		//accumulator += gl_FragColor.rgb * (lights.diffuseBrightness[i].rgb / length(lights.positionExponent[i].xyz - position));

		accumulator += calculateLight(gl_FragColor.rgb, position, Normal, v, Roughness,
										lights.positionExponent[i],
										lights.diffuseBrightness[i],
										lights.specularAttenuation[i],
										lights.directionAngle[i]);
	}

	gl_FragColor.rgb = applyGamma(accumulator);
}
