#pragma once

#include <SDL.h>

class Timer_DeltaTimer
{
    public:
        Timer_DeltaTimer();

        void Tick();
        void Restart();

        float GetDeltaTime() const;

    private:

        Uint32 m_LastTick;
        float m_DeltaTime;
};