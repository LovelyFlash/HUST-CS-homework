#pragma once

#include "cmder/Command.hpp"

#include <memory>
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
        explicit ExecutorImpl(const Pose &pose, CmderOrchestrator *orchestrator) noexcept;
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
        PoseHandler poseHandler;
        std::unique_ptr<CmderOrchestrator> orchestrator;
    };
}
