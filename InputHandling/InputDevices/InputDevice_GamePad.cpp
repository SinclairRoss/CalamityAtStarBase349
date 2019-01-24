#include "InputDevice_GamePad.h"

#include "Core\FileParsing\XMLParser.h"
#include "Core\InputHandling\InputMapping\InputMappingHelpers.h"

namespace Input
{

    InputDevice_GamePad::InputDevice_GamePad(InputMapper& inputMapper, int controllerIndex) :
        InputDevice(inputMapper),
        m_ButtonBindings(),
        m_AxisBindings(),
        m_ButtonStates(),
        m_Controller(SDL_GameControllerOpen(controllerIndex))
    {
        if (m_Controller != nullptr)
        {
            printf("Controller: %i - Connected\n", controllerIndex);

            // Read key bindings
            XMLParser::XMLDoc_ptr buttonMap = XMLParser::ReadFile("InputContext/ButtonMap.xml");
            rapidxml::xml_node<> *root = buttonMap->first_node();

            rapidxml::xml_node<> *buttonNode = root->first_node("Button");
            for (rapidxml::xml_node<> *child = buttonNode->first_node(); child != nullptr; child = child->next_sibling())
            {
                VirtualControllerButton rawButton = InputMappingHelpers::StringToVirtualControllerButton(child->first_node("VirtualControllerButton")->value());
                int padButton = InputMappingHelpers::StringToControllerButton(child->first_node("Pad")->value());

                m_ButtonBindings[padButton] = rawButton;
                m_ButtonStates[padButton] = false;
            }

            rapidxml::xml_node<> *rangeNode = root->first_node("Range");
            for (rapidxml::xml_node<> *child = rangeNode->first_node(); child != nullptr; child = child->next_sibling())
            {
                VirtualControllerAxis rawAxis = InputMappingHelpers::StringVirtualControllerAxis(child->first_node("VirtualControllerAxis")->value());
                int axis = InputMappingHelpers::StringToControllerAxis(child->first_node("Pad")->value());

                m_AxisBindings[axis] = rawAxis;
            }
        }
        else
        {
            printf("Unable to open controller with index: %i\n", controllerIndex);
        }
    }

    InputDevice_GamePad::~InputDevice_GamePad()
    {
        SDL_GameControllerClose(m_Controller);
        m_Controller = nullptr;
    }

    void InputDevice_GamePad::UpdateInput()
    {
        UpdateInput_Buttons();
        UpdateInput_Axis();
    }

    void InputDevice_GamePad::OnSDLEvent(SDL_Event& event)
    {}

    void InputDevice_GamePad::UpdateInput_Buttons()
    {
        assert(m_Controller != nullptr);

        for (const std::pair<int, VirtualControllerButton>& pair : m_ButtonBindings)
        {
            SDL_GameControllerButton button = static_cast<SDL_GameControllerButton>(pair.first);

            bool buttonPressed_Currently = SDL_GameControllerGetButton(m_Controller, button) == 1;
            if (buttonPressed_Currently)
            {
                bool buttonPressed_Previously = m_ButtonStates[button];
                if (!buttonPressed_Previously)
                {
                    m_InputMapper.SetVirtualControllerButton_Down(pair.second);
                    m_ButtonStates[button] = true;
                }
            }
            else
            {
                bool buttonPressed_Previously = m_ButtonStates[button];
                if (buttonPressed_Previously)
                {
                    m_InputMapper.SetVirtualControllerButton_Up(pair.second);
                    m_ButtonStates[button] = false;
                }
            }
        }
    }

    void InputDevice_GamePad::UpdateInput_Axis()
    {
        for (const std::pair<int, VirtualControllerAxis>& pair : m_AxisBindings)
        {
            Sint16 value = SDL_GameControllerGetAxis(m_Controller, static_cast<SDL_GameControllerAxis>(pair.first));
            float normalisedValue = (value < 0) ? value / 32768.0f : value / 32767.0f;

            if (abs(normalisedValue) < DEAD_ZONE)
            {
                normalisedValue = 0.0f;
            }

            m_InputMapper.SetVirtualControllerAxisValue(pair.second, value);
        }
    }
}