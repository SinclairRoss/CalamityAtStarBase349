#pragma once

enum class VirtualControllerButton
{
    BUTTON_A,
    BUTTON_B,
    BUTTON_X,
    BUTTON_Y,

    DPAD_DOWN,
    DPAD_UP,
    DPAD_LEFT,
    DPAD_RIGHT,

    MOUSE_LEFT,
    MOUSE_RIGHT,
    MOUSE_MIDDLE,

    ROTATE_CW,
    ROATE_CCW,

    HOTKEY_1,
    HOTKEY_2,
    HOTKEY_3,
    HOTKEY_4,
    HOTKEY_5,
    HOTKEY_6,
    HOTKEY_7,
    HOTKEY_8,
    HOTKEY_9,

    INVALID
};

enum class VirtualControllerAxis
{
    AXIS_LEFT_X,
    AXIS_LEFT_Y,
    AXIS_RIGHT_X,
    AXIS_RIGHT_Y,

    MOUSE_X,
    MOUSE_Y,
    MOUSE_DELTA_X,
    MOUSE_DELTA_Y,

    MOUSE_WHEEL,

    _INVALID
};