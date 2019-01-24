#include "BroadcastStation.h"

BroadcastStation::BroadcastStation() :
    m_Topics()
{
    int topicCount = static_cast<int>(BroadcastTopics::_COUNT);
    m_Topics.reserve(topicCount);

    for (int i = 0; i < topicCount; ++i)
    {
        m_Topics.emplace_back(static_cast<BroadcastTopics>(i));
    }
}

void BroadcastStation::Subscribe(BroadcastTopics topic, PubSub::TopicCallback callback)
{
    GetTopic(topic).AddTopicCallback(callback);
}

void BroadcastStation::BroadcastTopic(BroadcastTopics topic)
{
    GetTopic(topic).Broadcast();
}

Topic& BroadcastStation::GetTopic(BroadcastTopics topic)
{
    int topicIndex = static_cast<int>(topic);
    return m_Topics[topicIndex];
}