#include "Application.h"

#define LIGHT_COUNT	64

void TestApp::InitVars() {
	DtTimer.Init();
	Position = VECTOR4D(0.0f, 0.0f, 0.0f);
	Orientation = VECTOR4D(0.0f, 0.0f, 0.0f);
	Scaling = VECTOR4D(1.0f, 1.0f, 1.0f);

	MyCamera.Init(VECTOR4D(0.0f, 1.0f, 1.0f), 45.0f * (3.141592f / 180.0f), 1280.0f / 720.0f, 1.0f, 8000.0f, false);
	MyCamera.Speed = 10.0f;
	MyCamera.Eye = VECTOR4D(0.0f, 9.75f, -31.0f, 0.0f);
	MyCamera.Pitch = 0.14f;
	MyCamera.Roll = 0.0f;
	MyCamera.Yaw = 0.020f;
	MyCamera.Update(0.0f);

	LightCamera.Init(VECTOR4D(0.0f, 1.0f, 10.0f, 0.0f), 60.0f * (3.141592f / 180.0f), 1.0f, 0.1f, 8000.0f, false);
	LightCamera.Speed = 10.0f;
	LightCamera.Eye = VECTOR4D(0.0f, 25.0f, -40.0f, 0.0f);
	LightCamera.Pitch = 0.14f;
	LightCamera.Roll = 0.0f;
	LightCamera.Yaw = 0.020f;
	LightCamera.Update(0.0f);

	pCam = &MyCamera;
	MyScene.CreateCamera(pCam);
	MyScene.AmbientClr = (.5f, .5f, .5f, 1.0f);
	MyScene.CreateLightCamera(&LightCamera);

	for (int i = 0; i < LIGHT_COUNT; i++)
	{
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		MyScene.CreateLight(VECTOR4D(5.f, 0.0f, 0.0f), VECTOR4D(r, g, b), true);
	}


}

void TestApp::CreateAssets() {
	PrimitiveMgr.SetVP(&VP);

	int indexI = PrimitiveMgr.CreateMesh("CerdoNuevo.X");
	int indexI2 = PrimitiveMgr.CreateCube();
	Models[0].CreateInstance(PrimitiveMgr.GetPrimitive(indexI), &VP);
	Cubes[0].CreateInstance(PrimitiveMgr.GetPrimitive(indexI2), &VP);

	MATRIX4D View;
	VECTOR4D Pos		= VECTOR4D(0.0f,1.0f,5.0f);
	VECTOR4D Up			= VECTOR4D(0.0f,1.0f,0.0f);
	VECTOR4D LookAt		= VECTOR4D(0.0001f, 0.0001f, 0.0001f) - Pos;
	View = LookAtRH(Pos, LookAt, Up);

	MATRIX4D Proj = PerspectiveFOVRH(PI, (1280.0f / 720.0f), 0.1, 1000);

	//	D3DXMatrixOrthoRH(&Proj, 1280.0f / 720.0f, 1.0f , 0.1, 100.0f);
	VP = View*Proj;

	PrimitiveMgr.SetSceneProps(&MyScene);
}

void TestApp::DestroyAssets() {
	PrimitiveMgr.DestroyPrimitives();
}

void TestApp::OnUpdate() {
	DtTimer.Update();
	Delta = DtTimer.GetDTSecs();

	OnInput();

	pCam->Update(Delta);
	VP = pCam->VP;

	Models[0].TranslateAbsolute(Position.x, Position.y, Position.z);
	Models[0].RotateXAbsolute(Orientation.x);
	Models[0].RotateYAbsolute(Orientation.y);
	Models[0].RotateZAbsolute(Orientation.z);
	Models[0].ScaleAbsolute(Scaling.x);
	Models[0].Update();	

	Cubes[0].TranslateAbsolute(Position.x, Position.y, Position.z);
	Cubes[0].RotateXAbsolute(Orientation.x);
	Cubes[0].RotateYAbsolute(Orientation.y);
	Cubes[0].RotateZAbsolute(Orientation.z);
	Cubes[0].ScaleAbsolute(Scaling.x);
	Cubes[0].TranslateRelative(-MyScene.LightContainer[0].Position.x, -MyScene.LightContainer[0].Position.y, -MyScene.LightContainer[0].Position.z);
	Cubes[0].Update();
	
	OnDraw();
}

void TestApp::OnDraw() {
	pFramework->pVideoDriver->Clear();
	Models[0].Draw();
	Cubes[0].Draw();
	pFramework->pVideoDriver->SwapBuffers();
}

void TestApp::OnInput() {
	
	if (IManager.PressedKey(SDLK_UP)) {
		MyScene.LightContainer[0].Position.y -= 1.0f * DtTimer.GetDTSecs();
		//Position.y += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_DOWN)) {
		MyScene.LightContainer[0].Position.y += 1.0f * DtTimer.GetDTSecs();
		//Position.y -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_LEFT)) {
		MyScene.LightContainer[0].Position.x -= 1.0f * DtTimer.GetDTSecs();
		//Position.x -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_RIGHT)) {
		MyScene.LightContainer[0].Position.x += 1.0f * DtTimer.GetDTSecs();
		//Position.x += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_z)) {
		Position.z -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_x)) {
		Position.z += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP_PLUS)) {
		Scaling.x += 1.0f*DtTimer.GetDTSecs();
		Scaling.y += 1.0f*DtTimer.GetDTSecs();
		Scaling.z += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP_MINUS)) {
		Scaling.x -= 1.0f*DtTimer.GetDTSecs();
		Scaling.y -= 1.0f*DtTimer.GetDTSecs();
		Scaling.z -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP5)) {
		Orientation.x -= 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP6)) {
		Orientation.x += 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP2)) {
		Orientation.y -= 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP3)) {
		Orientation.y += 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP0)) {
		Orientation.z -= 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP_PERIOD)) {
		Orientation.z += 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_w))
	{
		pCam->MoveFront(Delta);
	}

	if (IManager.PressedKey(SDLK_s))
	{
		pCam->MoveBack(Delta);
	}

	if (IManager.PressedKey(SDLK_a))
	{
		pCam->MoveRight(Delta);
	}

	if (IManager.PressedKey(SDLK_d))
	{
		pCam->MoveLeft(Delta);
	}

	float yaw = 0.005f*static_cast<float>(IManager.xDelta);
	pCam->MoveYaw(yaw);

	float pitch = 0.005f*static_cast<float>(IManager.yDelta);
	pCam->MovePitch(pitch);
}

void TestApp::OnPause() {

}

void TestApp::OnResume() {

}

void TestApp::OnReset() {

}