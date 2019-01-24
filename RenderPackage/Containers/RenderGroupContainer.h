#pragma once

#include <vector>

#include "../RenderGroups/RenderGroup_Sprites.h"

class RenderGroupContainer
{
    public:
        RenderGroupContainer(int maxInstanceCount);

        void AddObject(const Sprite& object);
        void Clean();

        int GetUsedRenderGroupCount() const;
        const RenderGroup_Sprites& GetRenderGroupWithIndex(int i) const;

        void ForeachRenderGroup(std::function<void(const RenderGroup_Sprites&)> func) const;

    private:
        void CreateNewRenderGroup();

        std::vector<RenderGroup_Sprites> m_RenderGroups;
        size_t m_ActiveGroupIndex;

		int m_MaxInstanceCount;
};