#include "Camera.h"

const VECTOR4D CCamera::LookConstCameraSpace = VECTOR4D(0.0f, 0.0f, 1.0f);
const VECTOR4D CCamera::RIghtConstCameraSPace = VECTOR4D(1.0f, 0.0f, 0.0f);
const VECTOR4D CCamera::UpConstCameraSpace = VECTOR4D(0.0f, 1.0f, 0.0f);

CCamera::CCamera()
{
	Reset();
}


CCamera::~CCamera()
{
}

void CCamera::Init(VECTOR4D Pos, float FOV, float Ratio, float NP, float FP, bool LF)
{
	this->Eye = Pos;
	this->FOV = FOV;
	this->AR = Ratio;
	this->NearPlane = NP;
	this->FarPlane = FP;
	this->LeftHanded = LF;

	CreateProjection();
}

void CCamera::CreateProjection()
{
	if (LeftHanded)
	{
		Projection = PerspectiveFOVLH(FOV, AR, NearPlane, FarPlane);
	}
	else
	{
		Projection = PerspectiveFOVRH(FOV, AR, NearPlane, FarPlane);
	}
}

void CCamera::SetLookAt(VECTOR4D v)
{
	Look = v - Eye;
	Normalize(Look);
	Pitch = atan2f(-Look.y, -Look.z);
	Yaw = atan2f(-Look.x, Look.z);

	Update(1.0f / 60.0f);
}

void CCamera::MoveFront(float DT)
{
	Velocity.z += Speed * DT;
}

void CCamera::MoveBack(float DT)
{
	Velocity.z -= Speed * DT;
}

void CCamera::MoveLeft(float DT)
{
	Velocity.x -= Speed * DT;
}

void CCamera::MoveRight(float DT)
{
	Velocity.x += Speed * DT;
}

void CCamera::MoveYaw(float f)
{
	if (MaxYaw != 0.0f)
	{
		if ((Yaw + f) > MaxPitch || (Yaw + f) > -MaxPitch)
		{
			return;
		}
	}
	Yaw += f;
}

void CCamera::MovePitch(float f)
{
	if (MaxPitch != 0.0f)
	{
		if ((Pitch + f) > MaxPitch || (Pitch + f) < -MaxPitch)
		{
			return;
		}
	}
	Pitch += f;
}

void CCamera::MoveRoll(float f)
{
	if (MaxRoll != 0.0f)
	{
		if ((Roll + f) > MaxRoll || (Roll + f) < -MaxRoll)
		{
			return;
		}
	}
	Roll += f;
}

void CCamera::SetFov(float f)
{
	this->FOV = f;
	CreateProjection();
}

void CCamera::SetRatio(float f)
{
	this->AR = f;
	CreateProjection();
}

void CCamera::SetPlanes(float near, float far)
{
	this->NearPlane = near;
	this->FarPlane = far;
	CreateProjection();
}

void CCamera::Update(float DT)
{
	MATRIX4D XM, YM, ZM, TM;

	XM = RotateXRH(-Pitch);
	YM = RotateYRH(-Yaw);
	ZM = RotateZRH(-Roll);

	View = ZM * YM * XM;

	MATRIX4D TransposeM = Transpose(View);
	XVecTransformNormalRH(Look, LookConstCameraSpace, TransposeM);
	XVecTransformNormalRH(Up, UpConstCameraSpace, TransposeM);
	XVecTransformNormalRH(Right, RIghtConstCameraSPace, TransposeM);

	Normalize(Look);
	Normalize(Up);
	Normalize(Right);

	VECTOR4D ActualVel = Right * Velocity.x + Up * Velocity.y + Look * Velocity.z;
	Velocity -= Velocity * Friction;
	Eye += ActualVel;
	
	VECTOR4D TransformEye = Eye;
	/*TransformEye.x = -Eye.x;
	TransformEye.y = -Eye.y;
	TransformEye.z = -Eye.z;
	TransformEye.w = Eye.w;*/
	XMatTranslation(TM, TransformEye);
	View = TM * View;
	VP = View * Projection;
}

void CCamera::Reset()
{
	Eye = VECTOR4D(0.0f, 0.0f, 0.0f);
	Velocity = VECTOR4D(0.0f, 0.0f, 0.0f);
	FOV = (45.0f * (3.141592 / 180));
	NearPlane = 0.01f;
	FarPlane = 1000.0f;
	AR = 1.0f;
	Speed = 5000.0;
	Yaw = 0.0f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Friction = 0.1f;
	MaxRoll = 0.0f;
	MaxPitch = (89.0f *(3.141592/180));
	MaxYaw = 0.0f;
	LeftHanded = true;
}
