#include "MatrixCalculation.h"
#include <algorithm>

Vector3 Normalise(const Vector3& v)
{
	float len = Length(v);
	if (len != 0)
	{
		return { v.x / len,v.y / len,v.z / len };
	}
	return v;
}

float Length(const Vector3& v)
{
	return sqrtf(Dot(v, v));
}

float Dot(const Vector3& v1, const Vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

//X軸回転行列
Matrix4x4 MakeRotateXmatrix(float radian)
{
	Matrix4x4 result;
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = -std::sin(radian);
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;
	return result;
}

//Y軸回転行列
Matrix4x4 MakeRotateYmatrix(float radian)
{
	Matrix4x4 result;
	result.m[0][0] = std::cos(radian);
	result.m[0][1] = 0.0f;
	result.m[0][2] = -std::sin(radian);
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = std::sin(radian);
	result.m[2][1] = 0.0f;
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;
	return result;
}

//Z軸回転行列
Matrix4x4 MakeRotateZmatrix(float radian)
{
	Matrix4x4 result;
	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = -std::sin(radian);
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;
	return result;
}

//平行移動
Matrix4x4 MakeTranslateMatrix(Vector3 translate)
{
	Matrix4x4 result;
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;

	return result;
};

//拡大縮小
Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 result;

	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

//アフィン変換
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	Matrix4x4 result;
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

	Matrix4x4 rotateXMatrix = MakeRotateXmatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYmatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZmatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

	result = Multiply(scaleMatrix, Multiply(rotateXYZMatrix, translateMatrix));
	return result;
}

//行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}
	return result;
}

//行列の減法
Matrix4x4 Sub(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}
	return result;
}

//行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float Term = 0;
			for (int k = 0; k < 4; k++)
			{
				Term = Term + m1.m[i][k] * m2.m[k][j];
				result.m[i][j] = Term;
			}
		}
	}
	return result;
}

