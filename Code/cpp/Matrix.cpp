#include "Matrix.h"
#include <cmath>
#include <cassert>


/// 行列の積を返す関数
Matrix3x3 Matrix3::Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {

	return Matrix3x3{
	matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0] + matrix1.m[0][2] * matrix2.m[2][0],
	matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1] + matrix1.m[0][2] * matrix2.m[2][1],
	matrix1.m[0][0] * matrix2.m[0][2] + matrix1.m[0][1] * matrix2.m[1][2] + matrix1.m[0][2] * matrix2.m[2][2],
	matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0] + matrix1.m[1][2] * matrix2.m[2][0],
	matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1] + matrix1.m[1][2] * matrix2.m[2][1],
	matrix1.m[1][0] * matrix2.m[0][2] + matrix1.m[1][1] * matrix2.m[1][2] + matrix1.m[1][2] * matrix2.m[2][2],
	matrix1.m[2][0] * matrix2.m[0][0] + matrix1.m[2][1] * matrix2.m[1][0] + matrix1.m[2][2] * matrix2.m[2][0],
	matrix1.m[2][0] * matrix2.m[0][1] + matrix1.m[2][1] * matrix2.m[1][1] + matrix1.m[2][2] * matrix2.m[2][1],
	matrix1.m[2][0] * matrix2.m[0][2] + matrix1.m[2][1] * matrix2.m[1][2] + matrix1.m[2][2] * matrix2.m[2][2],
	};

}


/// アフィン変換行列を作成する
Matrix3x3 Matrix3::MakeAffine(Vector2 scalar, float theta, Vector2 translate) {

	return Matrix3x3{
		scalar.x * cosf(theta),	scalar.x * sinf(theta),	0,
		scalar.y * -sinf(theta),scalar.y * cosf(theta),	0,
		translate.x,			translate.y,			1,
	};

}



/// 逆行列を作成する
Matrix3x3 Matrix3::Inverse(Matrix3x3 matrix) {

	float im = (
		(matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2]) +
		(matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0]) +
		(matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1]) -
		(matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0]) -
		(matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2]) -
		(matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]));

	assert(im != 0.0f);

	return Matrix3x3{
		(1 / im) * matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1],
		(1 / im) * -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]),
		(1 / im) * matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1],

		(1 / im) * -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]),
		(1 / im) * matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0],
		(1 / im) * -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]),

		(1 / im) * matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0],
		(1 / im) * -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]),
		(1 / im) * matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]
	};

}


/// 転置行列の計算
Matrix3x3 Matrix3::Transpose(Matrix3x3 matrix) {

	return Matrix3x3{
		matrix.m[0][0],matrix.m[1][0],matrix.m[2][0],
		matrix.m[0][1],matrix.m[1][1],matrix.m[2][1],
		matrix.m[0][2],matrix.m[1][2],matrix.m[2][2]
	};

}


/// 正射影行列の作成
Matrix3x3 Matrix3::MakeOrthographic(float left, float top, float right, float bottom) {

	return Matrix3x3{
		2.0f / (right - left),
		0,
		0,
		0,
		2.0f / (top - bottom),
		0,
		(left + right) / (left - right),
		(top + bottom) / (bottom - top),
		1,
	};

}


/// ビューポート行列の作成
Matrix3x3 Matrix3::MakeViewport(float left, float top, float width, float height) {

	return Matrix3x3{
		width / 2.0f,
		0,
		0,
		0,
		-(height / 2.0f),
		0,
		left + (width / 2.0f),
		top + (height / 2.0f),
		1,
	};

}


/// 二次元ベクトルを同次座標として変換する関数
Vector2 Matrix3::Transform(Vector2 vector, Matrix3x3 matrix) {

	//w=1がデカルト座標系であるので(x,y,1)のベクトルとしてmatrixとの積をとる
	Vector2 result = { 0.0f,0.0f };
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];

	//ベクトルに対して基本的な操作を行う行列でwがゼロになることはあり得ない
	assert(w != 0.0f);

	//w=1がデカルト座標系にあるため、wを除算することで同次座標をデカルトに移す
	result.x /= w;
	result.y /= w;

	return result;
}


///  4か所の二次元ベクトルを同次座標として変換する関数
Quad Matrix3::Transform(Quad quad, Matrix3x3 matrix) {

	// 4か所それぞれで平行移動をおこなう
	quad.leftTop = Matrix3::Transform(quad.leftTop, matrix);
	quad.rightTop = Matrix3::Transform(quad.rightTop, matrix);
	quad.leftBottom = Matrix3::Transform(quad.leftBottom, matrix);
	quad.rightBottom = Matrix3::Transform(quad.rightBottom, matrix);

	return quad;

}


