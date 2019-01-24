#include "TileDataReader.h"

#include "GameConstants\GameConstants.h"
#include "Core\FileParsing\XMLParser.h"

namespace TileDataReader
{
    namespace
    {
        struct BasicData
        {
            BasicData(std::string& name, int textureID, float size_X, float size_Y, float posOffset_X, float posOffset_Y) :
                Name(name),
                TextureID(textureID),
                Size_X(size_X),
                Size_Y(size_Y),
                PosOffset_X(posOffset_X),
                PosOffset_Y(posOffset_Y)
            {}

            std::string Name;
            int TextureID;
            float Size_X;
            float Size_Y;
            float PosOffset_X;
            float PosOffset_Y;
        };

        BasicData ReadData_Basic(rapidxml::xml_node<>* node)
        {
            std::string tileName(node->first_node("Name")->value());
            std::string textureName(node->first_node("TextureName")->value());
            int textureID = GameConstants::TextureData.GetIDWithName(textureName);

            rapidxml::xml_node<>* node_size_x = node->first_node("Size_X");
            float size_x = node_size_x != nullptr ? static_cast<float>(atof(node_size_x->value())) : 1.0f;

            rapidxml::xml_node<>* node_size_y = node->first_node("Size_Y");
            float size_y = node_size_y != nullptr ? static_cast<float>(atof(node_size_y->value())) : 1.0f;

            rapidxml::xml_node<>* node_posOffset_x = node->first_node("PosOffset_X");
            float posOffset_x = node_posOffset_x != nullptr ? static_cast<float>(atof(node_posOffset_x->value())) : 0.0f;

            rapidxml::xml_node<>* node_posOffset_y = node->first_node("PosOffset_Y");
            float posOffset_y = node_posOffset_y != nullptr ? static_cast<float>(atof(node_posOffset_y->value())) : 0.0f;

            return BasicData(tileName, textureID, size_x, size_y, posOffset_x, posOffset_y);
        }

        InteractableType StringToInteractableType(const std::string& string)
        {
            InteractableType type = InteractableType::_INVALID;

            if (string == "Switch")
            {
                type = InteractableType::SWITCH;
            }
            else
            {
                printf("Unrecognised interactable type: %s\n", string.c_str());
            }

            return type;
        }

        extern std::vector<Vector2> StringToVectorList(const std::string& string)
        {
            size_t start = string.find('[', 0);
            size_t end = string.find(']', 0);

            std::vector<Vector2> list;

            while (start != std::string::npos)
            {
                std::string substring = string.substr(start + 1, end - start - 1);
                size_t separator = substring.find(',', 0);

                std::string x_str = substring.substr(0, separator);
                std::string y_str = substring.substr(separator+1);

                float x = std::atof(x_str.c_str());
                float y = std::atof(y_str.c_str());
                list.emplace_back(x,y);

                start = string.find('[', start+1);
                end = string.find(']', end+1);
            }

            return list;
        }
    }

    std::vector<ElementData_Floor> ReadData_Floor()
    {
        std::vector<ElementData_Floor> data;

        XMLParser::XMLDoc_ptr floorTileData = XMLParser::ReadFile("MapComponentData/FloorTileData.xml");
        rapidxml::xml_node<> *root = floorTileData->first_node();

        int textureCount = XMLParser::CalculateChildCount(*root);
        data.reserve(textureCount);

        for (rapidxml::xml_node<> *child = root->first_node(); child != nullptr; child = child->next_sibling())
        {
            BasicData basicData = ReadData_Basic(child);
       
            rapidxml::xml_node<>* node_traversable = child->first_node("Traversable");
            bool isTraversable = (node_traversable == nullptr || 
                                  node_traversable != nullptr && node_traversable->value() == "True");

            data.emplace_back(basicData.Name, basicData.TextureID, basicData.Size_X, basicData.Size_Y, isTraversable);
        }

        return data;
    }

    std::vector<ElementData_Wall> ReadData_Wall()
    {
        std::vector<ElementData_Wall> data;

        XMLParser::XMLDoc_ptr floorTileData = XMLParser::ReadFile("MapComponentData/WallTileData.xml");
        rapidxml::xml_node<> *root = floorTileData->first_node();

        int textureCount = XMLParser::CalculateChildCount(*root);
        data.reserve(textureCount);

        for (rapidxml::xml_node<> *child = root->first_node(); child != nullptr; child = child->next_sibling())
        {
            BasicData basicData = ReadData_Basic(child);
            data.emplace_back(basicData.Name, basicData.TextureID, basicData.Size_X, basicData.Size_Y);
        }

        return data;
    }

    std::vector<ElementData_Static> ReadData_Static()
    {
        std::vector<ElementData_Static> data;

        XMLParser::XMLDoc_ptr floorTileData = XMLParser::ReadFile("MapComponentData/StaticObjectData.xml");
        rapidxml::xml_node<> *root = floorTileData->first_node();

        int textureCount = XMLParser::CalculateChildCount(*root);
        data.reserve(textureCount);

        for (rapidxml::xml_node<> *child = root->first_node(); child != nullptr; child = child->next_sibling())
        {
            BasicData basicData = ReadData_Basic(child);
            data.emplace_back(basicData.Name, basicData.TextureID, basicData.Size_X, basicData.Size_Y, basicData.PosOffset_X, basicData.PosOffset_Y);
        }

        return data;
    }

    std::vector<ElementData_Interactable> ReadData_Interactable()
    {
        std::vector<ElementData_Interactable> data;

        XMLParser::XMLDoc_ptr floorTileData = XMLParser::ReadFile("MapComponentData/InteractableData.xml");
        rapidxml::xml_node<> *root = floorTileData->first_node();

        int textureCount = XMLParser::CalculateChildCount(*root);
        data.reserve(textureCount);

        for (rapidxml::xml_node<> *child = root->first_node(); child != nullptr; child = child->next_sibling())
        {
            BasicData basicData = ReadData_Basic(child);

            std::string tileName(child->first_node("Type")->value());
            InteractableType type = StringToInteractableType(tileName);

            std::string interactionNodes_Str = child->first_node("AIInteractionNode")->value();
            std::vector<Vector2> interactionNodeList = StringToVectorList(interactionNodes_Str);

            ElementData_Interactable elementData(basicData.Name, type, basicData.TextureID, basicData.Size_X, basicData.Size_Y, basicData.PosOffset_X, basicData.PosOffset_Y, interactionNodeList);
            data.emplace_back(std::move(elementData));
        }

        return data;
    }

}