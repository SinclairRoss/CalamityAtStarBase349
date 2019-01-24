#pragma once

#include "EventQueue\EventQueue.h"
#include "PublisherSubscriber\BroadcastStation.h"

namespace EventHandlers
{
    extern EventQueue MainEventQueue;
    extern BroadcastStation MainBroadcastStation;
}