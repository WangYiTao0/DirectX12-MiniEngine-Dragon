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

// ������Ƶ�
struct VS_CONTROL_POINT_OUTPUT
{
	float3 vPosition : POSITION;    // ��Ƭ�Ķ���(ģ������ϵ����)
};

// ������Ƶ�
struct HS_CONTROL_POINT_OUTPUT
{
	float3 vPosition : POSITION;    // ����Ķ���(ģ������ϵ����)
};

// ����޲����������ݡ�
struct HS_CONSTANT_DATA_OUTPUT
{
	float EdgeTessFactor[4]			: SV_TessFactor; // ���磬�����������򣬽�Ϊ [4]
	float InsideTessFactor[2]		: SV_InsideTessFactor; // ���磬�����������򣬽�Ϊ Inside[2]
	// TODO:  ����/������������
};

// 4�����Ƶ����Ƭ
#define NUM_CONTROL_POINTS 4

// �޲�����������
HS_CONSTANT_DATA_OUTPUT CalcHSPatchConstants(
	InputPatch<VS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> ip,
	uint PatchID : SV_PrimitiveID)
{
	HS_CONSTANT_DATA_OUTPUT Output;

    // ������Ƭ���ĵ�
    float3 centerL = 0.25f * (ip[0].vPosition + ip[1].vPosition + ip[2].vPosition + ip[3].vPosition);
    // ���ĵ�ת����������ϵ�ĵ�
    float3 centerW = mul(float4(centerL, 1.0f), gWorld).xyz;

    // ������������ľ���
    float d = distance(centerW, gEyePosW);

    // ���ݾ������ϸ�ֵ�����������
    const float d0 = 20.0f;
    const float d1 = 100.0f;
    // saturate����޶���[0.0, 1.0]��
    float tess = 64.0f * saturate((d1 - d) / (d1 - d0));

	// �ڴ˴���������Լ������
	Output.EdgeTessFactor[0] = 
		Output.EdgeTessFactor[1] = 
		Output.EdgeTessFactor[2] = 
        Output.EdgeTessFactor[3] = 
        Output.InsideTessFactor[0] = 
		Output.InsideTessFactor[1] = tess; // ���磬�ɸ�Ϊ���㶯̬�ָ�����

	return Output;
}

[domain("quad")]                                // �ı�����Ƭ
[partitioning("integer")]                       // ϸ��ģʽ fractional_even fractional_odd
[outputtopology("triangle_cw")]                 // ͨ��ϸ�ִ����������ζ�����
[outputcontrolpoints(4)]                        // ���4������
[patchconstantfunc("CalcHSPatchConstants")]     // ���������ɫ��������
HS_CONTROL_POINT_OUTPUT main( 
	InputPatch<VS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> ip, 
	uint i : SV_OutputControlPointID,
	uint PatchID : SV_PrimitiveID )
{
	HS_CONTROL_POINT_OUTPUT Output;

	// �ڴ˴���������Լ������
	Output.vPosition = ip[i].vPosition;

	return Output;
}