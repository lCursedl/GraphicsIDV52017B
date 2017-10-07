#include "Scene.h"

void CScene::CreateLight(VECTOR4D Pos, VECTOR4D Clr, bool active)
{
	Light L;
	L.Position = Pos;
	L.Color = Clr;
	L.Enable = (int)active;
	LightContainer.push_back(L);
}

void CScene::DeleteLight(unsigned int ind)
{
	if (ind < 0 || ind >= LightContainer.size())
		return;
	LightContainer.erase(LightContainer.begin() + ind);
}

void CScene::SetLightPos(unsigned int ind, VECTOR4D Pos)
{
	if (ind < 0 || ind >= LightContainer.size())
		return;
	LightContainer[ind].Position = Pos;
}

void CScene::CreateCamera(CCamera * MyPCamera)
{
	CameraContainer.push_back(MyPCamera);
}

void CScene::DeleteCamera(unsigned int ind)
{
	if (ind < 0 || ind >= CameraContainer.size())
		return;
	CameraContainer.erase(CameraContainer.begin() + ind);
}

void CScene::CreateLightCamera(CCamera * LightCam)
{
	CameraLightCont.push_back(LightCam);
}

void CScene::DeleteLightCamera(unsigned int ind)
{
	if (ind < 0 || ind >= CameraLightCont.size())
		return;
	CameraLightCont.erase(CameraLightCont.begin() + ind);
}