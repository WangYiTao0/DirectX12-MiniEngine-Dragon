#pragma once

#include <unordered_map>
#include "GameCore.h"
#include "RootSignature.h"
#include "GpuBuffer.h"
#include "PipelineState.h"
#include "Camera.h"
#include "d3dUtil.h"
#include "Waves.h"

class RootSignature;
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
    void buildLandGeo();
    void buildBoxGeo();
    void buildWavesGeo();
    void buildMaterials();
    void buildRenderItem();

    void drawRenderItems(GraphicsContext& gfxContext, std::vector<RenderItem*>& ritems);
    void setLightContantsBuff(GraphicsContext& gfxContext);

private:
    float GetHillsHeight(float x, float z) const;
    DirectX::XMFLOAT3 GetHillsNormal(float x, float z) const;
    void UpdateWaves(float deltaT);
    void AnimateMaterials(float deltaT);

private:
    // ���νṹmap
    std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> m_mapGeometries;
    // ����map
    std::unordered_map<std::string, std::unique_ptr<Material>> m_mapMaterial;

    // ��Ⱦ����
    enum class RenderLayer : int
    {
        Opaque = 0,
        AlphaTest,
        Transparent,
        Count
    };
    std::vector<RenderItem*> m_vecRenderItems[(int)RenderLayer::Count];
    std::vector<std::unique_ptr<RenderItem>> m_vecAll;

private:
    // ��ǩ��
    RootSignature m_RootSignature;

    // ��Ⱦ��ˮ��
    enum ePSOType
    {
        E_EPT_DEFAULT = 1,
        E_EPT_ALPHATEST,
        E_EPT_TRANSPARENT,
    };
    std::unordered_map<int, GraphicsPSO> m_mapPSO;

    // ˮ����
    Waves m_waves{ 128, 128, 1.0f, 0.03f, 4.0f, 0.2f };
    RenderItem* m_pWaveRItem = nullptr;

    // �����
    // ��(0, 0, -m_radius) Ϊ��ʼλ��
    Math::Camera m_Camera;
    Math::Matrix4 m_ViewProjMatrix;
    D3D12_VIEWPORT m_MainViewport;
    D3D12_RECT m_MainScissor;

    // �뾶
    float m_radius = 27.0f;

    // x���򻡶ȣ��������x�������ӣ���m_xRotate����
    float m_xRotate = -Math::XM_PIDIV4 / 2.0f;
    float m_xLast = 0.0f;
    float m_xDiff = 0.0f;

    // y���򻡶ȣ������y�������ӣ���m_yRotate����
    // m_yRotate��Χ [-XM_PIDIV2 + 0.1f, XM_PIDIV2 - 0.1f]
    float m_yRotate = Math::XM_PIDIV4 / 2.0f;
    float m_yLast = 0.0f;
    float m_yDiff = 0.0f;
};