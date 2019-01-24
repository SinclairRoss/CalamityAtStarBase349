#include "Timer_DeltaTimer.h"

Timer_DeltaTimer::Timer_DeltaTimer() :
    m_LastTick(SDL_GetTicks())
{}

void Timer_DeltaTimer::Tick()
{
    Uint32 tick = SDL_GetTicks();

    m_DeltaTime = (tick - m_LastTick) / 1000.0f;
    m_LastTick = tick;
}

void Timer_DeltaTimer::Restart()
{
    m_LastTick = SDL_GetTicks();
}

float Timer_DeltaTimer::GetDeltaTime() const
{
    return m_DeltaTime;
}