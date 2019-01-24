#include "InputDeviceHandler.h"

namespace Input
{
    InputDeviceHandler::InputDeviceHandler() :
        m_InputMapper(),
        m_InputDevice_Keyboard(m_InputMapper),
        m_InputDevice_GamePad(nullptr)
    {
        const int numJoysticks = SDL_NumJoysticks();
        for (int i = 0; i < numJoysticks; ++i)
        {
            if (SDL_IsGameController(i))
            {
                m_InputDevice_GamePad = std::make_unique<InputDevice_GamePad>(m_InputMapper, i);
            }
        }
    }

    InputDeviceHandler::~InputDeviceHandler()
    {}

    void InputDeviceHandler::Update()
    {
        m_InputDevice_Keyboard.UpdateInput();

        if (m_InputDevice_GamePad != nullptr)
        {
            m_InputDevice_GamePad->UpdateInput();
        }

        m_InputMapper.Dispatch();
        m_InputMapper.ClearInput();
    }

    void InputDeviceHandler::ClearContextStack()
    {
        m_InputMapper.ClearContextStack();
    }

    void InputDeviceHandler::AddContext(const std::string& context)
    {
        m_InputMapper.PushContext(context);
    }

    void InputDeviceHandler::ClearInputCallbacks()
    {
        m_InputMapper.ClearCallbackTable();
    }

    void InputDeviceHandler::AddInputCallback(InputCallback callback, int priority)
    {
        m_InputMapper.AddCallback(callback, priority);
    }

    void InputDeviceHandler::OnSDLEvent(SDL_Event& event)
    {
        m_InputDevice_Keyboard.OnSDLEvent(event);

        if (m_InputDevice_GamePad != nullptr)
        {
            m_InputDevice_GamePad->OnSDLEvent(event);
        }
    }
}