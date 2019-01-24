#include "InputMappingHelpers.h"

#include <locale>

namespace Input
{
    VirtualControllerButton InputMappingHelpers::StringToVirtualControllerButton(const std::string& string)
    {
        VirtualControllerButton rawButton = VirtualControllerButton::INVALID;
        if (string == "BUTTON_A") { rawButton = VirtualControllerButton::BUTTON_A; }
        else if (string == "BUTTON_B") { rawButton = VirtualControllerButton::BUTTON_B; }
        else if (string == "BUTTON_X") { rawButton = VirtualControllerButton::BUTTON_X; }
        else if (string == "BUTTON_Y") { rawButton = VirtualControllerButton::BUTTON_Y; }

        else if (string == "BUTTON_DPAD_UP") { rawButton = VirtualControllerButton::DPAD_UP; }
        else if (string == "BUTTON_DPAD_DOWN") { rawButton = VirtualControllerButton::DPAD_DOWN; }
        else if (string == "BUTTON_DPAD_LEFT") { rawButton = VirtualControllerButton::DPAD_LEFT; }
        else if (string == "BUTTON_DPAD_RIGHT") { rawButton = VirtualControllerButton::DPAD_RIGHT; }

        else if (string == "BUTTON_MOUSE_LEFT") { rawButton = VirtualControllerButton::MOUSE_LEFT; }
        else if (string == "BUTTON_MOUSE_MIDDLE") { rawButton = VirtualControllerButton::MOUSE_MIDDLE; }
        else if (string == "BUTTON_MOUSE_RIGHT") { rawButton = VirtualControllerButton::MOUSE_RIGHT; }

        else if (string == "HOTKEY_1") { rawButton = VirtualControllerButton::HOTKEY_1; }
        else if (string == "HOTKEY_2") { rawButton = VirtualControllerButton::HOTKEY_2; }
        else if (string == "HOTKEY_3") { rawButton = VirtualControllerButton::HOTKEY_3; }
        else if (string == "HOTKEY_4") { rawButton = VirtualControllerButton::HOTKEY_4; }
        else if (string == "HOTKEY_5") { rawButton = VirtualControllerButton::HOTKEY_5; }
        else if (string == "HOTKEY_6") { rawButton = VirtualControllerButton::HOTKEY_6; }
        else if (string == "HOTKEY_7") { rawButton = VirtualControllerButton::HOTKEY_7; }
        else if (string == "HOTKEY_8") { rawButton = VirtualControllerButton::HOTKEY_8; }
        else if (string == "HOTKEY_9") { rawButton = VirtualControllerButton::HOTKEY_9; }

        else if (string == "ROTATE_CW") { rawButton = VirtualControllerButton::ROTATE_CW; }
        else if (string == "ROTATE_CCW") { rawButton = VirtualControllerButton::ROATE_CCW; }

        else { printf("InputMappingHelpers: Unknown VirtualControllerButton name: %s\n", string.c_str()); }

        return rawButton;
    }

    VirtualControllerAxis InputMappingHelpers::StringVirtualControllerAxis(const std::string& string)
    {
        VirtualControllerAxis rawAxis = VirtualControllerAxis::_INVALID;
        if (string == "AXIS_LEFT_X") { rawAxis = VirtualControllerAxis::AXIS_LEFT_X; }
        else if (string == "AXIS_LEFT_Y") { rawAxis = VirtualControllerAxis::AXIS_LEFT_Y; }
        else if (string == "AXIS_RIGHT_X") { rawAxis = VirtualControllerAxis::AXIS_RIGHT_X; }
        else if (string == "AXIS_RIGHT_Y") { rawAxis = VirtualControllerAxis::AXIS_RIGHT_Y; }

        else if (string == "AXIS_MOUSE_X") { rawAxis = VirtualControllerAxis::MOUSE_X; }
        else if (string == "AXIS_MOUSE_Y") { rawAxis = VirtualControllerAxis::MOUSE_Y; }
        else if (string == "AXIS_MOUSE_DELTA_X") { rawAxis = VirtualControllerAxis::MOUSE_DELTA_X; }
        else if (string == "AXIS_MOUSE_DELTA_Y") { rawAxis = VirtualControllerAxis::MOUSE_DELTA_Y; }
        else if (string == "AXIS_MOUSEWHEEL") { rawAxis = VirtualControllerAxis::MOUSE_WHEEL; }

        else { printf("InputMappingHelpers: Unknown VirtualControllerAxis name: %s\n", string.c_str()); }

        return rawAxis;
    }

