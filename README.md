# IL2Cpp-Dictionary
Dictionary used in mono 

# Usage

```cpp
Dictionary<void*, void*> *get_Players(){
	return reinterpret_cast<Dictionary<void*, void*> *(*)()>(0x0)();
}

Dictionary<int, void*> *get_PlayersByID(){
	return reinterpret_cast<Dictionary<int, void*> *(*)()>(0x0)();
}

void setup(){
	// public static Dictionary<Transform, vp_MPNetworkPlayer> get_Players() { }
	// public static Dictionary<int, vp_MPNetworkPlayer> get_PlayersByID() { }

	// protected static Dictionary<Transform, vp_MPNetworkPlayer> m_Players; // 0x0
	// protected static Dictionary<int, vp_MPNetworkPlayer> m_PlayersByID; // 0x8

	// Methods Demo
	auto PlayersByID = get_PlayersByID();
	auto PlayerValues = PlayersByID->get_Values();
	auto PlayerKeys = PlayersByID->get_Keys();

	for(int i = 0; i < PlayerValues.get_Count(); i++){
		// Key: int value: vp_MPNetworkPlayer
		auto key = PlayerKeys[i];
		auto player = PlayerValues[i];
		/*
		int key = PlayerKeys[i];
		void* player = PlayerValues[i];
		*/

		/*
		Key to search can be any type
		Use the key to get a single Item from dict
		returns a player with that matching key
		*/
		auto gayPlayer = (*PlayersByID)[key];
	}


	auto Players = get_Players();
	auto PlayerValues = Players->get_Values();
	auto PlayerKeys = Players->get_Keys();

	for(int i = 0; i < PlayerValues.get_Count(); i++){
		// Key: Transform value: vp_MPNetworkPlayer
		auto key = PlayerKeys[i];
		auto player = PlayerValues[i];
		/*
		void* key = PlayerKeys[i];
		void* player = PlayerValues[i];
		*/

		/* 
		Key to search can be any type
		Use the key to get a single Item from dict
		returns a player with that matching key
		*/
		auto gayPlayer = (*get_Players)[key];
	}

	// Fields Demo
	auto m_Players = *(Dictionary<void*, void*> **)((uint64_t)_this + 0x0 );
	auto m_PlayerValues = m_Players->get_Values();
	auto m_PlayerKeys = m_Players->get_Keys();

	// Easy right have fun modding :)
	
	//@: Extras
	
	// Directly use a key
	// monoString* somestr;
	// (*m_Players)[somestr]; returns a value to needed object.
	auto gayPlayer = (*m_Players)[m_PlayerKeys[0]];
}
```

# Credits
- shmoo (monoArray)
- Me (Rednick16->Dictionary)
