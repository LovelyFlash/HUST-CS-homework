#pragma once

#include "core/PoseHandler.hpp"
#include "CmderOrchestrator.hpp"

#include <functional>

namespace adas
{
    class MoveCommand final
    {
    public:
        ActionGroup operator()(const PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
        {
            return orchestrator.Move(poseHandler);
        }
    };

    class TurnLeftCommand final
    {
    public:
        ActionGroup operator()(const PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
        {
            return orchestrator.TurnLeft(poseHandler);
        }
    };

    class TurnRightCommand final
    {
    public:
        ActionGroup operator()(const PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
        {
            return orchestrator.TurnRight(poseHandler);
        }
    };

    class TurnRoundCommand final
    {
    public:
        ActionGroup operator()(const PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
        {
            return orchestrator.TurnRound(poseHandler);
        }
    };

    class FastCommand final
    {
    public:
        ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
        {
            ActionGroup actionGroup;
            actionGroup.PushAction(ActionType::BE_FAST_ACTION);
            return actionGroup;
        }
    };

    class ReverseCommand final
    {
    public:
        ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
        {
            ActionGroup actionGroup;
            actionGroup.PushAction(ActionType::BE_REVERSE_ACTION);
            return actionGroup;
        }
    };
    /***
     * 以下为单车型命令
     */
    // class MoveCommand final
    // {
    // public:
    //     // 现在MoveCommand不再直接调用poseHander执行动作
    //     // 而是返回一个ActionGroup对象，里面包含了要执行命令的类型
    //     // 要执行命令的类型通过枚举ActionType表示
    //     // 现在动作的真正执行都是通过ActionGroup来完成
    //     ActionGroup operator()(PoseHandler &poseHandler) const noexcept
    //     {
    //         // 创建actionGroup对象
    //         ActionGroup actionGroup;
    //         if (poseHandler.IsFast())
    //             actionGroup.PushAction(ActionType::MOVE_1_STEP_ACTION);
    //         actionGroup.PushAction(ActionType::MOVE_1_STEP_ACTION);

    //         return actionGroup;
    //     }
    // };

    // class TurnLeftCommand final
    // {
    // public:
    //     ActionGroup operator()(PoseHandler &poseHandler) const noexcept
    //     {
    //         ActionGroup actionGroup;
    //         if (poseHandler.IsFast())
    //             actionGroup.PushAction(ActionType::MOVE_1_STEP_ACTION);
    //         if (poseHandler.IsReverse())
    //             actionGroup.PushAction(ActionType::REVERSE_TURNLEFT_ACTION);
    //         else
    //             actionGroup.PushAction(ActionType::TURNLEFT_ACTION);

    //         return actionGroup;
    //     }
    // };

    // class TurnRightCommand final
    // {
    // public:
    //     ActionGroup operator()(PoseHandler &poseHandler) const noexcept
    //     {
    //         ActionGroup actionGroup;
    //         if (poseHandler.IsFast())
    //             actionGroup.PushAction(ActionType::MOVE_1_STEP_ACTION);
    //         if (poseHandler.IsReverse())
    //             actionGroup.PushAction(ActionType::REVERSE_TURNRIGHT_ACTION);
    //         else
    //             actionGroup.PushAction(ActionType::TURNRIGHT_ACTION);

    //         return actionGroup;
    //     }
    // };

    // class TurnRoundCommand final
    // {
    // public:
    //     ActionGroup operator()(PoseHandler &poseHandler) const noexcept
    //     {
    //         if (poseHandler.IsReverse())
    //             return ActionGroup();
    //         else
    //         {
    //             ActionGroup actionGroup;
    //             if (poseHandler.IsFast())
    //                 actionGroup.PushAction(ActionType::MOVE_1_STEP_ACTION);
    //             actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
    //             actionGroup.PushAction(ActionType::MOVE_1_STEP_ACTION);
    //             actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
    //             return actionGroup;
    //         }
    //     }
    // };

    /***
     * 以下代码使用ICommand作为基类进行各个动作的定义
     */
    // class ICommand
    // {
    // public:
    //     virtual ~ICommand() = default;
    //     virtual void DoOperate(PoseHandler &poseHandler) const noexcept = 0;
    // };

    // class MoveCommand final : public
    // // ICommand 定义一个嵌套类MoveCommand，完成 Move动作(M指令)
    // {
    // public:
    //     // 执行Move动作，需要委托poseHandlerImp&执行器来完成动作
    //     void DoOperate(PoseHandler &poseHandler) const noexcept override
    //     {
    //         if (poseHandler.IsFast())
    //             poseHandler.Move();
    //         poseHandler.Move();
    //     }
    // };

