#include "InputMapper.h"

#include <memory>

#include "Core\FileParsing\XMLParser.h"

namespace Input
{

    InputMapper::InputMapper()
    {
        XMLParser::XMLDoc_ptr contextList = XMLParser::ReadFile("InputContext/InputContextList.xml");

        rapidxml::xml_node<> *root = contextList->first_node();
        for (rapidxml::xml_node<> *child = root->first_node(); child != nullptr; child = child->next_sibling())
        {
            std::string name = child->first_attribute()->name();
            std::string path = child->first_attribute()->value();
            path.insert(0, "InputContext/");

            m_InputContexts[name] = std::make_unique<InputContext>(path);
        }
    }

    void InputMapper::ClearInput()
    {
        m_CurrentMappedInput.Clear();
    }

    void InputMapper::SetVirtualControllerButton_Down(VirtualControllerButton button)
    {
        Action action = MapButtonToAction(button);
        if (action != Action::_INVALID)
        {
            m_CurrentMappedInput.ButtonPressed(action);
        }
    }

    void InputMapper::SetVirtualControllerButton_Up(VirtualControllerButton button)
    {
        Action action = MapButtonToAction(button);
        if (action != Action::_INVALID)
        {
            m_CurrentMappedInput.ButtonReleased(action);
        }
    }

    void InputMapper::SetVirtualControllerAxisValue(VirtualControllerAxis axis, float value)
    {
        for (InputContext* context : m_ActiveContexts)
        {
            Range range;
            if (context->MapAxisToRange(axis, range))
            {
                m_CurrentMappedInput.SetRange(range, value);
                break;
            }
        }
    }

    void InputMapper::Dispatch() const
    {
        MappedInput input(m_CurrentMappedInput);
        for (const InputCallback& callback : m_CallbackTable)
        {
            callback(input);
        }
    }

    void InputMapper::AddCallback(InputCallback callback, int priority)
    {
        m_CallbackTable.emplace_back(callback);
    }

    void InputMapper::ClearCallbackTable()
    {
        m_CallbackTable.clear();
    }

    void InputMapper::PushContext(const std::string& name)
    {
        std::unordered_map<std::string, std::unique_ptr<InputContext>>::iterator iter = m_InputContexts.find(name);
        if (iter == m_InputContexts.end())
        {
            printf("Invalid input context pushed %s\n", name.c_str());
        }

        m_ActiveContexts.push_front(iter->second.get());
    }

    void InputMapper::PopContext()
    {
        if (m_ActiveContexts.empty())
        {
            printf("Cannot Pop, input context list is empty\n");
        }

        m_ActiveContexts.pop_front();
    }

    void InputMapper::ClearContextStack()
    {
        m_ActiveContexts.clear();
    }

    Action InputMapper::MapButtonToAction(VirtualControllerButton button) const
    {
        Action action = Action::_INVALID;

        for (const InputContext* context : m_ActiveContexts)
        {
            action = context->MapButtonToAction(button);

            if (action != Action::_INVALID)
            {
                break;
            }
        }

        return action;
    }
}