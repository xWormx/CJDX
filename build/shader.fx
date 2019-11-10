Texture2D colorMap : register(t0);
SamplerState colorSampler : register(s0);

struct VSout
{
	float4 pos : SV_POSITION;
	float4 col : COLOR;
};


struct PSOut
{
	float4 col : SV_TARGET;
};

cbuffer cBuff
{
	float4x4 _posMatrix;
	float4 _color;
};

VSout VS_Main(float4 pos : POSITION, float4 col : COLOR)
{
	VSout vsOut;
	vsOut.pos = mul(pos, _posMatrix); 

	vsOut.col = _color; 

	return vsOut;
}

PSOut PS_Main(VSout vsOut)
{
	PSOut psOut;
	psOut.col = vsOut.col;
	
	return psOut;
}
