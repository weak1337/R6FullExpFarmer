#include "offsets.h"
#include "cloutmem.h"
#include "ccolor.h"
cMemory* mem;
class Localplayer{
private:
	
	uintptr_t GameProfile;
public:
	
	Localplayer() {
		this->GameProfile = mem->read<uintptr_t>(mem->get_base() + Offsets::GameProfile);
	}

	uintptr_t get_local_player() {
		uintptr_t _local = mem->read<uintptr_t>(this->GameProfile + 0x68);
		uintptr_t __local = mem->read<uintptr_t>(_local + 0x0);
		uintptr_t ___local = mem->read<uintptr_t>(__local + 0x28);
		return ___local;
	}

	void set_exp() {
		uintptr_t Localplayer = get_local_player();
		uintptr_t information = mem->read<uintptr_t>(Localplayer + 0xA8);
		mem->write(information + 0x12C, (int)99999);
	}

	int get_team() {
		uintptr_t Localplayer = get_local_player();
		uintptr_t information = mem->read<uintptr_t>(Localplayer + 0xA8);
		uintptr_t playerinfo = mem->read<uintptr_t>(information + 0x68);
		return mem->read<int>(playerinfo + 0x30);
	}

	void set_team(int team) {
		uintptr_t Localplayer = get_local_player();
		uintptr_t information = mem->read<uintptr_t>(Localplayer + 0xA8);
		uintptr_t playerinfo = mem->read<uintptr_t>(information + 0x68);
		mem->write(playerinfo + 0x30, team);
	}

	void force_team_switch() {
		if (get_team() == 3)
			set_team(4);
		else
			set_team(3);
	
	}
};

class Game {
private:
	uintptr_t RoundManager;
	
public:
	Localplayer* locplayer;
	Game() {
		mem = new cMemory();
		locplayer = new Localplayer();
		this->RoundManager = mem->read<uintptr_t>(mem->get_base() + Offsets::RoundManager);
	}

	bool is_in_game() {
		int Round = mem->read<int>(this->RoundManager + 0x2E8);
		return Round == 2 || Round == 3 || Round == 4;
	}
};
