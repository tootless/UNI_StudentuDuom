template<typename T>
class Vector {
private:
	T* data_; //pointer to T array
	size_t size_;
	size_t capacity;

public:
	using ref = T&;
	using iterator = T*;

	//member functions
	Vector();
	Vector(size_t count, const T& value);

	~Vector();

	void assign(size_t count, const T& value);

	//element access

	ref at(size_t pos);

	//iterators

	iterator begin();

	iterator end();

	//capacity

	bool empty() const; //getter
	size_t size() const { return size_; } //getter

	//modifiers
	
	void clear();
};