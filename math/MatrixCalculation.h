#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include "Vector4.h"
#include <assert.h>
#include <cmath>

struct Transform
{
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};

struct AABB {
	Vector3 min;
	Vector3 max;
	Vector3 pos;
	float width;
	float height;
	float length;
	int color;
};

struct OBB {
	Vector3 center;
	Vector3 orientations[3];
	Vector3 size;
};

struct Plane {
	Vector3 normal; // !< 法線
	float distance; //!< 距離
	int color;

};

float cot(float theta);
float Length(const Vector3& v);
float Dot(const Vector3& v1, const Vector3& v2);

Vector3 Normalise(const Vector3& v);

//X軸回転行列
Matrix4x4 MakeRotateXmatrix(float radian);

//Y軸回転行列
Matrix4x4 MakeRotateYmatrix(float radian);

//Z軸回転行列
Matrix4x4 MakeRotateZmatrix(float radian);

//平行移動
Matrix4x4 MakeTranslateMatrix(Vector3 translate);

//拡大縮小
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

// アフィン変換
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

//行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

//行列の減法
Matrix4x4 Sub(const Matrix4x4& m1, const Matrix4x4& m2);

//行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

//逆行列
Matrix4x4 Inverse(const Matrix4x4& m1);

//転置行列
Matrix4x4 Transpose(const Matrix4x4& m);

//単位行列
Matrix4x4 MakeIdentity4x4();

//透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRadio, float nearClip, float farClip);

// 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

// 座標返還
Vector3 TransformNormal(const Vector3& vector, const Matrix4x4& matrix);


bool IsCollisionAABB(Vector3 min, Vector3 max, float radius, Vector3 pos);


// ベクトルの差を計算する関数
Vector3 subtract(const Vector3& a, const Vector3& b);


// 原点から平面までの距離を計算する関数
float distanceToPlane(const Vector3& normal, const Vector3& pointOnPlane) ;
// ベクトルの内積を計算する関数
float dotProduct(const Vector3& a, const Vector3& b);
// 指定した点から平面までの距離を計算する関数
float adistanceToPlane(const Vector3& normal, const Vector3& pointOnPlane, const Vector3& fromPoint);

Vector3 multiplyMatrixVector(const Matrix4x4& mat, const Vector3& vec);
Vector3 Reflect(const Vector3& input, const Vector3& normal);


bool IsCollisionPlane(const Vector3& pos, float radius, const Plane& s2);

Vector3 Project(const Vector3& v1, const Vector3& v2);
Vector3 Normalize(const Vector3& v);

