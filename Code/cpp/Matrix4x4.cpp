#include <Matrix4x4.h>
#include <Novice.h>
#include <cmath>
#include <cassert>

/// 行列の和を返す関数
Matrix4x4 Matrix4x4Ex::Add(Matrix4x4 m1, Matrix4x4 m2) {

	return Matrix4x4{
		m1.m[0][0] + m2.m[0][0],m1.m[0][1] + m2.m[0][1],m1.m[0][2] + m2.m[0][2],m1.m[0][3] + m2.m[0][3],
		m1.m[1][0] + m2.m[1][0],m1.m[1][1] + m2.m[1][1],m1.m[1][2] + m2.m[1][2],m1.m[1][3] + m2.m[1][3],
		m1.m[2][0] + m2.m[2][0],m1.m[2][1] + m2.m[2][1],m1.m[2][2] + m2.m[2][2],m1.m[2][3] + m2.m[2][3],
		m1.m[3][0] + m2.m[3][0],m1.m[3][1] + m2.m[3][1],m1.m[3][2] + m2.m[3][2],m1.m[3][3] + m2.m[3][3],
	};

}

/// 行列の差を返す関数
Matrix4x4 Matrix4x4Ex::Subtract(Matrix4x4 m1, Matrix4x4 m2) {

	return Matrix4x4{
		m1.m[0][0] - m2.m[0][0],m1.m[0][1] - m2.m[0][1],m1.m[0][2] - m2.m[0][2],m1.m[0][3] - m2.m[0][3],
		m1.m[1][0] - m2.m[1][0],m1.m[1][1] - m2.m[1][1],m1.m[1][2] - m2.m[1][2],m1.m[1][3] - m2.m[1][3],
		m1.m[2][0] - m2.m[2][0],m1.m[2][1] - m2.m[2][1],m1.m[2][2] - m2.m[2][2],m1.m[2][3] - m2.m[2][3],
		m1.m[3][0] - m2.m[3][0],m1.m[3][1] - m2.m[3][1],m1.m[3][2] - m2.m[3][2],m1.m[3][3] - m2.m[3][3],
	};

}

/// 行列の積を返す関数
Matrix4x4 Matrix4x4Ex::Multiply(Matrix4x4 m1, Matrix4x4 m2) {

	return Matrix4x4{
	m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0],
	m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1],
	m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2],
	m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3],
	m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0],
	m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1],
	m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2],
	m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3],
	m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0],
	m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1],
	m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2],
	m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3],
	m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0],
	m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1],
	m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2],
	m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3],
	};

}