    // class TurnLeftCommand final : public ICommand
    // {
    // public:
    //     void DoOperate(PoseHandler &poseHandler) const noexcept override
    //     {
    //         if (poseHandler.IsFast())
    //             poseHandler.Move();
    //         if (poseHandler.IsReverse())
    //             poseHandler.TurnRight();
    //         else
    //             poseHandler.TurnLeft();
    //     }
    // };

    // class TurnRightCommand final : public ICommand
    // {
    // public:
    //     void DoOperate(PoseHandler &poseHandler) const noexcept override
    //     {
    //         if (poseHandler.IsFast())
    //             poseHandler.Move();
    //         if (poseHandler.IsReverse())
    //             poseHandler.TurnLeft();
    //         else
    //             poseHandler.TurnRight();
    //     }
    // };

    // class FastCommand final : public ICommand
    // {
    // public:
    //     void DoOperate(PoseHandler &poseHandler) const noexcept override
    //     {
    //         poseHandler.Fast();
    //     }
    // };

    // class ReverseCommand final : public ICommand
    // {
    //     public:
    //         void DoOperate(PoseHandler &poseHandler) const noexcept override
    //         {
    //             poseHandler.Reverse();
    //         }
    // };

    /***
     * 以下使用匿名函数和functional库对函数进行定义
     */
    // class MoveCommand final
    // {
    // public:
    //     const std::function<void(PoseHandler &poseHandler)> operate = [](PoseHandler &poseHandler) noexcept
    //     {
    //         if (poseHandler.IsFast())
    //             poseHandler.Move();
    //         poseHandler.Move();
    //     };
    // };

    // class TurnLeftCommand final
    // {
    // public:
    //     const std::function<void(PoseHandler &poseHandler)> operate = [](PoseHandler &poseHandler) noexcept
    //     {
    //         if (poseHandler.IsFast())
    //             poseHandler.Move();
    //         if (poseHandler.IsReverse())
    //             poseHandler.TurnRight();
    //         else
    //             poseHandler.TurnLeft();
    //     };
    // };

    // class TurnRightCommand final
    // {
    // public:
    //     const std::function<void(PoseHandler &poseHandler)> operate = [](PoseHandler &poseHandler) noexcept
    //     {
    //         if (poseHandler.IsFast())
    //             poseHandler.Move();
    //         if (poseHandler.IsReverse())
    //             poseHandler.TurnLeft();
    //         else
    //             poseHandler.TurnRight();
    //     };
    // };

    // class FastCommand final
    // {
    // public:
    //     const std::function<void(PoseHandler &poseHandler)> operate = [](PoseHandler &poseHandler) noexcept
    //     {
    //         poseHandler.Fast();
    //     };
    // };

    // class ReverseCommand final
    // {
    // public:
    //     const std::function<void(PoseHandler &poseHandler)> operate = [](PoseHandler &poseHandler) noexcept
    //     {
    //         poseHandler.Reverse();
    //     };
    // };

    /***
     * 以下用操作符重载对各类操作进行定义
     */

    // class MoveCommand final
    // {
    // public:
    //     void operator()(PoseHandler &poseHandler) const noexcept
    //     {
    //         if (poseHandler.IsFast())
    //             poseHandler.Move();
    //         poseHandler.Move();
    //     }
    // };

    // class TurnLeftCommand final
    // {
    // public:
    //     void operator()(PoseHandler &poseHandler) const noexcept
    //     {
    //         if (poseHandler.IsFast())
    //             poseHandler.Move();
    //         if (poseHandler.IsReverse())
    //             poseHandler.TurnRight();
    //         else
    //             poseHandler.TurnLeft();
    //     }
    // };

    // class TurnRightCommand final
    // {
    // public:
    //     void operator()(PoseHandler &poseHandler) const noexcept
    //     {
    //         if (poseHandler.IsFast())
    //             poseHandler.Move();
    //         if (poseHandler.IsReverse())
    //             poseHandler.TurnLeft();
    //         else
    //             poseHandler.TurnRight();
    //     }
    // };

    // class FastCommand final
    // {
    // public:
    //     void operator()(PoseHandler &poseHandler) const noexcept
    //     {
    //         poseHandler.Fast();
    //     }
    // };

    // class ReverseCommand final
    // {
    // public:
    //     void operator()(PoseHandler &poseHandler) const noexcept
    //     {
    //         poseHandler.Reverse();
    //     }
    // };
}
