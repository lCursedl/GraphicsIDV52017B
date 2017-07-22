#include "MATRiX4D.h"

VECTOR4D::VECTOR4D(float X, float Y, float Z, float W)
{
	x = X;
	y = Y;
	z = Z;
	w = W;
}

VECTOR4D::VECTOR4D(VECTOR4D& A)
{
	x = A.x;
	y = A.y;
	z = A.z;
	w = A.w;
}

VECTOR4D& VECTOR4D::operator+=(VECTOR4D& A)
{
	x += A.x;
	y += A.y;
	z += A.z;
	w += A.w;
	return *this;
}

VECTOR4D& VECTOR4D::operator-=(VECTOR4D& A)
{
	x -= A.x;
	y -= A.y;
	z -= A.z;
	w -= A.w;
	return *this;
}

VECTOR4D& VECTOR4D::operator*=(VECTOR4D& A)
{
	x *= A.x;
	y *= A.y;
	z *= A.z;
	w *= A.w;
	return *this;
}

VECTOR4D& VECTOR4D::operator*=(float S)
{
	x * S; 
	y * S;
	z * S;
	w * S;
	return *this;
}

VECTOR4D& VECTOR4D::operator/=(VECTOR4D& A)
{
	x /= A.x;
	y /= A.y;
	z /= A.z;
	w /= A.w;
	return *this;
}

float Dot(VECTOR4D& A, VECTOR4D& B)
{
	return A.x*B.x + A.y*B.y + A.z*B.z + A.w*B.w;
}

VECTOR4D Cross3(VECTOR4D& A, VECTOR4D& B)
{
	return VECTOR4D(A.y*B.z - B.y*A.z, A.z*B.x - B.z*A.x, A.x*B.y - B.x*A.y, 0);
}

VECTOR4D operator*(VECTOR4D& A, VECTOR4D& B)
{
	return VECTOR4D(A.x * B.x, A.y * B.y, A.z * B.z, A.w * B.w);
}

VECTOR4D operator+(VECTOR4D& A, VECTOR4D& B)
{
	return VECTOR4D(A.x + B.x, A.y + B.y, A.z + B.z, A.w + B.w);
}

VECTOR4D operator-(VECTOR4D& A, VECTOR4D& B)
{
	return VECTOR4D(A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w);
}

VECTOR4D operator/(VECTOR4D& A, VECTOR4D& B)
{
	return VECTOR4D(A.x / B.x, A.y / B.y, A.z / B.z, A.w / B.w);
}

VECTOR4D operator*(VECTOR4D& A, float S)
{
	return VECTOR4D(A.x * S, A.y * S, A.z * S, A.w * S);
}

VECTOR4D operator/(VECTOR4D& A, float S)
{
	return A*(1.0f / S);
}

#include <math.h>
float Mag(VECTOR4D& A)
{
	return sqrtf(Dot(A, A));
}

VECTOR4D Normalize(VECTOR4D& A)
{
	return A / Mag(A);
}

MATRIX4D::MATRIX4D()
{
	m00 = 0; m01 = 0; m02 = 0; m03 = 0;
	m10 = 0; m11 = 0; m12 = 0; m13 = 0;
	m20 = 0; m21 = 0; m22 = 0; m23 = 0;
	m30 = 0; m31 = 0; m32 = 0; m33 = 0;
}

MATRIX4D::MATRIX4D(float * F)
{
	for (int i = 0; i < 16; i++)
	{
		this->v[i] = F[i];
	}
}

MATRIX4D::MATRIX4D(const MATRIX4D& M)
{
	*this = M;
}

MATRIX4D::MATRIX4D(float _00, float _01, float _02, float _03,
				   float _10, float _11, float _12, float _13,
				   float _20, float _21, float _22, float _23,
				   float _30, float _31, float _32, float _33)
{
	m00 = _00; m01 = _01; m02 = _02; m03 = _03;
	m10 = _10; m11 = _11; m12 = _12; m13 = _13;
	m20 = _20; m21 = _21; m22 = _22; m23 = _23;
	m30 = _30; m31 = _31; m32 = _32; m33 = _33;
}

