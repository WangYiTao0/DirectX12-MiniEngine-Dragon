struct VertexIn
{
    float3 PosW  : POSITION;    // �������������
    float2 SizeW : SIZE;        // ����Ŀ��
};

struct VertexOut
{
    float3 CenterW : POSITION;  // ���ĵ����������
    float2 SizeW   : SIZE;      // ���
};

VertexOut main(VertexIn vin)
{
    VertexOut vout;

    // ����ֱ�Ӵ���������ɫ��
    vout.CenterW = vin.PosW;
    vout.SizeW = vin.SizeW;

    return vout;
}