#pragma once

#include "CmderOrchestrator.hpp"

namespace adas
{
    class NormalOrchestrator : public CmderOrchestrator
    {
    public:
        ActionGroup Move(const PoseHandler &poseHandler) const noexcept override
        {
            ActionGroup actionGroup;
            actionGroup += OnFast(poseHandler);
            actionGroup.PushAction(ActionType::MOVE_1_STEP_ACTION);
            return actionGroup;
        }

        ActionGroup TurnLeft(const PoseHandler &poseHandler) const noexcept override
        {
            ActionGroup actionGroup;
            actionGroup += OnFast(poseHandler);
            if (poseHandler.IsReverse())
                actionGroup.PushAction(ActionType::REVERSE_TURNLEFT_ACTION);
            else
                actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
            return actionGroup;
        }

        ActionGroup TurnRight(const PoseHandler &poseHandler) const noexcept override
        {
            ActionGroup actionGroup;
            actionGroup += OnFast(poseHandler);
            if (poseHandler.IsReverse())
                actionGroup.PushAction(ActionType::REVERSE_TURNRIGHT_ACTION);
            else
                actionGroup.PushAction(ActionType::TURNRIGHT_ACTION);
            return actionGroup;
        }

        ActionGroup TurnRound(const PoseHandler &poseHandler) const noexcept override
        {
            if (poseHandler.IsReverse())
                return ActionGroup();
            else
            {
                ActionGroup actionGroup;
                actionGroup += OnFast(poseHandler);
                actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
                actionGroup.PushAction(ActionType::MOVE_1_STEP_ACTION);
                actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
                return actionGroup;
            }
        }

    protected:
        ActionGroup OnFast(const PoseHandler &poseHandler) const noexcept
        {
            if (poseHandler.IsFast())
                return ActionGroup({ActionType::MOVE_1_STEP_ACTION});
            return ActionGroup();
        }
    };
}