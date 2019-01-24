#pragma once

#include "InputDevice.h"

namespace Input
{
    class InputDevice_Empty : public InputDevice
    {
        InputDevice_Empty(InputMapper& inputMapper);

        void UpdateInput() override;
        void OnSDLEvent(SDL_Event& event) override;
    };
}