//逆行列
Matrix4x4 Inverse(const Matrix4x4& m1)
{
	Matrix4x4 result;
	float deterninant = m1.m[0][0] * m1.m[1][1] * m1.m[2][2] * m1.m[3][3] +
		m1.m[0][0] * m1.m[1][2] * m1.m[2][3] * m1.m[3][1] +
		m1.m[0][0] * m1.m[1][3] * m1.m[2][1] * m1.m[3][2] -

		m1.m[0][0] * m1.m[1][3] * m1.m[2][2] * m1.m[3][1] -
		m1.m[0][0] * m1.m[1][2] * m1.m[2][1] * m1.m[3][3] -
		m1.m[0][0] * m1.m[1][1] * m1.m[2][3] * m1.m[3][2] -

		m1.m[0][1] * m1.m[1][0] * m1.m[2][2] * m1.m[3][3] -
		m1.m[0][2] * m1.m[1][0] * m1.m[2][3] * m1.m[3][1] -
		m1.m[0][3] * m1.m[1][0] * m1.m[2][1] * m1.m[3][2] +

		m1.m[0][3] * m1.m[1][0] * m1.m[2][2] * m1.m[3][1] +
		m1.m[0][2] * m1.m[1][0] * m1.m[2][1] * m1.m[3][3] +
		m1.m[0][1] * m1.m[1][0] * m1.m[2][3] * m1.m[3][2] +

		m1.m[0][1] * m1.m[1][2] * m1.m[2][0] * m1.m[3][3] +
		m1.m[0][2] * m1.m[1][3] * m1.m[2][0] * m1.m[3][1] +
		m1.m[0][3] * m1.m[1][1] * m1.m[2][0] * m1.m[3][2] -

		m1.m[0][3] * m1.m[1][2] * m1.m[2][0] * m1.m[3][1] -
		m1.m[0][2] * m1.m[1][1] * m1.m[2][0] * m1.m[3][3] -
		m1.m[0][1] * m1.m[1][3] * m1.m[2][0] * m1.m[3][2] -

		m1.m[0][1] * m1.m[1][2] * m1.m[2][3] * m1.m[3][0] -
		m1.m[0][2] * m1.m[1][3] * m1.m[2][1] * m1.m[3][0] -
		m1.m[0][3] * m1.m[1][1] * m1.m[2][2] * m1.m[3][0] +

		m1.m[0][3] * m1.m[1][2] * m1.m[2][1] * m1.m[3][0] +
		m1.m[0][2] * m1.m[1][1] * m1.m[2][3] * m1.m[3][0] +
		m1.m[0][1] * m1.m[1][3] * m1.m[2][2] * m1.m[3][0];

	assert(deterninant != 0.0f);
	float deterninantRect = 1.0f / deterninant;

	result.m[0][0] =
		(m1.m[1][1] * m1.m[2][2] * m1.m[3][3] +
			m1.m[1][2] * m1.m[2][3] * m1.m[3][1] +
			m1.m[1][3] * m1.m[2][1] * m1.m[3][2] -
			m1.m[1][3] * m1.m[2][2] * m1.m[3][1] -
			m1.m[1][2] * m1.m[2][1] * m1.m[3][3] -
			m1.m[1][1] * m1.m[2][3] * m1.m[3][2]) * deterninantRect;
	result.m[0][1] =
		(-m1.m[0][1] * m1.m[2][2] * m1.m[3][3] -
			m1.m[0][2] * m1.m[2][3] * m1.m[3][1] -
			m1.m[0][3] * m1.m[2][1] * m1.m[3][2] +
			m1.m[0][3] * m1.m[2][2] * m1.m[3][1] +
			m1.m[0][2] * m1.m[2][1] * m1.m[3][3] +
			m1.m[0][1] * m1.m[2][3] * m1.m[3][2]) * deterninantRect;
	result.m[0][2] =
		(m1.m[0][1] * m1.m[1][2] * m1.m[3][3] +
			m1.m[0][2] * m1.m[1][3] * m1.m[3][1] +
			m1.m[0][3] * m1.m[1][1] * m1.m[3][2] -
			m1.m[0][3] * m1.m[1][2] * m1.m[3][1] -
			m1.m[0][2] * m1.m[1][1] * m1.m[3][3] -
			m1.m[0][1] * m1.m[1][3] * m1.m[3][2]) * deterninantRect;
	result.m[0][3] =
		(-m1.m[0][1] * m1.m[1][2] * m1.m[2][3] -
			m1.m[0][2] * m1.m[1][3] * m1.m[2][1] -
			m1.m[0][3] * m1.m[1][1] * m1.m[2][2] +
			m1.m[0][3] * m1.m[1][2] * m1.m[2][1] +
			m1.m[0][2] * m1.m[1][1] * m1.m[2][3] +
			m1.m[0][1] * m1.m[1][3] * m1.m[2][2]) * deterninantRect;

	result.m[1][0] =
		(-m1.m[1][0] * m1.m[2][2] * m1.m[3][3] -
			m1.m[1][2] * m1.m[2][3] * m1.m[3][0] -
			m1.m[1][3] * m1.m[2][0] * m1.m[3][2] +
			m1.m[1][3] * m1.m[2][2] * m1.m[3][0] +
			m1.m[1][2] * m1.m[2][0] * m1.m[3][3] +
			m1.m[1][0] * m1.m[2][3] * m1.m[3][2]) * deterninantRect;
	result.m[1][1] =
		(m1.m[0][0] * m1.m[2][2] * m1.m[3][3] +
			m1.m[0][2] * m1.m[2][3] * m1.m[3][0] +
			m1.m[0][3] * m1.m[2][0] * m1.m[3][2] -
			m1.m[0][3] * m1.m[2][2] * m1.m[3][0] -
			m1.m[0][2] * m1.m[2][0] * m1.m[3][3] -
			m1.m[0][0] * m1.m[2][3] * m1.m[3][2]) * deterninantRect;
	result.m[1][2] =
		(-m1.m[0][0] * m1.m[1][2] * m1.m[3][3] -
			m1.m[0][2] * m1.m[1][3] * m1.m[3][0] -
			m1.m[0][3] * m1.m[1][0] * m1.m[3][2] +
			m1.m[0][3] * m1.m[1][2] * m1.m[3][0] +
			m1.m[0][2] * m1.m[1][0] * m1.m[3][3] +
			m1.m[0][0] * m1.m[1][3] * m1.m[3][2]) * deterninantRect;
	result.m[1][3] =
		(m1.m[0][0] * m1.m[1][2] * m1.m[2][3] +
			m1.m[0][2] * m1.m[1][3] * m1.m[2][0] +
			m1.m[0][3] * m1.m[1][0] * m1.m[2][2] -
			m1.m[0][3] * m1.m[1][2] * m1.m[2][0] -
			m1.m[0][2] * m1.m[1][0] * m1.m[2][3] -
			m1.m[0][0] * m1.m[1][3] * m1.m[2][2]) * deterninantRect;

	result.m[2][0] =
		(m1.m[1][0] * m1.m[2][1] * m1.m[3][3] +
			m1.m[1][1] * m1.m[2][3] * m1.m[3][0] +
			m1.m[1][3] * m1.m[2][0] * m1.m[3][1] -
			m1.m[1][3] * m1.m[2][1] * m1.m[3][0] -
			m1.m[1][1] * m1.m[2][0] * m1.m[3][3] -
			m1.m[1][0] * m1.m[2][3] * m1.m[3][1]) * deterninantRect;
	result.m[2][1] =
		(-m1.m[0][0] * m1.m[2][1] * m1.m[3][3] -
			m1.m[0][1] * m1.m[2][3] * m1.m[3][0] -
			m1.m[0][3] * m1.m[2][0] * m1.m[3][1] +
			m1.m[0][3] * m1.m[2][1] * m1.m[3][0] +
			m1.m[0][1] * m1.m[2][0] * m1.m[3][3] +
			m1.m[0][0] * m1.m[2][3] * m1.m[3][1]) * deterninantRect;
	result.m[2][2] =
		(m1.m[0][0] * m1.m[1][1] * m1.m[3][3] +
			m1.m[0][1] * m1.m[1][3] * m1.m[3][0] +
			m1.m[0][3] * m1.m[1][0] * m1.m[3][1] -
			m1.m[0][3] * m1.m[1][1] * m1.m[3][0] -
			m1.m[0][1] * m1.m[1][0] * m1.m[3][3] -
			m1.m[0][0] * m1.m[1][3] * m1.m[3][1]) * deterninantRect;
	result.m[2][3] =
		(-m1.m[0][0] * m1.m[1][1] * m1.m[2][3] -
			m1.m[0][1] * m1.m[1][3] * m1.m[2][0] -
			m1.m[0][3] * m1.m[1][0] * m1.m[2][1] +
			m1.m[0][3] * m1.m[1][1] * m1.m[2][0] +
			m1.m[0][1] * m1.m[1][0] * m1.m[2][3] +
			m1.m[0][0] * m1.m[1][3] * m1.m[2][1]) * deterninantRect;

	result.m[3][0] =
		(-m1.m[1][0] * m1.m[2][1] * m1.m[3][2] -
			m1.m[1][1] * m1.m[2][2] * m1.m[3][0] -
			m1.m[1][2] * m1.m[2][0] * m1.m[3][1] +
			m1.m[1][2] * m1.m[2][1] * m1.m[3][0] +
			m1.m[1][1] * m1.m[2][0] * m1.m[3][2] +
			m1.m[1][0] * m1.m[2][2] * m1.m[3][1]) * deterninantRect;
	result.m[3][1] =
		(m1.m[0][0] * m1.m[2][1] * m1.m[3][2] +
			m1.m[0][1] * m1.m[2][2] * m1.m[3][0] +
			m1.m[0][2] * m1.m[2][0] * m1.m[3][1] -
			m1.m[0][2] * m1.m[2][1] * m1.m[3][0] -
			m1.m[0][1] * m1.m[2][0] * m1.m[3][2] -
			m1.m[0][0] * m1.m[2][2] * m1.m[3][1]) * deterninantRect;
	result.m[3][2] =
		(-m1.m[0][0] * m1.m[1][1] * m1.m[3][2] -
			m1.m[0][1] * m1.m[1][2] * m1.m[3][0] -
			m1.m[0][2] * m1.m[1][0] * m1.m[3][1] +
			m1.m[0][2] * m1.m[1][1] * m1.m[3][0] +
			m1.m[0][1] * m1.m[1][0] * m1.m[3][2] +
			m1.m[0][0] * m1.m[1][2] * m1.m[3][1]) * deterninantRect;
	result.m[3][3] =
		(m1.m[0][0] * m1.m[1][1] * m1.m[2][2] +
			m1.m[0][1] * m1.m[1][2] * m1.m[2][0] +
			m1.m[0][2] * m1.m[1][0] * m1.m[2][1] -
			m1.m[0][2] * m1.m[1][1] * m1.m[2][0] -
			m1.m[0][1] * m1.m[1][0] * m1.m[2][2] -
			m1.m[0][0] * m1.m[1][2] * m1.m[2][1]) * deterninantRect;

	return result;
}

