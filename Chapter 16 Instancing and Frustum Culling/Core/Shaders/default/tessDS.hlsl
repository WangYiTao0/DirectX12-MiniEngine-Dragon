
// ����������b0
cbuffer cbPerObject : register(b0)
{
    float4x4 gWorld;
};

// ����������b1
cbuffer cbPass : register(b1)
{
    float4x4 gViewProj;
    float3 gEyePosW;
};

struct DS_OUTPUT
{
	float4 vPosition  : SV_POSITION;
};

// ������Ƶ�
struct HS_CONTROL_POINT_OUTPUT
{
	float3 vPosition : POSITION;
};

// ����޲����������ݡ�
struct HS_CONSTANT_DATA_OUTPUT
{
	float EdgeTessFactor[4]			: SV_TessFactor; // ���磬�����������򣬽�Ϊ [4]
	float InsideTessFactor[2]		: SV_InsideTessFactor; // ���磬�����������򣬽�Ϊ Inside[2]
};

// 4�����Ƶ����Ƭ
#define NUM_CONTROL_POINTS 4

[domain("quad")]
DS_OUTPUT main(
	HS_CONSTANT_DATA_OUTPUT input,      // ����ϸ������
	float2 domain : SV_DomainLocation,  // �²��붥���uv����(������Ƭ�ڲ�)
	const OutputPatch<HS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> patch)   // ԭʼ��Ƭ��4����
{
	DS_OUTPUT Output;

    // ˫���Բ�ֵ lerp(x, y, s) = x + s(y - x)
    float3 v1 = lerp(patch[0].vPosition, patch[1].vPosition, domain.x);
    float3 v2 = lerp(patch[2].vPosition, patch[3].vPosition, domain.x);
    // ����ö����ʵ��λ��(ģ������ϵ)
    float3 p = lerp(v1, v2, domain.y);

    // �ʵ��޸�y���Ա�ߵ����
    p.y = 0.3f * (p.z * sin(p.x) + p.x * cos(p.z));

    // ת��������ϵ
    float4 posW = mul(float4(p, 1.0f), gWorld);

    // ת�۲�����ϵ
    Output.vPosition = mul(posW, gViewProj);

	return Output;
}
