#include "RenderGroupContainer.h"

RenderGroupContainer::RenderGroupContainer(int maxInstanceCount) :
    m_RenderGroups(),
    m_ActiveGroupIndex(0),
	m_MaxInstanceCount(maxInstanceCount)
{
    CreateNewRenderGroup();
}

void RenderGroupContainer::AddObject(const Sprite& object)
{
    RenderGroup_Sprites* rGroup = &m_RenderGroups[m_ActiveGroupIndex];

    if (!rGroup->HasSpace())
    {
        ++m_ActiveGroupIndex;
        if (m_ActiveGroupIndex >= m_RenderGroups.size())
        {
            CreateNewRenderGroup();
        }

        rGroup = &m_RenderGroups[m_ActiveGroupIndex];
    }

    rGroup->AddObject(object);
}

void RenderGroupContainer::Clean()
{
    for (size_t i = 0; i <= m_ActiveGroupIndex; ++i)
    {
        m_RenderGroups[i].Clean();
    }

    m_ActiveGroupIndex = 0;
}

void RenderGroupContainer::ForeachRenderGroup(std::function<void(const RenderGroup_Sprites&)> func) const
{
    for (const RenderGroup_Sprites& renderGroup : m_RenderGroups)
    {
        func(renderGroup);
    }
}

int RenderGroupContainer::GetUsedRenderGroupCount() const
{
    return m_ActiveGroupIndex+1;
}

const RenderGroup_Sprites& RenderGroupContainer::GetRenderGroupWithIndex(int i) const
{
    return m_RenderGroups[i];
}

void RenderGroupContainer::CreateNewRenderGroup()
{
    m_RenderGroups.reserve(1);
	m_RenderGroups.emplace_back(m_MaxInstanceCount);
}