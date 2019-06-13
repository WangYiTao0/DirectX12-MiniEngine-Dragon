// Include structures and functions for lighting.
#include "LightingUtil.hlsl"

// Constant data that varies per frame.
cbuffer cbPass : register(b1)
{
    float4x4 gViewProj;
    float3 gEyePosW;
    float pad;
    float4 gAmbientLight;

    // Allow application to change fog parameters once per frame.
    // For example, we may only use fog for certain times of day.
    float4 gFogColor;
    float gFogStart;
    float gFogRange;
    float2 pad2;

    // Indices [0, NUM_DIR_LIGHTS) are directional lights;
    // indices [NUM_DIR_LIGHTS, NUM_DIR_LIGHTS+NUM_POINT_LIGHTS) are point lights;
    // indices [NUM_DIR_LIGHTS+NUM_POINT_LIGHTS, NUM_DIR_LIGHTS+NUM_POINT_LIGHT+NUM_SPOT_LIGHTS)
    // are spot lights for a maximum of MaxLights per object.
    Light gLights[MaxLights];
};

struct VertexOut
{
    float3 CenterW : POSITION;
    float2 SizeW   : SIZE;
};

struct GeoOut
{
    float4 PosH    : SV_POSITION;       // ������������
    float3 PosW    : POSITION;          // �������������
    float3 NormalW : NORMAL;            // ��������編����
    float2 TexC    : TEXCOORD;          // �������������
    uint   PrimID  : SV_PrimitiveID;    // ����ID
};

[maxvertexcount(4)]
void main(
	point VertexOut gin[1],
    uint primID : SV_PrimitiveID,
	inout TriangleStream< GeoOut > triStream
)
{
    // ����up����
    float3 up = float3(0.0f, 1.0f, 0.0f);
    // ����Ŀ��㵽�۲�������
    float3 look = gEyePosW - gin[0].CenterW;
    // ��֤Ŀ���͹۲����ͨһ��xzƽ��
    look.y = 0.0f;
    // ��׼��
    look = normalize(look);
    // ����������
    float3 right = cross(up, look);

    // ���㹫������Ŀ�͸�
    float halfWidth = 0.5f * gin[0].SizeW.x;
    float halfHeight = 0.5f * gin[0].SizeW.y;

    // ��������4������
    float4 v[4];
    v[0] = float4(gin[0].CenterW + halfWidth * right - halfHeight * up, 1.0f);
    v[1] = float4(gin[0].CenterW + halfWidth * right + halfHeight * up, 1.0f);
    v[2] = float4(gin[0].CenterW - halfWidth * right - halfHeight * up, 1.0f);
    v[3] = float4(gin[0].CenterW - halfWidth * right + halfHeight * up, 1.0f);

    // �ĸ����Ӧ����������
    float2 texC[4] =
    {
        float2(0.0f, 1.0f),
        float2(0.0f, 0.0f),
        float2(1.0f, 1.0f),
        float2(1.0f, 0.0f)
    };

    // ���ͼԴ
    GeoOut gout;
    [unroll]
    for (int i = 0; i < 4; ++i)
    {
        gout.PosH = mul(v[i], gViewProj);   // ��������������ϵת��ͶӰ����ϵ
        gout.PosW = v[i].xyz;               // �������������
        gout.NormalW = look;                // ����ķ�����
        gout.TexC = texC[i];                // ���������
        gout.PrimID = primID;               // �ö�������ɵ����ID

        triStream.Append(gout);
    }
}