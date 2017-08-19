#ifndef UAD_PRIMITIVEBASE_H
#define UAD_PRIMITIVEBASE_H

#include "Scene.h"

class PrimitiveBase {
public:
	virtual void Create() = 0;
	virtual void Create(char *) = 0;
	virtual void Transform(float *t) = 0;
	virtual void Draw(float *t,float *vp) = 0;
	virtual void Destroy() = 0;

	void SetSceneProps(CScene *S)
	{
		pScProp = S;
	}
	CScene *pScProp;
};
#endif