void MATRIX4D::SetCol(VECTOR4D & V, int nCol)
{
	for (int i = 0; i < 4; i++)
		m[i][nCol] = V.v[i];
}

void MATRIX4D::SetRow(VECTOR4D & V, int nRow)
{
	for (int i = 0; i < 4; i++)
		m[nRow][i] = V.v[i];
}

VECTOR4D MATRIX4D::GetCol(int nCol)
{
	VECTOR4D R;
	for (int i = 0; i < 4; i++)
		R.v[i] = m[i][nCol];
	return R;
}

VECTOR4D MATRIX4D::GetRow(int nRow)
{
	VECTOR4D R;
	for (int i = 0; i < 4; i++)
		R.v[i] = m[nRow][i];
	return R;
}

MATRIX4D & MATRIX4D::operator+=(MATRIX4D & A)
{
	*this = *this+A;
	return *this;
}

MATRIX4D & MATRIX4D::operator-=(MATRIX4D & A)
{
	*this = *this-A;
	return *this;
}

MATRIX4D & MATRIX4D::operator*=(MATRIX4D & A)
{
	*this = *this*A;
	return *this;
}

MATRIX4D & MATRIX4D::operator*=(float s)
{
	*this = *this*s;
	return *this;
}

MATRIX4D & MATRIX4D::operator/=(float s)
{
	*this = *this/s;
	return *this;
}

MATRIX4D & MATRIX4D::operator=(float * s)
{
	for (int i = 0; i < 16; i++)
	{
		v[i] = s[i];
	}
	//*this = *s;
	return *this;
}

MATRIX4D Zero(void) {
	MATRIX4D R;
	for (int i = 0; i < 16; i++)
		R.v[i] = 0;
	return R;
}

MATRIX4D Identity(void) {
	MATRIX4D R;

	R.m01 = R.m02 = R.m03 =
		R.m10 = R.m12 = R.m13 =
		R.m20 = R.m21 = R.m23 =
		R.m30 = R.m31 = R.m32 = 0.0f;

	R.m00 = R.m11 = R.m22 = R.m33 = 1.0f;
	/*for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			R.m[i][j] = 0;*/
	return R;
}

MATRIX4D operator+(MATRIX4D & A, MATRIX4D & B) {
	MATRIX4D R;
	for (int i = 0; i < 16; i++)
		R.v[i] = A.v[i]+ B.v[i];
	return R;
}

MATRIX4D operator-(MATRIX4D & A, MATRIX4D & B) {
	MATRIX4D R;
	for (int i = 0; i < 16; i++)
		R.v[i] = A.v[i] - B.v[i];
	return R;
}

MATRIX4D operator*(MATRIX4D & A, MATRIX4D & B) {
	MATRIX4D R;
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			for (int k = 0; k < 4; k++)
				R.m[j][i] += A.m[j][k] * B.m[k][i];
	return R;
}

MATRIX4D operator*(MATRIX4D& M, float s) {
	MATRIX4D R;
	for (int i = 0; i < 16; i++)
		R.v[i] = M.v[i] * s;
	return R;
}

MATRIX4D operator*(float s, MATRIX4D& M) {
	return M*s;
}

MATRIX4D operator/(MATRIX4D& M, float s) {
	s = 1.0f / s;
	return M*s;
}

MATRIX4D Transpose(MATRIX4D& A)
{
	MATRIX4D MatTemp = { 0,0 };
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			MatTemp.m[j][i] = A.m[i][j];
	return MatTemp;
}

MATRIX4D LookAtRH(VECTOR4D & EyePos, VECTOR4D & Target, VECTOR4D & Up)
{
	VECTOR4D xDir, yDir, zDir;
	zDir = Normalize(EyePos - Target);
	xDir = Normalize(Cross3(Up, zDir));
	yDir = Cross3(zDir, xDir);

	MATRIX4D View = { xDir.x,	yDir.x,	zDir.x, 0,
						xDir.y, yDir.y, zDir.y, 0,
						xDir.z, yDir.z, zDir.z, 0,
						-Dot(xDir, EyePos), -Dot(yDir, EyePos), -Dot(zDir, EyePos), 1 };
	return View;
}