//転置行列
Matrix4x4 Transpose(const Matrix4x4& m)
{
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result.m[j][i] = m.m[i][j];
		}
	}
	return result;
}

//単位行列
Matrix4x4 MakeIdentity4x4()
{
	return{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
}

float contangent(float b, float a)
{
	return(b / tan(a));
}

//透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRadio, float nearClip, float farClip)
{
	Matrix4x4 result;
	result.m[0][0] = contangent((1 / aspectRadio), (fovY / 2));
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = contangent(1, fovY / 2);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = -nearClip * farClip / (farClip - nearClip);
	result.m[3][3] = 0.0f;

	return result;
}

// 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
{
	Matrix4x4 result;
	result.m[0][0] = 2 / (right - left);
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = 2 / (top - bottom);
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1 / (farClip - nearClip);
	result.m[2][3] = 0;
	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1;
	return result;
}

// 座標返還
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m) {
	Vector3 result{
		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2],
	};
	return result;
};



bool IsCollisionAABB(Vector3 min, Vector3 max, float radius, Vector3 pos) {
	bool g = false;

	// 最近接点を求める
	Vector3 closestPoint{
		std::clamp(pos.x,min.x,max.x),
		std::clamp(pos.y,min.y,max.y),
		std::clamp(pos.z,min.z,max.z)
	};

	// 最近接点と弾の中心との距離を求める
	float distance = Length({
		closestPoint.x - pos.x,
		closestPoint.y - pos.y,
		closestPoint.z - pos.z });
	// 距離が半径よりも小さければ衝突
	if (distance <= radius) {
		g = true;
	}
	else { g = false; }
	return g;
}
// ベクトルの差を計算する関数
Vector3 subtract(const Vector3& a, const Vector3& b) {
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}


