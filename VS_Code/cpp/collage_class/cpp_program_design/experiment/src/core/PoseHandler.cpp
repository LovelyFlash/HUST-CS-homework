#include "PoseHandler.hpp"

namespace adas
{
    PoseHandler::PoseHandler(const Pose &pose) noexcept : point(pose.x, pose.y), facing(&Direction::GetDirection(pose.heading)) {}

    void PoseHandler::Move() noexcept
    {
        if (reverse_mode)
            point -= facing->Move();
        else
            point += facing->Move();
    }

    void PoseHandler::TurnLeft() noexcept
    {
        facing = &(facing->LeftOne());
    }

    void PoseHandler::TurnRight() noexcept
    {
        facing = &(facing->RightOne());
    }

    void PoseHandler::Reverse(void) noexcept
    {
        reverse_mode = !reverse_mode;
    }

    bool PoseHandler::IsReverse() const noexcept
    {
        if (reverse_mode)
            return true;
        return false;
    }

    void PoseHandler::Fast() noexcept
    {
        fast_mode = !fast_mode;
    }

    bool PoseHandler::IsFast() const noexcept
    {
        if (fast_mode)
            return true;
        return false;
    }

    Pose PoseHandler::Query(void) const noexcept
    {
        return {point.GetX(), point.GetY(), facing->GetHeading()};
    }
}