#pragma once

#include "Utils/ColliderRegisterSet.h"

class RigidBody;

namespace RigidBodyRegister
{
	namespace Internal
	{
		extern ColliderRegisterSet<RigidBody> Static;
		extern ColliderRegisterSet<RigidBody> Dynamic;
	}

    extern const ColliderRegisterSet<RigidBody>& GetRigidBodies_Static();
    extern const ColliderRegisterSet<RigidBody>& GetRigidBodies_Dynamic();

    extern void RegisterObject(RigidBody& object, float mass_inv, const Collider_AABB& collider);
	extern void RegisterObject(RigidBody& object, float mass_inv, const Collider_Sphere& collider);
	extern void RegisterObject(RigidBody& object, float mass_inv, Collider* collider);

	extern void DeregisterObject(const RigidBody& object, float mass_inv);
	extern void UpdatePhysics();
}
