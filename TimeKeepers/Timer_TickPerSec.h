#pragma once

#include "Timer_RealTime.h"

class Timer_TickPerSec
{
	public:
		Timer_TickPerSec();

		void Tick();

		double GetTicksPerSecond();

	private:
        Timer_RealTime m_Timer;
		int m_Ticks;

		double m_TicksPerSecond;
};