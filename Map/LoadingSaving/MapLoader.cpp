#include "MapLoader.h"

#include "Core\FileParsing\XMLParser.h"
#include "GameConstants\GameConstants.h"
#include "LevelEditor\Brushes\Brush.h"
#include "Map\Utils\MapUtils.h"
#include "GameConstants\TileData\Interactables\ElementInstanceData_Interactable.h"
#include "GameConstants\TileData\Wall\ElementInstanceData_Wall.h"

#include "GameConstants\TileData\Utils\BrushTypes.h"
#include "Utils\Helpers.h"

#include "WorldState\WorldState.h"

namespace MapLoader
{
    namespace
    {
        template <typename T>
        void UpdateBrush_Basic(Brush<T>& brush, rapidxml::xml_node<>* elementNode)
        {
           std::string tileName = elementNode->first_node("Name")->value();
           int id = GameConstants::TileData.GetElementIDWithName<BrushType<T>::ElementData>(tileName);

            int rotationIndex = atoi(elementNode->first_node("RotationIndex")->value());
            float worldX = static_cast<float>(atof(elementNode->first_node("WorldX")->value()));
            float worldY = static_cast<float>(atof(elementNode->first_node("WorldY")->value()));
            Vector2 worldPos(worldX, worldY);
            
            brush.SelectElement(id);
            brush.SetPosition(worldPos);
            brush.SetRotationIndex(rotationIndex);
        }

        template<typename T_Element>
        void UpdateBrush(Brush<T_Element>& brush, rapidxml::xml_node<>* elementNode) {}

        template<>
        void UpdateBrush(Brush<Interactable>& brush, rapidxml::xml_node<>* elementNode)
        {
            UpdateBrush_Basic<Interactable>(brush, elementNode);

            std::unique_ptr<InteractableEffect> effect =  Utils::CreateInteractableEffect(elementNode);
            brush.SetInstanceData("Test", std::move(effect));
        }
    }

    Map LoadMap(const std::string& mapName)
    {
        XMLParser::XMLDoc_ptr mapData = XMLParser::ReadFile("SavedMaps/" + mapName + ".xml");

        rapidxml::xml_node<>* mapRoot = mapData->first_node();

        int levelCount = XMLParser::CalculateChildCount(*mapRoot);
        Map map(levelCount);

        Brush<MapElement_Floor> brush_Floor;
        Brush<MapElement_Wall> brush_Wall;
        Brush<Interactable> brush_Interactable;

        int zDepth = 0;

        for (rapidxml::xml_node<> *levelNode = mapRoot->first_node("Level"); levelNode != nullptr; levelNode = levelNode->next_sibling())
        {
            rapidxml::xml_node<> *elementRoot = levelNode->first_node("FloorTiles");
            for (rapidxml::xml_node<> *element = elementRoot->first_node("Element"); element != nullptr; element = element->next_sibling())
            {
                UpdateBrush_Basic<MapElement_Floor>(brush_Floor, element);
                brush_Floor.CreateObject(map, zDepth);
            }

            elementRoot = levelNode->first_node("Walls");
            for (rapidxml::xml_node<> *element = elementRoot->first_node("Element"); element != nullptr; element = element->next_sibling())
            {
                UpdateBrush_Basic<MapElement_Wall>(brush_Wall, element);
                brush_Wall.CreateObject(map, zDepth);
            }

            elementRoot = levelNode->first_node("Interactables");
            for (rapidxml::xml_node<> *element = elementRoot->first_node("Element"); element != nullptr; element = element->next_sibling())
            {
                UpdateBrush<Interactable>(brush_Interactable, element);
                brush_Interactable.CreateObject(map, zDepth);
            }

            ++zDepth;
        }

        MapUtils::CalculateFloorTileNeighbourhoods(map);
        MapUtils::GenerateBounds(map);
        MapUtils::GenerateNavMesh(map);

        return map;
    }
}