attribute highp vec4 Vertex;
attribute highp vec4 Normal;
attribute highp vec2 UV;

varying highp vec2 vecUVCoords;
varying highp vec4 wPos;
varying highp vec4 normal;
varying highp vec4 pos;


uniform highp mat4 WVP;
uniform highp mat4 World;
uniform highp vec4 LightPos;
uniform highp vec4 CameraPos;


void main()
{
	pos = WVP * Vertex;
	mat3 RotWorld = mat3(World);
	normal	= vec4(normalize(RotWorld*vec3(Normal)),1.0);
	wPos = World*Vertex;
	vecUVCoords = UV;
	gl_Position = WVP*Vertex;
	
}