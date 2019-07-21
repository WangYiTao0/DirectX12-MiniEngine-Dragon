#pragma once

#include <unordered_map>
#include "GameCore.h"
#include "RootSignature.h"
#include "GpuBuffer.h"
#include "PipelineState.h"
#include "Camera.h"
#include "ShadowCamera.h"
#include "d3dUtil.h"
#include "CameraController.h"

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
    virtual void RenderUI(class GraphicsContext& gfxContext) override;

private:
    void cameraUpdate();   // camera����

private:
    void buildPSO();
    void buildGeo();
    void buildMaterials();
    void buildRenderItem();
    void drawRenderItems(GraphicsContext& gfxContext, std::vector<RenderItem*>& ritems);
    
    void buildCubeCamera(float x, float y, float z);
    void DrawShadow(GraphicsContext& gfxContext);
    void DrawSceneToCubeMap(GraphicsContext& gfxContext);

private:
    void buildShapeGeo();
    void buildSkullGeo();

    void updatePassConstants(PassConstants& psc, Math::BaseCamera& camera);

private:
    // ���νṹmap
    std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> m_mapGeometries;

    // ��Ⱦ����
    enum class RenderLayer : int
    {
        Opaque = 0,
        OpaqueDynamicReflectors,
        Sky,
        allButSky,
        shadowDebug,
        Count
    };
    std::vector<RenderItem*> m_vecRenderItems[(int)RenderLayer::Count];
    std::vector<std::unique_ptr<RenderItem>> m_vecAll;

    enum eMaterialType
    {
        bricks = 0,
        tile,
        mirror,
        skull,
        sky
    };
    StructuredBuffer m_mats;    // t1 �洢���е���������
    std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> m_srvs;  // �洢���е�������Դ

private:
    // ��ǩ��
    RootSignature m_RootSignature;

    // ��Ⱦ��ˮ��
    enum ePSOType
    {
        E_EPT_DEFAULT = 1,
        E_EPT_SKY,
        E_EPT_SHADOW,
        E_EPT_SHADOW_DEBUG,
    };
    std::unordered_map<int, GraphicsPSO> m_mapPSO;

    RenderItem* m_SkullRItem = nullptr;

    // ��պ������
    Math::Camera m_CameraCube[6];

    // ��Ӱ�����
    GameCore::ShadowCamera m_CameraShadow;

    // ��Դ
    float mLightRotationAngle = 0.0f;
    XMFLOAT3 mBaseLightDirections[3] = {
        XMFLOAT3(0.57735f, -0.57735f, 0.57735f),
        XMFLOAT3(-0.57735f, -0.57735f, 0.57735f),
        XMFLOAT3(0.0f, -0.707f, -0.707f)
    };
    XMFLOAT3 mRotatedLightDirections[3];

    // �����
    // ��(0, 0, -m_radius) Ϊ��ʼλ��
    Math::Camera m_Camera;
    D3D12_VIEWPORT m_MainViewport;
    D3D12_RECT m_MainScissor;

    // �����������
    std::unique_ptr<GameCore::CameraController> m_CameraController;

    // �뾶
    float m_radius = 10.0f;

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