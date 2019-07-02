
// ÿ������Ľṹ������
struct InstanceData
{
    float4x4 World;
    float4x4 TexTransform;
    float4x4 MatTransform;
    uint     MaterialIndex;
    uint     InstPad0;
    uint     InstPad1;
    uint     InstPad2;
};

// ���ж���Ľṹ������
StructuredBuffer<InstanceData> gInstanceData : register(t0);

// ����������
cbuffer cbPass : register(b0)
{
    float4x4 gViewProj;
};

cbuffer cbPass1 : register(b1)
{
    int gDrawObjs[128];     // �����е�ÿ��Ԫ�ض��ᱻ��װΪfloat4��d3d12����727ҳ
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
    float3 PosW    : POSITION;
    float3 NormalW : NORMAL;
    float2 TexC    : TEXCOORD;

    // ������۸ģ���ֵ
    nointerpolation uint MatIndex  : MATINDEX;
};

VertexOut main(VertexIn vin, uint instanceID : SV_InstanceID)
{
    VertexOut vout = (VertexOut)0.0f;

    InstanceData instData = gInstanceData[gDrawObjs[instanceID]];
    float4x4 modelToWorld = instData.World;
    float4x4 texTransform = instData.TexTransform;
    float4x4 matTransform = instData.MatTransform;
    vout.MatIndex = instData.MaterialIndex;

    // �Ѷ������ŷ�����ƫ��һ��
    float3 viPos = vin.PosL + vin.NormalL * 0.2;

    // �Ѷ���ת������������ϵ
    float4 posW = mul(float4(viPos, 1.0f), modelToWorld);
    vout.PosW = posW.xyz;

    // ������ת������������ϵ
    vout.NormalW = mul(vin.NormalL, (float3x3)modelToWorld);

    // ����ת����ͶӰ����ϵ
    vout.PosH = mul(posW, gViewProj);

    // ֱ�ӷ�������
    float4 texC = mul(float4(vin.TexC, 0.0f, 1.0f), texTransform);
    vout.TexC = mul(texC, matTransform).xy;

    return vout;
}