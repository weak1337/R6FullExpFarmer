#include <Windows.h>
#include <iostream>

class cMemory {
private:
	uintptr_t base;
public:
	cMemory() {
		this->base = reinterpret_cast<uintptr_t>(GetModuleHandleA(0));
	}

	template <class C>
	__forceinline C read(uintptr_t address) {
		if (address != 0)
			return *(C*)address;
	}

	template <class C>
	__forceinline void write(uintptr_t address, C val) {
		if (address != 0)
			*(C*)address = val;
	}
	

	uintptr_t get_base() {
		return this->base;
	}

};