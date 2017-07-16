#include "PrimitiveInstance.h"

void PrimitiveInst::TranslateAbsolute(float x, float y, float z){
	
	Position = Translation(x, y, z);
	//D3DXMatrixTranslation(&Position, x, y, z);
}

void PrimitiveInst::RotateXAbsolute(float ang) {
	RotationX = RotateXRH(ang*(PI/10));
	//D3DXMatrixRotationX(&RotationX,D3DXToRadian(ang));
}

void PrimitiveInst::RotateYAbsolute(float ang) {
	RotationY = RotateYRH(ang*(PI / 10));
	//D3DXMatrixRotationY(&RotationY, D3DXToRadian(ang));
}

void PrimitiveInst::RotateZAbsolute(float ang) {
	RotationZ = RotateZRH(ang*(PI / 10));
	//D3DXMatrixRotationZ(&RotationZ, D3DXToRadian(ang));
}

void PrimitiveInst::ScaleAbsolute(float sc) {
	Scale = Scaling(sc, sc, sc);
	//D3DXMatrixScaling(&Scale,sc,sc,sc);
}

void PrimitiveInst::TranslateRelative(float x, float y, float z) {
	MATRIX4D tmp;
	tmp = Translation(x, y, z);
	Position *= tmp;
	/*D3DXMATRIX tmp;
	D3DXMatrixTranslation(&tmp, x, y, z);
	Position *= tmp;*/
}

void PrimitiveInst::RotateXRelative(float ang) {
	MATRIX4D tmp;
	tmp = RotateXRH(ang*(PI / 10));
	RotationX *= tmp;
	/*D3DXMATRIX tmp;
	D3DXMatrixRotationX(&tmp, D3DXToRadian(ang));
	RotationX *= tmp;*/
}

void PrimitiveInst::RotateYRelative(float ang) {
	MATRIX4D tmp;
	tmp = RotateYRH(ang*(PI / 10));
	RotationY *= tmp;
	/*D3DXMATRIX tmp;
	D3DXMatrixRotationY(&tmp, D3DXToRadian(ang));
	RotationY *= tmp;*/
}

void PrimitiveInst::RotateZRelative(float ang) {
	MATRIX4D tmp;
	tmp = RotateZRH(ang*(PI / 10));
	RotationZ *= tmp;

	/*D3DXMATRIX tmp;
	D3DXMatrixRotationZ(&tmp, D3DXToRadian(ang));
	RotationZ *= tmp;*/
}

void PrimitiveInst::ScaleRelative(float sc) {
	MATRIX4D tmp;
	tmp = Scaling(sc, sc, sc);
	Scale *= tmp;
	
	/*D3DXMATRIX tmp;
	D3DXMatrixScaling(&tmp, sc, sc, sc);
	Scale *= tmp;*/
}

void PrimitiveInst::Update() {
	Final = Scale*RotationX*RotationY*RotationZ*Position;
}

void PrimitiveInst::Draw(){
	pBase->Draw(&Final.m[0][0],&(*pViewProj).m[0][0]);
}
