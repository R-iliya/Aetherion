#pragma once

#include "core.h"
#include "log.h"
#include "delegate_list.h"

namespace Aetherion {

namespace detail {
	using LogCallback = DelegateList<void(LogLevel, const char*)>;
	AETHERION_CORE_API LogCallback& getLogCallback();
} // namespace detail

template <auto F> void registerLogCallback() {
	detail::lock();
	detail::getLogCallback().bind<F>();
	detail::unlock();
}

template <auto F> void unregisterLogCallback() {
	detail::lock();
	detail::getLogCallback().unbind<F>();
	detail::unlock();
}

template <auto F, typename T> void registerLogCallback(T* inst) {
	detail::lock();
	detail::getLogCallback().bind<F>(inst);
	detail::unlock();
}

template <auto F, typename T> void unregisterLogCallback(T* inst) {
	detail::lock();
	detail::getLogCallback().unbind<F>(inst);
	detail::unlock();
}

} // namespace Aetherion
