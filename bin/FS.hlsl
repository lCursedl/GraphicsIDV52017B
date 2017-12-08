cbuffer ConstantBuffer{
    float4x4 World;
    float4x4 WVP;
	float4	 LightPos;
	float4 	 LightFinal;
	float4   CameraPosition;
	float4	 Ambient;
}

Texture2D TextureRGB : register(t0);
Texture2D TextureNormal : register(t1);

SamplerState SS;

struct VS_OUTPUT{
    float4 hposition	: SV_POSITION;
	float4 hnormal		: NORMAL;
    float2 texture0		: TEXCOORD;
	float4 wPos			: TEXCOORD1;
};

float4 FS( VS_OUTPUT input ) : SV_TARGET
{
	float4 Color = float4(0.0, 0.0, 0.0, 1.0);
	//Output
	float4 Final = float4(0.0, 0.0, 0.0, 1.0);
	//
	Color 		= TextureRGB.Sample(SS, input.texture0);
	//Specular variables
	float specular = 0.0;
	float SpecularIntensivity = 1.0;
	float Shinness = 32.0;
	//
	
	float4 Ambiental	= Color * Ambient;
	float4 Lambert		= LightFinal;
	float4 Specular		= LightFinal;
	float3 LightDir		= normalize(LightPos - input.wPos).xyz;
	float3 EyeDir		= normalize(CameraPosition - input.wPos).xyz;
	float3 normal		= input.hnormal.xyz;
	float Att			= 1.0;
	
	//Normal Map
	
	//
	
	//float4 LightDir	= normalize(LightPos - input.wPos);
	//float4 EyeDir	= normalize(CameraPosition - input.wPos);
	//float4 normal	= input.hnormal;
	
	//float4 DiffuseClr = TextureRGB.Sample(SS, input.texture0);
	//float Att = clamp(dot(LightDir, normal), 0.0, 1.0);
	
	//Diffuse Map
	
	Att 		= dot(LightDir, normal) * 0.5 + 0.5;
	Att 		= pow(Att, 32.0);
	Att 		= clamp(Att, 0.0, 1.0);
	//Att 		= clamp(dot(LightDir, normal), 0.0, 1.0);
	Lambert 	*= Color * Att;
	//
	
	//Specular
		//Map
		//
		//Blinn
			float3 ReflectedLight = normalize(EyeDir + LightDir);
			specular = max(dot(ReflectedLight, normal) * 0.5 + 0.5, 0.0);
			specular = pow(specular, Shinness);
		//
		 
		specular *= SpecularIntensivity;
		Specular *= specular;
	//
	
	Final += Ambiental;
	Final += Lambert;
	Final += Specular;	
	
	//Final = TextureRGB.Sample( SS, input.texture0 );	
	return Final;
	//return float4(1.0,0.0,1.0,1.0);
}