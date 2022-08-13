# IL2Cpp-Dictionary
Dictionary used in mono 

# Usage

```cpp
Dictionary<void*, void*> *get_Players(){
	// public static Dictionary<Transform, vp_MPNetworkPlayer> get_Players() { }

    	// Dictionary<void*, void*> *get_Players() = (Dictionary<int, void*> *(*)())getRealOffset(0x0);
    	return reinterpret_cast<Dictionary<void*, void*> *(*)()>(0x0)();
}

Dictionary<int, void*> *get_PlayersByID(){
    	// public static Dictionary<int, vp_MPNetworkPlayer> get_PlayersByID() { }

    	// Dictionary<int, void*> *_get_PlayersByID() = (Dictionary<int, void*> *(*)())getRealOffset(0x0);
	return reinterpret_cast<Dictionary<int, void*> *(*)()>(0x0)();
}

Dictionary<int, void*>::KeyCollection *get_IDs(){
    	// public static Dictionary.KeyCollection<int, vp_MPNetworkPlayer> get_IDs() { }

    	// Dictionary<int, void*>::KeyCollection *_get_IDs() = (Dictionary<int, void*>::KeyCollection *(*)())getRealOffset(0x0);
	return reinterpret_cast<Dictionary<int, void*>::KeyCollection *(*)()>(0x0)();
}

void setup(){

	// Methods Demo
	auto PlayersByID = get_PlayersByID();
    	if(!PlayersByID)
        	return;

	auto PlayerValues = PlayersByID->get_Values();
	auto PlayerKeys = PlayersByID->get_Keys();

	for(int i = 0; i < PlayersByID->count; i++){
		// Key: int value: vp_MPNetworkPlayer
		auto key = PlayerKeys[i];
		auto player = PlayerValues[i];

		/*
		Key to search can be any type
		Use the key to get a single Item from dict
		returns a player with that matching key
		*/
		auto gayPlayer = (*PlayersByID)[key];
	}

	auto Players = get_Players();
    	if(!Players)
        	return;

	auto PlayerValues = Players->get_Values();
	auto PlayerKeys = Players->get_Keys();

	for(int i = 0; i < Players->count; i++){
		// Key: Transform value: vp_MPNetworkPlayer
		auto key = PlayerKeys[i];
		auto player = PlayerValues[i];

		/* 
		Key to search can be any type
		Use the key to get a single Item from dict
		returns a player with that matching key
		*/
		auto gayPlayer = (*Players)[key];
	}

    	auto p_ids = get_IDs();
    	auto p_idsDictionary = p_ids->dictionary;
    	for (int i = 0; i < p_idsDictionary->count; i++){
        	// Im pretty sure this only contains keys soooo yea GL
        auto key = p_idsDictionary->get_Keys()[i];
    	}

	// Fields Demo

    	// protected static Dictionary<Transform, vp_MPNetworkPlayer> m_Players; // 0x0
   	// protected static Dictionary<int, vp_MPNetworkPlayer> m_PlayersByID; // 0x8

	auto m_Players = *(Dictionary<void*, void*> **)((uint64_t)_this + 0x0 );
	auto m_PlayerValues = m_Players->get_Values();
	auto m_PlayerKeys = m_Players->get_Keys();

    	// Lets loop through the keys and use the keys to get the values we want
    	// You can use [get_Count or count]
    	for (int i = 0; i < m_PlayerKeys.get_Count(); i++){
        	void* key = m_PlayerKeys[i];
        	void* value = (*m_PlayerValues)[key];
		// Do stuff with these values
    	}
}
// Easy right have fun modding :)
```

# Credits
- shmoo (monoArray)
- Me (Rednick16->Dictionary)
