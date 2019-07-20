cbuffer VSConstants : register(b0)
{
    float4x4 modelToWorld;
    float4x4 gTexTransform;
    float4x4 gMatTransform;
    uint gMaterialIndex;
};

cbuffer PassConstants : register(b1)
{
    float4x4 gViewProj;
    float3 gEyePosW;
    float pad;
    // ...
};

struct VertexIn
{
    float3 PosL  : POSITION;
    float3 NormalL : NORMAL;
    float2 TexC    : TEXCOORD;
};

struct VertexOut
{
    float4 PosH    : SV_POSITION;
    float3 PosL    : POSITION;
};

VertexOut main(VertexIn vin)
{
    VertexOut vout = (VertexOut)0.0f;

    // ʹ��ģ������ϵ
    vout.PosL = vin.PosL;

    // �Ѷ���ת������������ϵ
    float4 posW = mul(float4(vin.PosL, 1.0f), modelToWorld);
    
    // ������պе�����ʼ�����������λ��
    posW.xyz += gEyePosW;

    // ����ת����ͶӰ����ϵ
    // ʹ��z=w������ʼ������Զ��ƽ��
    vout.PosH = mul(posW, gViewProj).xyww;

    return vout;
}