// 原点から平面までの距離を計算する関数
float distanceToPlane(const Vector3& normal, const Vector3& pointOnPlane) {
	return -(normal.x * pointOnPlane.x + normal.y * pointOnPlane.y + normal.z * pointOnPlane.z);
}

// ベクトルの内積を計算する関数
float dotProduct(const Vector3& a, const Vector3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
// 指定した点から平面までの距離を計算する関数
float adistanceToPlane(const Vector3& normal, const Vector3& pointOnPlane, const Vector3& fromPoint) {
	Vector3 vectorToPoint = subtract(fromPoint, pointOnPlane);
	return dotProduct(normal, vectorToPoint);
}

Vector3 multiplyMatrixVector(const Matrix4x4& mat, const Vector3& vec) {
	Vector3 result;
	result.x = mat.m[0][0] * vec.x + mat.m[1][0] * vec.y + mat.m[2][0] * vec.z + mat.m[3][0];
	result.y = mat.m[0][1] * vec.x + mat.m[1][1] * vec.y + mat.m[2][1] * vec.z + mat.m[3][1];
	result.z = mat.m[0][2] * vec.x + mat.m[1][2] * vec.y + mat.m[2][2] * vec.z + mat.m[3][2];
	return result;
}

Vector3 Reflect(const Vector3& input, const Vector3& normal) {
	Vector3 r;
	Vector3 proj = Project(input, normal);
	r.x = input.x - 2 * proj.x;
	r.y = input.y - 2 * proj.y;
	r.z = input.z - 2 * proj.z;
	return r;
}


bool IsCollisionPlane(const Vector3& pos, float radius, const Plane& s2) {
	bool g = false;
	//Vector3 q = { s1.center.x - s2.normal.x * s2.distance,s1.center.y - s2.normal.y * s2.distance, s1.center.z - s2.normal.z * s2.distance, };
	//float d = Dot(s2.normal, q);
	// 2つの弾の中心点間の距離を求める
	float distance = fabsf(Dot(s2.normal, pos) - s2.distance);
	if (distance <= radius) {
		g = true;
	}
	else { g = false; }
	return g;
}

Vector3 Project(const Vector3& v1, const Vector3& v2) {
	float m3 = Dot(v1, Normalize(v2));
	Vector3 result;
	Vector3 demo = Normalize(v2);
	result.x = m3 * demo.x;
	result.y = m3 * demo.y;
	result.z = m3 * demo.z;
	return result;
}	//正規化
		Vector3 Normalize(const Vector3 & v) {
		Vector3 m3;
		float mag = 1 / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
		m3 = { v.x * mag,v.y * mag,v.z * mag };

		return m3;

	};