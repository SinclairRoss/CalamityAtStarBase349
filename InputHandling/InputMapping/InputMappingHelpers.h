#pragma once

#include <iostream>
#include <SDL.h>
#include <string>

#include "VirtualControllerInputs.h"
#include "InputConstants.h"
#include "../InputDevices/MouseMoveRangeName.h"

namespace Input
{
    namespace InputMappingHelpers
    {
        extern VirtualControllerButton StringToVirtualControllerButton(const std::string& string);
        extern VirtualControllerAxis StringVirtualControllerAxis(const std::string& string);

        extern Action StringToAction(const std::string& string);
        extern Range StringToRange(const std::string& string);

        extern SDL_Scancode StringToScanCode(const std::string& string);
        extern int StringToMouseButton(const std::string& string);
        extern MouseMoveRangeName StringToMouseMoveRangeName(const std::string& string);

        extern int StringToControllerButton(const std::string& string);
        extern int StringToControllerAxis(const std::string& string);
    }
}