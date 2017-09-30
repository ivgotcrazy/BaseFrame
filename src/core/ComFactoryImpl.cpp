#include "ComFactoryImpl.h"

#include <iostream>

#ifdef _WIN32
#include "WinDynamicLoader.h"
#endif

#ifdef _LINUX
#include "LinuxDynamicLoader.h"
#endif

#include "Component.h"

using namespace bf;

ComFactoryImpl::ComFactoryImpl()
{
}


ComFactoryImpl::~ComFactoryImpl()
{
}

IComFactory* ComFactoryImpl::GetInstance()
{
	static ComFactoryImpl instance;
	return (&instance);
}


bool ComFactoryImpl::Init(const char* com_path)
{
	IDynamicLoader* loader = nullptr;
#ifdef _WIN32
	loader = new WinDynamicLoader();
#elif _LINUX
	loader = new LinuxDynamicLoader();
#endif

	// Load all lib and get export function address
	IDynamicLoader::EntryVec vec;
	loader->Load(com_path, COM_ENTRY_NAME, &vec);

	// Load com by export function address
	for each(const IDynamicLoader::DynamicEntry& entry in vec)
	{
		std::cout << "Begin to load com from " << entry.lib_name << std::endl;

		// Get all com objects
		ComObject* objs = nullptr;
		uint8_t count = 0;
		if (!entry.func(&objs, &count))
		{
			std::cout << "Failed to call GetComObjects." << std::endl;
			continue;
		}

		// none!!!
		if (count == 0)
		{
			std::cout << "Get no com objects"<< std::endl;
			continue;
		}

		// Maybe some com objects
		for (uint8_t i = 0; i < count; i++)
		{
			ComObject* object = (objs + i);
			if (m_creators.end() != m_creators.find(object->com_cid))
			{
				std::cout << "COM " << object->com_cid << "exists." << std::endl;
				continue;
			}

			m_creators.insert(std::make_pair(object->com_cid, object->com_create));

			std::cout << "Get one com object" << std::endl;
		}
	}

	return true;
}

bf::IUnknown* ComFactoryImpl::CreateComponent(IUnknown* outer, const char* cid, const char* iid)
{
	for (auto iter = m_creators.begin(); iter != m_creators.end(); iter++)
	{
		if (iter->first == cid)
		{
			IUnknown* com = (iter->second)(this, outer);
			if (!com)
			{
				printf("Failed to create com %s.\n", iid);
				return nullptr;
			}

			IUnknown* itf = static_cast<IUnknown*>(com->QueryInterface(iid));
			if (!itf)
			{
				printf("Failed to query interface %s.\n", iid);
			}

			return itf;
		}
	}

	printf("Failed to find com %s.\n", cid);
	return nullptr;
}
