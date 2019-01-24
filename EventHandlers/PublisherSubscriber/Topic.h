#pragma once

#include <vector>

#include "Enums\BroadcastTopics.h"
#include "Types.h"

class Topic
{
    public:
        Topic(BroadcastTopics broadcastTopic);

        void Broadcast();
        void AddTopicCallback(PubSub::TopicCallback callback);

        BroadcastTopics GetTopic() const;

    private:
        BroadcastTopics m_BroadcastTopic;

        std::vector<PubSub::TopicCallback> m_Callbacks;
};