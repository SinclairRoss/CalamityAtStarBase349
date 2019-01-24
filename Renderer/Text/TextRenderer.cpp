#include "TextRenderer.h"

#include "GameConstants\GameConstants.h"
#include "Core\Math\MathsHelper.h"

TextRenderer::TextRenderer() :
    m_GlyphSprite()
{}

TextRenderer::~TextRenderer()
{}

void TextRenderer::Draw(glm::mat4& vpMatrix, const RenderGroup_Text& rgt)
{
    //FontName activeFont = FontName::BODY;
    
    
    float white[4] = { 1,1,1,1 };

    int numTexts = rgt.GetInstanceCount();
    for (int textIndex = 0; textIndex < numTexts; ++textIndex)
    {
        const Matrix4& transform = rgt.GetTransform(textIndex);
        const std::string& text = rgt.GetText(textIndex);
        FontName activeFont = rgt.GetFontName(textIndex);

        float penX = transform.GetPosition_Local().X;
        float penY = transform.GetPosition_Local().Y;

        int stringLength = text.size();
        const FontData& fontData = GameConstants::FontData.GetFontDataWithName(activeFont);

        std::vector<float> transforms;
        transforms.resize(16 * stringLength, 0.0f);

        std::vector<float> uv;
        uv.resize(2 * stringLength, 0.0f);

        std::vector<float> wh;
        wh.resize(2 * stringLength, 0.0f);

       // std::vector<int> texID;
       // texID.resize(stringLength, 0);
        int fontTextureID[] = { GameConstants::TextureData.GetTextureCount() + static_cast<int>(activeFont) };

        for (int i = 0; i < stringLength; ++i)
        {
            const char ch = text.at(i);
            const GlyphData* glyphData = fontData.GetGlyphData(ch);

            float scalar = 700.0f; //Hacky, please fix.
            float bearingX = (float)glyphData->Glyph_BearingX / scalar;
            float bearingY = (float)glyphData->Glyph_BearingY / scalar;
            float advance = (float)glyphData->Glyph_AdvanceX / scalar;
            float width = (float)glyphData->Glyph_Width / scalar;
            float height = (float)glyphData->Glyph_Height / scalar;

            float x = penX + bearingX;
            float y = penY + bearingY;

            transforms[i * 16] = width;
            transforms[i * 16 + 5] = height;
            transforms[i * 16 + 10] = 1.0f;
            transforms[i * 16 + 12] = x;
            transforms[i * 16 + 13] = y;
            transforms[i * 16 + 15] = 1.0f;

            uv[i * 2] = glyphData->Tex_U;
            uv[i * 2 + 1] = glyphData->Tex_V;

            wh[i * 2] = glyphData->Tex_W;
            wh[i * 2 + 1] = glyphData->Tex_H;

            penX += advance;
        }

        m_GlyphSprite.Draw(transforms.data(), fontTextureID, white, uv.data(), wh.data(), vpMatrix, stringLength);
    }
}