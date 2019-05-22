#pragma once

#include "VectorMath.h"

using namespace Math;
// ��HLSLһ��
struct Light
{
    XMFLOAT3 Strength = { 0.0f, 0.0f, 0.05f };
    float FalloffStart = 0.0f;                          // point/spot light only
    XMFLOAT3 Direction = { 0.0f, 0.0f, 0.0f };          // directional/spot light only
    float FalloffEnd = 0.0f;                           // point/spot light only
    XMFLOAT3 Position = { 0.0f, 0.0f, 0.0f };            // point/spot light only
    float SpotPower = 0;                            // spot light only
};

#define MaxLights 16

__declspec(align(16)) struct ObjectConstants
{
    Matrix4 World = Matrix4(kIdentity); // �������ģ������ת������������
};

__declspec(align(16)) struct PassConstants
{
    Matrix4 viewProj = Matrix4(kIdentity);      // ����������תΪͶӰ����ľ���
    Vector3 eyePosW = { 0.0f, 0.0f, 0.0f };     // �۲��Ҳ���������λ��
    Vector4 ambientLight = { 0.0f, 0.0f, 0.0f, 1.0f };

    // Indices [0, NUM_DIR_LIGHTS) are directional lights;
    // indices [NUM_DIR_LIGHTS, NUM_DIR_LIGHTS+NUM_POINT_LIGHTS) are point lights;
    // indices [NUM_DIR_LIGHTS+NUM_POINT_LIGHTS, NUM_DIR_LIGHTS+NUM_POINT_LIGHT+NUM_SPOT_LIGHTS)
    // are spot lights for a maximum of MaxLights per object.
    Light Lights[MaxLights];
};

__declspec(align(16)) struct MaterialConstants
{
    Vector4 DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
    Vector3 FresnelR0 = { 0.01f, 0.01f, 0.01f };
    float Roughness = 0.25f;
};