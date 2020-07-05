
vec3 calculateLight(vec3 color, vec3 p, vec3 n, vec3 v, float specular,
					vec4 lightPosition, vec4 lightColor, vec4 lightSpecular, vec4 lightDirection)
{
	float lightExponent = lightPosition.w;
	float lightBrightness = lightColor.w;
	float lightAttenuation = lightSpecular.w;
	float lightAngle = lightDirection.w;

	vec3 l;
	if (lightAngle < 1.0)
		l = lightPosition.xyz - p;
	else
		l = -lightDirection.xyz;

	// Gauss constant
	const float c = 1.0;

	vec3 s = normalize(l);
	vec3 h = normalize(v + s);

	float attenuation = (lightBrightness / (1.0f + lightAttenuation * pow(length(lightPosition.xyz - p), 2.5)));

	if (lightAngle > 0.0 && lightAngle < 1.0)
	{
		float spot = dot(-s, lightDirection.xyz);

		if (spot > lightAngle)
		{
			spot = clamp(pow(spot - lightAngle, lightExponent), 0.0, 1.0);
			attenuation *= spot;
		}
		else
			return vec3(0.0f, 0.0f, 0.0f);
	}

	float nDoth = max(0.0, dot(n, h));
	float nDotv = dot(n, v);
	float vDoth = max(0.0, dot(v, h));
	float nDots = max(0.0, dot(n, s));

	float spec = pow(nDoth, specular);

	vec3 retval = nDots*(color.rgb * lightColor.rgb) + spec*(lightColor.rgb * Specular.rgb);

	return attenuation * retval;
}