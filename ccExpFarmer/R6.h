
class LocalPlayer {
private:
	uintptr_t decryption_key = 0xEBAB0991057478ED;
public:
	uintptr_t address;

	void set_exp(int amount);
	void switch_team();
};

class R6Game {
private:
	uintptr_t base;
public:

	uintptr_t GameManager;
	uintptr_t GameProfileManager;
	uintptr_t RoundManager;
	uintptr_t GameStatus;
	enum Rounds {
		swap,
		selection,
		prep,
		action,
		end,
		mainlobby
	};

	R6Game();
	LocalPlayer* localplayer;
	bool is_ingame();
	bool is_tabbed_in();
	
};