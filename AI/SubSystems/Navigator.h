#pragma once

#include "Core\Math\Vector.h"
#include "Characters\Character.h"
#include "Map\Map.h"

class Navigator
{
    public:
        Navigator::Navigator(Character& puppet, Map& map);

        bool SetDestination(Vector2& destination);
        bool SetDestination(Interactable& interactable);

        void Update();

    private:
        Character* m_Puppet;
        Map* m_Map;

        std::vector<MapElement_Floor*> m_Path;

        const float m_NodeReachedThreshold_Sqr;
};