#pragma once

#include "engine/aetherion.h"

namespace Aetherion
{

template <typename T> struct Delegate;
template <typename T> struct UniquePtr;

struct AETHERION_EDITOR_API FileSystemWatcher
{
	virtual ~FileSystemWatcher() {}

	static UniquePtr<FileSystemWatcher> create(const char* path, struct IAllocator& allocator);
	virtual Delegate<void (const char*)>& getCallback() = 0;
};


} // namespace Aetherion