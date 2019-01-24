#pragma once

struct GlyphData
{
    GlyphData(char glyphChar, float tex_u, float tex_v, float tex_w, float tex_h, int glyph_Width, int glyph_Height, int glyph_advanceX, int glyph_advanceY, int glyph_bearingX, int glyph_bearingY) :
       
        GlyphChar(glyphChar),

        Tex_U(tex_u),
        Tex_V(tex_v),
        Tex_W(tex_w),
        Tex_H(tex_h),

        Glyph_Width(glyph_Width),
        Glyph_Height(glyph_Height),
        Glyph_AdvanceX(glyph_advanceX),
        Glyph_AdvanceY(glyph_advanceY),
        Glyph_BearingX(glyph_bearingX),
        Glyph_BearingY(glyph_bearingY)
    {}

    const char GlyphChar;

    const float Tex_U;
    const float Tex_V;
    const float Tex_W;
    const float Tex_H;

    const int Glyph_Width;
    const int Glyph_Height;
    const int Glyph_AdvanceX;
    const int Glyph_AdvanceY;
    const int Glyph_BearingX;
    const int Glyph_BearingY;
};