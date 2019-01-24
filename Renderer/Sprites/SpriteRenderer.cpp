#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer() :
	m_Sprite()
{}

SpriteRenderer::~SpriteRenderer()
{}

void SpriteRenderer::Draw(glm::mat4& vpMatrix, const RenderGroup_Sprites& renderGroup)
{
    int instanceCount = renderGroup.GetInstanceCount();

    const std::vector<float>& transformData = renderGroup.GetTransformData();
    const std::vector<int>& textureData = renderGroup.GetTextureData();
    const std::vector<float>& colourData = renderGroup.GetColourData();

	m_Sprite.Draw(transformData.data(), textureData.data(), colourData.data(), vpMatrix, instanceCount);
}