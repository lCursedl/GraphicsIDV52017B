#ifndef UAD_PRIMITIVE_INSTANCE_H
#define UAD_PRIMITIVE_INSTANCE_H

#include "PrimitiveBase.h"
#include <d3dx9math.h>
#include "MATRIX4D.h"



class PrimitiveInst {
	public:
		void	CreateInstance(PrimitiveBase *pPrim, MATRIX4D *pVP) {
			pBase = pPrim;
			pViewProj = pVP;
			Position = Identity();
			Scale = Identity();
			RotationX = Identity();
			RotationY = Identity();
			RotationZ = Identity();
			Final = Identity();
			/*D3DXMatrixIdentity(&Position);
			D3DXMatrixIdentity(&Scale);
			D3DXMatrixIdentity(&RotationX);
			D3DXMatrixIdentity(&RotationY);
			D3DXMatrixIdentity(&RotationZ);
			D3DXMatrixIdentity(&RotationZ);
			D3DXMatrixIdentity(&Final);		*/	
		}

		void	TranslateAbsolute(float x, float y, float z);
		void	RotateXAbsolute(float ang);
		void	RotateYAbsolute(float ang);
		void	RotateZAbsolute(float ang);
		void	ScaleAbsolute(float sc);

		void	TranslateRelative(float x, float y, float z);
		void	RotateXRelative(float ang);
		void	RotateYRelative(float ang);
		void	RotateZRelative(float ang);
		void	ScaleRelative(float sc);

		void	Update();
		void	Draw();

		MATRIX4D		Position;
		MATRIX4D		Scale;
		MATRIX4D		RotationX;
		MATRIX4D		RotationY;
		MATRIX4D		RotationZ;
		MATRIX4D		Final;

		MATRIX4D		*pViewProj;
		
		/*D3DXMATRIX		Position;
		D3DXMATRIX		Scale;
		D3DXMATRIX		RotationX;
		D3DXMATRIX		RotationY;
		D3DXMATRIX		RotationZ;
		D3DXMATRIX		Final;*/

		//D3DXMATRIX		*pViewProj;

		PrimitiveBase	*pBase;
};
#endif