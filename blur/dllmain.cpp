#include "dllmain.h"

void Thread()
{
	while (!*(int*)0xB6F5F0) Sleep(50);
	
	DWORD OldProtect;

	VirtualProtect((unsigned char*)0x704E8A, 5, PAGE_EXECUTE_READWRITE, &OldProtect);

	*(unsigned char*)0x704E8A = 232;
	*(unsigned char*)0x704E8B = 17; 
	*(unsigned char*)0x704E8C = 226;
	*(unsigned char*)0x704E8D = 255;
	*(unsigned char*)0x704E8E = 255;

	if (fexists("blur.ini"))
	{
		*(unsigned char*)0x8D5104 = (unsigned char)GetPrivateProfileInt("Settings", "BlurLevel", 36, "./blur.ini");
	}
	else
	{
		WritePrivateProfileString("Settings", "BlurLevel", "36", "./blur.ini");

		*(unsigned char*)0x8D5104 = 36;
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Thread, 0, 0, 0);
	}
	return 1;
}