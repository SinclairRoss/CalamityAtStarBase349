#pragma once

#include "GameObjects\Interactables\Interactable.h"
#include "GameConstants\TileData\Interactables\ElementData_Interactable.h"
#include "GameConstants\TileData\Interactables\ElementInstanceData_Interactable.h"

#include "Map\MapElements\Wall\MapElement_Wall.h"
#include "GameConstants\TileData\Wall\ElementData_Wall.h"
#include "GameConstants\TileData\Wall\ElementInstanceData_Wall.h"

#include "Map\MapElements\Floor\MapElement_Floor.h"
#include "GameConstants\TileData\Floor\ElementData_Floor.h"
#include "GameConstants\TileData\Floor\ElementInstanceData_Floor.h"

//class Interactable;
//class ElementData_Interactable;
//class ElementInstanceData_Interactable;

//class MapElement_Wall;
//class ElementData_Wall;
//class ElementInstanceData_Wall;

//class MapElement_Floor;
//class ElementData_Floor;
//class ElementInstanceData_Floor;

template<typename T>
struct BrushType
{
    //static_assert(false, "No specialisation for given type");
};

template<>
struct BrushType<Interactable>
{
    using ElementData = ElementData_Interactable;
    using ElementInstanceData = ElementInstanceData_Interactable;
};

template<>
struct BrushType<MapElement_Wall>
{
    using ElementData = ElementData_Wall;
    using ElementInstanceData = ElementInstanceData_Wall;
};

template<>
struct BrushType<MapElement_Floor>
{
    using ElementData = ElementData_Floor;
    using ElementInstanceData = ElementInstanceData_Floor;
};