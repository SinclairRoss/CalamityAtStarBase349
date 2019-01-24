#pragma once

#include <map>
#include <memory>
#include <SDL.h>
#include <vector>

#include "InputMapping\InputConstants.h"
#include "InputDevices\InputDevices.h"
#include "InputDevices\InputDevice_GamePad.h"
#include "InputDevices\InputDevice_Keyboard.h"
#include "InputMapping\InputMapper.h"

namespace Input
{

    class InputDeviceHandler
    {
        public:
            InputDeviceHandler();
            ~InputDeviceHandler();

            void Update();

            void ClearContextStack();
            void AddContext(const std::string& context);

            void ClearInputCallbacks();
            void AddInputCallback(InputCallback callback, int priority);

            void OnSDLEvent(SDL_Event& event);
        private:

            InputMapper m_InputMapper;
            InputDevice_Keyboard m_InputDevice_Keyboard;
            std::unique_ptr<InputDevice_GamePad> m_InputDevice_GamePad;
    };
}