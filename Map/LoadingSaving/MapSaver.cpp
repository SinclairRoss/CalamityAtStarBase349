#include "MapSaver.h"

#include <string>

#include "Core\FileParsing\XMLParser.h"
#include "GameConstants\GameConstants.h"
#include "GameConstants\TileData\StaticElements\ElementData_Static.h"
#include "GameObjects\Interactables\Interactable.h" // possibly not needed

namespace MapSaver
{
    namespace
    {
        rapidxml::xml_node<>* AddNode(XMLParser::XMLDoc_ptr& doc, rapidxml::xml_node<>* rootNode, const std::string& name, const std::string& value = "")
        {
            char* nameBuff = doc->allocate_string("", 32);
            snprintf(nameBuff, sizeof(char) * 32, name.c_str());
            rapidxml::xml_node<>* node = doc->allocate_node(rapidxml::node_element, nameBuff);

            if (!value.empty())
            {
                char* valBuff = doc->allocate_string("", 32);
                snprintf(valBuff, sizeof(char) * 32, value.c_str());
                node->value(valBuff);
            }

            rootNode->append_node(node);
            return node;
        }
    }

    void SaveMap(const Map& map)
    {
        XMLParser::XMLDoc_ptr doc = XMLParser::CreateXMLDoc();

        rapidxml::xml_node<>* root = doc->allocate_node(rapidxml::node_element, "Map");
        doc->append_node(root);
        
        map.ForeachLevel([&](const MapLayer& layer)
        {
            rapidxml::xml_node<>* levelRootNote = AddNode(doc, root, "Level");
            rapidxml::xml_node<>* elementRoot = nullptr;

            auto elementFunc = [&](const MapElement* element)
            {
                if (element != nullptr)
                {
                    rapidxml::xml_node<>* elementNode = AddNode(doc, elementRoot, "Element");

                    const std::string& tileName = element->GetElementDataName();
                    AddNode(doc, elementNode, "Name", tileName);

                    int rotationIndex = element->GetRotationIndex();
                    AddNode(doc, elementNode, "RotationIndex", std::to_string(rotationIndex));

                    const Vector2& worldPos = element->GetPosition();
                    AddNode(doc, elementNode, "WorldX", std::to_string(worldPos.X));
                    AddNode(doc, elementNode, "WorldY", std::to_string(worldPos.Y));
                }
            };

            elementRoot = AddNode(doc, levelRootNote, "FloorTiles");
            layer.ForeachElement<MapElement_Floor>(elementFunc);

            elementRoot = AddNode(doc, levelRootNote, "Walls");
            layer.ForeachElement<MapElement_Wall>(elementFunc);

            elementRoot = AddNode(doc, levelRootNote, "Interactables");
            layer.ForeachElement<Interactable>(elementFunc);
        });

        XMLParser::SaveXMLToFile(doc, "Resources/GameData/SavedMaps", "NewMap");
    }
}