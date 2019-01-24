#pragma once

#include <unordered_map>

namespace WorldState
{
#define BOOLEAN_STATE_DECLARE \
        BOOLEAN_STATE_DECLARATION(SWITCH_ON)

    // Enum declaration
#define BOOLEAN_STATE_DECLARATION(name) name,
    enum class BooleanState
    {
        BOOLEAN_STATE_DECLARE

        _COUNT,
        _INVALID
    };
#undef BOOLEAN_STATE_DECLARATION

    namespace Internal
    {
        // Variable declaration
#define BOOLEAN_STATE_DECLARATION(name) extern bool name;
        BOOLEAN_STATE_DECLARE
#undef BOOLEAN_STATE_DECLARATION

        extern std::unordered_map<BooleanState, bool*> Map_BooleanState;
    }

    extern bool GetState(const BooleanState state);
    extern void SetState(const BooleanState state, const bool val);
    void ToggleState(const BooleanState state);
    extern BooleanState StringToBooleanState(const std::string& string); // This function should not be used regularly, part of loading phase only.
}