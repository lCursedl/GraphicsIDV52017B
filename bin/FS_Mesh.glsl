uniform mediump sampler2D Diffuse;

varying highp vec2 vecUVCoords;
varying highp vec4 normal;
varying highp vec4 wPos;
varying highp vec4 pos;

uniform highp vec4 LightPos;
uniform highp vec4 CameraPos;



void main()
{
	highp vec4 color;

	highp vec4	LightDir = normalize(LightPos - wPos);
	highp vec4  EyeDir = normalize(CameraPos - wPos);
	highp vec4	_normal = normal;
	highp vec4 DiffuseClr = texture2D(Diffuse,vecUVCoords);
	highp float Att = clamp(dot(LightDir, _normal), 0.0, 1.0);
	

	highp vec4 SpecularClr = vec4(1.0, 1.0, 1.0, 1.0);
	highp float specular = 0.0;
	highp float specIntesivity = 1.0;
	highp float gloss = 32.0;
	
	//highp vec3 	ReflectedLight = reflect(-LightDir.xyz, _normal.xyz);
	//specular = max ( dot(ReflectedLight.xyz,EyeDir.xyz)/2.0 +0.5, -dot(ReflectedLight.xyz, EyeDir.xyz)/2.0+0.5);
	//specular = pow(specular, gloss);
	
	
	highp vec3 ReflectedLight = normalize(EyeDir.xyz + LightDir.xyz);
	specular = max ( dot(ReflectedLight.xyz,_normal.xyz)/2.0 +0.5, -dot(ReflectedLight.xyz, _normal.xyz)/2.0+0.5);
	specular = pow(specular, gloss);

	specular *= Att;
	specular *= specIntesivity;
	SpecularClr *= specular;

	color = (DiffuseClr + SpecularClr)*Att;
	//color = SpecularClr;
	gl_FragColor = vec4(color);
}