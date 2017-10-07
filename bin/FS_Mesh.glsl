varying highp vec3 vecTransformed;
varying highp vec2 vecUVCoords;
varying highp vec4 VecPosition;

uniform highp sampler2D Diffuse;
uniform highp vec4 LightPos;

void main(){
	
	highp vec3 veclight = VecPosition.xyz - LightPos.xyz;
	veclight = normalize(veclight);
	highp vec3 vecNormal = normalize(vecTransformed);
	
	highp vec4 Diff = texture2D(Diffuse, vecUVCoords);
	highp float Att = clamp(dot(veclight, vecNormal), 0.0, 1.0);
	
	highp vec3 Color = Diff.rgb;
	Color = Color * Att;
	Color = Color + Diff.rgb * 0.15;
	
	gl_FragColor = vec4(Color, 1.0);
}