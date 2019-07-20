
// Texture2D gDiffuseMap[7] : register(t1);
// gDiffuseMapռ�ݵ���t1-t7������պ��������Ƿ���t7λ�ã�����ת��cube����
TextureCube gCubeMap : register(t7);

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