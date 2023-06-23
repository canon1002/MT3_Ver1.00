#include "./Code/hedaer/MatrixCamera.h"

MatrixCamera::MatrixCamera(Vector2 windowSize)
{
	//	画面サイズを設定
	m_windowSize = windowSize;
}

MatrixCamera::~MatrixCamera() {};

void MatrixCamera::Initialize() {

#pragma region ワールド座標系

	// 拡大率
	m_scale = { 1.0f,1.0f,1.0f };
	// 回転量
	m_rotate = { 0.0f,0.0f,0.0f };
	// 移動量
	m_translate = { 0.0f,0.0f,0.0f };

#pragma endregion

#pragma region カメラ座標系

	// 拡大率
	m_scale = { 1.0f,1.0f,1.0f };
	// 回転量
	m_rotate = { 0.0f,0.0f,0.0f };
	// 移動量
	m_translate = { 0.0f,0.0f,0.0f };
	// Near(近平面への距離)
	m_nearClip = 0.1f;
	// Far(遠平面への距離)
	m_farClip = 100.0f;
	// AspectRatio(アスペクト比)
	m_aspectRatio = (m_windowSize.x / m_windowSize.y);
	// VerticalFOV(縦画角)
	m_VerticalFOV = 0.45f;

#pragma endregion

	worldMatrix = Matrix4x4Funk::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });
	cameraMatrix = Matrix4x4Funk::MakeAffineMatrix(m_cameraScale, m_cameraRotate, m_cameraTranslate);
	viewMatrix = Matrix4x4Funk::Inverse(cameraMatrix);
	projectionMatrix = Matrix4x4Funk::MakePerspectiveMatrix(m_VerticalFOV, m_aspectRatio, m_nearClip, m_farClip);
	viewprojectionMatrix = Matrix4x4Funk::Multiply(viewMatrix, projectionMatrix);
	worldViewProjectionMatrix = Matrix4x4Funk::Multiply(worldMatrix, viewprojectionMatrix);
	viewportMatrix = Matrix4x4Funk::MakeViewportMatrix(0, 0, m_windowSize.x, m_windowSize.y, 0.0f, 1.0f);

}



void MatrixCamera::Update() 
{
	worldMatrix = Matrix4x4Funk::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });
	cameraMatrix = Matrix4x4Funk::MakeAffineMatrix(m_cameraScale, m_cameraRotate, m_cameraTranslate);
	viewMatrix = Matrix4x4Funk::Inverse(cameraMatrix);
	projectionMatrix = Matrix4x4Funk::MakePerspectiveMatrix(m_VerticalFOV, m_aspectRatio, m_nearClip, m_farClip);
	viewprojectionMatrix = Matrix4x4Funk::Multiply(viewMatrix, projectionMatrix);
	worldViewProjectionMatrix = Matrix4x4Funk::Multiply(worldMatrix, viewprojectionMatrix);
	viewportMatrix = Matrix4x4Funk::MakeViewportMatrix(0, 0, m_windowSize.x, m_windowSize.y, 0.0f, 1.0f);
}

void MatrixCamera::SetCameraAffine(Vector3 scale, Vector3 rotate, Vector3 translate) 
{
	m_cameraScale = scale;
	m_cameraRotate = rotate;
	m_cameraTranslate = translate;
}

void MatrixCamera::SetCrip(float nearCrip, float farClip)
{
	m_nearClip = nearCrip;
	m_farClip = farClip;

}

void MatrixCamera::SetAspectRatio(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
}