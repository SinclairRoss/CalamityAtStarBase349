#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "AStarNode.h"
#include "Map\MapElements\MapElement.h"
#include "DebugTemplates\DebugTemplates.h"

namespace AStar
{
    namespace
    {
        template<typename T>
        void OrderedInsert(std::vector<AStarNode<T>*>& list, AStarNode<T>& node)
        {
            float nodeHeuristic = node.GetHeuristic();

            std::vector<AStarNode<T>*>::iterator iter = std::find_if(list.begin(), list.end(), [nodeHeuristic](AStarNode<T>* node) 
            {
                return nodeHeuristic <= node->GetHeuristic();
            });

            list.insert(iter, &node);
        }

        template<typename T>
        void RemoveElement(std::vector<AStarNode<T>*>& list, AStarNode<T>& node)
        {
            std::vector<AStarNode<T>*>::iterator iter = std::find(list.begin(), list.end(), &node);
            if (iter != list.end())
            {
                list.erase(iter);
            }
        }
    }

    template <typename T, bool isAnimated = false>
    std::vector<T*> Path(AStarNode<T>& origin, AStarNode<T>& destination)
    {
        std::vector<T*> path;

        if (&origin == &destination)
        {
          //  printf("AStar: Origin == Destination\n");
        }
        else
        {
            std::vector<AStarNode<T>*> openList;
            std::vector<AStarNode<T>*> closedList;

            AStarNode<T>* pFinalNode = nullptr;

            origin.InvestigateNode<T>(nullptr, &destination);
            openList.emplace_back(&origin);

            while (!openList.empty() && pFinalNode == nullptr)
            {
                AStarNode<T>* pActiveNode = openList.front();
                openList.erase(openList.begin());
                closedList.push_back(pActiveNode);

                OnSearched<T, isAnimated>(pActiveNode);

                pActiveNode->ForeachNeighbour([&](AStarNode<T>* pNeighbour)
                {
                    if (pNeighbour == &destination) // If we have found the destination.
                    {
                        pNeighbour->SetParent(pActiveNode);
                        pFinalNode = pNeighbour;
                    }
                    else // If we are still looking.
                    {
                        if (std::find(closedList.begin(), closedList.end(), pNeighbour) == closedList.end())    // If we haven't searched this neighbour yet.
                        {
                            if (pNeighbour->InvestigateNode<T>(pActiveNode, &destination))
                            {
                                RemoveElement(openList, *pNeighbour);
                                OrderedInsert<T>(openList, *pNeighbour);
                                OnFound<T, isAnimated>(pNeighbour);
                            }
                        }
                    }
                });
            }

            if (pFinalNode != nullptr)
            {
                AStarNode<T>* activeNode = pFinalNode;
                while (activeNode != nullptr)
                {
                    path.push_back(&activeNode->Data());
                    activeNode = activeNode->GetParentNode();
                }
            }

            for (AStarNode<T>* pNode : openList) { pNode->CleanSearchData(); }
            for (AStarNode<T>* pNode : closedList) { pNode->CleanSearchData(); }

            OnPathFound<T, isAnimated>(path);
        }

        return path;
    }
}