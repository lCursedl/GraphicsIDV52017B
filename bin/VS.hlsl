cbuffer ConstantBuffer{
    float4x4 WVP;
	float4x4 World;
	float4	 LightPos;
	float4 	 LightColor;
	float4   CameraPosition;
	float4	 Ambient;
}

struct VS_INPUT{
    float4 position : POSITION;
	float4 normal   : NORMAL;
    float2 texture0 : TEXCOORD;
};

struct VS_OUTPUT{
    float4 hposition : SV_POSITION;
	float4 hnormal   : NORMAL;
    float2 texture0  : TEXCOORD;
	float4 wPos       : TEXCOORD1;
};

VS_OUTPUT VS( VS_INPUT input ){
    VS_OUTPUT OUT;
    OUT.hposition = mul( WVP , input.position );
	
	float3x3 RotWorld = (float3x3)World;
	
	//OUT.hnormal = normalize( mul( World , input.normal ) );
    //OUT.texture0 = input.texture0;
	
	OUT.hnormal = float4(normalize(mul(RotWorld, input.normal.xyz)), 1.0);
	OUT.texture0 = input.texture0;
	OUT.wPos = mul(World,input.position);
	
    return OUT;
}
