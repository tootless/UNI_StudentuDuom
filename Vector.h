#include <stdexcept>
#include <ranges>
#include <limits>
#include <algorithm>

template<typename T>
class Vector {
private:
	T* data_;
	size_t size_;
	size_t capacity_;

public:
	using ref = T&; //reference
	using const_ref = const T&;
	using it = T*; //iterator
	using const_it = const T*;
	using reverse_it = std::reverse_iterator<it>;
	using const_reverse_it = std::reverse_iterator<const_it>;

	//member functions
	Vector();
	Vector(size_t count);
	Vector(size_t count, const T& value);

	~Vector();

	void assign(size_t count, const T& value);
	template<std::ranges::input_range R>
	void assign_range(R&& rg);

	//element access

	ref at(size_t pos);
	const_ref at(size_t pos) const;

	// iterators
	it begin() noexcept { return data_; }
	it end() noexcept { return data_ + size_; }

	const_it begin() const noexcept { return data_; }
	const_it end() const noexcept { return data_ + size_; }

	const_it cbegin() const noexcept { return begin(); }
	const_it cend() const noexcept { return end(); }

	// reverse iterators
	reverse_it rbegin() noexcept { return reverse_it(end()); }
	reverse_it rend() noexcept { return reverse_it(begin()); }

	const_reverse_it rbegin() const noexcept { return const_reverse_it(end()); }
	const_reverse_it rend() const noexcept { return const_reverse_it(begin()); }

	const_reverse_it crbegin() const noexcept { return rbegin(); }
	const_reverse_it crend() const noexcept { return rend(); }

	//capacity

	bool empty() const { return size_ == 0; }; //getter
	size_t size() const { return size_; } //getter
	size_t max_size() const { return std::numeric_limits<T>::max() / sizeof(T); } //getter
	size_t capacity() const { return capacity_; } //getter

	void reserve(size_t new_capacity);
	void shrink_to_fit();

	//modifiers

	void clear();
	it insert(const_it pos, const T& value);
	it insert(const_it pos, T&& value);
	void push_back(const T& value);
	void push_back(T&& value);
	void pop_back();
	void resize(size_t count);
	void resize(size_t count, const T& value);
	template<class... Args>
	it emplace(const_it pos, Args&&... args);
	it erase(const_it pos);
	it erase(const_it first, const_it last);
	constexpr void swap(Vector& other) noexcept;

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

template<typename T>
template<std::ranges::input_range R>
void Vector<T>::assign_range(R&& rg) {
	clear();

	for (auto&& value : R) {
		push_back(value);
	}
}

// element access 

template<typename T>
typename Vector<T>::ref Vector<T>::at(size_t pos) {
	if (pos >= size_ || empty()) throw std::out_of_range("Vector::at");

	return data_[pos];
}

template<typename T>
typename Vector<T>::const_ref Vector<T>::at(size_t pos) const {
	if (pos >= size_ || empty()) throw std::out_of_range("Vector::at");

	return data_[pos];
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

template<typename T>
void Vector<T>::shrink_to_fit() {
	if (size_ == capacity_) return;

	T* new_data = nullptr;
	if (size_ > 0) {
		new_data = new T[size_];

		for (size_t i = 0; i < size_; i++) {
			new_data[i] = std::move(data_[i]);
		}
	}
	delete[] data_;

	new_data = data_;
	capacity_ = size_;
}

// modifiers

template<typename T>
template<class... Args>
Vector<T>::it Vector<T>::emplace(const_it pos, Args&&... args) {
	if (pos < begin() || pos > end()) throw std::out_of_range("Vector::emplace");

	size_t index = pos - begin();

	if (size_ == capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2);

	T temp_elem(std::forward<Args>(args)...);

	if (index < size_) {
		std::move_backward(begin() + index, end(), end() + 1);
		data_[index] = std::move(temp_elem);
	}
	else {
		new (&data_[index]) T(std::move(temp_elem));
	}

	++size_;

	return begin() + index;
}

template<typename T>
void Vector<T>::clear() {
	size_ = 0;
}

template<typename T>
typename Vector<T>::it Vector<T>::insert(const_it pos, const T& value) {
	if (pos < begin() || pos > end()) throw std::out_of_range("Vector::insert");

	size_t index = pos - begin(); //del reserve()

	if (size_ == capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2);

	std::move_if_noexcept(begin() + index, end(), end() + 1);

	data_[index] = value;
	++size_;

	return begin() + index;
}

template<typename T>
typename Vector<T>::it
Vector<T>::insert(const_it pos, T&& value) {
	if (pos < begin() || pos > end()) throw std::out_of_range("Vector::insert");

	size_t index = pos - begin();

	if (size_ == capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2);

	for (size_t i = size_; i > index; --i) {
		data_[i] = std::move(data_[i - 1]);
	}

	data_[index] = std::move(value);
	size_++;

	return begin() + index;
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
	if (size_ == capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2);

	data_[size_] = std::move(value);
	size_++;
}

template<typename T>
void Vector<T>::pop_back() {
	if (!empty()) size_--;
}

template<typename T>
void Vector<T>::resize(size_t count) {
	if (count == size_) return;
	if (size_ > count) {
		for (size_t i = size_; i > count; --i) {
			data[i]
		}
	}
}

template<typename T>
void Vector<T>::resize(size_t count, const T& value) {

}

template<typename T>
typename Vector<T>::it Vector<T>::erase(const_it pos) {
	if (pos < begin() || pos >= end())
		throw std::out_of_range("Vector::erase");

	size_t index = pos - begin();

	std::move(begin() + index + 1, end(), begin() + index);

	--size_;

	return begin() + index;
}

template<typename T>
Vector<T>::it Vector<T>::erase(const_it first, const_it last)
{
	return it();
}

template<typename T>
constexpr void Vector<T>::swap(Vector& other) noexcept {
	std::swap(data_, other.data_);
	std::swap(size_, other.size_);
	std::swap(capacity_, other.capacity_);
}