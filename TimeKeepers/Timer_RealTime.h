#pragma once

#include <SDL.h>

class Timer_RealTime
{
	public:
        Timer_RealTime();

		void Start();
		void Stop();
		void Restart();

		Uint32 GetTime_Millis();
        float GetTime_Seconds();

	private:

		bool m_Active;
		Uint32 m_StartTicks;
};

