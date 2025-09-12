#pragma once

#include <functional>
#include <memory>
#include <type_traits>

namespace scrambleverse::win32
{
    template <typename T, void (*deleter)(T), T invalid>
    class HandleBase
    {
    private:
        struct Deleter
        {
            bool auto_delete;

            Deleter(bool auto_delete) : auto_delete(auto_delete) {}

            void operator()(T handle) const noexcept
            {
                if (auto_delete && handle != invalid)
                {
                    deleter(handle);
                }
            }
        };

        std::shared_ptr<std::remove_pointer_t<T>> ptr;

    public:
        HandleBase() : ptr(invalid, Deleter(false)) {}
        explicit HandleBase(T handle, bool auto_delete = true) : ptr(handle, Deleter(auto_delete)) {}

        // コピー／代入
        HandleBase(const HandleBase &) = default;
        HandleBase &operator=(const HandleBase &) = default;

        // 移動
        HandleBase(HandleBase &&) noexcept = default;
        HandleBase &operator=(HandleBase &&) noexcept = default;

        T get() const noexcept { return ptr.get(); }
        operator T() const noexcept { return get(); }

        bool operator==(HandleBase h) const noexcept { return get() == h.get(); };
        bool operator!=(HandleBase h) const noexcept { return get() != h.get(); };

        bool operator==(const HandleBase &other) const noexcept { return get() == other.get(); }
        bool operator!=(const HandleBase &other) const noexcept { return get() != other.get(); }

        class Weak
        {
        private:
            std::weak_ptr<std::remove_pointer_t<T>> weak_ptr;

        public:
            explicit Weak(const HandleBase &handle) : weak_ptr(handle.ptr) {}

            HandleBase lock() const noexcept
            {
                if (auto sp = weak_ptr.lock())
                {
                    return HandleBase(sp.get());
                }

                return HandleBase(invalid);
            }
        };
    };
}
