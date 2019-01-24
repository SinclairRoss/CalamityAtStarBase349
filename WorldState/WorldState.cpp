#include "WorldState.h"

namespace WorldState
{
    namespace Internal
    {
#define BOOLEAN_STATE_DECLARATION(name) bool name = true;
        BOOLEAN_STATE_DECLARE
#undef BOOLEAN_STATE_DECLARATION

#define BOOLEAN_STATE_DECLARATION(name) {BooleanState::name, &name},
        std::unordered_map<BooleanState, bool*> Map_BooleanState =
        {
            BOOLEAN_STATE_DECLARE
        };
#undef BOOLEAN_STATE_DECLARATION
    }

    bool GetState(const BooleanState state)
    {
        return *Internal::Map_BooleanState[state];
    }

    void SetState(const BooleanState state, const bool val)
    {
        *Internal::Map_BooleanState[state] = val;
    }

    void ToggleState(const BooleanState state)
    {
        *Internal::Map_BooleanState[state] = !*Internal::Map_BooleanState[state];
    }

    BooleanState StringToBooleanState(const std::string& string)
    {
        BooleanState ws = BooleanState::_INVALID;
#define BOOLEAN_STATE_DECLARATION(name) if(string == #name) { ws = BooleanState::name; }
            BOOLEAN_STATE_DECLARE
#undef BOOLEAN_STATE_DECLARATION
        return ws;
    }
}