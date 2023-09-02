Texture2D resource;

SamplerState linearfilter
{
    Filter = MIN_MAG_MIP_LINEAR;
};
// MIN_MAG_MIP_POINT -> pixelArt
SamplerState anisotropic
{
    Filter = ANISOTROPIC;
    MaxAnisotropy = 4;
};

struct pixelIn
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
    float2 Tex : TEXCOORD;
};

float4 main(pixelIn pIn) : SV_TARGET
{
    return resource.Sample(linearfilter, pIn.Tex) * pIn.Color;
}