MATRIX4D LookAtLH(VECTOR4D & EyePos, VECTOR4D & Target, VECTOR4D & Up)
{
	VECTOR4D xDir, yDir, zDir;
	zDir = Normalize(Target - EyePos);
	xDir = Normalize(Cross3(Up, zDir));
	yDir = Cross3(zDir, xDir);

	MATRIX4D View = { xDir.x,	yDir.x,	zDir.x, 0,
		xDir.y, yDir.y, zDir.y, 0,
		xDir.z, yDir.z, zDir.z, 0,
		-Dot(xDir, EyePos), -Dot(yDir, EyePos), -Dot(zDir, EyePos), 1 };
	return View;
}

MATRIX4D PerspectiveFOVRH(float FOVY, float ratio, float zNear, float zFar)
{
	float ang = FOVY / 2;

	float h = cos(ang) / sin(ang);
	float w = h / ratio;
	MATRIX4D P = { w,	0,	0,								0,
					0,	h,	0,								0,
					0,	0,	zFar / (zNear - zFar),			-1,
					0,	0,	zNear * zFar / (zNear - zFar),	0 };
	return P;
}

MATRIX4D PerspectiveFOVLH(float FOVY, float ratio, float zNear, float zFar)
{
	float ang = FOVY / 2;

	float h = cos(ang) / sin(ang);
	float w = h / ratio;
	MATRIX4D P = { w,	0,	0,								0,
		0,	h,	0,								0,
		0,	0,	zFar / (zFar - zNear),			1,
		0,	0,	-zNear * zFar / (zFar - zNear),	0};
	return P;
}

float Det(MATRIX4D& A) {
	/*float det = A.m[1][1];
	for (int k = 1; k <= 3; k++)
	{
		int l = k + 1;
		for (int i = l; i <= 4; i++)
		{
			for (int j = l; j <= 3; j++)
				A.m[i][j] = (A.m[k][k] * A.m[i][j] - A.m[k][j] * A.m[i][k]) / A.m[k][k];
		}
		det = det*A.m[k + 1][k + 1];
	}*/
	float det = A.m00*(A.m11*(A.m22*A.m33 - A.m23*A.m32)
		- A.m12*(A.m21*A.m33 - A.m23*A.m31)
		+ A.m13*(A.m21*A.m32 - A.m22*A.m31))
		- A.m01*(A.m10*(A.m22*A.m33 - A.m23*A.m32)
			- A.m12*(A.m20*A.m33 - A.m23*A.m30)
			+ A.m13*(A.m20*A.m32 - A.m22*A.m30))
		+ A.m02*(A.m10*(A.m21*A.m33 - A.m23*A.m31)
			- A.m11*(A.m20*A.m33 - A.m23*A.m30)
			+ A.m13*(A.m20*A.m31 - A.m21*A.m30))
		- A.m03*(A.m10*(A.m21*A.m32 - A.m22*A.m31)
			- A.m11*(A.m20*A.m32 - A.m22*A.m30)
			+ A.m12*(A.m20*A.m31 - A.m21*A.m30));
	return det;
}

