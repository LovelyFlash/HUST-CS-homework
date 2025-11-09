#pragma once

namespace adas
{
    template <typename T>
    class Singleton final
    {
    public:
        static T &Inatance(void) noexcept
        {
            static T instance;
            return instance;
        }

        Singleton(const Singleton &) = delete;
        Singleton &operator=(const Singleton &) = delete;

    private:
        Singleton(void) = default;
        ~Singleton(void) = default;
    };
}