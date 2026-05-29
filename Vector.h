#pragma once
#include <stdexcept>
#include <ranges>
#include <limits>
#include <algorithm>
#include <compare>
#include <cassert>
#include "timer.h"

template<typename T>
class Vector {
private:
	T* data_;
	size_t size_;
	size_t capacity_;

public:
	using size_type = std::size_t;
	using ref = T&; //reference
	using const_ref = const T&;
	using it = T*; //iterator
	using const_it = const T*;
	using reverse_it = std::reverse_iterator<it>;
	using const_reverse_it = std::reverse_iterator<const_it>;

	//member functions
	Vector();
	Vector(size_type count);
	Vector(size_type count, const T& value);
	Vector(std::initializer_list<T> init);
	Vector(const Vector& other);
	Vector(Vector&& other) noexcept;

	~Vector();

	void assign(size_type count, const T& value);
	template<std::ranges::input_range R>
	void assign_range(R&& rg);

	//element access

	ref at(size_type pos);
	const_ref at(size_type pos) const;

	ref front();
	const_ref front() const;

	ref back();
	const_ref back() const;

	T* data();
	const T* data() const;



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
	size_type size() const { return size_; } //getter
	size_type max_size() const { return std::numeric_limits<size_type>::max(); } //getter
	size_type capacity() const { return capacity_; } //getter

	void reserve(size_type new_capacity);
	void shrink_to_fit();

	//modifiers

	void clear();
	it insert(const_it pos, const T& value);
	it insert(const_it pos, T&& value);
	it insert(const_it pos, std::initializer_list<T> ilist);
	template<class InputIt>
	it insert(const_it pos, InputIt first, InputIt last);
	template<std::ranges::input_range R>
	constexpr it insert_range(const_it pos, R&& rg);
	void push_back(const T& value);
	void push_back(T&& value);
	void pop_back();
	void resize(size_type count);
	void resize(size_type count, const T& value);
	template<class... Args>
	it emplace(const_it pos, Args&&... args);
	template<class... Args>
	ref emplace_back(Args&&... args);
	it erase(const_it pos);
	it erase(const_it first, const_it last);
	constexpr void swap(Vector& other) noexcept;

	// operators

	Vector& operator=(const Vector& other);

	Vector& operator=(Vector&& other) noexcept;

	ref operator[](size_type pos);
	const_ref operator[](size_type pos) const;
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
Vector<T>::Vector(size_type count)
	:
	data_(new T[count]),
	size_(count),
	capacity_(count)
{
}

template<typename T>
Vector<T>::Vector(size_type count, const T& value)
	:
	data_(new T[count]),
	size_(count),
	capacity_(count)
{
	assign(count, value);
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> init) {
	size_ = init.size();
	capacity_ = init.size();
	data_ = new T[capacity_];

	size_type i = 0;
	for (const auto& v : init)
		data_[i++] = v;
}

template<typename T>
Vector<T>::Vector(const Vector& other)
	:
	data_(nullptr),
	size_(other.size_),
	capacity_(other.capacity_)
{
	if (capacity_ > 0)
	{
		data_ = new T[capacity_];

		for (size_type i = 0; i < size_; ++i)
			data_[i] = other.data_[i];
	}
}

template<typename T>
Vector<T>::Vector(Vector&& other) noexcept
	:
	data_(other.data_),
	size_(other.size_),
	capacity_(other.capacity_)
{
	other.data_ = nullptr;
	other.size_ = 0;
	other.capacity_ = 0;
}

// destructor

template<typename T>
Vector<T>::~Vector() {
	delete[] data_;
}

//operators

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
	if (this == &other)
		return *this;

	T* new_data = nullptr;

	if (other.capacity_ > 0)
	{
		new_data = new T[other.capacity_];

		for (size_type i = 0; i < other.size_; ++i)
			new_data[i] = other.data_[i];
	}

	delete[] data_;