MATRIX4D Cofactor(MATRIX4D & A)
{
	MATRIX4D B;
	B.m00 = (A.m11*(A.m22*A.m33 - A.m23*A.m32)
				  - A.m12*(A.m21*A.m33 - A.m23*A.m31)
				  + A.m13*(A.m21*A.m32 - A.m22*A.m31));
	B.m01 = -(A.m10*(A.m22*A.m33 - A.m23*A.m32)
				  - A.m12*(A.m20*A.m33 - A.m23*A.m30)
				  + A.m13*(A.m20*A.m32 - A.m22*A.m30));
	B.m02 = (A.m10*(A.m21*A.m33 - A.m23*A.m31)
				  - A.m11*(A.m20*A.m33 - A.m23*A.m30)
				  + A.m13*(A.m20*A.m31 - A.m21*A.m30));
	B.m03 = -(A.m10*(A.m21*A.m32 - A.m22*A.m31)
				  - A.m11*(A.m20*A.m32 - A.m22*A.m30)
				  + A.m12*(A.m20*A.m31 - A.m21*A.m30));

	B.m10 = -(A.m01*(A.m22*A.m33 - A.m23*A.m32)
				  - A.m02*(A.m21*A.m33 - A.m23*A.m31)
				  + A.m03*(A.m21*A.m32 - A.m22*A.m31));
	B.m11 = (A.m00*(A.m22*A.m33 - A.m23*A.m32)
				  - A.m02*(A.m20*A.m33 - A.m23*A.m30)
				  + A.m03*(A.m20*A.m32 - A.m22*A.m30));
	B.m12 = -(A.m00*(A.m21*A.m33 - A.m23*A.m31)
				  - A.m01*(A.m20*A.m33 - A.m23*A.m30)
				  + A.m03*(A.m20*A.m31 - A.m21*A.m30));
	B.m13 = (A.m00*(A.m21*A.m32 - A.m22*A.m31)
				  - A.m01*(A.m20*A.m32 - A.m22*A.m30)
				  + A.m02*(A.m20*A.m31 - A.m21*A.m30));

	B.m20 = (A.m01*(A.m12*A.m33 - A.m13*A.m32)
				  - A.m02*(A.m11*A.m33 - A.m13*A.m31)
				  + A.m03*(A.m11*A.m32 - A.m12*A.m31));
	B.m21 = -(A.m00*(A.m12*A.m33 - A.m13*A.m32)
				  - A.m02*(A.m10*A.m33 - A.m13*A.m30)
				  + A.m03*(A.m10*A.m32 - A.m12*A.m30));
	B.m22 = (A.m00*(A.m11*A.m33 - A.m13*A.m31)
				  - A.m01*(A.m10*A.m33 - A.m13*A.m30)
				  + A.m03*(A.m10*A.m31 - A.m11*A.m30));
	B.m23 = -(A.m00*(A.m11*A.m32 - A.m12*A.m31)
				  - A.m01*(A.m10*A.m32 - A.m12*A.m30)
				  + A.m02*(A.m10*A.m31 - A.m11*A.m30));

	B.m30 = -(A.m01*(A.m12*A.m23 - A.m13*A.m22)
				  - A.m02*(A.m11*A.m23 - A.m13*A.m21)
				  + A.m03*(A.m11*A.m22 - A.m12*A.m21));
	B.m31 = (A.m00*(A.m12*A.m23 - A.m13*A.m22)
				  - A.m02*(A.m10*A.m23 - A.m13*A.m20)
				  + A.m03*(A.m10*A.m22 - A.m12*A.m20));
	B.m32 = -(A.m00*(A.m11*A.m23 - A.m13*A.m21)
				  - A.m01*(A.m10*A.m23 - A.m13*A.m20)
				  + A.m03*(A.m10*A.m21 - A.m11*A.m20));
	B.m33 = (A.m00*(A.m11*A.m22 - A.m12*A.m21)
				  - A.m01*(A.m10*A.m22 - A.m12*A.m20)
				  + A.m02*(A.m10*A.m21 - A.m11*A.m20));
	return B;
}

MATRIX4D InverseGJ(MATRIX4D& A) 
{
	int i, j, k, n , d;
	n = 4;
	MATRIX4D R = { 0,0 };
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			R.m[i][j] = A.m[i][j];

	for (i = 1; i <= n; i++)
		for (j = 1; j <= 2 * n; j++)
			if (j == (i + n))
				R.m[i][j] = 1;

	/************** partial pivoting **************/
	for (i = n; i>1; i--)
	{
		if (R.m[i - 1][1]<R.m[i][1])
			for (j = 1; j <= n * 2; j++)
			{
				d = R.m[i][j];
				R.m[i][j] = R.m[i - 1][j];
				R.m[i - 1][j] = d;
			}
	}
	/********** reducing to diagonal  matrix ***********/

	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n * 2; j++)
			if (j != i)
			{
				d = R.m[j][i] / R.m[i][i];
				for (k = 1; k <= n * 2; k++)
					R.m[j][k] -= R.m[i][k] * d;
			}
	}
	/************** reducing to unit matrix *************/
	for (i = 1; i <= n; i++)
	{
		d = R.m[i][i];
		for (j = 1; j <= n * 2; j++)
			R.m[i][j] = R.m[i][j] / d;
	}
	return R;
}

