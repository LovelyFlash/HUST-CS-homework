#include "ExecutorImpl.hpp"

#include <new>
#include <memory>

namespace adas
{
    ExecutorImpl::ExecutorImpl(const Pose &pose) noexcept : pose(pose), fast_mode(false) {}

    Pose ExecutorImpl::Query(void) const noexcept
    {
        return pose;
    }

    void ExecutorImpl::Execute(const std::string &commands) noexcept
    {
        for (const auto cmd : commands)
        {
            if (cmd == 'M')
            {
                std::unique_ptr<MoveCommand> cmder = std::make_unique<MoveCommand>();
                //*this就是 ExecutorImpl实例对象，作为实参 传递给 DoOperate方法
                cmder->DoOperate(*this); // 执行 MoveCommand的 DoOperate，即 Move
            }
            else if (cmd == 'L')
            {
                std::unique_ptr<TurnLeftCommand> cmder = std::make_unique<TurnLeftCommand>();
                cmder->DoOperate(*this);
            }
            else if (cmd == 'R')
            {
                std::unique_ptr<TurnRightCommand> cmder = std::make_unique<TurnRightCommand>();
                cmder->DoOperate(*this);
            }
            else if (cmd == 'F')
                fast_mode = true;
        }
    }

    void ExecutorImpl::Move() noexcept
    {
        if (pose.heading == 'W')
            --pose.x;
        else if (pose.heading == 'E')
            ++pose.x;
        else if (pose.heading == 'N')
            ++pose.y;
        else if (pose.heading == 'S')
            --pose.y;
    }

    void ExecutorImpl::TurnLeft() noexcept
    {
        if (pose.heading == 'W')
            pose.heading = 'S';
        else if (pose.heading == 'S')
            pose.heading = 'E';
        else if (pose.heading == 'E')
            pose.heading = 'N';
        else if (pose.heading == 'N')
            pose.heading = 'W';
    }

    void ExecutorImpl::TurnRight() noexcept
    {
        if (pose.heading == 'W')
            pose.heading = 'N';
        else if (pose.heading == 'S')
            pose.heading = 'W';
        else if (pose.heading == 'E')
            pose.heading = 'S';
        else if (pose.heading == 'N')
            pose.heading = 'E';
    }

    /*
        std::nothrow是C++标准库中的一个常量，用于指示在分配内存时不抛出任何异常。
        它是std::nothrow_t类型的实例，通常用在new运算符和std::nothrow命名空间中，
        以请求内存分配器在分配失败时返回一个空指针，而不是抛出std::bad_alloc异常。
    */

    Executor *Executor::NewExecutor(const Pose &pose) noexcept
    {
        return new (std::nothrow) ExecutorImpl(pose);
    }
}