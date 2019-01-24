#pragma once

#include "InputDevice.h"
#include <unordered_map>

#include <SDL.h>

#include "Core\Math\Vector.h"

namespace Input
{
    class InputDevice_GamePad : public InputDevice
    {
        public:
            InputDevice_GamePad(InputMapper& inputMapper, int controllerIndex);
            ~InputDevice_GamePad();

            void UpdateInput() override;
            void OnSDLEvent(SDL_Event& event) override;

        private:

            void UpdateInput_Buttons();
            void UpdateInput_Axis();

            const float DEAD_ZONE = 0.1f;

            std::unordered_map<int, VirtualControllerButton> m_ButtonBindings;
            std::unordered_map<int, VirtualControllerAxis> m_AxisBindings;

            std::unordered_map<int, bool> m_ButtonStates;

            SDL_GameController* m_Controller;
    };
}