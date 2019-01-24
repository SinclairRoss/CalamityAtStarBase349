#pragma once

#include <algorithm>

#include "RigidBody.h"
#include "Collisions\CollisionDetection\CollisionReport.h"

namespace CollisionSolver
{
	namespace
	{
		extern void PositionalCorrection(const CollisionReport<RigidBody>& report);
	}

	extern void SolveCollision(const CollisionReport<RigidBody>& report);
}