// BaseFrameTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include "ComFactory.h"
#include "IUnknown.h"
#include "IComTest.h"

using namespace bf;

int main()
{
	IComFactory* factory = GetComFactory();
	if (!factory->Init("..\\..\\build\\windows\\BaseFrame\\Debug")) {
		std::cout << "Init faild!" << std::endl;
		return -1;
	}

	bf::IUnknown* com = factory->CreateComponent(nullptr, "ComTest_CID");
	if (nullptr == com) {
		std::cout << "Create component faild!" << std::endl;
		return -1;
	}

	testbf::IComTest* p = (testbf::IComTest*)com->QueryInterface("ComTest_IID");
	if (nullptr == p) {
		std::cout << "Query interface failed!" << std::endl;
		return -1;
	}

    std::cout << "Calc result: " << p->CalcResult() << std::endl;
}
