#include "GameConstants.h"

namespace GameConstants
{
    const WindowConstants Window;
    const TextureDataContainer TextureData;
    const TileDataContainer TileData;
    const FontDataContainer FontData;
    const StringDataContainer StringData;
    const GUIPageDataContainer GUIPageData;

    const float DeltaTime_Real = 1.0f / Window.FrameRate();
    const float DimetricProjectionScale = 0.75f;
};