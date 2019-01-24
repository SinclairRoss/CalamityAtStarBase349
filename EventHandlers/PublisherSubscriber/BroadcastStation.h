#pragma once

#include <functional>
#include <vector>

#include "Enums\BroadcastTopics.h"
#include "Topic.h"
#include "Types.h"

class BroadcastStation
{
    public:
        BroadcastStation();

        void Subscribe(BroadcastTopics topic, PubSub::TopicCallback callback);
        void BroadcastTopic(BroadcastTopics topic);

    private:
        
        BroadcastStation(const BroadcastStation&) = delete;
        BroadcastStation& operator=(const BroadcastStation&) = delete;

        BroadcastStation(BroadcastStation&&) = delete;
        BroadcastStation& operator=(BroadcastStation&&) = delete;

        Topic& GetTopic(BroadcastTopics topic);

        std::vector<Topic> m_Topics;
};
