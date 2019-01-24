#pragma once

namespace Input
{
    enum class Action
    {
        INTERACT,

        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,

        MENU_NAVIGATE_UP,
        MENU_NAVIGATE_DOWN,
        MENU_NAVIGATE_LEFT,
        MENU_NAVIGATE_RIGHT,
        MENU_SELECT,
        MENU_CANCEL,

        // Level Editor.
        INTERACT_ALT,

        CAMERA_PAN_MODE,
        CAMERA_PAN_UP,
        CAMERA_PAN_DOWN,
        CAMERA_PAN_LEFT,
        CAMERA_PAN_RIGHT,

        ROTATE_CW,
        ROTATE_CCW,

        NAVIGATE_LEVEL_UP,
        NAVIGATE_LEVEL_DOWN,

        SELECT_NEXT_MAP_ELEMENT,
        SELECT_PREVIOUS_MAP_ELEMENT,

        HOTKEY_1,
        HOTKEY_2,
        HOTKEY_3,
        HOTKEY_4,
        HOTKEY_5,
        HOTKEY_6,
        HOTKEY_7,
        HOTKEY_8,
        HOTKEY_9,

        // Pathing test
        START_PATHING,

        _INVALID,
    };

    enum class Range
    {
        MOVE_X,
        MOVE_Y,
        LOOK_X,
        LOOK_Y,

        // Level Editor.
        CURSOR_X,
        CURSOR_Y,
        CURSOR_DELTA_X,
        CURSOR_DELTA_Y,
        CAMERA_ZOOM,

        _INVALID
    };
}