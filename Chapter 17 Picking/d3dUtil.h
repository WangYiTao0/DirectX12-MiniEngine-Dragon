#pragma once

#include <string>
#include <unordered_map>
#include "VectorMath.h"

// ���Ũ��
static float flFrogAlpha = 0.0f;
// �Ƿ�����׶���޳�
static bool g_openFrustumCull = true;

// ��HLSLһ��
struct Light
{
    DirectX::XMFLOAT3 Strength = { 0.0f, 0.0f, 0.05f };
    float FalloffStart = 0.0f;                          // point/spot light only
    DirectX::XMFLOAT3 Direction = { 0.0f, 0.0f, 0.0f };          // directional/spot light only
    float FalloffEnd = 0.0f;                           // point/spot light only
    DirectX::XMFLOAT3 Position = { 0.0f, 0.0f, 0.0f };            // point/spot light only
    float SpotPower = 0;                            // spot light only
};

#define MaxLights 16

struct ObjectConstants
{
    Math::Matrix4 World = Math::Matrix4(Math::kIdentity); // �������ģ������ת������������
    Math::Matrix4 texTransform = Math::Matrix4(Math::kIdentity); // �ö������������ת������
    Math::Matrix4 matTransform = Math::Matrix4(Math::kIdentity);
    UINT MaterialIndex;
    UINT ObjPad0;
    UINT ObjPad1;
    UINT ObjPad2;
};

struct PassConstants
{
    Math::Matrix4 viewProj = Math::Matrix4(Math::kIdentity);      // ����������תΪͶӰ����ľ���
    Math::Vector3 eyePosW = { 0.0f, 0.0f, 0.0f };     // �۲��Ҳ���������λ��
    Math::Vector4 ambientLight = { 0.0f, 0.0f, 0.0f, 1.0f };

    Math::Vector4 FogColor = { 0.7f, 0.7f, 0.7f, flFrogAlpha };
    float gFogStart = 50.0f;
    float gFogRange = 200.0f;
    DirectX::XMFLOAT2 pad;

    // Indices [0, NUM_DIR_LIGHTS) are directional lights;
    // indices [NUM_DIR_LIGHTS, NUM_DIR_LIGHTS+NUM_POINT_LIGHTS) are point lights;
    // indices [NUM_DIR_LIGHTS+NUM_POINT_LIGHTS, NUM_DIR_LIGHTS+NUM_POINT_LIGHT+NUM_SPOT_LIGHTS)
    // are spot lights for a maximum of MaxLights per object.
    Light Lights[MaxLights];
};

struct MaterialConstants
{
    Math::Vector4 DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };  // ռ��16�ֽ�
    Math::Vector3 FresnelR0 = { 0.01f, 0.01f, 0.01f };  // ռ��16�ֽ�
    float Roughness = 0.25f;
    UINT DiffuseMapIndex = 0;
    UINT MaterialPad0;      // ռλ����16�ֽڶ���
    UINT MaterialPad1;
};


// ����Ϊ����ʹ��

// ����ṹ
struct Vertex
{
    Vertex() = default;
    Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v) :
        Pos(x, y, z),
        Normal(nx, ny, nz),
        TexC(u, v) {}

    DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT3 Normal;
    DirectX::XMFLOAT2 TexC;
};

// ÿһ����Ŀ��Ľṹ��
struct SubmeshGeometry
{
    int IndexCount = 0;
    int StartIndexLocation = 0;
    int BaseVertexLocation = 0;
    Math::Vector3 vMin;
    Math::Vector3 vMax;
};

class StructuredBuffer;
class ByteAddressBuffer;
// ����Ŀ��ļ��νṹ
class MeshGeometry
{
public:
    MeshGeometry() = default;
    virtual ~MeshGeometry()
    {
        
    }

public:
    void createVertex(const std::wstring& name, uint32_t NumElements, uint32_t ElementSize,
        const void* initialData = nullptr)
    {
        vertexBuff.Create(name, NumElements, ElementSize, initialData);
        vertexView = vertexBuff.VertexBufferView();
    }

    void createIndex(const std::wstring& name, uint32_t NumElements, uint32_t ElementSize,
        const void* initialData = nullptr)
    {
        indexBuff.Create(name, NumElements, ElementSize, initialData);
        indexView = indexBuff.IndexBufferView();
    }

    void storeVertexAndIndex(std::vector<Vertex>& vertex, std::vector<std::int32_t>& index)
    {
        vecVertex = std::move(vertex);
        vecIndex = std::move(index);
    }

    void destroy()
    {
        vertexBuff.Destroy();
        indexBuff.Destroy();
    }

public:
    std::string name;

    std::unordered_map<std::string, SubmeshGeometry> geoMap;    // ʹ�øö��������������

    D3D12_VERTEX_BUFFER_VIEW vertexView;
    D3D12_INDEX_BUFFER_VIEW indexView;

    // �洢�������������
    std::vector<Vertex> vecVertex;
    std::vector<std::int32_t> vecIndex;

private:
    StructuredBuffer vertexBuff;    // ����buff
    ByteAddressBuffer indexBuff;    // ����buff
};

struct RenderItem
{
    RenderItem() = default;
    ~RenderItem()
    {
        matrixs.Destroy();
    }

    std::string name;

    int allCount = 0;               // ������

    int visibileCount = 0;          // ���Ƶ����� �ھ�ͷ�е�����
    std::vector<Math::XMUINT4> vDrawObjs;  // ��Ҫ���Ƶ�Ŀ������λ��

    int selectedCount = 0;          // ѡ�е���������Ҫ���
    std::vector<Math::XMUINT4> vDrawOutLineObjs;  // ��Ҫ��ߵ�Ŀ������λ��

    int IndexCount = 0;             // ��������
    int StartIndexLocation = 0;     // ������ʼλ��
    int BaseVertexLocation = 0;     // ������ʼλ��
    D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    MeshGeometry* geo = nullptr;    // ���νṹָ�룬������Ӧ�Ķ����Լ�����

    std::vector<ObjectConstants> vObjsData;
    StructuredBuffer matrixs;     // t0 �洢�����һЩ�����Լ���������id

    Math::Vector3 vMin;
    Math::Vector3 vMax;
};