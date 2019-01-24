#pragma once

#include "TextureData\TextureDataContainer.h"
#include "TileData\TileDataContainer.h"
#include "WindowConstants\WindowConstants.h"
#include "FontData\FontDataContainer.h"
#include "StringData\StringDataContainer.h"
#include "GUIpageData\GUIPageDataContainer.h"

namespace GameConstants
{
    extern const WindowConstants Window;
    extern const TextureDataContainer TextureData;
    extern const TileDataContainer TileData;
    extern const FontDataContainer FontData;
    extern const StringDataContainer StringData;
    extern const GUIPageDataContainer GUIPageData;

    extern const float DeltaTime_Real;
    extern const float DimetricProjectionScale;
};