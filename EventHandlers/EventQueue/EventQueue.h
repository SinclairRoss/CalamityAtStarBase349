#pragma once

#include <queue>

#include "Enums\EventType.h"

class EventQueue
{
    public:
        EventQueue();

        void PostEvent(EventType event);
        EventType PopQueue();

        bool EventsRemaining();

    private:
        std::queue<EventType> m_EventQueue;
};