#pragma once

#include <memory>
#include <utility>
#include <spdlog/spdlog.h>

template <typename T> using Ref = std::shared_ptr<T>;
template <typename T, typename... Args> constexpr Ref<T> CreateRef(Args &&...args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

#define RO_LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define RO_LOG_WARN(...) spdlog::warn(__VA_ARGS__)
#define RO_LOG_ERR(...) spdlog::error(__VA_ARGS__)
