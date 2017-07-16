attribute highp vec4 Vertex;

uniform highp mat4 WVP;
uniform highp mat4 World;

void main(){
	gl_Position = WVP*Vertex;
}