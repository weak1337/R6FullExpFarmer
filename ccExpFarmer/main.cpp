#include "Includes.h"
R6Game* current_game;
bool _stdcall MainThread(HMODULE hModule) {

	AllocConsole();
	SetConsoleTitle("Simple EXP Farmer by weak Operation STEEL WAVE");
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	current_game = new R6Game();
	
	while (true) {
		if (current_game->is_tabbed_in()) {
			if (current_game->is_ingame()) {
				current_game->localplayer->set_exp(99999);
				current_game->localplayer->switch_team();
			}
			else
			{
				keybd_event(VK_RETURN, 0x9C, 0, 0); //enter down
				keybd_event(VK_RETURN, 0x9C, KEYEVENTF_KEYUP, 0); //enter up
			}
		}
		Sleep(10);
		if (GetAsyncKeyState(VK_F6))
			break;
	}

	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return true;
}

bool __stdcall DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved)
{
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), hModule, 0, 0));
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}