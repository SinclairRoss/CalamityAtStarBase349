#include "RigidBodyRegister.h"

#include "../../CollisionSolver.h"

#define OUTPUT_TEST_COUNT false

namespace RigidBodyRegister
{
	namespace Internal
	{
#if OUTPUT_TEST_COUNT
		int numComparisons;
#endif

		ColliderRegisterSet<RigidBody> Static;
		ColliderRegisterSet<RigidBody> Dynamic;

		template<typename ColliderA, typename ColliderB>
		void TestCollisions(std::vector<std::pair<RigidBody*, const ColliderA*>>& lhs, std::vector<std::pair<RigidBody*, const ColliderB*>>& rhs)
		{
			for (size_t a = 0; a < lhs.size(); ++a)
			{
				for (size_t b = 0; b < rhs.size(); ++b)
				{
					CollisionReport<RigidBody> report = CollisionDetection::CheckCollision<RigidBody>(*lhs[a].first, *lhs[a].second, *rhs[b].first, *rhs[b].second);
					if (report.CollisionDetected())
					{
						CollisionSolver::SolveCollision(report);
					}
#if OUTPUT_TEST_COUNT
					numComparisons++;
#endif
				}
			}
		}

		template<typename ColliderA>
		void TestCollisions(std::vector<std::pair<RigidBody*, const ColliderA*>>& list)
		{
			for (size_t a = 0; a < list.size(); ++a)
			{
				for (size_t b = a+1; b < list.size(); ++b)
				{
					CollisionReport<RigidBody> report = CollisionDetection::CheckCollision<RigidBody>(*list[a].first, *list[a].second, *list[b].first, *list[b].second);
					if (report.CollisionDetected())
					{
						CollisionSolver::SolveCollision(report);
					}

#if OUTPUT_TEST_COUNT
					numComparisons++;
#endif
				}
			}
		}

		ColliderRegisterSet<RigidBody>& GetRegister(float mass_inv)
		{
			return abs(mass_inv) > 0.001f ? Dynamic : Static;
		}
	}

	void DeregisterObject(const RigidBody& object, float mass_inv)
	{
		ColliderRegisterSet<RigidBody>& reg = Internal::GetRegister(mass_inv);
		reg.DeregisterObject(&object);
	}

	void RegisterObject(RigidBody& object, float mass_inv, Collider* collider)
	{
		if (Collider_Sphere* s = dynamic_cast<Collider_Sphere*>(collider))
		{
			RegisterObject(object, mass_inv, *s);
		}
		else if (Collider_AABB* b = dynamic_cast<Collider_AABB*>(collider))
		{
			RegisterObject(object, mass_inv, *b);
		}
	}

	void RegisterObject(RigidBody& object, float mass_inv, const Collider_Sphere& collider)
	{
		Internal::GetRegister(mass_inv).RegisterObject(&object, &collider);
	}

	void RegisterObject(RigidBody& object, float mass_inv, const Collider_AABB& collider)
	{
		Internal::GetRegister(mass_inv).RegisterObject(&object, &collider);
	}

	void UpdatePhysics()
	{

#if OUTPUT_TEST_COUNT
		Internal::numComparisons = 0;
#endif

		std::vector<std::pair<RigidBody*, const Collider_AABB*>> aabb_static = Internal::Static.GetSet<std::pair<RigidBody*, const Collider_AABB*>>();
		std::vector<std::pair<RigidBody*, const Collider_Sphere*>> sphere_static = Internal::Static.GetSet<std::pair<RigidBody*, const Collider_Sphere*>>();

		std::vector<std::pair<RigidBody*, const Collider_AABB*>> aabb_dynamic = Internal::Dynamic.GetSet<std::pair<RigidBody*, const Collider_AABB*>>();
		std::vector<std::pair<RigidBody*, const Collider_Sphere*>> sphere_dynamic = Internal::Dynamic.GetSet<std::pair<RigidBody*, const Collider_Sphere*>>();

		Internal::TestCollisions<Collider_AABB, Collider_AABB>(aabb_static, aabb_dynamic);
		Internal::TestCollisions<Collider_Sphere, Collider_Sphere>(sphere_static, sphere_dynamic);
		Internal::TestCollisions<Collider_AABB, Collider_Sphere>(aabb_static, sphere_dynamic);
		Internal::TestCollisions<Collider_Sphere, Collider_AABB>(sphere_static, aabb_dynamic);

		Internal::TestCollisions<Collider_AABB>(aabb_dynamic);
		Internal::TestCollisions<Collider_Sphere>(sphere_dynamic);
		Internal::TestCollisions<Collider_Sphere, Collider_AABB>(sphere_dynamic, aabb_dynamic);

#if OUTPUT_TEST_COUNT
		printf("Num Comparisons: %i\n", Internal::numComparisons);
#endif

        for (std::pair<RigidBody*, const Collider_AABB*>& pair : aabb_dynamic)
        {
            pair.first->Update();
        }

        for (std::pair<RigidBody*, const Collider_Sphere*>& pair : sphere_dynamic)
        {
            pair.first->Update();
        }
	}

    const ColliderRegisterSet<RigidBody>& GetRigidBodies_Static() { return Internal::Static; }
    const ColliderRegisterSet<RigidBody>& GetRigidBodies_Dynamic() { return Internal::Dynamic; }
}

#undef OUTPUT_TEST_COUNT