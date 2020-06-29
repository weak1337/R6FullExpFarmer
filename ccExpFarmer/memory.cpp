#include "Includes.h"

uintptr_t mem::get_base() {
	return (uintptr_t)GetModuleHandleA(0);
}

void mem::read_chunk(uintptr_t at, uintptr_t to, size_t size) {
	if (!IsBadReadPtr((void*)at, size)) {
		memcpy((void*)to, (void*)at, size);
	}
}
