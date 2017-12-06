cbuffer ConstantBuffer{
    float4x4 World;
    float4x4 WVP;
	float4	 LightPos;
	float4 	 LightColor;
	float4   CameraPosition;
	float4	 Ambient;
}

Texture2D TextureRGB : register(t0);
Texture2D TextureNormal : register(t1);

SamplerState SS;

struct VS_OUTPUT{
    float4 hposition : SV_POSITION;
	float4 hnormal   : NORMAL;
    float2 texture0  : TEXCOORD;
	float4 wPos		: TEXCOORD1;
};

float4 FS( VS_OUTPUT input ) : SV_TARGET  {
	float4 color;
	
	float4 LightDir = normalize(LightPos - input.wPos);
	float4 EyeDir= normalize(CameraPosition - input.wPos);
	float4 normal = input.hnormal;
	
	float4 DiffuseClr = TextureRGB.Sample(SS, input.texture0);
	float Att = clamp(dot(LightDir, normal), 0.0, 1.0);
	
	color = DiffuseClr * Att;
	color += Ambient * 0.30;
	
	//color = TextureRGB.Sample( SS, input.texture0 );	
	return color;
	//return float4(1.0,0.0,1.0,1.0);
}