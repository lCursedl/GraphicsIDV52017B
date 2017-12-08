#include "Physics.h"
#include <iostream>
#include "MATRIX4D.h"

CPhysics::CPhysics()
{
}


CPhysics::~CPhysics()
{
}

void CPhysics::init()
{
	m_foundation = PxCreateFoundation(PX_FOUNDATION_VERSION, m_defaultAllocatorCallback, m_defaultErrorCallback);
	if (!m_foundation)
	{
		return;
	}

	m_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_foundation, PxTolerancesScale(), true);
	if (!m_physics)
	{
		return;
	}
	PxSceneDesc MySceneDesc(m_physics->getTolerancesScale());
	MySceneDesc.gravity = PxVec3(0.0f, GRAVITY, 0.0f);
	m_Dispatcher = PxDefaultCpuDispatcherCreate(0);
	MySceneDesc.cpuDispatcher = m_Dispatcher;
	MySceneDesc.filterShader = PxDefaultSimulationFilterShader;

	m_scene = m_physics->createScene(MySceneDesc);
	m_material = m_physics->createMaterial(0.5f, 0.5f, 0.6f);

	PxRigidStatic * Plane = PxCreatePlane(*m_physics, PxPlane(0, 1, 0, 0), *m_material);
	m_scene->addActor(*Plane);
}

void CPhysics::update()
{
	m_scene->simulate(1.0f / 60.0f);
	m_scene->fetchResults(true);
}

void CPhysics::clear()
{
	m_scene->release();
	m_Dispatcher->release();
	m_physics->release();
	m_foundation->release();
}

PxRigidDynamic * CPhysics::CreateG(const PxTransform & t)
{
	PxRigidDynamic * D = PxCreateDynamic(*m_physics, t, PxBoxGeometry(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE), *m_material, 10.0f);
	D->setAngularDamping(0.5f);
	D->setLinearVelocity(PxVec3(0.1f));
	m_scene->addActor(*D);
	m_RDList.push_back(D);
	return D;
}

std::vector<VECTOR4D> CPhysics::m_Actors()
{
	std::vector<VECTOR4D> Positions;
	for (unsigned int i = 0; i < m_RDList.size(); i++)
	{
		Positions.push_back(VECTOR4D{ (m_RDList[i]->getGlobalPose()).p.x, (m_RDList[i]->getGlobalPose()).p.y, (m_RDList[i]->getGlobalPose()).p.z });
	}
	return Positions;
}