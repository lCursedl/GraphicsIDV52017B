#pragma once
#include <math.h>

static const float PI = (const float)(tan(1) / 4);

struct VECTOR4D
{
	union
	{
		struct
		{
			float x, y, z, w;
		};
		float v[4];
	};
	VECTOR4D() { x = 0; y = 0; z = 0; w = 0;};
	VECTOR4D(const VECTOR4D& V);
	VECTOR4D(float X, float Y = 0, float Z = 0, float W = 1);
	VECTOR4D& operator+=(VECTOR4D& A);
	VECTOR4D& operator-=(VECTOR4D& A);
	VECTOR4D& operator*=(VECTOR4D& A);
	VECTOR4D& operator/=(VECTOR4D& A);
	VECTOR4D& operator*=(float S);
};

float Dot(VECTOR4D& A, VECTOR4D& B);
VECTOR4D Cross3(VECTOR4D& A, VECTOR4D& B);
VECTOR4D operator*(VECTOR4D& A, VECTOR4D& B);
VECTOR4D operator+(VECTOR4D& A, VECTOR4D& B);
VECTOR4D operator-(VECTOR4D& A, VECTOR4D& B);
VECTOR4D operator/(VECTOR4D& A, VECTOR4D& B);
VECTOR4D operator*(VECTOR4D& A, float S);
VECTOR4D operator/(VECTOR4D& A, float S);
float Mag(VECTOR4D& A);
VECTOR4D Normalize(VECTOR4D& A);

class MATRIX4D 
{
public:
	union {
		struct 
		{
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
		};
		float m[4][4];
		float v[16];
	};
	MATRIX4D();
	MATRIX4D(float * F);
	MATRIX4D(const MATRIX4D& M);
	MATRIX4D(float _00   , float _01= 0, float _02= 0, float _03= 0,
			 float _10= 0, float _11= 1, float _12= 0, float _13= 0,
			 float _20= 0, float _21= 0, float _22= 1, float _23= 0,
			 float _30= 0, float _31= 0, float _32= 0, float _33= 1);
	void SetCol(VECTOR4D& V, int nCol);
	void SetRow(VECTOR4D& V, int nRow);
	VECTOR4D GetCol(int nCol);
	VECTOR4D GetRow(int nRow);

	MATRIX4D& operator+=(MATRIX4D& A);
	MATRIX4D& operator-=(MATRIX4D& A);
	MATRIX4D& operator*=(MATRIX4D& A);
	MATRIX4D& operator*=(float s);
	MATRIX4D& operator/=(float s);
	MATRIX4D& operator=(float *s);
};

MATRIX4D Zero(void);
MATRIX4D Identity(void);
MATRIX4D operator+(MATRIX4D& A, MATRIX4D& B);
MATRIX4D operator-(MATRIX4D& A, MATRIX4D& B);
MATRIX4D operator*(MATRIX4D& A, MATRIX4D& B);
MATRIX4D operator*(MATRIX4D& M, float s);
MATRIX4D operator/(MATRIX4D& M, float s);
MATRIX4D Transpose(MATRIX4D& A);
void XVecTransformNormalRH(VECTOR4D &vpout, const VECTOR4D &v, const MATRIX4D &mat);
MATRIX4D LookAtRH(VECTOR4D & EyePos, VECTOR4D & Target, VECTOR4D & Up);
MATRIX4D LookAtLH(VECTOR4D & EyePos, VECTOR4D & Target, VECTOR4D & Up);
MATRIX4D PerspectiveFOVRH(float FOVY, float ratio, float zNear, float zFar);
MATRIX4D PerspectiveFOVLH(float FOVY, float ratio, float zNear, float zFar);
float Det(MATRIX4D& A);
MATRIX4D Cofactor(MATRIX4D& A);
MATRIX4D InverseGJ(MATRIX4D& A);
MATRIX4D Adjunt(MATRIX4D& A);
MATRIX4D Inverse(MATRIX4D& A);
VECTOR4D operator*(MATRIX4D& M, VECTOR4D& V);
VECTOR4D operator*(VECTOR4D& V, MATRIX4D& M);
VECTOR4D Cramer(MATRIX4D& M, VECTOR4D& V);
MATRIX4D Translation(float x, float y, float z);
void XMatTranslation(MATRIX4D &mpout, VECTOR4D& v);
MATRIX4D Scaling(float x, float y, float z);
MATRIX4D RotateXRH(float theta);
MATRIX4D RotateYRH(float theta);
MATRIX4D RotateZRH(float theta);