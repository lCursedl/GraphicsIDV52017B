attribute highp vec4 Vertex;
attribute highp vec4 Normal;
attribute highp vec2 UV;


varying highp vec3 vecTransformed;
varying highp vec2 vecUVCoords;
varying highp vec4 VecPosition;

uniform highp mat4 WVP;
uniform highp mat4 World;

void main(){
	vecTransformed = normalize(mat3(World)*vec3(Normal));
	VecPosition = World * Vertex;
	vecUVCoords = UV;
	gl_Position = WVP*Vertex;
}