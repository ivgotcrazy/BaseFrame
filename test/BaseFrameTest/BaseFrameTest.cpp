// BaseFrameTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include "ComFactory.h"
#include "IUnknown.h"

using namespace bf;

int main()
{
	IComFactory* factory = GetComFactory();
	if (!factory->Init("./")) {
		std::cout << "Init faild!" << std::endl;
		return -1;
	}

    std::cout << "Hello World!\n"; 
}
