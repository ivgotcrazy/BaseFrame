#pragma once

#include <inttypes.h>

namespace bf {

#define BF_IID_IUNKNOWN "BF_IID_IUNKNOWN"

struct IUnknown
{
	virtual void* QueryInterface(const char* riid) = 0;
	virtual uint32_t AddRef() = 0;
	virtual uint32_t Release() = 0;
};

// ND: NonDelegating
struct INDUnknown
{
	virtual void* NDQueryInterface(const char* riid) = 0;
	virtual uint32_t NDAddRef() = 0;
	virtual uint32_t NDRelease() = 0;
};

}