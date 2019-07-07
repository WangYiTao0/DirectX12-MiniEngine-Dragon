/*
	��պ���ɫ������
	�����ػ�������һ����װ�����ÿ�������д洢������ɫֵ

	ά����ͼ��
	m_SRVHandle: ��ɫ����Դ��ͼ
	m_RTVHandle[6]: ��ȾĿ����ͼ

	CreateFromSwapChain�� ��װ�������Ļ�����(����)
	Create: ֱ�Ӵ���������
*/

#pragma once

#include "PixelBuffer.h"
#include "Color.h"

class EsramAllocator;

class ColorCubeBuffer : public PixelBuffer
{
public:
    ColorCubeBuffer( Color ClearColor = Color(0.0f, 0.0f, 0.0f, 0.0f)  )
        : m_ClearColor(ClearColor)
    {
        m_SRVHandle.ptr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN;
        std::memset(m_RTVHandle, 0xFF, sizeof(m_RTVHandle));
    }

    // Create a color buffer.  If an address is supplied, memory will not be allocated.
    // The vmem address allows you to alias buffers (which can be especially useful for
    // reusing ESRAM across a frame.)
    void Create(const std::wstring& Name, uint32_t Width, uint32_t Height, uint32_t NumMips,
        DXGI_FORMAT Format, D3D12_GPU_VIRTUAL_ADDRESS VidMemPtr = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN);
 
    // Get pre-created CPU-visible descriptor handles
    const D3D12_CPU_DESCRIPTOR_HANDLE& GetSRV(void) const { return m_SRVHandle; }
    const D3D12_CPU_DESCRIPTOR_HANDLE& GetRTV(int idx = 0) const {
        if (idx < 0 || idx > 5)
            idx = 0;

        return m_RTVHandle[idx]; 
    }

    Color GetClearColor(void) const { return m_ClearColor; }

protected:
    void CreateDerivedViews(ID3D12Device* Device, DXGI_FORMAT Format, uint32_t ArraySize, uint32_t NumMips = 1);

    Color m_ClearColor;
    D3D12_CPU_DESCRIPTOR_HANDLE m_SRVHandle;
    D3D12_CPU_DESCRIPTOR_HANDLE m_RTVHandle[6];
};
