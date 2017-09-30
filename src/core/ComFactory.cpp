#include "ComFactory.h"
#include "ComFactoryImpl.h"

namespace bf
{

IComFactory* GetComFactory(void)
{
	return ComFactoryImpl::GetInstance();
}

}
