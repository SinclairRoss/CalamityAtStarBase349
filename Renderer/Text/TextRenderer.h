#pragma once

#include <memory>
#include <string>
#include <vector>

#include <glm\glm.hpp>
#include <GL\glew.h>

#include "GlyphSprite.h"
#include "Core\RenderPackage\RenderGroups\RenderGroup_Text.h"

class TextRenderer
{
    public:
        TextRenderer();
        ~TextRenderer();

        TextRenderer(const TextRenderer&) = delete;
        TextRenderer& operator=(const TextRenderer&) = delete;

        TextRenderer(TextRenderer&&) = delete;
        TextRenderer& operator=(TextRenderer&&) = delete;

        void Draw(glm::mat4& vpMatrix, const RenderGroup_Text& rgt);

    private:
        GlyphSprite m_GlyphSprite;
};
