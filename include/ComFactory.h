#pragma once

#include "IUnknown.h"

namespace bf {

/***
 * Export interface
 */
class IComFactory
{
public:
	// Initialize component factory with component path.
	virtual bool Init(const char* com_dir) = 0;

	// Create component with class ID and interface ID.
	virtual IUnknown* CreateComponent(IUnknown* outer, const char* cid, const char* iid) = 0;
};

// Global function to get component factory.
IComFactory* GetComFactory(void);

}



