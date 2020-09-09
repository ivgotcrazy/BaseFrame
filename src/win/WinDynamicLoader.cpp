#include <windows.h>

#include <string>
#include <iostream>
#include <filesystem>

#include "WinDynamicLoader.h"

#include "Component.h"

namespace fs = std::experimental::filesystem::v1;

using namespace bf;

void WinDynamicLoader::Load(const char* path, const char* entry_name, EntryVec* entries)
{
	if (!path || !entry_name || !entries)
		return;

	// Get all dll files
	DllVec dll_files;
	GetAllDllFiles(path, &dll_files);

	for (const std::string& dll_file : dll_files) {
		HMODULE module = ::LoadLibraryA(dll_file.c_str());
		if (module == NULL) {
			std::cout << "Failed to load library " << dll_file << std::endl;
			continue;
		}

		void* func = ::GetProcAddress(module, entry_name);
		if (!func) {
			std::cout << "Failed to get " << entry_name 
				<< "func from " << dll_file << std::endl;
			continue;
		}

		DynamicEntry entry;
		entry.lib_name = path;
		entry.func =  static_cast<GetComObjFunc>(func);
		entries->push_back(entry);

		std::cout << "Find entry in " << dll_file << std::endl;
	}
}

void WinDynamicLoader::GetAllDllFiles(const char* com_path, DllVec* pdv)
{
	if (!pdv || !fs::exists(com_path))
		return;

	// file
	if (!fs::is_directory(com_path)) {
		if (fs::path(com_path).extension() == ".dll") {
			pdv->push_back(com_path);
			std::cout << "Add dll file: " << com_path << std::endl;
		}
		return;
	}

	// directory
	fs::directory_iterator begin_iter(com_path);
	fs::directory_iterator end_iter;
	for (auto iter = begin_iter; iter != end_iter; ++iter) {
		if (fs::is_directory(*iter)) {
			GetAllDllFiles(iter->path().string().c_str(), pdv);
		} 
		else {
			if (iter->path().extension() == ".dll") {
				pdv->push_back(iter->path().string());
				std::cout << "Add dll file: " << iter->path().string() << std::endl;
			}
		}
			
	}
}