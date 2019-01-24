#pragma once

#include <SDL.h>
#include <unordered_map>

#include "Core\InputHandling\InputMapping\VirtualControllerInputs.h"
#include "Core\Math\Vector.h"
#include "InputDevice.h"
#include "MouseMoveRangeName.h"
#include "Utils\KeyRange.h"

namespace Input
{
    class InputDevice_Keyboard : public InputDevice
    {
        public:
            InputDevice_Keyboard(InputMapper& inputMapper);

            void UpdateInput() override;
            void OnSDLEvent(SDL_Event& event) override;

        private:
            void UpdateInput_Key();
            void UpdateInput_Mouse();

            std::unordered_map<SDL_Scancode, VirtualControllerButton> m_KeyBindings;
            std::unordered_map<int, VirtualControllerButton> m_MouseBindings;
            std::unordered_map<KeyRange, VirtualControllerAxis> m_KeyRanges;
            std::unordered_map<MouseMoveRangeName, VirtualControllerAxis> m_MouseMoveBindings;

            Uint8* m_PreviousKeyState;
            Uint32 m_PreviousMouseState;
            SDL_Point m_PreviousMousePos;
            int m_WheelDelta;
    };
}