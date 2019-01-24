#include "InputDevice.h"

namespace Input
{
    InputDevice::InputDevice(InputMapper& inputMapper) :
        m_InputMapper(inputMapper)
    {}

    InputDevice::~InputDevice()
    {}
}