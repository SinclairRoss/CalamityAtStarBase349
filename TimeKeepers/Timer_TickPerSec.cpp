#include "Timer_TickPerSec.h"

#include <SDL.h>

Timer_TickPerSec::Timer_TickPerSec() :
	m_Timer(),
	m_Ticks(0),
	m_TicksPerSecond(0.0)
{
	m_Timer.Start();
}

void Timer_TickPerSec::Tick()
{
	++m_Ticks;

	double timeSeconds = m_Timer.GetTime_Seconds();
	m_TicksPerSecond = m_Ticks / (timeSeconds);

	if(timeSeconds > 1.0)
	{ 
		m_Ticks = 0;
		m_Timer.Restart();
	}
}

double Timer_TickPerSec::GetTicksPerSecond()
{
	return m_TicksPerSecond;
}