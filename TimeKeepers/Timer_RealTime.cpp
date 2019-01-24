#include "Timer_RealTime.h"

Timer_RealTime::Timer_RealTime() :
	m_Active(false),
	m_StartTicks(0)
{}

void Timer_RealTime::Start()
{
	m_Active = true;
	m_StartTicks = SDL_GetTicks();
}

void Timer_RealTime::Stop()
{
	m_Active = false;
	m_StartTicks = 0;
}

void Timer_RealTime::Restart()
{
	m_StartTicks = SDL_GetTicks();
}

Uint32 Timer_RealTime::GetTime_Millis()
{
	Uint32 time = (m_Active) ? SDL_GetTicks() - m_StartTicks : 0;
	return time;
}

float Timer_RealTime::GetTime_Seconds()
{
    float time = GetTime_Millis() / 1000.0f;
	return time;
}