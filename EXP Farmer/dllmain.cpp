#include "Game.h"

bool __stdcall MainThread(HMODULE hMod) {


	bool renown = false;
	AllocConsole();
	SetConsoleTitle("Simple EXP Farmer by weak");
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	
	std::cout << red << "[Simple EXP Farmer by weak]" << std::endl;
	std::cout << blue << "F1 EXP but low Renown (fast)" << std::endl;
	std::cout << blue << "F2 EXP + Renown (slow)" << std::endl;
	while (1) {
		if (GetAsyncKeyState(VK_F1))
		{
			renown = false;
			break;
		}
		else if (GetAsyncKeyState(VK_F2)) {
			renown = true;
			break;
		}

	}
	std::cout << red << "Starting in 5 Seconds" << std::endl;
	Sleep(5000);
	system("cls");
	std::cout << red << "F6 to exit" << std::endl;
	//setup game
	Game* game = new Game();

	while (1) {

		if (game->is_in_game()) //if spawned
		{
			game->locplayer->set_exp(); //set max exp
			if(renown)
				Sleep(60000);
			game->locplayer->force_team_switch(); //switch team to stop game
		}
		else
		{
			keybd_event(VK_RETURN, 0x9C, 0, 0); //enter down
			keybd_event(VK_RETURN, 0x9C, KEYEVENTF_KEYUP, 0); //enter up
		}
		Sleep(10);

		if (GetAsyncKeyState(VK_F6))
			break;
	}
	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hMod, 0);

	return true;
}

bool __stdcall DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved)
{
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(0, 0,reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), hModule, 0,0));
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}