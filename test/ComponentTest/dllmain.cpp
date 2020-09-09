// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

#include "Component.h"
#include "ComTest.h"


bf::ComObject TestComObjArray[] = {
	{"ComTest", "ComTest_CID", testbf::ComTest::CreateInstance}
};

// 导出函数
bool GetComObj(bf::ComObject** objects, uint8_t* count)
{
	*objects = TestComObjArray;
	*count = 1;

	return true;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

