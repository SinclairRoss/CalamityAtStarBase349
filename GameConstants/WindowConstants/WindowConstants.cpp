#include "WindowConstants.h"

#include "Core\FileParsing\XMLParser.h"

namespace GameConstants
{
    WindowConstants::WindowConstants()
    {
        XMLParser::XMLDoc_ptr contextList = XMLParser::ReadFile("WindowData/WindowConstants.xml");
        rapidxml::xml_node<> *root = contextList->first_node();

        m_ScreenWidth = atoi(root->first_node("Screen_Width")->value());
        m_ScreenHeight = atoi(root->first_node("Screen_Height")->value());
        m_AspectRatio = static_cast<float>(m_ScreenWidth) / m_ScreenHeight;

        m_WindowMode = StringToWindowFlag(root->first_node("WindowMode")->value());

        m_FrameRate = atoi(root->first_node("FrameRate")->value());
        m_VSyncMode = StringToVSyncState(root->first_node("VSync")->value());
    }

    int WindowConstants::StringToWindowFlag(const std::string& string) const
    {
        int flag = -1;

        if (string == "FULLSCREEN") { flag = SDL_WINDOW_FULLSCREEN; }
        else if (string == "DESKTOP") { flag = SDL_WINDOW_FULLSCREEN_DESKTOP; }
        else if (string == "WINDOW") { flag = 0; }
        else { printf("Window Constants: Unknown window mode %s\n", string.c_str()); }

        return flag;
    }

    int WindowConstants::StringToVSyncState(const std::string& string) const
    {
        int state = -1;

        if (string == "ON") { state = 1; }
        else if (string == "OFF") { state = 0; }

        return state;
    }

    int WindowConstants::ScreenWidth() const { return m_ScreenWidth; }
    int WindowConstants::ScreenHeight() const { return m_ScreenHeight; }
    float WindowConstants::AspectRatio() const { return m_AspectRatio; }
    int WindowConstants::WindowMode() const { return m_WindowMode; }
    int WindowConstants::FrameRate() const { return m_FrameRate; }
    int WindowConstants::VSyncMode() const { return m_VSyncMode; }
}