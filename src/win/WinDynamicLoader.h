#pragma once

#include <vector>

#include "IDynamicLoader.h"

namespace bf
{

class WinDynamicLoader : public IDynamicLoader
{
public:
	void Load(const char* path, const char* entry_name, EntryVec* entries) override;

private:
	typedef std::vector<std::string> DllVec;
	void GetAllDllFiles(const char* com_path, DllVec* pdv);
};

}

