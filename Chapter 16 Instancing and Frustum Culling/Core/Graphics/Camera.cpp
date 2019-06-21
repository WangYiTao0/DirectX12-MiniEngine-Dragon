//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Developed by Minigraph
//
// Author:  James Stanard 
//

#include "pch.h"
#include "Camera.h"
#include <cmath>

using namespace Math;

// meng �����޸�Ϊ��������ϵ
void BaseCamera::SetLookDirection( Vector3 forward, Vector3 up )
{
    // ����ǰ��
    Scalar forwardLenSq = LengthSquare(forward);
    forward = Select(forward * RecipSqrt(forwardLenSq), Vector3(kZUnitVector), forwardLenSq < Scalar(0.000001f));

    // �����ṩ���Ϻ�ǰ���������ҷ�
    Vector3 right = Cross(up, forward);
    Scalar rightLenSq = LengthSquare(right);
    right = Select(right * RecipSqrt(rightLenSq), Cross(Vector3(kYUnitVector), forward), rightLenSq < Scalar(0.000001f));

    // ������������ʵ�ʵ��Ϸ�
    up = Cross(forward, right);

    // �����������ת������
    m_Basis = Matrix3(right, up, forward);
    m_CameraToWorld.SetRotation(Quaternion(m_Basis));
}

void BaseCamera::Update()
{
    // �����ӽǱ任���󣬻�û�п��� m_CameraToWorld
    m_ViewMatrix = Matrix4(~m_CameraToWorld);
    
    // Matrix4�е�*���أ����ⷴ��д�ġ��������ﷴ�ų�
    // �����ӽ�ͶӰת�����������õ���������ٳ������ֵ�Ϳ���������յ�ͶӰ������
    m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
}

void Camera::Update()
{
    BaseCamera::Update();

    m_FrustumVS = Frustum(m_ProjMatrix, m_NearClip / m_FarClip);
    m_FrustumWS = m_CameraToWorld * m_FrustumVS;
}

void Camera::UpdateProjMatrix( void )
{
    DirectX::XMMATRIX mat = XMMatrixPerspectiveFovLH(m_VerticalFOV, m_AspectRatio, m_NearClip, m_FarClip);

    SetProjMatrix(Matrix4(mat));
}