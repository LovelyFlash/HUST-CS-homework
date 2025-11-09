#pragma once

#include "Executor.hpp"
#include "Direction.hpp"

namespace adas
{
    class PoseHandler final
    {
    public:
        PoseHandler(const Pose &pose) noexcept;
        PoseHandler(const PoseHandler &pose) = delete;
        PoseHandler &operator=(const PoseHandler &) = delete;

    public:
        void Move(void) noexcept;
        void TurnLeft(void) noexcept;
        void TurnRight(void) noexcept;
        void Reverse(void) noexcept;
        bool IsReverse(void) const noexcept;
        void Fast(void) noexcept;
        bool IsFast(void) const noexcept;
        Pose Query(void) const noexcept;

    private:
        Point point;
        const Direction *facing;
        bool fast_mode{false};
        bool reverse_mode{false};
    };
}
