#pragma once

#include "GameCore.h"
#include "RootSignature.h"
#include "GpuBuffer.h"
#include "PipelineState.h"

class RootSignature;
class StructuredBuffer;
class ByteAddressBuffer;
class GraphicsPSO;
class GameApp : public GameCore::IGameApp
{
public:

	GameApp(void) {}

	virtual void Startup(void) override;
	virtual void Cleanup(void) override;

	virtual void Update(float deltaT) override;
	virtual void RenderScene(void) override;

private:
    // ��ǩ��
    RootSignature m_RootSignature;
    // ���㻺����
    StructuredBuffer m_VertexBuffer;
    // ����������
    ByteAddressBuffer m_IndexBuffer;
    // ��ˮ�߶���
    GraphicsPSO m_PSO;
};