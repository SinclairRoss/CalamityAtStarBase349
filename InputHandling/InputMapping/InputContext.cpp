#include "InputContext.h"

#include "Core\FileParsing\XMLParser.h"
#include "InputMappingHelpers.h"

namespace Input
{

    InputContext::InputContext(const std::string& path)
    {
        XMLParser::XMLDoc_ptr inputContext = XMLParser::ReadFile(path);
        rapidxml::xml_node<> *root = inputContext->first_node();

        // Ranges
        rapidxml::xml_node<> *ranges = root->first_node("Ranges");
        for (rapidxml::xml_node<> *child = ranges->first_node(); child != nullptr; child = child->next_sibling())
        {
            Range range = InputMappingHelpers::StringToRange(child->first_attribute()->name());
            VirtualControllerAxis axis = InputMappingHelpers::StringVirtualControllerAxis(child->first_attribute()->value());


            m_RangeMap[axis] = range;
        }

        // Actions
        rapidxml::xml_node<> *actions = root->first_node("Actions");
        for (rapidxml::xml_node<> *child = actions->first_node(); child != nullptr; child = child->next_sibling())
        {
            Action action = InputMappingHelpers::StringToAction(child->first_attribute()->name());
            VirtualControllerButton button = InputMappingHelpers::StringToVirtualControllerButton(child->first_attribute()->value());


            m_ActionMap[button] = action;
        }
    }

    InputContext::~InputContext()
    {}

    Action InputContext::MapButtonToAction(VirtualControllerButton button) const
    {
        Action action = Action::_INVALID;
        std::unordered_map<VirtualControllerButton, Action>::const_iterator iter = m_ActionMap.find(button);

        if (iter != m_ActionMap.end())
        {
            action = iter->second;
        }

        return action;
    }

    bool InputContext::MapAxisToRange(VirtualControllerAxis axis, Range& out) const
    {
        std::unordered_map<VirtualControllerAxis, Range>::const_iterator iter = m_RangeMap.find(axis);

        if (iter != m_RangeMap.end())
        {
            out = iter->second;
        }

        return iter != m_RangeMap.end();
    }
}