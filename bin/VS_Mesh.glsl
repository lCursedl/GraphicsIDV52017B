attribute highp vec4 Vertex;
attribute highp vec4 Normal;
attribute highp vec2 UV;
attribute highp	vec4 Diffuse;

varying highp vec3 vecTransformed;
varying highp vec2 vecUVCoords;

uniform highp mat4 WVP;
uniform highp mat4 World;


void main(){
	vecUVCoords = UV;
	vecTransformed = normalize(mat3(World)*vec3(Normal));
	
	
	
	gl_Position = WVP*Vertex;
}