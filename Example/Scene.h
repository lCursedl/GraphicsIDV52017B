#pragma once
#include "MATRIX4D.h"
#include "Camera.h"
#include <vector>
//struct Light
//{
//	Light() {};
//	VECTOR4D Position;
//	VECTOR4D Color;
//};

struct CScene
{
public:
	CScene() : ActiveCam(0), ActiveLight(1){}

	/*void CreateLight(VECTOR4D Pos, VECTOR4D Clr);*/
	void CreateCamera(CCamera * MyPCamera);

	/*std::vector<Light>LightContainer;*/
	std::vector<CCamera*>CameraContainer;

	int ActiveCam;
	int ActiveLight;
};