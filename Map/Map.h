#pragma once

#include <functional>
#include <vector>

#include "Map\MapLayer.h"
#include "AIHooks\AINodeRegister.h"

class Map
{
    public:
        Map(int levelCount);
        ~Map() = default;
        Map(const Map&) = default;
        Map& operator=(const Map&) = default;
        Map(Map&& other) noexcept = default;
        Map& operator=(Map&& other) noexcept = default;

        const MapLayer& GetMapLayer(int index) const;
        MapLayer& GetMapLayer(int index);

        void AddNewLevel();

        int GetLevelCount() const;

        void ForeachLevel(std::function<void(const MapLayer&)> func) const;
        void ForeachLevel(std::function<void(MapLayer&)> func);

    private:
        std::vector<MapLayer> m_MapLevels;  
        AINodeRegister m_AINodeRegister;
};
