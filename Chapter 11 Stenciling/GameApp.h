#pragma once

#include "GameCore.h"
#include "RootSignature.h"
#include "GpuBuffer.h"
#include "PipelineState.h"
#include "Camera.h"
#include "d3dUtil.h"
#include <unordered_map>

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

    // ��Ⱦ��ˮ��
    enum ePSOType
    {
        E_EPT_DEFAULT = 1
    };
    std::unordered_map<int, GraphicsPSO> m_mapPSO;

    // �����
    Camera m_Camera;
    Matrix4 m_ViewProjMatrix;
    D3D12_VIEWPORT m_MainViewport;
    D3D12_RECT m_MainScissor;

    // �뾶
    float m_radius = 22.0f;
    // x���򻡶�
    float m_xRotate = -Math::XM_PIDIV2;
    float m_xLast = 0.0f;
    float m_xDiff = 0.0f;
    // y���򻡶�
    float m_yRotate = Math::XM_PIDIV4;
    float m_yLast = 0.0f;
    float m_yDiff = 0.0f;
};