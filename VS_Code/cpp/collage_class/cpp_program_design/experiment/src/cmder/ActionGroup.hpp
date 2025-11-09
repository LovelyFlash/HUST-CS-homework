#pragma once

#include <list>

#include "core/PoseHandler.hpp"

namespace adas
{
    enum class ActionType : __UINT16_TYPE__
    {
        MOVE_1_STEP_ACTION = 0,
        TURNLEFT_ACTION,
        REVERSE_TURNLEFT_ACTION,
        TURNRIGHT_ACTION,
        REVERSE_TURNRIGHT_ACTION,
        BE_REVERSE_ACTION,
        BE_FAST_ACTION,
    };

    class ActionGroup final
    {
    public:
        ActionGroup(void) = default;
        explicit ActionGroup(const std::list<ActionType> &actions) noexcept;
        ~ActionGroup() = default;
        ActionGroup &operator+=(const ActionGroup &rhs) noexcept;

    public:
        void PushAction(const ActionType ActionType) noexcept;
        void DoOperate(PoseHandler &poseHandler) const noexcept;

    private:
        std::list<ActionType> actions;
    };
}
