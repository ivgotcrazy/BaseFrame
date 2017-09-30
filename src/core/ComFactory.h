#pragma once

#include "IUnknown.h"

namespace bf {

class IComFactory
{
public:
	virtual bool Init(const char* com_dir) = 0;

	virtual IUnknown* CreateComponent(IUnknown* outer, const char* cid, const char* iid) = 0;
};

IComFactory* GetComFactory(void);

}



