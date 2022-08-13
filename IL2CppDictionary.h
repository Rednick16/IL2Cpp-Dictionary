#include "monoArray.h"

template<typename TKey, typename TValue> 
struct Dictionary {
struct KeysCollection;
struct ValueCollection;

	struct Entry
	{
		int hashCode; 
		int next;
		TKey key;
		TValue value;
	};

	void *kass;
	void *monitor;
	monoArray<int *> *buckets;
	monoArray<Entry *> *entries;
	int count;
	int version;
	int freeList;
	int freeCount;
	void* comparer;
	KeysCollection *keys;
	ValueCollection *values;
	void *_syncRoot;

	void* get_Comparer(){
		return comparer;
	}

	int get_Count(){
		return (count - freeCount);
	}

	KeysCollection get_Keys(){
		if(!keys){
			keys = new KeysCollection;
			keys->dictionary = this;
		}
		return (*keys);
	}

	ValueCollection get_Values(){
		if(!values){
			values = new ValueCollection;
			values->dictionary = this;
		}
		return (*values);
	}

	TValue operator [] (TKey key) {
		int i = FindEntry(key);
        if (i >= 0) return entries->getPointer()[i].value;
		return TValue();
	}

	const TValue operator [] (TKey key) const {
		int i = FindEntry(key);
        if (i >= 0) return entries->getPointer()[i].value;
		return TValue();
	}
	
	int FindEntry(TKey key) {
		for (int i = 0; i < count; i++){
			if(entries->getPointer()[i].key == key) return i;
		}
	    return -1;
	}
	
	bool ContainsKey(TKey key) {
		return FindEntry(key) >= 0;
	}
	
	bool ContainsValue(TValue value) {
		for (int i = 0; i < count; i++){
			if(entries->getPointer()[i].hashCode >= 0 && 
					entries->getPointer()[i].value == value) return true;
		}
	    return false;
	}

	struct KeysCollection {
		void *kass;
		void *monitor;
		Dictionary<TKey, TValue> *dictionary;

		TKey operator [] (int i) {
			if(dictionary->entries)return dictionary->entries->getPointer()[i].key;
			return TKey();
		}

		const TKey operator [] (int i) const {
			if(dictionary->entries)return dictionary->entries->getPointer()[i].key;
			return TKey();
		}

		int get_Count(){
			return dictionary->count();
		}
	};

	struct ValueCollection {
		void *kass;
		void *monitor;
		Dictionary<TKey, TValue> *dictionary;

		TValue operator [] (int i) {
			if(dictionary->entries)return dictionary->entries->getPointer()[i].value;
			return TValue();
		}

		const TValue operator [] (int i) const {
			if(dictionary->entries)return dictionary->entries->getPointer()[i].value;
			return TValue();
		}

		int get_Count(){
			return dictionary->count();
		}
	};
};
