#pragma once

#include <stack>

#include "Core\Utils\ColourLibrary.h"
#include "Map\MapElements\MapElement.h"
#include "../AStarNode.h"

namespace AStar
{
    namespace
    {
        template <typename T, bool isAnimated> void OnFound(AStarNode<T>* pNode) {}
        template <typename T, bool isAnimated> void OnSearched(AStarNode<T>* pNode) {}
        template <typename T, bool isAnimated> void OnPathFound(std::vector<T*> path) {}

        template <>
        void OnFound<MapElement_Floor, true>(AStarNode<MapElement_Floor>* pNode)
        {
            pNode->Data().GetSprite().SetColour(ColourLibrary::Cyan);
        }

        template <>
        void OnSearched<MapElement_Floor, true>(AStarNode<MapElement_Floor>* pNode)
        {
            pNode->Data().GetSprite().SetColour(ColourLibrary::SuperBlue);
        }

        template<>
        void OnPathFound<MapElement_Floor, true>(std::vector<MapElement_Floor*> path)
        {
            while (!path.empty())
            {
                path.back()->GetSprite().SetColour(ColourLibrary::SexyOrange);
                path.pop_back();
            }
        }
    }
}