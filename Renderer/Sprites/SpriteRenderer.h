// name: SpriteRenderer
// date: 05/01/2017
// Note: A container for all the different sprites that will be used.

#pragma once

#include "Core\RenderPackage\RenderGroups\RenderGroup_Sprites.h"
#include "GLSprite.h"

class SpriteRenderer
{
	public:
		SpriteRenderer();
		~SpriteRenderer();

		void Draw(glm::mat4& vpMatrix, const RenderGroup_Sprites& renderGroup);

	private:
		GLSprite m_Sprite;
};