    Action InputMappingHelpers::StringToAction(const std::string& string)
    {
        Action action = Action::_INVALID;
        if (string == "INTERACT") { action = Action::INTERACT; }
        else if (string == "INTERACT_ALT") { action = Action::INTERACT_ALT; }

        else if (string == "MENU_NAVIGATE_UP") { action = Action::MENU_NAVIGATE_UP; }
        else if (string == "MENU_NAVIGATE_DOWN") { action = Action::MENU_NAVIGATE_DOWN; }
        else if (string == "MENU_NAVIGATE_LEFT") { action = Action::MENU_NAVIGATE_LEFT; }
        else if (string == "MENU_NAVIGATE_RIGHT") { action = Action::MENU_NAVIGATE_RIGHT; }
        else if (string == "MENU_SELECT") { action = Action::MENU_SELECT; }
        else if (string == "MENU_CANCEL") { action = Action::MENU_CANCEL; }
        else if (string == "MOVE_UP") { action = Action::MOVE_UP; }
        else if (string == "MOVE_DOWN") { action = Action::MOVE_DOWN; }
        else if (string == "MOVE_LEFT") { action = Action::MOVE_LEFT; }
        else if (string == "MOVE_RIGHT") { action = Action::MOVE_RIGHT; }

        else if (string == "CAMERA_PAN_MODE") { action = Action::CAMERA_PAN_MODE; }
        else if (string == "CAMERA_PAN_UP") { action = Action::CAMERA_PAN_UP; }
        else if (string == "CAMERA_PAN_DOWN") { action = Action::CAMERA_PAN_DOWN; }
        else if (string == "CAMERA_PAN_LEFT") { action = Action::CAMERA_PAN_LEFT; }
        else if (string == "CAMERA_PAN_RIGHT") { action = Action::CAMERA_PAN_RIGHT; }

        else if (string == "NAVIGATE_LEVEL_UP") { action = Action::NAVIGATE_LEVEL_UP; }
        else if (string == "NAVIGATE_LEVEL_DOWN") { action = Action::NAVIGATE_LEVEL_DOWN; }

        else if (string == "SELECT_NEXT_MAP_ELEMENT") { action = Action::SELECT_NEXT_MAP_ELEMENT; }
        else if (string == "SELECT_PREVIOUS_MAP_ELEMENT") { action = Action::SELECT_PREVIOUS_MAP_ELEMENT; }

        else if (string == "HOTKEY_1") { action = Action::HOTKEY_1; }
        else if (string == "HOTKEY_2") { action = Action::HOTKEY_2; }
        else if (string == "HOTKEY_3") { action = Action::HOTKEY_3; }
        else if (string == "HOTKEY_4") { action = Action::HOTKEY_4; }
        else if (string == "HOTKEY_5") { action = Action::HOTKEY_5; }
        else if (string == "HOTKEY_6") { action = Action::HOTKEY_6; }
        else if (string == "HOTKEY_7") { action = Action::HOTKEY_7; }
        else if (string == "HOTKEY_8") { action = Action::HOTKEY_8; }
        else if (string == "HOTKEY_9") { action = Action::HOTKEY_9; }

        else if (string == "ROTATE_CW") { action = Action::ROTATE_CW; }
        else if (string == "ROTATE_CCW") { action = Action::ROTATE_CCW; }

        else if (string == "START_PATHING") { action = Action::START_PATHING; }

        else { printf("InputMappingHelpers: Unknown Action name: %s\n", string.c_str()); }

        return action;
    }

    Range InputMappingHelpers::StringToRange(const std::string& string)
    {
        Range range = Range::_INVALID;
        if (string == "MOVE_X") { range = Range::MOVE_X; }
        else if (string == "MOVE_Y") { range = Range::MOVE_Y; }
        else if (string == "LOOK_X") { range = Range::LOOK_X; }
        else if (string == "LOOK_Y") { range = Range::LOOK_Y; }

        else if (string == "CURSOR_X") { range = Range::CURSOR_X; }
        else if (string == "CURSOR_Y") { range = Range::CURSOR_Y; }
        else if (string == "CURSOR_DELTA_X") { range = Range::CURSOR_DELTA_X; }
        else if (string == "CURSOR_DELTA_Y") { range = Range::CURSOR_DELTA_Y; }
        else if (string == "CAMERA_ZOOM") { range = Range::CAMERA_ZOOM; }

        else { printf("InputContext: Unknown Range name: %s\n", string.c_str()); }

        return range;
    }

