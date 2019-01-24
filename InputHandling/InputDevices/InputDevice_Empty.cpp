#include "InputDevice_Empty.h"

namespace Input
{
    InputDevice_Empty::InputDevice_Empty(InputMapper& inputMapper) :
        InputDevice(inputMapper)
    {}

    void InputDevice_Empty::UpdateInput()
    {}

    void InputDevice_Empty::OnSDLEvent(SDL_Event& event)
    {}
}