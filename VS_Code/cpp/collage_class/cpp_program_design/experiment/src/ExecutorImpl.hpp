#pragma once

#include "Executor.hpp"
#include <string>

namespace adas
{
    /*
        Executor的具体实现
    */
    class ExecutorImpl final : public Executor
    {
    public:
        // 构造函数
        explicit ExecutorImpl(const Pose &pose) noexcept;

        // 默认析构函数
        ~ExecutorImpl() noexcept = default;

        // 不能拷贝
        ExecutorImpl(const ExecutorImpl &) = delete;
        // 不能赋值
        ExecutorImpl &operator=(const ExecutorImpl &) = delete;

    public:
        // 询当前汽车姿态，是父类抽象方法Query的具体实现、
        Pose Query(void) const noexcept override;
        void Execute(const std::string &commands) noexcept override;

    private:
        // 私有数据成员，汽车当前姿态
        Pose pose;
        bool fast_mode;
        void Move(void) noexcept;
        void TurnLeft(void) noexcept;
        void TurnRight(void) noexcept;

        class MoveCommand final // 定义 一个 嵌套 类 MoveCommand，完成 Move动作（ M指令）
        {
        public:
            // 执行 Move动作，需要 委托 ExecutorImp&执行 器 来完成动作
            void DoOperate(ExecutorImpl &executor) const noexcept
            {
                executor.Move();
            }
        };

        class TurnLeftCommand final
        {
        public:
            void DoOperate(ExecutorImpl &executor) const noexcept
            {
                executor.TurnLeft();
            }
        };

        class TurnRightCommand final 
        {
        public:
            void DoOperate(ExecutorImpl &executor) const noexcept
            {
                executor.TurnRight();
            }
        };
    };
}