/// 逆行列を作成する
Matrix4x4 Matrix4x4Ex::Inverse(Matrix4x4 m) {

	float im = (
		(m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) + (m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) - (m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) - (m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) - (m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) + (m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) - (m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) - (m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) - (m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) + (m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0])
		);

	return Matrix4x4{

		(1 / im) * ((m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[1][2] * m.m[2][3] * m.m[3][1]) + (m.m[1][3] * m.m[2][1] * m.m[3][2]) -
					(m.m[1][3] * m.m[2][2] * m.m[3][1]) - (m.m[1][2] * m.m[2][1] * m.m[3][3]) - (m.m[1][1] * m.m[2][3] * m.m[3][2])),
		(1 / im) * (-(m.m[0][1] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[2][3] * m.m[3][1]) - (m.m[0][3] * m.m[2][1] * m.m[3][2]) +
					(m.m[0][3] * m.m[2][2] * m.m[3][1]) + (m.m[0][2] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[2][3] * m.m[3][2])),
		(1 / im) * ((m.m[0][1] * m.m[1][2] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[3][2]) -
					(m.m[0][3] * m.m[1][2] * m.m[3][1]) - (m.m[0][2] * m.m[1][1] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[3][2])),
		(1 / im) * (-(m.m[0][1] * m.m[1][2] * m.m[2][3]) - (m.m[0][2] * m.m[1][3] * m.m[2][1]) - (m.m[0][3] * m.m[1][1] * m.m[2][2]) +
					(m.m[0][3] * m.m[1][2] * m.m[2][1]) + (m.m[0][2] * m.m[1][1] * m.m[2][3]) + (m.m[0][1] * m.m[1][3] * m.m[2][2])),

		(1 / im) * ((m.m[1][0] * m.m[2][2] * m.m[3][3]) + (m.m[1][2] * m.m[2][3] * m.m[3][0]) + (m.m[1][3] * m.m[2][0] * m.m[3][2]) -
					(m.m[1][3] * m.m[2][2] * m.m[3][0]) - (m.m[1][2] * m.m[2][0] * m.m[3][3]) - (m.m[1][0] * m.m[2][3] * m.m[3][2])),
		(1 / im) * (-(m.m[0][0] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[2][3] * m.m[3][0]) - (m.m[0][3] * m.m[2][0] * m.m[3][2]) +
					(m.m[0][3] * m.m[2][2] * m.m[3][0]) + (m.m[0][2] * m.m[2][0] * m.m[3][3]) + (m.m[0][0] * m.m[2][3] * m.m[3][2])),
		(1 / im) * ((m.m[0][0] * m.m[1][2] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[3][0]) + (m.m[0][3] * m.m[1][0] * m.m[3][2]) -
					(m.m[0][3] * m.m[1][2] * m.m[3][0]) - (m.m[0][2] * m.m[1][0] * m.m[3][3]) - (m.m[0][0] * m.m[1][3] * m.m[3][2])) ,
		(1 / im) * (-(m.m[0][0] * m.m[1][2] * m.m[2][3]) - (m.m[0][2] * m.m[1][3] * m.m[2][0]) - (m.m[0][3] * m.m[1][0] * m.m[2][2]) +
					(m.m[0][3] * m.m[1][2] * m.m[2][0]) + (m.m[0][2] * m.m[1][0] * m.m[2][3]) + (m.m[0][0] * m.m[1][3] * m.m[2][2])),

		(1 / im) * ((m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[1][3] * m.m[2][0] * m.m[3][1]) -
					(m.m[1][3] * m.m[2][1] * m.m[3][0]) - (m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[1][0] * m.m[2][3] * m.m[3][1])),
		(1 / im) * (-(m.m[0][0] * m.m[2][1] * m.m[3][3]) - (m.m[0][1] * m.m[2][3] * m.m[3][0]) - (m.m[0][3] * m.m[2][0] * m.m[3][1]) +
					(m.m[0][3] * m.m[2][1] * m.m[3][0]) + (m.m[0][1] * m.m[2][0] * m.m[3][3]) + (m.m[0][0] * m.m[2][3] * m.m[3][1])),
		(1 / im) * ((m.m[0][0] * m.m[1][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][3] * m.m[3][0]) + (m.m[0][3] * m.m[1][0] * m.m[3][1]) -
					(m.m[0][3] * m.m[1][1] * m.m[3][0]) - (m.m[0][1] * m.m[1][0] * m.m[3][3]) - (m.m[0][0] * m.m[1][3] * m.m[3][1])),
		(1 / im) * (-(m.m[0][0] * m.m[1][1] * m.m[2][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0]) - (m.m[0][3] * m.m[1][0] * m.m[2][1]) +
					(m.m[0][3] * m.m[1][1] * m.m[2][0]) + (m.m[0][1] * m.m[1][0] * m.m[2][3]) + (m.m[0][0] * m.m[1][3] * m.m[2][1])),

		(1 / im) * ((m.m[1][0] * m.m[2][1] * m.m[3][2]) + (m.m[1][1] * m.m[2][2] * m.m[3][0]) + (m.m[1][2] * m.m[2][0] * m.m[3][1]) -
					(m.m[1][2] * m.m[2][1] * m.m[3][0]) - (m.m[1][1] * m.m[2][0] * m.m[3][2]) - (m.m[1][0] * m.m[2][2] * m.m[3][1])),
		(1 / im) * (-(m.m[0][0] * m.m[2][1] * m.m[3][2]) - (m.m[0][1] * m.m[2][2] * m.m[3][0]) - (m.m[0][2] * m.m[2][0] * m.m[3][1]) +
					(m.m[0][2] * m.m[2][1] * m.m[3][0]) + (m.m[0][1] * m.m[2][0] * m.m[3][2]) + (m.m[0][0] * m.m[2][2] * m.m[3][1])),
		(1 / im) * ((m.m[0][0] * m.m[1][1] * m.m[3][2]) + (m.m[0][1] * m.m[1][2] * m.m[3][0]) + (m.m[0][2] * m.m[1][0] * m.m[3][1]) -
					(m.m[0][2] * m.m[1][1] * m.m[3][0]) - (m.m[0][1] * m.m[1][0] * m.m[3][2]) - (m.m[0][0] * m.m[1][2] * m.m[3][1])),
		(1 / im) * (-(m.m[0][0] * m.m[1][1] * m.m[2][2]) - (m.m[0][1] * m.m[1][2] * m.m[2][0]) - (m.m[0][2] * m.m[1][0] * m.m[2][1]) +
					(m.m[0][2] * m.m[1][1] * m.m[2][0]) + (m.m[0][1] * m.m[1][0] * m.m[2][2]) + (m.m[0][0] * m.m[1][2] * m.m[2][1])),

	};

}

