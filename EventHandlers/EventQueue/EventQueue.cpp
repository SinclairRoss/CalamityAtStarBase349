#include "EventQueue.h"

EventQueue::EventQueue()
{}

void EventQueue::PostEvent(EventType event)
{
    m_EventQueue.push(event);
}

EventType EventQueue::PopQueue()
{
    EventType event = EventType::_NULL_EVENT;

    if (!m_EventQueue.empty())
    {
        event = m_EventQueue.front();
        m_EventQueue.pop();
    }

    return event;
}

bool EventQueue::EventsRemaining()
{
    bool eventsRemaining = !m_EventQueue.empty();
    return eventsRemaining;
}