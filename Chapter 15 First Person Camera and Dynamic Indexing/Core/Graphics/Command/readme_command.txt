
�ӿ�˵����
--������У�ID3D12CommandQueue
--�����б�ID3D12CommandList
--�����������ID3D12CommandAllocator
--Χ����ID3D12Fence

�ļ�˵����
--CommandAllocatorPool
--����������أ���Ҫ��ʼ��Ϊһ���ض����͡�ͨ��Χ�����ƿ�����������������

--CommandListManager
--ά��������С������б�Χ����

--CommandContext
--������������װ������ʹ��

����GPUִ����������:
1. �����Ѿ�����ID3D12Device

2. ����һ��Χ��ID3D12Fence
	ID3D12Device->CreateFence

3. ������Ը��豸���������: ID3D12CommandQueue
	ID3D12Device->CreateCommandQueue

4. ����һ�����������:ID3D12CommandAllocator����Ӧ����Ҫִ�е��������ͣ�
	ID3D12Device->CreateCommandAllocator

5. ʹ�ø��������������һ�������б�: ID3D12CommandList
	ID3D12Device->CreateCommandList

6. �������б��в�������
	ID3D12CommandList->xxx		// ��������
	ID3D12CommandList->xxx		// ��������
	CreateCommandList->close(); // �ر�

7. ���͸�GPUִ������
	ID3D12CommandQueue->ExecuteCommandLists

8. ����Χ��ֵ
	ID3D12CommandQueue-Signal

9. ���������������������ȣ�����������Ĺ���

˵�����£�
1. ����3��4��5�Ǳر��ļ���������
2. ����6��ʵ���ǰ���������������������
3. ����7�������Ǹ���GPU��ʼִ�У�GPU���ȡ����������е���������ִ��
4. ����8����ΪGPUά������һ�����У����ζ��У���ֻ����ִ�����ϱߵ������Ż�ִ�е����Χ��
	ִ�е����Χ��ʱ������������õ�Χ��ֵ���µ�Χ�������У�ʹ��Χ���������֪������7�������Ƿ�ִ����