MATRIX4D Adjunt(MATRIX4D& A)
{
	MATRIX4D B = Cofactor(A);
	B = Transpose(B);
	return B;
}

MATRIX4D Inverse(MATRIX4D& A)
{
	float DetA = Det(A);
	if (DetA != 0)
	{
		MATRIX4D B = Adjunt(A);
		B = B / Det(A);
		return B;
	}
	return MATRIX4D{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
}

VECTOR4D operator*(MATRIX4D& M, VECTOR4D& V) {
	VECTOR4D R;
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			R.v[j] += M.m[j][i] * V.v[i];
	return R;
}

VECTOR4D operator*(VECTOR4D& V, MATRIX4D& M)
{
	VECTOR4D R;
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			R.v[j] += M.m[i][j] * V.v[i];
	return R;
}

VECTOR4D Cramer(MATRIX4D& M, VECTOR4D& V)
{
	float DetM = Det(M);
	if (DetM != 0)
	{
		MATRIX4D D0 = { V.x, M.m01, M.m02, M.m03,
						V.y, M.m11, M.m12, M.m13,
						V.z, M.m21, M.m22, M.m23,
						V.w, M.m31, M.m32, M.m33 };
		MATRIX4D D1 = { M.m00, V.x, M.m02, M.m03,
						M.m10, V.y, M.m12, M.m13,
						M.m20, V.z, M.m22, M.m23,
						M.m30, V.w, M.m32, M.m33 };
		MATRIX4D D2 = { M.m00, M.m01, V.x, M.m03,
						M.m10, M.m11, V.y, M.m13,
						M.m20, M.m21, V.z, M.m23,
						M.m30, M.m31, V.w, M.m33 };
		MATRIX4D D3 = { M.m00, M.m01, M.m02, V.x,
						M.m10, M.m11, M.m12, V.y,
						M.m20, M.m21, M.m22, V.z,
						M.m30, M.m31, M.m32, V.w };
		float d0 = Det(D0);
		float d1 = Det(D1);
		float d2 = Det(D2);
		float d3 = Det(D3);

		return VECTOR4D { d0 / DetM, d1 / DetM, d2 / DetM, d3 / DetM };
	}
	return VECTOR4D{ -1,-1,-1,-1 };
}

MATRIX4D Scaling(float x, float y, float z)
{
	return MATRIX4D(x,0,0,0,
					0,y,0,0,
					0,0,z,0,
					0,0,0,1);
}

MATRIX4D RotateXRH(float theta)
{
	MATRIX4D R(1);
	R.m22 = R.m11 = cosf(theta);
	R.m12 = -sinf(theta);
	R.m21 = -R.m12;
	/*R.m00 = R.m22 = cosf(theta);
	R.m12 = -sinf(theta);
	R.m21 = -R.m12;*/
	return R;
}

MATRIX4D RotateYRH(float theta)
{
	MATRIX4D R(1);
	R.m00 = R.m22 = cosf(theta);
	R.m20 = -sinf(theta);
	R.m02 = -R.m20;

	/*R.m00 = R.m22 = cosf(theta);
	R.m20 = -sinf(theta);
	R.m02 = -R.m20;*/
	return R;
}

MATRIX4D RotateZRH(float theta)
{
	MATRIX4D R(1);
	R.m11 = R.m00 = cosf(theta);
	R.m01 = -sinf(theta);
	R.m10 = -R.m01;

	/*R.m11 = R.m00 = cosf(theta);
	R.m01 = -sinf(theta);
	R.m10 = -R.m01;*/
	return R;
}



MATRIX4D Translation(float x, float y, float z)
{
	return MATRIX4D(1,0,0,0,
					0,1,0,0,
					0,0,1,0,
					x,y,z,1);
}
