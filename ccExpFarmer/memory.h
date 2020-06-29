namespace mem {

	void read_chunk(uintptr_t at, uintptr_t to, size_t size);

	template <typename T>
	T read(uintptr_t at)
	{
		if (!IsBadReadPtr((void*)at, sizeof(T))) {
			return *(T*)at;
		}
		return 0;
	}

	template <typename T>
	void write(uintptr_t at, T val) {
		if (!IsBadReadPtr((void*)at, sizeof(T) )) {
			*(T*)at = val;
		}
	}

	uintptr_t get_base();


}