	data_ = new_data;
	size_ = other.size_;
	capacity_ = other.capacity_;

	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept
{
	if (this == &other)
		return *this;

	delete[] data_;

	data_ = other.data_;
	size_ = other.size_;
	capacity_ = other.capacity_;

	other.data_ = nullptr;
	other.size_ = 0;
	other.capacity_ = 0;

	return *this;
}

template<typename T>
Vector<T>::ref Vector<T>::operator[](size_type pos) {
	return data_[pos];
}

template<typename T>
Vector<T>::const_ref Vector<T>::operator[](size_type pos) const {
	return data_[pos];
}

//non-member operators

template<typename T>
bool operator==(const Vector<T>& a, const Vector<T>& b)
{
	if (a.size() != b.size())
		return false;

	for (size_t i = 0; i < a.size(); ++i) {
		if (!(a[i] == b[i])) return false;
	}

	return true;
}

template<typename T>
bool operator!=(const Vector<T>& a, const Vector<T>& b)
{
	return !(a == b);
}

template<typename T>
bool operator<(const Vector<T>& a, const Vector<T>& b)
{
	return std::lexicographical_compare(
		a.begin(), a.end(),
		b.begin(), b.end()
	);
}

template<typename T>
bool operator>(const Vector<T>& a, const Vector<T>& b)
{
	return b < a;
}

template<typename T>
bool operator<=(const Vector<T>& a, const Vector<T>& b)
{
	return !(b < a);
}

template<typename T>
bool operator>=(const Vector<T>& a, const Vector<T>& b)
{
	return !(a < b);
}

template<typename T>
auto operator<=>(const Vector<T>& a, const Vector<T>& b)
{
	return std::lexicographical_compare_three_way(
		a.begin(), a.end(),
		b.begin(), b.end()
	);
}

//non-member functions

template<typename T>
typename Vector<T>::size_type erase(Vector<T>& v, const T& value)
{
	auto new_end = std::remove(v.begin(), v.end(), value);
	auto removed = v.end() - new_end;

	v.erase(new_end, v.end());

	return removed;
}

template<typename T, class Pred>
typename Vector<T>::size_type erase_if(Vector<T>& v, Pred pred)
{
	auto new_end = std::remove_if(v.begin(), v.end(), pred);

	size_t removed = v.end() - new_end;

	v.erase(new_end, v.end());

	return removed;
}

// member functions

template<typename T>
void Vector<T>::assign(size_type count, const T& value) {
	if (count > capacity_) {
		delete[] data_;

		data_ = new T[count];
		capacity_ = count;
	}

	for (size_type i = 0; i < count; i++) {
		data_[i] = value;
	}
	size_ = count;
}

template<typename T>
template<std::ranges::input_range R>
void Vector<T>::assign_range(R&& rg) {
	clear();

	for (auto&& value : rg) {
		push_back(value);
	}
}

// element access 

template<typename T>
typename Vector<T>::ref Vector<T>::at(size_type pos) {
	if (pos >= size_ || empty()) throw std::out_of_range("Vector::at");

	return data_[pos];
}

template<typename T>
typename Vector<T>::const_ref Vector<T>::at(size_type pos) const {
	if (pos >= size_ || empty()) throw std::out_of_range("Vector::at");

	return data_[pos];
}

template<typename T>
typename Vector<T>::ref Vector<T>::front() {
	return *begin();
}

template<typename T>
typename Vector<T>::const_ref Vector<T>::front() const {
	return *begin();
}

template<typename T>
typename Vector<T>::ref Vector<T>::back() {
	return *(end() - 1);
}

template<typename T>
typename Vector<T>::const_ref Vector<T>::back() const {
	return *(end() - 1);
}

template<typename T>
T* Vector<T>::data() {
	return data_;
}

template<typename T>
const T* Vector<T>::data() const {
	return data_;
}

// capacity

template<typename T>
void Vector<T>::reserve(size_type new_capacity) {
	if (new_capacity <= capacity_)
		return;

	T* new_data = new T[new_capacity];
	for (size_type i = 0; i < size_; i++) {
		new_data[i] = data_[i];
	}
	delete[] data_;

	data_ = new_data;
	capacity_ = new_capacity;
}

template<typename T>
void Vector<T>::shrink_to_fit()
{
	if (size_ == capacity_) return;

	T* new_data = nullptr;

	if (size_ > 0)
	{
		new_data = new T[size_];

		for (size_type i = 0; i < size_; ++i)
			new_data[i] = std::move(data_[i]);
	}

	delete[] data_;
	data_ = new_data;
	capacity_ = size_;
}

// modifiers

template<typename T>
template<class... Args>
typename Vector<T>::it Vector<T>::emplace(const_it pos, Args&&... args)
{
	size_type index = pos - begin();

	if (size_ == capacity_)
		reserve(capacity_ ? capacity_ * 2 : 1);

	std::move_backward(begin() + index, end(), end() + 1);

	data_[index] = T(std::forward<Args>(args)...);

	++size_;
	return begin() + index;
}

template<typename T>
template<class... Args>
typename Vector<T>::ref Vector<T>::emplace_back(Args&&... args) {
	emplace(end(), std::forward<Args>(args)...);

	return back();
}

template<typename T>
void Vector<T>::clear()
{
	for (size_type i = 0; i < size_; ++i)
		data_[i].~T();

	size_ = 0;
}

template<typename T>
typename Vector<T>::it Vector<T>::insert(const_it pos, const T& value) {
	if (pos < begin() || pos > end()) throw std::out_of_range("Vector::insert");

	size_type index = pos - begin(); //del reserve()

	if (size_ == capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2);

	std::move_backward(begin() + index, end(), end() + 1);

	data_[index] = value;
	++size_;

	return begin() + index;
}

template<typename T>
template<class InputIt>
typename Vector<T>::it
Vector<T>::insert(const_it pos, InputIt first, InputIt last)
{
	size_type index = pos - begin();

	size_type count = std::distance(first, last);

	if (size_ + count > capacity_)
		reserve(std::max(capacity_ * 2, size_ + count));

	std::move_backward(begin() + index, end(), end() + count);

	size_type i = index;
	for (auto it = first; it != last; ++it)
		data_[i++] = *it;

	size_ += count;

	return begin() + index;
}

template<typename T>
typename Vector<T>::it Vector<T>::insert(const_it pos, T&& value) {
	if (pos < begin() || pos > end()) throw std::out_of_range("Vector::insert");

	size_type index = pos - begin();

	if (size_ == capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2);

	std::move_backward(begin() + index, end(), end() + 1);

	data_[index] = std::move(value);
	size_++;

	return begin() + index;
}

template<typename T>
typename Vector<T>::it Vector<T>::insert(const_it pos, std::initializer_list<T> ilist) {
	size_type index = pos - begin();
	size_type count = ilist.size();

	if (size_ + count > capacity_)
		reserve(std::max(capacity_ * 2, size_ + count));

	// shift existing elements
	std::move_backward(begin() + index, end(), end() + count);

	// copy new elements
	size_type i = index;
	for (const auto& v : ilist)
		data_[i++] = v;

	size_ += count;

	return begin() + index;
}

template<typename T>
template<std::ranges::input_range R>
constexpr typename Vector<T>::it Vector<T>::insert_range(const_it pos, R&& rg){
	if (pos < begin() || pos > end())
		throw std::out_of_range("Vector::insert_range");

	size_type index = pos - begin();

	size_type original_index = index;

	for (auto&& value : rg)
	{
		insert(begin() + index, value);
		++index;
	}

	return begin() + original_index;
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
void Vector<T>::resize(size_type count)
{
	if (count == size_) return;

	if (count > capacity_)
		reserve(count);

	if (count > size_)
	{
		for (size_type i = size_; i < count; ++i)
			data_[i] = T{};
	}

	size_ = count;
}

template<typename T>
void Vector<T>::resize(size_type count, const T& value)
{
	if (count > capacity_)
		reserve(count);

	if (count > size_)
	{
		for (size_type i = size_; i < count; ++i)
			data_[i] = value;
	}

	size_ = count;
}

template<typename T>
typename Vector<T>::it Vector<T>::erase(const_it pos) {
	if (pos < begin() || pos >= end())
		throw std::out_of_range("Vector::erase");

	size_type index = pos - begin();

	std::move(begin() + index + 1, end(), begin() + index);

	--size_;

	return begin() + index;
}

template<typename T>
typename Vector<T>::it Vector<T>::erase(const_it first, const_it last)
{
	if (first < begin() || first > end() ||
		last < begin() || last > end() ||
		first > last)
	{
		throw std::out_of_range("Vector::erase");
	}

	size_type start = first - begin();
	size_type count = last - first;

	std::move(begin() + start + count, end(), begin() + start);

	size_ -= count;

	return begin() + start;
}

template<typename T>
constexpr void Vector<T>::swap(Vector& other) noexcept {
	std::swap(data_, other.data_);
	std::swap(size_, other.size_);
	std::swap(capacity_, other.capacity_);
}

//Testing 
template<typename Vec>
auto measure_push_back(size_t count)
{
	Vec v;

	Timer timer;

	for (size_t i = 0; i < count; ++i)
	{
		v.push_back(i);
	}

	volatile auto size = v.size();

	return timer.elapsed();
}