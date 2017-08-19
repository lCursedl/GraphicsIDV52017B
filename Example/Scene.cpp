#include "Scene.h"

//void CScene::CreateLight(VECTOR4D Pos, VECTOR4D Clr)
//{
//	Light L;
//	L.Position = Pos;
//	L.Color = Clr;
//	LightContainer.push_back(L);
//}

void CScene::CreateCamera(CCamera * MyPCamera)
{
	CameraContainer.push_back(MyPCamera);
}