#pragma once
#include <string>

namespace adas
{
    // 汽车姿态
    struct Pose
    {
        int x;        // x坐标
        int y;        // y坐标
        char heading; // 'N'、'S'、'E'、'W'表示汽车朝向
    };
    // 驾驶动作执行接口
    class Executor
    {
    public:
        static Executor *NewExecutor(const Pose &pose = {0, 0, 'N'}) noexcept;

    public:
        Executor() = default;                           // 默认构造函数
        virtual ~Executor() = default;                  // 默认虚析构函数
        Executor(const Executor &) = delete;            // 不允许拷贝
        Executor &operator=(const Executor &) = delete; // 不允许赋值

    public:
        // 查询当前汽车状态，纯虚函数
        virtual Pose Query(void) const noexcept = 0;
        virtual void Execute(const std::string &commands) noexcept = 0;
    };
}