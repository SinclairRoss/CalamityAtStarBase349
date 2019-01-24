#pragma once

#include <functional>
#include <list>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "InputConstants.h"
#include "InputContext.h"
#include "MappedInput.h"
#include "VirtualControllerInputs.h"

namespace Input
{
    using InputCallback = std::function<void(const MappedInput& inputs)>;

    class InputMapper
    {
        public:
            InputMapper();

            InputMapper(const InputMapper&) = delete;
            InputMapper& operator=(const InputMapper&) = delete;
            InputMapper(const InputMapper&&) = delete;
            InputMapper& operator=(const InputMapper&&) = delete;

            void ClearInput();
            void SetVirtualControllerButton_Down(VirtualControllerButton button);
            void SetVirtualControllerButton_Up(VirtualControllerButton button);
            void SetVirtualControllerAxisValue(VirtualControllerAxis axis, float value);

            void Dispatch() const;

            void AddCallback(InputCallback callback, int priority);
            void ClearCallbackTable();

            void PushContext(const std::string& name);
            void PopContext();
            void ClearContextStack();

        private:
            Input::Action MapButtonToAction(VirtualControllerButton button) const;

            std::unordered_map<std::string, std::unique_ptr<InputContext>> m_InputContexts;
            std::list<InputContext*> m_ActiveContexts;

            std::vector<InputCallback> m_CallbackTable;
            Input::MappedInput m_CurrentMappedInput;
        };
}