#include "CollisionSolver.h"

namespace CollisionSolver
{

	namespace
	{
		void PositionalCorrection(const CollisionReport<RigidBody>& report)
		{
			RigidBody* body_A = report.GetObjectA();
			RigidBody* body_B = report.GetObjectB();

			Vector2 normal = report.GetNormal();
			float percent = 0.2f;
			float slop = 0.1f;
			float penetrationDepth = report.GetPenetrationDepth();

			Vector2 correction = normal * percent * (std::max(penetrationDepth - slop, 0.0f) / (body_A->GetMass_Inv() + body_B->GetMass_Inv()));

			body_A->Translate(-correction * body_A->GetMass_Inv());
			body_B->Translate(correction * body_B->GetMass_Inv());
		}
	}

	void SolveCollision(const CollisionReport<RigidBody>& report)
	{
		RigidBody* body_A = report.GetObjectA();
		RigidBody* body_B = report.GetObjectB();

		Vector2 normal = report.GetNormal();

		Vector2 velocity_relative = body_B->GetVelocity() - body_A->GetVelocity();
		float relativeSpeedAlongNorm = velocity_relative.Dot(normal);

        // < 0 i.e heading towards eachother.
		if (relativeSpeedAlongNorm < 0.0f)
		{
 			float restitution = std::min(body_A->GetBounciness(), body_B->GetBounciness());
			float impulseScalar = ((1.0f + restitution) * -relativeSpeedAlongNorm) / (body_A->GetMass_Inv() + body_B->GetMass_Inv());
			Vector2 impulse = normal * impulseScalar;

			body_A->ApplyForce_Instant(-impulse);
			body_B->ApplyForce_Instant(impulse);
		}

        PositionalCorrection(report);
	}
}