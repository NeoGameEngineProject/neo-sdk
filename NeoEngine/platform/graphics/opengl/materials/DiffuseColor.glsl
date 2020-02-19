$version 400

#if NEO_VERTEX
#include "builtin/vertex_header.glsl"

void main()
{
	gl_Position = ModelViewProjectionMatrix * vec4(Position, 1.0);
	position = (ModelViewMatrix * vec4(Position, 1.0)).xyz;
	normal = mat3(NormalMatrix) * Normal;
}

#else

uniform vec3 Diffuse;
uniform vec3 Specular;
uniform vec3 Emit;
uniform float Opacity;
uniform float Shininess;

#include "builtin/fragment_header.glsl"
#include "builtin/cook_torrance.glsl"
#include "builtin/gamma.glsl"

float rand(vec2 co, float rnd_scale)
{
	vec2 v1 = vec2(92.,80.);
	vec2 v2 = vec2(41.,62.);
	return fract(sin(dot(co.xy, v1)) + cos(dot(co.xy, v2)) * rnd_scale);
}

void main()
{
	vec3 Normal = normal;
	float Roughness = 0.4f / Shininess;
	vec3 v = normalize(-position);
	
	gl_FragColor = vec4(Diffuse, Opacity);
	
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

	// Add random part to prevent color banding
	gl_FragColor.rgb = applyGamma(accumulator) + 0.025f*rand(position.xz*1000.0f, 1000.0f);
}

#endif