/// 転置行列の計算
Matrix4x4 Matrix4x4Ex::Transpose(Matrix4x4 m) {

	return Matrix4x4{
		m.m[0][0],m.m[1][0],m.m[2][0],m.m[3][0],
		m.m[0][1],m.m[1][1],m.m[2][1],m.m[3][1],
		m.m[0][2],m.m[1][2],m.m[2][2],m.m[3][2],
		m.m[0][3],m.m[1][3],m.m[2][3],m.m[3][3]
	};

}

/// 単位行列の作成
Matrix4x4 Matrix4x4Ex::MakeIdentity() {

	return Matrix4x4{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1,
	};

}


// 平行移動行列の作成
Matrix4x4 Matrix4x4Ex::MakeTranslateMatrix(const Vector3 translate) {

	return Matrix4x4{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		translate.x,translate.y,translate.z,1
	};

}

// 拡大縮小行列の作成
Matrix4x4 Matrix4x4Ex::MakeScaleMatrix(const Vector3 scale) {

	return Matrix4x4{
		scale.x,0,0,0,
		0,scale.y,0,0,
		0,0,scale.z,0,
		0,0,0,1,
	};

}


// 回転行列の作成(X軸周り：YZ平面)
Matrix4x4 Matrix4x4Ex::MakeRoatateXMatrix(float rad) {

	return Matrix4x4{
		1,0,0,0,
		0,std::cos(rad),std::sin(rad), 0,
		0,-std::sin(rad),std::cos(rad),0,
		0,0,0,1,
	};

}

// 回転行列の作成(Y軸周り：XZ平面)
Matrix4x4 Matrix4x4Ex::MakeRoatateYMatrix(float rad) {

	return Matrix4x4{
		std::cos(rad),0,-std::sin(rad),0,
		0,1,0,0,
		std::sin(rad),0,std::cos(rad),0,
		0,0,0,1,
	};

}

// 回転行列の作成(Z軸周り：XY平面)
Matrix4x4 Matrix4x4Ex::MakeRoatateZMatrix(float rad) {

	return Matrix4x4{
		std::cos(rad),std::sin(rad),0,0,
		-std::sin(rad),std::cos(rad),0,0,
		0,0,1,0,
		0,0,0,1,
	};

}


// 座標変換
Vector3 Matrix4x4Ex::Transform(const Vector3& v, const Matrix4x4& m) {
	Vector3 result;
	result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + 1.0f * m.m[3][0];
	result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + 1.0f * m.m[3][1];
	result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + 1.0f * m.m[3][2];
	float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + 1.0f * m.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

// アフィン行列の作成
Matrix4x4 Matrix4x4Ex::MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

	// 回転行列を作成
	Matrix4x4 rotatExMatrix = Matrix4x4Ex::MakeRoatateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = Matrix4x4Ex::MakeRoatateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = Matrix4x4Ex::MakeRoatateZMatrix(rotate.z);
	Matrix4x4 rotatExYZMatrix = Matrix4x4Ex::Multiply(rotatExMatrix, Matrix4x4Ex::Multiply(rotateYMatrix, rotateZMatrix));

	return Matrix4x4{
		scale.x * rotatExYZMatrix.m[0][0],	scale.x * rotatExYZMatrix.m[0][1],	scale.x * rotatExYZMatrix.m[0][2],0,
		scale.y * rotatExYZMatrix.m[1][0],	scale.y * rotatExYZMatrix.m[1][1],	scale.y * rotatExYZMatrix.m[1][2],0,
		scale.z * rotatExYZMatrix.m[2][0],	scale.z * rotatExYZMatrix.m[2][1],	scale.z * rotatExYZMatrix.m[2][2],0,
		translate.x,translate.y,translate.z,1
	};

}


/// 描画関数 ///


/// 4x4行列の数値表示
void Matrix4x4Ex::MatrixScreenPrintf(int x, int y, Matrix4x4& matrix, const char* label) {

	// ラベルの表示
	Novice::ScreenPrintf(x, y, "%s", label);

	// 行列の数値を表示

	// Y座標操作
	for (int h = 0; h < 4; h++) {
		// X座標操作
		for (int w = 0; w < 4; w++) {

			Novice::ScreenPrintf(x + 80 * w, (y + 20 * h) + 20, "%6.02f", matrix.m[h][w]);

		}
	}

}

/// 3次元ベクトルの数値表示
	/// <summary>
void Matrix4x4Ex::VectorScreenPrintf(int x, int y, Vector3& vector, const char* label) {

	// ラベルの表示
	Novice::ScreenPrintf(x, y, "%s", label);

	// 3次元ベクトルの表示
	Novice::ScreenPrintf(x, y + 20, "%6.02f", vector.x);
	Novice::ScreenPrintf(x + 80, y + 20, "%6.02f", vector.y);
	Novice::ScreenPrintf(x + 160, y + 20, "%6.02f", vector.z);

}