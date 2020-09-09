#pragma once

#include "IUnknown.h"
#include <string>

namespace bf
{

//==============================================================================

// ND: Non-Delegating
struct INDUnknown
{
	virtual void* NDQueryInterface(const char* riid) = 0;
	virtual uint32_t NDAddRef() = 0;
	virtual uint32_t NDRelease() = 0;
};

//==============================================================================

class ProxyUnknown : public INDUnknown
{
public:
	ProxyUnknown(IUnknown* owner)
		: m_owner((owner ? owner : reinterpret_cast<IUnknown*>(static_cast<INDUnknown*>(this))))
		, m_ref_count(0)
	{}

	virtual ~ProxyUnknown()
	{}

	virtual void* NDQueryInterface(const char* riid) override
	{
		// We know only about IUnknown
		if (0 == strcmp(riid, BF_IID_IUNKNOWN)) {
			m_owner->AddRef();
			return m_owner;
		}
		else {
			return nullptr;
		}
	}

	virtual uint32_t NDAddRef() override
	{
		m_ref_count++;
		return m_ref_count;
	}

	virtual uint32_t NDRelease() override
	{
		if (m_ref_count == 0)
			return 0;

		m_ref_count--;
		if (m_ref_count == 0) {
			delete this;
			return 0;
		}
		else {
			return m_ref_count;
		}
	}

	IUnknown* GetOwner()
	{
		return m_owner;
	}

private:
	IUnknown* m_owner;

	// Long way to guarantee multi-threading safety!!!
	uint32_t m_ref_count;
};

//==============================================================================

#define COMPONENT_IUNKNOWN_IMPL										\
virtual void* QueryInterface(const char* iid) override	\
{																\
	return ProxyUnknown::GetOwner()->QueryInterface(iid);		\
}																\
virtual uint32_t AddRef() override								\
{																\
	return ProxyUnknown::GetOwner()->AddRef();					\
}																\
virtual uint32_t Release() override								\
{																\
	return ProxyUnknown::GetOwner()->Release();					\
}																\

}

