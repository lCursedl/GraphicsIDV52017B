#include <Core.h>
#include <PrimitiveManager.h>
#include <PrimitiveInstance.h>
#include "Scene.h"

#include <d3dx9math.h>
#include <Timer.h>

class TestApp : public AppBase {
public:
	TestApp() : AppBase() {}
	void InitVars();
	void CreateAssets();
	void DestroyAssets();

	void OnUpdate();
	void OnDraw();
	void OnInput();

	void OnPause();
	void OnResume();

	void OnReset();

	PrimitiveManager PrimitiveMgr;
	PrimitiveInst	Cubes[10];
	PrimitiveInst	Triangle[10];
	PrimitiveInst	Models[10];

	CCamera			MyCamera;
	CCamera			*pCam;
	CCamera			LightCamera;

	VECTOR4D		Position;
	VECTOR4D		Orientation;
	VECTOR4D		Scaling;
	VECTOR4D		WorldTransform;

	MATRIX4D		View;
	MATRIX4D		Projection;
	MATRIX4D		VP;

	CScene			MyScene;

	Timer			DtTimer;
	float			Delta;
};