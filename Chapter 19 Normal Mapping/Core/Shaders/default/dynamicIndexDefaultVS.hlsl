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
};

struct VertexIn
{
    float3 PosL  : POSITION;
    float3 NormalL : NORMAL;
    float2 TexC    : TEXCOORD;
    float3 TangentU : TANGENT; // ��������
};

struct VertexOut
{
    float4 PosH    : SV_POSITION;
    float3 PosW    : POSITION;
    float3 NormalW : NORMAL;
    float3 TangentW : TANGENT; // ���ߵ���������
    float2 TexC    : TEXCOORD;
};

VertexOut main(VertexIn vin)
{
    VertexOut vout = (VertexOut)0.0f;

    // �Ѷ���ת������������ϵ
    float4 posW = mul(float4(vin.PosL, 1.0f), modelToWorld);
    vout.PosW = posW.xyz;

    // ������ת������������ϵ
    vout.NormalW = mul(vin.NormalL, (float3x3)modelToWorld);

    // ��������ת������������ϵ
    vout.TangentW = mul(vin.TangentU, (float3x3)modelToWorld);

    // ����ת����ͶӰ����ϵ
    vout.PosH = mul(posW, gViewProj);

    // ֱ�ӷ�������
    float4 texC = mul(float4(vin.TexC, 0.0f, 1.0f), gTexTransform);
    vout.TexC = mul(texC, gMatTransform).xy;

    return vout;
}