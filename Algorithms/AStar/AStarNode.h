#pragma once

#include <limits>
#include <functional>
#include <vector>

#include "Map\MapElements\Floor\MapElement_Floor.h"

template <typename T>
class AStarNode
{
    public:
        AStarNode(T& data) :
            m_Neighbours(),
            m_Data(&data),
            m_ParentNode(nullptr),
            m_Cost(std::numeric_limits<float>::max()),
            m_ToDestination(std::numeric_limits<float>::max()),
            m_Heuristic(std::numeric_limits<float>::max())
        {}

        AStarNode(const AStarNode<T>&) = default;
        AStarNode& operator=(const AStarNode<T>&) = default;
        AStarNode(AStarNode<T>&&) noexcept = default;
        AStarNode& operator=(AStarNode&&) noexcept = default;
      
        T& Data() { return *m_Data; }
        const T& Data() const { return *m_Data; }

        void SetParent(AStarNode<T>* parent) { m_ParentNode = parent; }
        const AStarNode<T>* GetParentNode() const { return m_ParentNode; }
        AStarNode<T>* GetParentNode() { return m_ParentNode; }
   
        float GetHeuristic() const { return m_Heuristic; }
        float GetCost() const { return m_Cost; }
        float GetToDestination() const { return m_ToDestination; }

        void AddNeighbour(AStarNode<T>& neighbour)
        {
            m_Neighbours.reserve(m_Neighbours.size() + 1);
            m_Neighbours.emplace_back(&neighbour);
        }

        void ForeachNeighbour(std::function<void(const AStarNode<T>*)> func) const {  for (const AStarNode<T>* node : m_Neighbours) { func(node); } }
        void ForeachNeighbour(std::function<void(AStarNode<T>*)> func)  { for (AStarNode<T>* node : m_Neighbours) { func(node); } }

        void CleanSearchData()
        {
            m_ParentNode = nullptr;
            m_Cost = std::numeric_limits<float>::max();
            m_ToDestination = std::numeric_limits<float>::max();
            m_Heuristic = std::numeric_limits<float>::max();
        }

    private:
        std::vector<AStarNode<T>*> m_Neighbours;
        T* m_Data;

        // Search Data
        AStarNode<T>* m_ParentNode;
        float m_Cost;
        float m_ToDestination;
        float m_Heuristic;

    public:
        template<typename T>
        bool InvestigateNode(AStarNode<T>* parent, AStarNode<T>* destination)
        {
            printf("No heuristic defined for this type\n");
            return false;
        }

        template<>
        bool InvestigateNode<MapElement_Floor>(AStarNode<MapElement_Floor>* parent, AStarNode<MapElement_Floor>* destination)
        {
            float prospectiveCost = (parent != nullptr) ? parent->GetCost() + 1.0f : 0.0f;
            if (prospectiveCost < m_Cost)   // If the cost of getting to this node from the new parent is less than from a previously searched parent node, update to use new parent node.
            {
                m_ParentNode = parent;
                m_Cost = prospectiveCost;

                Vector2 toDestination = destination->Data().GetTransform().GetPosition_Local() - m_Data->GetTransform().GetPosition();
                m_ToDestination = abs(toDestination.X) + abs(toDestination.Y);

                m_Heuristic = m_Cost + m_ToDestination;
            }

            return m_ParentNode == parent; // Has the parent node changed.
        }
};