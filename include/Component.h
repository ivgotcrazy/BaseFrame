#pragma once

#include <inttypes.h>

#include "IUnknown.h"

namespace bf
{

class IComFactory;
typedef bf::IUnknown* (*CreateComFunc)(IComFactory*, bf::IUnknown*);

struct ComObject
{
	const char*		com_name;
	const char*		com_cid;
	CreateComFunc	com_create;
};

////////////////////////////////////////////////////////////////////////////////

// export function name
#define COM_ENTRY_NAME	"GetComObj"

// export function definition
typedef bool (*GetComObjFunc)(ComObject** objects, uint8_t* count);	

}