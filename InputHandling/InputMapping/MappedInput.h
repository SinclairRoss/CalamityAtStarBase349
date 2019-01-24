#pragma once

#include <unordered_map>
#include <set>

#include "InputConstants.h"

namespace Input
{
    class MappedInput
    {
        public:
            MappedInput();

            void ButtonPressed(Action action);
            void ButtonReleased(Action action);
            void SetRange(Range range, float val);

            bool IsPressed(Action action) const;
            bool IsReleased(Action action) const;
            bool IsHeld(Action action) const;
            float GetRange(Range range) const;

            void Clear();

        private:
            std::set<Action> m_Pressed;
            std::set<Action> m_Released;
            std::set<Action> m_Held;
            std::unordered_map<Range, float> m_Ranges;
    };
}