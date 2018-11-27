#ifndef NEO_PLATFORMPHYSICSCONTEXT_H
#define NEO_PLATFORMPHYSICSCONTEXT_H

#include <btBulletDynamicsCommon.h>

namespace Neo 
{

class Level;
class PlatformRigidbodyPhysicsBehavior;
class PlatformPhysicsContext
{
	friend PlatformRigidbodyPhysicsBehavior;
	btBroadphaseInterface* m_broadphase = nullptr;
	btDefaultCollisionConfiguration* m_collisionConfig = nullptr;
	btCollisionDispatcher* m_collisionDispatcher = nullptr;
	btSequentialImpulseConstraintSolver* m_solver = nullptr;
	btDiscreteDynamicsWorld* m_world = nullptr;
	
protected:
	btDiscreteDynamicsWorld* getWorld() { return m_world; }
	
public:
	void begin();
	virtual void update(float dt);
	void end();
};

}

#endif // NEO_PLATFORMPHYSICSCONTEXT_H