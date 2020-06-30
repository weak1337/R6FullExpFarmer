#include "Includes.h"

R6Game::R6Game() {
	this->base = mem::get_base();
	printf("R6Base: %p\n", this->base);
	MODULEINFO modinfo = { 0 };
	GetModuleInformation(GetCurrentProcess(), (HMODULE)this->base, &modinfo, sizeof(MODULEINFO));
	DWORD size = modinfo.SizeOfImage;
	printf("SIZE: %x\n", size);

	uintptr_t start = this->base;

	this->GameManager = base + 0x6713ED8;// "\x4c\x8b\x0d\x00\x00\x00\x00\x31\xdb\xeb\x00\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x8d\x0c\xdd\x00\x00\x00\x00\xbe";
	
	this->GameProfileManager = base + 0x671BA70;// "\x48\x8b\x05\x00\x00\x00\x00\x48\x8b\x40\x00\x48\x85\xc0\x74\x00\x8b\x0d\x00\x00\x00\x00\x65\x48\x8b\x14\x25\x00\x00\x00\x00\x48\x8b\x0c\xca\x83\xb9\x00\x00\x00\x00\x00\x74\x00\x83\x78\x00\x00\x79\x00\x48\x8b\x18\x48\x85\xdb\x74\x00\x48\x8b\x03\x48\x89\xd9\xff\x50\x00\x48\x8b\x0d\x00\x00\x00\x00\x0f\xb7\x50\x00\x66\x3b\x51\x00\x72\x00\x0f\xb7\x40\x00\x66\x3b\x41\x00\x77\x00\x41\x83\xbc\x24";

	this->RoundManager = base + 0x6CA0848;//"\x48\x8b\x05\x00\x00\x00\x00\x8b\x80\x00\x00\x00\x00\x83\xc0\x00\x83\xf8\x00\x77\x00\x83\x41\x00\x00\x83\x41\x00\x00\xe9";
	
	this->GameStatus = base + 0x5476093; //c6 05 ? ? ? ? ? c7 05 ? ? ? ? ? ? ? ? c6 05 ? ? ? ? ? 48 8b 0d

	this->localplayer = new LocalPlayer();
	printf("Found \nGameManager: %x\nGameProfileManager: %x\nRoundManager: %x\n", this->GameManager - base, this->GameProfileManager - base, this->RoundManager - base);
	system("pause");
	system("cls");
}

bool R6Game::is_ingame() {
	BYTE current_round = mem::read<BYTE>(mem::read<uintptr_t>(this->RoundManager) + 0x2E8);
	if (current_round == action)
		return true;
	return false;
}


extern R6Game* current_game;
void LocalPlayer::set_exp(int amount) {
	uintptr_t _Local = mem::read<uintptr_t>(mem::read<uintptr_t>(current_game->GameProfileManager) + 0x68);
	_Local = mem::read<uintptr_t>(_Local);
	this->address = mem::read<uintptr_t>(_Local + 0x28) + this->decryption_key;
	uintptr_t info = mem::read<uintptr_t>(this->address + 0xD0);

	DWORD decryption_key = 0x7A456E04;
	int encrypted_exp = mem::read<int>(info + 0x164);  //For exp decryption use: 0x7A456E04 add eax(0x7A456E04), real_exp
	int decrypted_exp = encrypted_exp + decryption_key;
	int amount_to_write = encrypted_exp + amount; //This is not exactly how it works but we wanna max out exp
	mem::write<int>(info + 0x164, amount_to_write);
	mem::write<int>(info + 0x144, amount);
}

void LocalPlayer::switch_team() {
	uintptr_t info = mem::read<uintptr_t>(this->address + 0xD0);
	uintptr_t team_info = mem::read<uintptr_t>(info + 0x98);
	BYTE team = mem::read<BYTE>(team_info + 0xAB);
	if (team == 3)
		mem::write<BYTE>(team_info + 0xAB, 0x4);
	else
		mem::write<BYTE>(team_info + 0xAB, 0x3);
}

bool R6Game::is_tabbed_in() {
	BYTE status = mem::read<BYTE>(this->GameStatus);
	if (status)
		return true;
	return false;
}
