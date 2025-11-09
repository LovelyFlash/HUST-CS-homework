#include "ExecutorImpl.hpp"
// #include "Command.hpp"
#include "cmder/CmderFactory.hpp"
#include "cmder/NormalOrchestrator.hpp"
#include "cmder/SportsCarOrchestrator.hpp"
#include "cmder/BusOrchestrator.hpp"
#include "core/Singleton.hpp"

#include <algorithm>
// #include <new>
// #include <memory>
// #include <unordered_map>

namespace adas
{
    Executor *Executor::NewExecutor(const Pose &pose, const ExecutorType executorType) noexcept
    {
        CmderOrchestrator *orchestrator = nullptr;
        switch (executorType)
        {
        case ExecutorType::NORMAL:
        {
            orchestrator = new (std::nothrow) NormalOrchestrator();
            break;
        }

        case ExecutorType::SPORTS_CAR:
        {
            orchestrator = new (std::nothrow) SportsCarOrchestrator();
            break;
        }

        case ExecutorType::BUS:
        {
            orchestrator = new (std::nothrow) BusOrchestrator();
            break;
        }
        }
        return new (std::nothrow) ExecutorImpl(pose, orchestrator);
    }

    ExecutorImpl::ExecutorImpl(const Pose &pose, CmderOrchestrator *orchestrator) noexcept : poseHandler(pose), orchestrator(orchestrator) {};

    Pose ExecutorImpl::Query() const noexcept
    {
        return poseHandler.Query();
    }

    void ExecutorImpl::Execute(const std::string &commands) noexcept
    {
        /***
         * 不使用指令工厂
         */
        // std::unordered_map<char, std::function<void(PoseHandler & poseHandler)>> cmderMap{
        //     {'M', MoveCommand()},
        //     {'L', TurnLeftCommand()},
        //     {'R', TurnRightCommand()},
        //     {'F', FastCommand()},
        //     {'B', ReverseCommand()},
        // };

        // cmderMap.emplace('M', std::make_unique<MoveCommand>());
        // cmderMap.emplace('L', std::make_unique<TurnLeftCommand>());
        // cmderMap.emplace('R', std::make_unique<TurnRightCommand>());
        // cmderMap.emplace('F', std::make_unique<FastCommand>());
        // cmderMap.emplace('B', std::make_unique<ReverseCommand>());

        // MoveCommand MoveCommand;
        // TurnLeftCommand TurnLeftCommand;
        // TurnRightCommand TurnRightCommand;
        // FastCommand FastCommand;
        // ReverseCommand ReverseCommand;
        // cmderMap.emplace('M', MoveCommand.operate);
        // cmderMap.emplace('L', TurnLeftCommand.operate);
        // cmderMap.emplace('R', TurnRightCommand.operate);
        // cmderMap.emplace('F', FastCommand.operate);
        // cmderMap.emplace('B', ReverseCommand.operate);

        // for (const auto cmd : commands)
        // {
        //     const auto cmder = cmderMap.find(cmd);

        //     if (cmder != cmderMap.end())
        //         cmder->second(poseHandler);
        // }

        /***
         * 使用指令工厂
         */

        const auto cmders = Singleton<CmderFactory>::Inatance().GetCmders(commands);

        std::for_each(
            cmders.begin(),
            cmders.end(),
            [this](const Cmder &cmder) noexcept
            {
                cmder(poseHandler, *orchestrator).DoOperate(poseHandler);
            });
    }

    /*
        std::nothrow是C++标准库中的一个常量，用于指示在分配内存时不抛出任何异常。
        它是std::nothrow_t类型的实例，通常用在new运算符和std::nothrow命名空间中，
        以请求内存分配器在分配失败时返回一个空指针，而不是抛出std::bad_alloc异常。
    */
}