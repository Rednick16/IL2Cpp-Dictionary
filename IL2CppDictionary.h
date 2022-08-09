#include "monoArray.h"

template<typename T>
struct IEqualityComparer
{
    bool Equals(T x, T y){
		if(x == y)return true;
		return false;
	}
    int GetHashCode(T obj){
		/*
		optional System::InternalGetHashCode(obj o)
		
		return reinterpret_cast<int (*)(T)>(getRealOffset(0x242B9FC))(obj);
		*/
	    return 0;
	}
};

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
	IEqualityComparer<TKey> comparer;
	KeysCollection *keys;
	ValueCollection *values;
	void *_syncRoot;

	IEqualityComparer<TKey> *get_Comparer(){
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
		return FindEntry(key);
	}

	const TValue operator [] (TKey key) const {
		return FindEntry(key);
	}

	TValue FindEntry(TKey key){
		if(!key) return TValue();

		for (int i = 0; i < entries->getLength(); i++){
			if(comparer.Equals(entries->getPointer()[i].key, key)) return entries->getPointer()[i].value;
		}

		return TValue();
	}

	struct KeysCollection {
		Dictionary<TKey, TValue> *dictionary;

		TKey operator [] (int i) {
			return dictionary->entries->getPointer()[i].key;
		}

		const TKey operator [] (int i) const {
			return dictionary->entries->getPointer()[i].key;
		}

		int get_Count(){
			return dictionary->entries->getLength();
		}
	};

	struct ValueCollection {
		Dictionary<TKey, TValue> *dictionary;

		TValue operator [] (int i) {
			if(dictionary && dictionary->entries) return dictionary->entries->getPointer()[i].value;
			return TValue();
		}

		const TValue operator [] (int i) const {
			if(dictionary && dictionary->entries) return dictionary->entries->getPointer()[i].value;
			return TValue();
		}

		int get_Count(){
			return dictionary->entries->getLength();
		}
	};
};
