#include "Topic.h"

Topic::Topic(BroadcastTopics broadcastTopic) :
    m_BroadcastTopic(broadcastTopic)
{}

void Topic::Broadcast()
{
    for (PubSub::TopicCallback callback : m_Callbacks)
    {
        callback();
    }
}

void Topic::AddTopicCallback(PubSub::TopicCallback callback)
{
    m_Callbacks.push_back(callback);
}

BroadcastTopics Topic::GetTopic() const
{
    return m_BroadcastTopic;
}