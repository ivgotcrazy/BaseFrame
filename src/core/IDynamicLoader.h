#pragma once

#include <string>
#include <vector>
#include "Component.h"

namespace bf
{

class IDynamicLoader
{
public:
	struct DynamicEntry
	{
		std::string lib_name;
		GetComObjFunc func;
	};

	typedef std::vector<DynamicEntry> EntryVec;

	virtual void Load(const char* path, const char* entry_name, EntryVec* entries) = 0;
};

}
