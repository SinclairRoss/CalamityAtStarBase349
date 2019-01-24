#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "VirtualControllerInputs.h"
#include "InputConstants.h"

namespace Input
{
    class InputContext
    {
        public:
            InputContext(const std::string& path);
            ~InputContext();

            InputContext(const InputContext&) = delete;
            InputContext& operator=(const InputContext&) = delete;
            InputContext(const InputContext&&) = delete;
            InputContext& operator=(const InputContext&&) = delete;

            Action MapButtonToAction(VirtualControllerButton button) const;
            bool MapAxisToRange(VirtualControllerAxis axis, Range& out) const;

        private:

            std::unordered_map<VirtualControllerButton, Action> m_ActionMap;
            std::unordered_map<VirtualControllerAxis, Range> m_RangeMap;
    };
}