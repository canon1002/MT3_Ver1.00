#pragma once
#include"Vector2.h"

//3x3の行列を表す構造体
typedef struct Matrix3x3 {
	float m[3][3] = { 0 };
};

typedef struct Quad {
	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftBottom;
	Vector2 rightBottom;
};

class Matrix3 {

public: // 3x3行列 メゾット

	/// <summary>
	/// 行列の和を返す関数
	/// </summary>
	/// <param name="matrix1">行列1</param>
	/// <param name="matrix2">行列2</param>
	/// <returns>"行列1"と"行列2"の積を返す</returns>
	static Matrix3x3 Add(Matrix3x3 matrix1, Matrix3x3 matrix2);

	/// <summary>
	/// 行列の差を返す関数
	/// </summary>
	/// <param name="matrix1">行列1</param>
	/// <param name="matrix2">行列2</param>
	/// <returns>"行列1"と"行列2"の積を返す</returns>
	static Matrix3x3 Subtract(Matrix3x3 matrix1, Matrix3x3 matrix2);

	/// <summary>
	/// 行列の積を返す関数
	/// </summary>
	/// <param name="matrix1">行列1</param>
	/// <param name="matrix2">行列2</param>
	/// <returns>"行列1"と"行列2"の積を返す</returns>
	static Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);


	/// <summary>
	/// アフィン変換行列を作成する
	/// </summary>
	/// <param name="scalar">拡縮</param>
	/// <param name="theta">回転</param>
	/// <param name="translate">平行移動</param>
	/// <returns>拡縮・回転・平行移動を行った行列を返す</returns>
	static Matrix3x3 MakeAffine(Vector2 scalar, float theta, Vector2 translate);


	/// <summary>
	/// 逆行列を作成する
	/// </summary>
	/// <param name="matrix">3x3の正方行列</param>
	/// <returns>引数の逆行列を返す</returns>
	static Matrix3x3 Inverse(Matrix3x3 matrix);


	/// <summary>
	/// 転置行列の計算
	/// </summary>
	/// <param name="matrix">3x3の行列</param>
	/// <returns>引数の行列の"列"と"行"を入れ替えた転置行列を返す</returns>
	static Matrix3x3 Transpose(Matrix3x3 matrix);


	/// <summary>
	/// 正射影行列の作成
	/// </summary>
	/// <param name="left">左側のサイズ</param>
	/// <param name="top">上側のサイズ</param>
	/// <param name="right">右側のサイズ</param>
	/// <param name="bottom">下側のサイズ</param>
	/// <returns>引数をもとにした正射影行列を返す</returns>
	static Matrix3x3 MakeOrthographic(float left, float top, float right, float bottom);


	/// <summary>
	/// ビューポート行列の作成
	/// </summary>
	/// <param name="left">左側のサイズ</param>
	/// <param name="top">上側のサイズ</param>
	/// <param name="width">横幅</param>
	/// <param name="height">縦幅</param>
	/// <returns>引数をもとにしたビューポート行列を返す</returns>
	static Matrix3x3 MakeViewport(float left, float top, float width, float height);


	/// <summary>
	/// 二次元ベクトルを同次座標として変換する関数
	/// </summary>
	/// <param name="vector">二次元ベクトル</param>
	/// <param name="matrix">3x3の行列</param>
	/// <returns>引数をもとに平行移動した二次元ベクトルを返す</returns>
	static Vector2 Transform(Vector2 vector, Matrix3x3 matrix);


	/// <summary>
	/// 4か所の二次元ベクトルを同次座標として変換する関数
	/// </summary>
	/// <param name="quad">左上,右上,左下,右下の二次元ベクトル</param>
	/// <param name="matrix">3x3の行列</param>
	/// <returns>引数をもとに平行移動した4か所二次元ベクトルを返す</returns>
	static Quad Transform(Quad quad, Matrix3x3 matrix);

};

