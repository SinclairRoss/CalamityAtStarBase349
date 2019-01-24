#pragma once

#include <SDL.h>
#include "Core\InputHandling\InputMapping\InputMapper.h"

namespace Input
{
    class InputDevice
    {
        public:
            InputDevice(InputMapper& inputMapper);
            virtual ~InputDevice();

            virtual void UpdateInput() = 0;
            virtual void OnSDLEvent(SDL_Event& event) = 0;

        protected:
            InputMapper& m_InputMapper;
    };
}
