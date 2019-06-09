//=============================================================================
// Performs a separable Guassian blur with a blur radius up to 5 pixels.
//=============================================================================

cbuffer cbSettings : register(b0)
{
    // ģ���뾶
    int gBlurRadius;

    // ���֧��һ��11������Ȩ��
    float w0;
    float w1;
    float w2;
    float w3;
    float w4;
    float w5;
    float w6;
    float w7;
    float w8;
    float w9;
    float w10;
};

// ���֧�ֵ�ģ���뾶=5
static const int gMaxBlurRadius = 5;

Texture2D gInput            : register(t0);
RWTexture2D<float4> gOutput : register(u0);

// Ϊ�˱�֤���������ͳһ��Ҳ����ÿ�ζ��ܼ���gBlurRadius*2+1��Ȩ��
// gCache�ĳ�����Ҫλ���߳�������������+gBlurRadius*2
// ������Ե��ģ��Ҳ��ͳһ����
#define N 256
#define CacheSize (N + 2*gMaxBlurRadius)
groupshared float4 gCache[CacheSize];

[numthreads(N, 1, 1)]
void main(int3 groupThreadID : SV_GroupThreadID,
    int3 dispatchThreadID : SV_DispatchThreadID)
{
    // ��¼Ȩ��ֵ
    float weights[11] = { w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10 };

    if (groupThreadID.x < gBlurRadius)
    {
        // ���������磬�Ͳ��ñ�Ե��ֵ���
        int x = max(dispatchThreadID.x - gBlurRadius, 0);
        gCache[groupThreadID.x] = gInput[int2(x, dispatchThreadID.y)];
    }
    if (groupThreadID.x >= N - gBlurRadius)
    {
        // �ұ�������磬�Ͳ��ñ�Ե��ֵ���
        int x = min(dispatchThreadID.x + gBlurRadius, gInput.Length.x - 1);
        gCache[groupThreadID.x + 2 * gBlurRadius] = gInput[int2(x, dispatchThreadID.y)];
    }

    // ÿ���߳���̶�����N���̣߳�����N�����أ��п������ز���������Ҳ��Ҫ������
    gCache[groupThreadID.x + gBlurRadius] = gInput[min(dispatchThreadID.xy, gInput.Length.xy - 1)];

    // �ȴ������߳̽�����Ҳ����gCache����˶�Ӧ������
    GroupMemoryBarrierWithGroupSync();

    // ���ݴ����Ȩ�أ��������ֵ
    float4 blurColor = float4(0, 0, 0, 0);

    for (int i = -gBlurRadius; i <= gBlurRadius; ++i)
    {
        int k = groupThreadID.x + gBlurRadius + i;

        blurColor += weights[i + gBlurRadius] * gCache[k];
    }

    gOutput[dispatchThreadID.xy] = blurColor;
}