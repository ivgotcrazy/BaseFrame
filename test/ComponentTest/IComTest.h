#pragma once

#include "IUnknown.h"

namespace testbf {

class IComTest : public bf::IUnknown
{
public:
	virtual int CalcResult() = 0;
};

}
