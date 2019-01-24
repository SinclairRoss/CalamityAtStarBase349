#include "InputDevice_Keyboard.h"

#include "Core\InputHandling\InputMapping\InputMappingHelpers.h"
#include "Core\FileParsing\XMLParser.h"
#include "GameConstants\GameConstants.h"

namespace Input
{
    InputDevice_Keyboard::InputDevice_Keyboard(InputMapper& inputMapper) :
        InputDevice(inputMapper),
        m_KeyBindings(),
        m_MouseBindings(),
        m_PreviousKeyState(nullptr),
        m_PreviousMouseState(0),
        m_PreviousMousePos(),
        m_WheelDelta(0)
    {
        // Read key bindings
        XMLParser::XMLDoc_ptr buttonMap = XMLParser::ReadFile("InputContext/ButtonMap.xml");
        rapidxml::xml_node<> *root = buttonMap->first_node();

        rapidxml::xml_node<> *buttonNode = root->first_node("Button");
        for (rapidxml::xml_node<> *child = buttonNode->first_node(); child != nullptr; child = child->next_sibling())
        {
            VirtualControllerButton virtualControllerButton = InputMappingHelpers::StringToVirtualControllerButton(child->first_node("VirtualControllerButton")->value());
            std::string keyValue(child->first_node("Key")->value());

            SDL_Scancode scancode = InputMappingHelpers::StringToScanCode(keyValue);
            if (scancode != SDL_SCANCODE_UNKNOWN)
            {
                m_KeyBindings[scancode] = virtualControllerButton;
            }
            else
            {
                int mouseButton = InputMappingHelpers::StringToMouseButton(keyValue);
                if (mouseButton >= 0)
                {
                    m_MouseBindings[mouseButton] = virtualControllerButton;
                }
                else
                {
                    printf("InputDevice Keyboard: Unknown Key: %s\n", keyValue.c_str());
                }
            }
        }

        // Ranges
        rapidxml::xml_node<> *rangeNode = root->first_node("Range");
        for (rapidxml::xml_node<> *child = rangeNode->first_node(); child != nullptr; child = child->next_sibling())
        {
            VirtualControllerAxis axis = InputMappingHelpers::StringVirtualControllerAxis(child->first_node("VirtualControllerAxis")->value());

            std::string keyVal = child->first_node("Key")->value();
            MouseMoveRangeName key = InputMappingHelpers::StringToMouseMoveRangeName(keyVal);
            if (key != MouseMoveRangeName::_INVALID)
            {
                m_MouseMoveBindings[key] = axis;
            }
            else
            {
                size_t delimeter = keyVal.find('/');
                if (delimeter != keyVal.npos)
                {
                    std::string posVal = keyVal.substr(0, delimeter);
                    KeyRange posKey(InputMappingHelpers::StringToScanCode(posVal), 1.0f);
                    m_KeyRanges[posKey] = axis;

                    std::string negVal = keyVal.substr(delimeter + 1);
                    KeyRange negKey(InputMappingHelpers::StringToScanCode(negVal), -1.0f);
                    m_KeyRanges[negKey] = axis;
                }
            }
        }

        // Create previous keystate buffer
        int numKeys;
        const Uint8* currentKeyState = SDL_GetKeyboardState(&numKeys);
        m_PreviousKeyState = (Uint8*)malloc(numKeys);
        memcpy(m_PreviousKeyState, currentKeyState, numKeys);
    }

    void InputDevice_Keyboard::UpdateInput()
    {
        UpdateInput_Key();
        UpdateInput_Mouse();
    }

    void InputDevice_Keyboard::OnSDLEvent(SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_MOUSEWHEEL:
            {
                m_WheelDelta = event.wheel.y;
                break;
            }
        }
    }

    void InputDevice_Keyboard::UpdateInput_Key()
    {
        int numKeys;
        const Uint8* currentKeyState = SDL_GetKeyboardState(&numKeys);

        for (const std::pair<SDL_Scancode, VirtualControllerButton>& pair : m_KeyBindings)
        {
            int scancode = pair.first;
            if (currentKeyState[scancode])  // Is key down?
            {
                if (!m_PreviousKeyState[scancode])  // Was the key up in the previous frame?
                {
                    m_InputMapper.SetVirtualControllerButton_Down(pair.second);
                }
            }
            else    // The key is up.
            {
                if (m_PreviousKeyState[scancode])    // Was the key down in the previous frame?
                {
                    m_InputMapper.SetVirtualControllerButton_Up(pair.second);
                }
            }
        }

        for (const std::pair<KeyRange, VirtualControllerAxis>& pair : m_KeyRanges)
        {
            KeyRange keyRange = pair.first;
            int scancode = keyRange.Key;

            if (currentKeyState[scancode])
            {
                m_InputMapper.SetVirtualControllerAxisValue(pair.second, keyRange.Polarity);
            }
        }

        memcpy(m_PreviousKeyState, currentKeyState, numKeys);
    }

    void InputDevice_Keyboard::UpdateInput_Mouse()
    {
        int mouse_X, mouse_Y;
        Uint32 currentMouseState = SDL_GetMouseState(&mouse_X, &mouse_Y);

        for (const std::pair<int, VirtualControllerButton>& pair : m_MouseBindings)
        {
            int buttonID = pair.first;
            if (currentMouseState & buttonID) // Is key down?
            {
                if ((m_PreviousMouseState & buttonID) == 0) // Was the key up in the previous frame?
                {
                    m_InputMapper.SetVirtualControllerButton_Down(pair.second);
                }
            }
            else // The key is up.
            {
                if ((m_PreviousMouseState & buttonID) > 0) // Was the key down in the previous frame?
                {
                    m_InputMapper.SetVirtualControllerButton_Up(pair.second);
                }
            }
        }

        for (const std::pair<MouseMoveRangeName, VirtualControllerAxis>& pair : m_MouseMoveBindings)
        {
            MouseMoveRangeName range = pair.first;
            VirtualControllerAxis rawAxis = pair.second;

            int value = 0;

            switch (range)
            {
            case MouseMoveRangeName::X: { value = mouse_X; break; }
            case MouseMoveRangeName::Y: { value = mouse_Y; break; }
            case MouseMoveRangeName::DELTA_X: { value = mouse_X - m_PreviousMousePos.x;  break; }
            case MouseMoveRangeName::DELTA_Y: { value = mouse_Y - m_PreviousMousePos.y; break; }
            case MouseMoveRangeName::WHEEL_DELTA: { value = m_WheelDelta; m_WheelDelta = 0; break; }
            }

            m_InputMapper.SetVirtualControllerAxisValue(rawAxis, static_cast<float>(value));
        }

        m_PreviousMouseState = currentMouseState;
        m_PreviousMousePos.x = mouse_X;
        m_PreviousMousePos.y = mouse_Y;
    }
}