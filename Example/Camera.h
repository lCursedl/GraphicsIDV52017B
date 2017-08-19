#pragma once
#include "MATRIX4D.h"

class CCamera
{
public:
	CCamera();
	~CCamera();

	void Init(VECTOR4D Pos, float FOV,  float Ratio, float NP, float FP, bool LF = true);
	void CreateProjection();
	void SetLookAt(VECTOR4D v);
	void MoveFront(float DT);
	void MoveBack(float DT);
	void MoveLeft(float DT);
	void MoveRight(float DT);

	void MoveYaw(float f);
	void MovePitch(float f);
	void MoveRoll(float f);

	void SetFov(float f);
	void SetRatio(float f);
	void SetPlanes(float near, float far);

	void Update(float DT);
	void Reset();

	VECTOR4D Eye, Look, Right, Up;

	VECTOR4D Velocity;

	float FOV, AR, NearPlane, FarPlane;

	float Yaw, Pitch, Roll, MaxYaw, MaxPitch, MaxRoll;

	float Speed, Friction;

	bool LeftHanded;

	MATRIX4D Position, RotateX, RotateY, RotateZ;

	MATRIX4D View, Projection, VP;

	static const VECTOR4D LookConstCameraSpace;
	static const VECTOR4D RIghtConstCameraSPace;
	static const VECTOR4D UpConstCameraSpace;
};