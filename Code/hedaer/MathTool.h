#pragma once

// 自作コードのインクルード
#include"./Code/hedaer/MathObject.h"
#include "./Code/hedaer/MatrixCamera.h"

// エンジンコードなどのインクルード
#define _USE_MATH_DEFINES
#include<cmath>
#include"Novice.h"
#include<Vector2.h>
#include<Vector3.h>


#pragma region 共通

/// <summary>
/// 
/// </summary>
/// <param name="num"></param>
/// <param name="max"></param>
/// <param name="min"></param>
/// <returns></returns>
float clamp(float num, float max, float min);

#pragma endregion


#pragma region 二次元ベクトル

/// <summary>
/// ベクトルの長さを求める
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
static float Length(const Vector2& v);

/// <summary>
/// 正規化
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
Vector2 Nomalize(const Vector2& v);

#pragma endregion

#pragma region 三次元ベクトル


Vector3 Add(const Vector3& v1, const Vector3& v2);

Vector3 Subtract(const Vector3& v1, const Vector3& v2);

Vector3 Scalar(float scalar, const Vector3& v);

/// <summary>
/// ベクトルの長さを求める
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
static float Length(const Vector3& v);

/// <summary>
/// 正規化
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
Vector3 Nomalize(const Vector3& v);

/// <summary>
/// クロス積・外積
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vector3 Cross(const Vector3& v1, const Vector3& v2);

/// <summary>
/// ドット積・内積
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
float Dot(const Vector3& v1, const Vector3& v2);

/// <summary>
/// 正射影ベクトル
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vector3 Project(const Vector3& v1, const Vector3& v2);

/// <summary>
/// 最近接点
/// </summary>
/// <param name="point"></param>
/// <param name="segment"></param>
/// <returns></returns>
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

/// <summary>
/// グリッド線を表示する関数
/// </summary>
/// <param name="viewProjection"></param>
/// <param name="viewport"></param>
void DrawGrid(const Matrix4x4& viewProjection, const Matrix4x4& viewport);

/// <summary>
/// 球体を描画する
/// </summary>
/// <param name="sphere"></param>
/// <param name="viewProjection"></param>
/// <param name="viewport"></param>
/// <param name="color"></param>
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjection, const Matrix4x4& viewport, uint32_t color);


#pragma endregion