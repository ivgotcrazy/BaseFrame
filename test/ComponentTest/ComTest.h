#pragma once

#include "IComTest.h"
#include "ProxyUnknown.h"

namespace testbf {

class ComTest : public bf::ProxyUnknown, public IComTest
{
public:
	ComTest(bf::IUnknown* outer) : ProxyUnknown(outer)
	{}

	COMPONENT_IUNKNOWN_IMPL

	static bf::IUnknown* CreateInstance(bf::IUnknown* outer);

	virtual void* NDQueryInterface(const char* riid) override;

	virtual int CalcResult() override;
};

}
