
// Texture2D gDiffuseMap[4] : register(t1);
// gDiffuseMapռ�ݵ���t1-t4������պ��������Ƿ���t4λ�ã�����ת��cube����
TextureCube gCubeMap : register(t4);

SamplerState gsamLinearWrap  : register(s0);

struct VertexOut
{
    float4 PosH    : SV_POSITION;
    float3 PosL    : POSITION;
};

float4 main(VertexOut pin) : SV_Target0
{
    return gCubeMap.Sample(gsamLinearWrap, pin.PosL);
}