    SDL_Scancode InputMappingHelpers::StringToScanCode(const std::string& string)
    {
        SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

        if (string == "A") { scancode = SDL_SCANCODE_A; }
        else if (string == "B") { scancode = SDL_SCANCODE_B; }
        else if (string == "C") { scancode = SDL_SCANCODE_C; }
        else if (string == "D") { scancode = SDL_SCANCODE_D; }
        else if (string == "E") { scancode = SDL_SCANCODE_E; }
        else if (string == "F") { scancode = SDL_SCANCODE_F; }
        else if (string == "G") { scancode = SDL_SCANCODE_G; }
        else if (string == "H") { scancode = SDL_SCANCODE_H; }
        else if (string == "I") { scancode = SDL_SCANCODE_I; }
        else if (string == "J") { scancode = SDL_SCANCODE_J; }
        else if (string == "K") { scancode = SDL_SCANCODE_K; }
        else if (string == "L") { scancode = SDL_SCANCODE_L; }
        else if (string == "M") { scancode = SDL_SCANCODE_M; }
        else if (string == "N") { scancode = SDL_SCANCODE_N; }
        else if (string == "O") { scancode = SDL_SCANCODE_O; }
        else if (string == "P") { scancode = SDL_SCANCODE_P; }
        else if (string == "Q") { scancode = SDL_SCANCODE_Q; }
        else if (string == "R") { scancode = SDL_SCANCODE_R; }
        else if (string == "S") { scancode = SDL_SCANCODE_S; }
        else if (string == "T") { scancode = SDL_SCANCODE_T; }
        else if (string == "U") { scancode = SDL_SCANCODE_U; }
        else if (string == "V") { scancode = SDL_SCANCODE_V; }
        else if (string == "W") { scancode = SDL_SCANCODE_W; }
        else if (string == "X") { scancode = SDL_SCANCODE_X; }
        else if (string == "Y") { scancode = SDL_SCANCODE_Y; }
        else if (string == "Z") { scancode = SDL_SCANCODE_Z; }

        else if (string == "0") { scancode = SDL_SCANCODE_0; }
        else if (string == "1") { scancode = SDL_SCANCODE_1; }
        else if (string == "2") { scancode = SDL_SCANCODE_2; }
        else if (string == "3") { scancode = SDL_SCANCODE_3; }
        else if (string == "4") { scancode = SDL_SCANCODE_4; }
        else if (string == "5") { scancode = SDL_SCANCODE_5; }
        else if (string == "6") { scancode = SDL_SCANCODE_6; }
        else if (string == "7") { scancode = SDL_SCANCODE_7; }
        else if (string == "8") { scancode = SDL_SCANCODE_8; }
        else if (string == "9") { scancode = SDL_SCANCODE_9; }

        else if (string == "UP") { scancode = SDL_SCANCODE_UP; }
        else if (string == "DOWN") { scancode = SDL_SCANCODE_DOWN; }
        else if (string == "LEFT") { scancode = SDL_SCANCODE_LEFT; }
        else if (string == "RIGHT") { scancode = SDL_SCANCODE_RIGHT; }

        return scancode;
    }

    int InputMappingHelpers::StringToMouseButton(const std::string& string)
    {
        int mouseButton = -1;

        if (string == "MOUSE_LEFT") { mouseButton = SDL_BUTTON_LEFT; }
        else if (string == "MOUSE_RIGHT") { mouseButton = SDL_BUTTON_X1; }
        else if (string == "MOUSE_MIDDLE") { mouseButton = SDL_BUTTON_MIDDLE; }

        return mouseButton;
    }

    MouseMoveRangeName InputMappingHelpers::StringToMouseMoveRangeName(const std::string& string)
    {
        MouseMoveRangeName rangeName = MouseMoveRangeName::_INVALID;

        if (string == "MOUSE_X") { rangeName = MouseMoveRangeName::X; }
        else if (string == "MOUSE_Y") { rangeName = MouseMoveRangeName::Y; }
        else if (string == "MOUSE_DELTA_X") { rangeName = MouseMoveRangeName::DELTA_X; }
        else if (string == "MOUSE_DELTA_Y") { rangeName = MouseMoveRangeName::DELTA_Y; }
        else if (string == "MOUSE_WHEEL_DELTA") { rangeName = MouseMoveRangeName::WHEEL_DELTA; }

        return rangeName;
    }

    int InputMappingHelpers::StringToControllerButton(const std::string& string)
    {
        int button = SDL_CONTROLLER_BUTTON_INVALID;

        if (string == "-") { button = SDL_CONTROLLER_BUTTON_INVALID; }
        else if (string == "A") { button = SDL_CONTROLLER_BUTTON_A; }
        else if (string == "B") { button = SDL_CONTROLLER_BUTTON_B; }
        else if (string == "X") { button = SDL_CONTROLLER_BUTTON_X; }
        else if (string == "Y") { button = SDL_CONTROLLER_BUTTON_Y; }

        else if (string == "DPAD_UP") { button = SDL_CONTROLLER_BUTTON_DPAD_UP; }
        else if (string == "DPAD_DOWN") { button = SDL_CONTROLLER_BUTTON_DPAD_DOWN; }
        else if (string == "DPAD_LEFT") { button = SDL_CONTROLLER_BUTTON_DPAD_LEFT; }
        else if (string == "DPAD_RIGHT") { button = SDL_CONTROLLER_BUTTON_DPAD_RIGHT; }

        else { printf("InputMappingHelpers: Unknown pad button: %s\n", string.c_str()); }

        return button;
    }

    extern int InputMappingHelpers::StringToControllerAxis(const std::string& string)
    {
        int axis = SDL_CONTROLLER_AXIS_INVALID;

        if (string == "-") { axis = SDL_CONTROLLER_AXIS_INVALID; }
        else if (string == "STICK_LEFT_X") { axis = SDL_CONTROLLER_AXIS_LEFTX; }
        else if (string == "STICK_LEFT_Y") { axis = SDL_CONTROLLER_AXIS_LEFTY; }
        else if (string == "STICK_RIGHT_X") { axis = SDL_CONTROLLER_AXIS_RIGHTX; }
        else if (string == "STICK_RIGHT_Y") { axis = SDL_CONTROLLER_AXIS_RIGHTY; }

        else { printf("InputMappingHelpers: Unknown controller axis: %s\n", string.c_str()); }

        return axis;
    }
}