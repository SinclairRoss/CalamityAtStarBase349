#pragma once

#include <memory>
#include <string>

#include "Map/Map.h"

namespace MapLoader
{
    extern Map LoadMap(const std::string& mapName);
}
