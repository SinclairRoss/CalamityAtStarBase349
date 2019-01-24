#include "MappedInput.h"

namespace Input
{

    MappedInput::MappedInput()
    {}

    void MappedInput::ButtonPressed(Action action)
    {
        m_Pressed.insert(action);
        m_Held.insert(action);
    }

    void MappedInput::ButtonReleased(Action action)
    {
        m_Released.insert(action);
        m_Held.erase(action);
    }

    void MappedInput::SetRange(Range range, float val)
    {
        m_Ranges[range] = val;
    }

    bool MappedInput::IsPressed(Action action) const
    {
        return m_Pressed.find(action) != m_Pressed.end();
    }

    bool MappedInput::IsReleased(Action action) const
    {
        return m_Released.find(action) != m_Released.end();
    }

    bool MappedInput::IsHeld(Action action) const
    {
        return m_Held.find(action) != m_Held.end();
    }

    float MappedInput::GetRange(Range range) const
    {
        auto pair = m_Ranges.find(range);
        float val = (pair != m_Ranges.end()) ? pair->second : 0.0f;

        return val;
    }

    void MappedInput::Clear()
    {
        m_Pressed.clear();
        m_Released.clear();
        m_Ranges.clear();
    }
}