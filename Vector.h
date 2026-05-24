template<typename T>
class Vector {
private:
	T* data_; //pointer to T array
	size_t size_;
	size_t capacity_;

public:
	using ref = T&;
	using it = T*; //iterator
	using const_it = const T*;

	//member functions
	Vector();
	Vector(size_t count);
	Vector(size_t count, const T& value);

	~Vector();

	void assign(size_t count, const T& value);

	//element access

	ref at(size_t pos);

	//iterators

	it begin();
	it end();

	//capacity

	bool empty() const { return size_ == 0; }; //getter
	size_t size() const { return size_; } //getter
	size_t capacity() const { return capacity_; } //getter
	void reserve(size_t new_capacity);

	//modifiers

	void clear() { size_ = 0; };
	it insert(const_it pos, T& value);
};

// constructors

template<typename T>
Vector<T>::Vector()
	:
	data_(nullptr),
	size_(0),
	capacity_(0)
{
}

template<typename T>
Vector<T>::Vector(size_t count)
	:
	data_(new T[count]),
	size_(count),
	capacity_(count)
{
}

template<typename T>
Vector<T>::Vector(size_t count, const T& value)
	:
	data_(new T[count]),
	size_(count),
	capacity_(count)
{
	assign(count, value);
}

// destructors

template<typename T>
Vector<T>::~Vector() {
	delete[] data_;
}

// member functions

template<typename T>
void Vector<T>::assign(size_t count, const T& value) {
	if (count > capacity_) {
		delete[] data_;

		data_ = new T[count];
		capacity_ = count;
	}

	for (size_t i = 0; i < count; i++) {
		data_[i] = value;
	}
	size_ = count;
}

// element access 

template<typename T>
Vector<T>::ref Vector<T>::at(size_t pos) {

}

// iterators

template<typename T>
Vector<T>::it Vector<T>::begin() {

}

template<typename T>
Vector<T>::it Vector<T>::end() {

}

// capacity

template<typename T>
void Vector<T>::reserve(size_t new_capacity) {
	if (new_capacity <= capacity_) 
		return;

	T* new_data = new T[new_capacity];
	for (size_t i = 0; i < size_; i++) {
		new_data[i] = data_[i];
	}
	delete[] data_;

	data_ = new_data;
	capacity_ = new_capacity;
}

// modifiers

template<typename T>
Vector<T>::it Vector<T>::insert(const_it pos, T& value) {

}