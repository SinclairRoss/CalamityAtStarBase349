#pragma once

#include <vector>

#include "Map\MapElements\Floor\MapElement_Floor.h"
#include "Core/Physics/Collisions/ColliderRegister/RigidBodyRegister.h"

namespace AStar
{
    void TrimPath(std::vector<MapElement_Floor*>& path, float characterBoundRadius)
    {
        MapElement_Floor& activeTile = *path[0];
        for (std::vector<MapElement_Floor*>::iterator iter = path.begin()+1; iter != path.end(); ++iter)
        {
            const ColliderRegisterSet<RigidBody>& staticBodies = RigidBodyRegister::GetRigidBodies_Static();
        }
    }
}