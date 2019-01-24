#include "RenderGroup_Sprites.h"

#include "GameConstants\GameConstants.h"

RenderGroup_Sprites::RenderGroup_Sprites(int maxInstanceCount) :
    m_TransformData(maxInstanceCount * STRIDE_TRANSFORM),
    m_TextureData(maxInstanceCount * STRIDE_TEXTURE_ID),
	m_ColourData(maxInstanceCount * STRIDE_COLOUR),
    m_InstanceCount(0),
	m_InstanceCount_Max(maxInstanceCount)
{}

void RenderGroup_Sprites::AddObject(const Sprite& object)
{
    if (m_InstanceCount < m_InstanceCount_Max)
    {
        FillTransformData(object);
        FillTextureData(object);
        FillColourData(object);

        ++m_InstanceCount;
    }
    else
    {
        printf("Instance cap reached: RenderGroup_Sprites");
    }
}

void RenderGroup_Sprites::Clean()
{
    m_InstanceCount = 0;
}

const std::vector<float>& RenderGroup_Sprites::GetTransformData() const{ return m_TransformData; }
const std::vector<int>& RenderGroup_Sprites::GetTextureData() const { return m_TextureData; }
const std::vector<float>& RenderGroup_Sprites::GetColourData() const { return m_ColourData; }

int RenderGroup_Sprites::GetInstanceCount() const { return m_InstanceCount; }
bool RenderGroup_Sprites::HasSpace() const { return m_InstanceCount < m_InstanceCount_Max; }

void RenderGroup_Sprites::FillTransformData(const Sprite& object)
{
    const std::array<float, 16>& transform = object.GetTransform().ResolveParents().Data();

    int startPoint = m_InstanceCount * STRIDE_TRANSFORM;
    std::copy(transform.begin(), transform.end(), m_TransformData.begin() + startPoint);
    m_TransformData[startPoint + 14] += GetSortingDepth(object.GetDisplayLayer());
}

void RenderGroup_Sprites::FillTextureData(const Sprite& object)
{
    m_TextureData[m_InstanceCount] = object.GetTextureID();
}

void RenderGroup_Sprites::FillColourData(const Sprite& object)
{
    const Colour& colour = object.GetColour();
    m_ColourData[(m_InstanceCount * 4) + 0] = colour.R;
    m_ColourData[(m_InstanceCount * 4) + 1] = colour.G;
    m_ColourData[(m_InstanceCount * 4) + 2] = colour.B;
    m_ColourData[(m_InstanceCount * 4) + 3] = colour.A;
}

// This is a hacky little piece of code that will need updated later, will not cut the mustard.
float RenderGroup_Sprites::GetSortingDepth(DisplayLayer layer)
{
    float depth = static_cast<float>(layer) * 0.1f;
    return depth;
}