#pragma once

#include <functional>

namespace PubSub
{
    using TopicCallback = std::function<void()>;
}