#pragma once

#include <string>
#include <unordered_map>
#include "VectorMath.h"

struct ObjectConstants
{
    Math::Matrix4 World = Math::Matrix4(Math::kIdentity); // �������ģ������ת������������
};

struct PassConstants
{
    Math::Matrix4 viewProj = Math::Matrix4(Math::kIdentity);    // ����������תΪͶӰ����ľ���
    Math::Vector3 eyePosW = { 0.0f, 0.0f, 0.0f };               // �۲��Ҳ���������λ��
};

// ����Ϊ����ʹ��

// ����ṹ
struct Vertex
{
    Vertex() = default;
    Vertex(float x, float y, float z) :
        Pos(x, y, z) {}

    DirectX::XMFLOAT3 Pos;
};

// ÿһ����Ŀ��Ľṹ��
struct SubmeshGeometry
{
    int IndexCount = 0;
    int StartIndexLocation = 0;
    int BaseVertexLocation = 0;
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

private:
    StructuredBuffer vertexBuff;    // ����buff
    ByteAddressBuffer indexBuff;    // ����buff
};

struct RenderItem
{
    Math::Matrix4 modeToWorld = Math::Matrix4(Math::kIdentity);      // ģ������ת�����������

    int IndexCount = 0;             // ��������
    int StartIndexLocation = 0;     // ������ʼλ��
    int BaseVertexLocation = 0;     // ������ʼλ��
    D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    MeshGeometry* geo = nullptr;    // ���νṹָ�룬������Ӧ�Ķ����Լ�����
};