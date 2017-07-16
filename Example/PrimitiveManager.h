#ifndef UAD_PRIMITIVEMANAGER_H
#define UAD_PRIMITIVEMANAGER_H

#include <vector>
#include <d3dx9math.h>
#include "MATRIX4D.h"
#include "PrimitiveBase.h"

class PrimitiveManager {
public:
	void SetVP(MATRIX4D *vp) {
		pVP = vp;
	}
	int  CreateTriangle();
	int	 CreateCube();
	int	 CreateMesh(char * fname);

	void DrawPrimitives();
	void DestroyPrimitives();
	PrimitiveBase*	GetPrimitive(unsigned int);

	std::vector<PrimitiveBase*> primitives;

	MATRIX4D *pVP;
	//D3DXMATRIX *pVP;
};

#endif