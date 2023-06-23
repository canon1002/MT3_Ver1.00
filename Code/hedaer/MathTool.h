#pragma once

#include<cmath>
#include<Vector2.h>
#include<Vector3.h>

#pragma region ����

/// <summary>
/// 
/// </summary>
/// <param name="num"></param>
/// <param name="max"></param>
/// <param name="min"></param>
/// <returns></returns>
float clamp(float num, float max, float min) 
{
	if (num > max) 
	{
		return max;
	}
	else if (num < min)
	{
		return max;
	}
	else
	{
		return num;
	}
}

#pragma endregion


#pragma region �񎟌��x�N�g��

float Nomalize(Vector2) 
{
	float result;

	return result;
}

#pragma endregion

#pragma region �O�����x�N�g��


Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	Vector3 result;
	result.x = v1.x + v2.x;
	result.x = v1.y + v2.y;
	result.x = v1.z + v2.z;
	return result;
}


Vector3 Subtract(const Vector3& v1, const Vector3& v2)
{
	Vector3 result;
	result.x = v1.x - v2.x;
	result.x = v1.y - v2.y;
	result.x = v1.z - v2.z;
	return result;
}


Vector3 Scalar(float scalar, const Vector3& v)
{
	Vector3 result;
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return result;
}

/// <summary>
/// ���K��
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
Vector3 Nomalize(const Vector3& v)
{
	Vector3 result;
	result.x = v.x / Length(v);
	result.y = v.y / Length(v);
	result.z = v.z / Length(v);

	return result;
}

/// <summary>
/// �x�N�g���̒��������߂�
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
static float Length(const Vector3& v)
{
	float result;
	result = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return result;
}

/// <summary>
/// �N���X�ρE�O��
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
static Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	return Vector3{
		(v1.y * v2.z) - (v1.z * v2.y),
		(v1.z * v2.x) - (v1.x * v2.z),
		(v1.x * v2.y) - (v1.y * v2.x)
	};
};

/// <summary>
/// �h�b�g�ρE����
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
static float Dot(const Vector3& v1, const Vector3& v2)
{
	return float{ v1.x * v2.x + v1.y * v2.y + v1.z * v2.z };
};

/// <summary>
/// ���ˉe�x�N�g��
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
static Vector3 Project(const Vector3& v1, const Vector3& v2)
{
	return Scalar(Dot(v1, Nomalize(v2)), Nomalize(v2));
}

/// <summary>
/// �ŋߐړ_
/// </summary>
/// <param name="point"></param>
/// <param name="segment"></param>
/// <returns></returns>
static Vector3 ClosestPoint(const Vector3& point, const Segment& segment)
{
	float t = Dot(Subtract(point, segment.origin), segment.diff) / pow(Length(segment.diff), 2.0f);
	t = clamp(t, 1.0f, 0.0f);

	return Add(segment.origin, Scalar(t, segment.diff));
}

#pragma endregion


