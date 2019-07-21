//***************************************************************************************
// Default.hlsl by Frank Luna (C) 2015 All Rights Reserved.
//
// Default shader, currently supports lighting.
//***************************************************************************************

struct MaterialData
{
    float4   DiffuseAlbedo;
    float3   FresnelR0;
    float    Mpad0;   // ռλ��
    float    Roughness;
    uint     DiffuseMapIndex;   // ����ID
    uint     NormalMapIndex;    // ������ͼ��ID
    float    Mpad2;   // ռλ��
};

StructuredBuffer<MaterialData> gMaterialData : register(t0);

// ռ��t1-t7
Texture2D gTextureMaps[7] : register(t1);

SamplerState gsamAnisotropicWrap  : register(s1);

cbuffer VSConstants : register(b0)
{
    float4x4 modelToWorld;
    float4x4 gTexTransform;
    float4x4 gMatTransform;
    uint gMaterialIndex;
    uint vPad0;   // ռλ��
    uint vPad1;   // ռλ��
    uint vPad2;   // ռλ��
};

struct VertexOut
{
    float4 PosH    : SV_POSITION;
    float2 TexC    : TEXCOORD;
};

void main(VertexOut pin)
{
    // ��ȡ������Ĳ���
    MaterialData matData = gMaterialData[gMaterialIndex];
    float4 diffuseAlbedo = matData.DiffuseAlbedo;
    uint diffuseTexIndex = matData.DiffuseMapIndex;

    diffuseAlbedo *= gTextureMaps[diffuseTexIndex].Sample(gsamAnisotropicWrap, pin.TexC);

    // ���������Ϊ���޳�һЩ����
    // ͸�����ص��޳�
    //clip(diffuseAlbedo.a - 0.1f);
}