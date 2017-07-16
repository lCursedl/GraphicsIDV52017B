#include <Core.h>
#include <PrimitiveManager.h>
#include <PrimitiveInstance.h>

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

	VECTOR4D		Position;
	VECTOR4D		Orientation;
	VECTOR4D		Scaling;
	VECTOR4D		WorldTransform;

	/*D3DXVECTOR3		Position;
	D3DXVECTOR3		Orientation;
	D3DXVECTOR3		Scaling;
	D3DXMATRIX		WorldTransform;*/

	MATRIX4D		View;
	MATRIX4D		Projection;
	MATRIX4D		VP;
	/*D3DXMATRIX		View;
	D3DXMATRIX		Projection;
	D3DXMATRIX		VP;*/

	Timer			DtTimer;
};