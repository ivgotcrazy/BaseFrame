#pragma once

#include <map>
#include <functional>

#include "ComFactory.h"
#include "Component.h"

namespace bf {

class ComFactoryImpl : public IComFactory
{
public:
	ComFactoryImpl();
	~ComFactoryImpl();

	static IComFactory* GetInstance();

	bool Init(const char* com_dir) override;

	IUnknown* CreateComponent(IUnknown* outer, const char* cid, const char* iid) override;

private:
	typedef std::string CID; // class id
	typedef std::map<CID, CreateComFunc> CMAP;

	CMAP m_creators;
};

}