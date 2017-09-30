#pragma once

#include "IDynamicLoader.h"

namespace bf
{

class LinuxDynamicLoader : public IDynamicLoader
{
public:
	void Load(const char* path, const char* entry_name, EntryVec* entries) override;
};

}
