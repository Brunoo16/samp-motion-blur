#include "dllmain.h"

void Thread()
{
	while (!*reinterpret_cast<int*>(0xB6F5F0)) Sleep(50);

	DWORD OldProtect = NULL;

	const BYTE byte_array[] = {0xE8, 0x11, 0xE2, 0xFF, 0xFF};

	VirtualProtect(reinterpret_cast<void*>(0x704E8A), 5, PAGE_EXECUTE_READWRITE, &OldProtect);

	memcpy(reinterpret_cast<void*>(0x704E8A), byte_array, 5);

	if (fexists("blur.ini"))
	{
		*reinterpret_cast<BYTE*>(0x8D5104) = GetPrivateProfileInt("Settings", "BlurLevel", 36, "./blur.ini");
	}
	else
	{
		WritePrivateProfileString("Settings", "BlurLevel", "36", "./blur.ini");

		*reinterpret_cast<BYTE*>(0x8D5104) = 0x24;
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Thread), 0, 0, 0);
	}
	return 1;
}