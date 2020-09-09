#include "pch.h"
#include "ComTest.h"

using namespace testbf;

bf::IUnknown* ComTest::CreateInstance(bf::IUnknown* outer)
{
	return new ComTest(outer);
}

void* ComTest::NDQueryInterface(const char* riid)
{
	if (strcmp("ComTest_IID", riid) == 0) {
		return (IComTest*)this;
	}
	else {
		return nullptr;
	}
}

int ComTest::CalcResult()
{
	return 100;
}