#pragma once
#define GRAVITY		-9.8f
#define CUBE_SIZE	5.0f
#include <PxPhysicsAPI.h>
#include <vector>

using namespace physx;

struct VECTOR4D;
class CPhysics
{
private:
	std::vector<PxRigidDynamic*> m_RDList;

	PxFoundation			*m_foundation = NULL;
	PxPhysics				*m_physics = NULL;
	PxScene					*m_scene = NULL;
	PxDefaultCpuDispatcher	*m_Dispatcher = NULL;
	PxCudaContextManager	*m_CudaContextManager = NULL;
	PxMaterial				*m_material = NULL;

	PxDefaultErrorCallback	m_defaultErrorCallback;
	PxDefaultAllocator 		m_defaultAllocatorCallback;

	float			m_gravity;
	float			m_size;
public:
	CPhysics();
	~CPhysics();

	void init();
	void update();
	void clear();

	PxRigidDynamic * CreateG(const PxTransform& t);
	std::vector<VECTOR4D> m_Actors();
};

