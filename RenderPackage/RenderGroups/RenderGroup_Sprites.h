#pragma once

#include <array>

#include "Core\Renderables\Sprite.h"

constexpr static int STRIDE_TRANSFORM = 16;
constexpr static int STRIDE_TEXTURE_ID = 1;
constexpr static int STRIDE_COLOUR = 4;

class RenderGroup_Sprites
{
    public:
        RenderGroup_Sprites(int maxInstanceCount);

        void AddObject(const Sprite& object);
        void Clean();

        const std::vector<float>& GetTransformData() const;
        const std::vector<int>& GetTextureData() const;
        const std::vector<float>& GetColourData() const;

        int GetInstanceCount() const;
        bool HasSpace() const;

    private: 
        void FillTransformData(const Sprite& object);
        void FillTextureData(const Sprite& object);
        void FillColourData(const Sprite& object);

        float GetSortingDepth(DisplayLayer layer);

        std::vector<float> m_TransformData;
		std::vector<int> m_TextureData;
		std::vector<float> m_ColourData;

        size_t m_InstanceCount;
		size_t m_InstanceCount_Max;
};