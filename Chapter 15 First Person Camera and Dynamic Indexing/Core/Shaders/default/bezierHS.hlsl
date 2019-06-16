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
	// TODO:  ����/�����������
};

// 4�����Ƶ����Ƭ
#define NUM_CONTROL_POINTS 4

// �޲�����������
HS_CONSTANT_DATA_OUTPUT CalcHSPatchConstants(
	InputPatch<VS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> ip,
	uint PatchID : SV_PrimitiveID)
{
	HS_CONSTANT_DATA_OUTPUT Output;

	// �ڴ˴���������Լ������
	Output.EdgeTessFactor[0] = 
		Output.EdgeTessFactor[1] = 
		Output.EdgeTessFactor[2] = 
        Output.EdgeTessFactor[3] = 
        Output.InsideTessFactor[0] = 
		Output.InsideTessFactor[1] = 25; // ���磬�ɸ�Ϊ���㶯̬�ָ�����

	return Output;
}

[domain("quad")]                                // �ı�����Ƭ
[partitioning("integer")]                       // ϸ��ģʽ fractional_even fractional_odd
[outputtopology("triangle_cw")]                 // ͨ��ϸ�ִ����������ζ�����
[outputcontrolpoints(16)]                       // ���16������
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
