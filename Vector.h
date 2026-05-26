#include <stdexcept>

template<typename T>
class Vector {
private:
	T* data_; //pointer to T array
	size_t size_;
	size_t capacity_;

public:
	using ref = T&; //reference
	using const_ref = const T&;
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
	const_ref at(size_t pos) const;

	//iterators

	it begin();
	it end();

	//capacity

	bool empty() const { return size_ == 0; }; //getter
	size_t size() const { return size_; } //getter
	size_t capacity() const { return capacity_; } //getter
	void reserve(size_t new_capacity);

	//modifiers

	void clear();
	it insert(const_it pos, const T& value);
	it insert(const_it pos, T&& value);
	void push_back(const T& value);
	void push_back(T&& value);
	void pop_back();

	// operators

	Vector& operator=(const Vector& other);

	Vector& operator=(Vector&& other);
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

//operators

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
	if (this == &other) return *this;
	if (capacity_ < other.size_) {
		delete[] data_;
		data_ = new T[other.capacity_];
		capacity_ = other.capacity_;
	}

	for (size_t i = 0; i < other.size_; i++) {
		data_[i] = other.data_[i];
	}
	size_ = other.size_;

	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) {
	if (this == &other) return *this;

	delete[] data_;
	data_ = other.data_;
	size_ = other.size_;
	capacity_ = other.capacity_;

	other.data_ = nullptr;
	other.size_ = 0;
	other.capacity_ = 0;

	return *this;
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
	if (pos >= size_ || empty()) throw std::out_of_range("Vector::at");

	return data_[pos];
}

template<typename T>
Vector<T>::const_ref Vector<T>::at(size_t pos) const {
	if (pos >= size_ || empty()) throw std::out_of_range("Vector::at");

	return data_[pos];
}

// iterators

template<typename T>
Vector<T>::it Vector<T>::begin() {
	return data_;
}

template<typename T>
Vector<T>::it Vector<T>::end() {
	return data_ + size_;
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
void Vector<T>::clear() {
	size_ = 0;
}

template<typename T>
Vector<T>::it Vector<T>::insert(const_it pos, const T& value) {
	size_t index = pos - begin(); //del reserve()

	if (size_ == capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2);

	for (size_t i = size_; i > index; --i) {
		data_[i] = data_[i-1];
	}

	data_[index] = value;
	size_++;

	return begin() + index;
}

template<typename T>
Vector<T>::it Vector<T>::insert(const_it pos, T&& value) {

}

template<typename T>
void Vector<T>::push_back(const T& value)
{
	if (size_ == capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2);

	data_[size_] = value;
	size_++;
}

template<typename T>
void Vector<T>::push_back(T&& value) {

}

template<typename T>
void Vector<T>::pop_back() {
	if (!empty()) size_--;
}