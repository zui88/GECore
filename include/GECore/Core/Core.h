#pragma once

#include "Logger.h"
#include <signal.h>
#include "memory"
#include "zui/zui.h"
#include "utility"

#define GE_CORE_ASSERT(x, ...) {if (!(x)) { GE_CORE_ERROR(__VA_ARGS__); raise (SIGTRAP); }}

namespace GECore {

    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = zui::handle<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args) {
        return zui::make_handle<T>(std::forward<Args>(args)...);
    }

}