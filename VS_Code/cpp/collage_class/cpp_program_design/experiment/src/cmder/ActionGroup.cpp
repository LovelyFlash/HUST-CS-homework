#include "ActionGroup.hpp"
#include "CmderFactory.hpp"

#include <vector>
#include <algorithm>

namespace adas
{
    class MoveAction final
    {
    public:
        void operator()(PoseHandler &poseHandler) const noexcept
        {
            poseHandler.Move();
        }
    };

    class TurnLeftAction final
    {
    public:
        void operator()(PoseHandler &poseHandler) const noexcept
        {
            poseHandler.TurnLeft();
        }
    };

    class ReverseTurnLeftAction final
    {
    public:
        void operator()(PoseHandler &poseHandler) const noexcept
        {
            poseHandler.TurnRight();
        }
    };

    class TurnRightAction final
    {
    public:
        void operator()(PoseHandler &poseHandler) const noexcept
        {
            poseHandler.TurnRight();
        }
    };

    class ReverseTurnRightAction final
    {
    public:
        void operator()(PoseHandler &poseHandler) const noexcept
        {
            poseHandler.TurnLeft();
        }
    };

    class BeReverseAction final
    {
    public:
        void operator()(PoseHandler &poseHandler) const noexcept
        {
            poseHandler.Reverse();
        }
    };

    class BeFastAction final
    {
    public:
        void operator()(PoseHandler &poseHandler) const noexcept
        {
            poseHandler.Fast();
        }
    };

    ActionGroup::ActionGroup(const std::list<ActionType> &actions) noexcept : actions(actions) {}

    ActionGroup &ActionGroup::operator+=(const ActionGroup &rhs) noexcept
    {
        for (ActionType act : rhs.actions)
            actions.push_back(act);
        return *this;
    }

    void ActionGroup::PushAction(const ActionType ActionType) noexcept
    {
        actions.push_back(ActionType);
    }

    void ActionGroup::DoOperate(PoseHandler &poseHandler) const noexcept
    {
        static std::vector<std::function<void(PoseHandler & poseHandler)>> actionVec = {
            MoveAction(),
            TurnLeftAction(),
            ReverseTurnLeftAction(),
            TurnRightAction(),
            ReverseTurnRightAction(),
            BeReverseAction(),
            BeFastAction(),
        };

        std::for_each(actions.begin(), actions.end(), [&poseHandler](const ActionType actionType) mutable noexcept
                      { actionVec[static_cast<__UINT16_TYPE__>(actionType)](poseHandler); });
    }

}