#include "config.h"
#include "LibInit.h"



#include "./sdf/SDF.h"
#include "./base/Context.h"
#include "config.h"
#include "debug.h"
#include "LibInit.h"



























static void InitConfig()
{
	LIB_HandleInit();

	//mydebug << "Initconfig" << endl;
	//LIB_ReleaseALLDevice(1);
	//Configuration *phandleConfig = new Configuration("D:\\logSDF\\my.conf");

}

static void ExitConfig()
{
	LIB_ReleaseALLDevice(1);
}







#ifdef _WIN32

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		InitConfig();
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		ExitConfig();
		break;
	case DLL_THREAD_DETACH:
		break;	
	}
	return TRUE;

}
#else

void __attribute__((constructor)) sdf_lib_init()
{
	InitConfig();
}

void __attribute__((destructor)) sdf_lib_final()
{
	ExitConfig();
}

#endif