#pragma once

#include <vector>

namespace GOAP
{
    using ActionStack = std::vector<std::unique_ptr<Action>>;
}