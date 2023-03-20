template <typename T>
struct monoArray
{
    	void* klass;
    	void* monitor;
	void* bounds;
    	int   max_length;
    	T vector[65535];

    	T &operator [] (int i) 
    	{
        	return vector[i];
    	}

    	const T &operator [] (int i) const 
    	{
        	return vector[i];
    	}

    	bool Contains(T item) 
    	{
        	for (int i = 0; i < max_length; i++)
        	{
            		if(vector[i] == item) return true;
        	}
        	return false;
    	}
};

template<typename T>
using Array = monoArray<T>;
