#pragma once

#include <sdl.h>
#include <string>

namespace GameConstants
{
    class WindowConstants
    {
        public:
            WindowConstants();

            int ScreenWidth() const;
            int ScreenHeight() const;
            float AspectRatio() const;
            
            int WindowMode() const;

            int FrameRate() const;
            int VSyncMode() const;

        private:
            int StringToWindowFlag(const std::string& string) const;
            int StringToVSyncState(const std::string& string) const;

            int m_ScreenWidth;
            int m_ScreenHeight;
            float m_AspectRatio;

            int m_WindowMode;

            int m_FrameRate;
            int m_VSyncMode;
    };
}