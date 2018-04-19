#include <iostream>
#include <iterator>

template<class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T> {

public:
    explicit Iterator(T* ptr) : ptr_(ptr) {}

    Iterator& operator++() {
        ++ptr_;

        return (*this);
    }

    Iterator& operator--() {
        --ptr_;

        return (*this);
    }

    Iterator operator+(T x) {
        return Iterator(ptr_ + x);
    }

    Iterator operator-(T x) {
        return Iterator(ptr_ - x);
    }

    Iterator& operator+=(T x) {
        ptr_ += x;

        return (*this);
    }

    Iterator& operator-=(T x) {
        ptr_ -= x;

        return (*this);
    }

    bool operator==(const Iterator& it) {
        return (ptr_ == it.ptr_);
    }

    bool operator!=(const Iterator& it) {
        return (ptr_ != it.ptr_);
    }

    T& operator*() {
        return (*ptr_);
    }

    T* operator->() {
        return ptr_;
    }

private:
    T* ptr_;
};

template<class T>
class ReverseIterator : public std::iterator<std::random_access_iterator_tag, T> {

public:
    explicit ReverseIterator(T* ptr) : ptr_(ptr) {}

    ReverseIterator& operator++() {
        --ptr_;

        return (*this);
    }

    ReverseIterator& operator--() {
        ++ptr_;

        return (*this);
    }

    ReverseIterator operator+(T x) {
        return ReverseIterator(ptr_ - x);
    }

    ReverseIterator operator-(T x) {
        return ReverseIterator(ptr_ + x);
    }

    ReverseIterator& operator+=(T x) {
        ptr_ -= x;

        return (*this);
    }

    ReverseIterator& operator-=(T x) {
        ptr_ += x;

        return (*this);
    }

    bool operator==(const ReverseIterator& it) {
        return (ptr_ == it.ptr_);
    }

    bool operator!=(const ReverseIterator& it) {
        return (ptr_ != it.ptr_);
    }

    T& operator*() {
        return (*ptr_);
    }

    T* operator->() {
        return ptr_;
    }

private:
    T* ptr_;
};


template<class T>
class Vector {

public:
    using value_type = T;
    using iterator = Iterator<T>;
    using const_iterator = Iterator<const T>;
    using reverse_iterator = ReverseIterator<T>;
    using const_reverse_iterator = ReverseIterator<const T>;

    T* allocate(ssize_t size) {
        return static_cast<T*> (::operator new(sizeof(T) * size));
    }

    void deallocate() {
        if (data_) {
            ::operator delete(data_);
            data_ = nullptr;
        }
    }

    // BEGIN---------------------------------------------- CONSTRUCTOR ------------------------------------------------
    Vector() {
        data_ = nullptr;

        size_ = 0;
        capacity_ = 0;
    }

    explicit Vector(ssize_t size) {
        size_ = size;
        capacity_ = size_ * 2;

        data_ = new T[capacity_];
    }

    Vector(const Vector& vector) : Vector() {
        (*this) = vector;
    }

    Vector(Vector&& vector) : Vector() {
        (*this) = vector;
    }

    explicit Vector(ssize_t size, const T& default_value) : Vector(size) {
        for (ssize_t i = 0; i < size; i++) {
            data_[i] = default_value;
        }
    }

    Vector(std::initializer_list<T> v_list) : Vector(v_list.size()) {
        ssize_t i = 0;

        for (auto it = v_list.begin(); it < v_list.end(); it++) {
            data_[i++] = (*it);
        }
    }
    // END------------------------------------------------ CONSTRUCTOR ------------------------------------------------

    // BEGIN---------------------------------------------- OPERATORS --------------------------------------------------
    Vector& operator=(const Vector& _v) {
        if (_v.data_ != data_ || _v.size_ > size_) {
            deallocate();

            size_ = _v.size_;
            capacity_ = _v.capacity_;

            data_ = allocate(capacity_);
        }

        for (ssize_t i = 0; i < size_; i++) {
            data_[i] = _v.data_[i];
        }

        return (*this);
    }

    Vector& operator=(Vector&& _v) {
        deallocate();

        data_ = std::move(_v.data_);

        size_ = _v.size_;
        capacity_ = _v.capacity_;

        _v.data_ = nullptr;
        _v.size_ = 0;
        _v.capacity_ = 0;

        return (*this);
    }

    T& operator[](ssize_t _pos) {
        return data_[_pos];
    }

    const T& operator[](ssize_t _pos) const {
        return data_[_pos];
    }
    // END------------------------------------------------ OPERATORS --------------------------------------------------

    void destroy(T* ptr, const ssize_t i) {
        (ptr + i)->~value_type();
    }

    const T* data() const {
        return data_;
    }

    void push_back(const T& _value) {
        if (size_ == capacity_) {
            reserve(std::max((ssize_t)8, size_) * 2);
        }

        data_[size_++] = _value;
    }

    void pop_back() {
        if (size_ == 1) {
            clear();
        } else if (size_ > 1) {
            destroy(data_, size_-- - 1);
        }
    }

    void resize(ssize_t size) {
        if (size > 0) {
            T* new_data = allocate(size);

            std::copy(data_, &data_[std::min(size_, size)], new_data);

            std::swap(data_, new_data);

            for (ssize_t i = 0; i < size_; i++) {
                destroy(new_data, i);
            }

            if (size_ < size) {
                for (ssize_t i = size_; i < size; i++) {
                    data_[i] = T();
                }
            }

            size_ = size;
        } else {
            size_ = 0;
        }
    }

    void reserve(ssize_t size) {
        ssize_t oldsize = size_;
        resize(size);
        capacity_ = size_;
        size_ = oldsize;
    }

    ssize_t size() const noexcept {
        return size_;
    }

    ssize_t capacity() const noexcept {
        return capacity_;
    }

    bool empty() const noexcept {
        return (size_ == 0);
    }

    void clear() {
        for (ssize_t i = 0; i < size_; i++) {
            destroy(data_, i);
        }

        size_ = 0;
        capacity_ = 0;

        deallocate();
    }


    // BEGIN---------------------------------------------- ITERATORS --------------------------------------------------
    iterator begin() noexcept {
        return Iterator<T>(data_);
    }
    iterator end() noexcept {
        return Iterator<T>(data_ + size_);
    }

    const_iterator cbegin() const noexcept {
        return Iterator<const T>(data_);
    }
    const_iterator cend() const noexcept {
        return Iterator<const T>(data_ + size_);
    }

    reverse_iterator rbegin() noexcept {
        return ReverseIterator<T>(data_ + size_ - 1);
    }
    reverse_iterator rend() noexcept {
        return ReverseIterator<T>(data_ - 1);
    }

    const_reverse_iterator crbegin() const noexcept {
        return ReverseIterator<const T>(data_ + size_ - 1);
    }
    const_reverse_iterator crend() const noexcept {
        return ReverseIterator<const T>(data_ - 1);
    }
    // END------------------------------------------------ ITERATORS --------------------------------------------------

    // BEGIN---------------------------------------------- DESTRUCTOR ------------------------------------------------
    ~Vector() {
        clear();
    }
    // END------------------------------------------------ DESTRUCTOR ------------------------------------------------

private:
    T* data_;

    ssize_t size_;
    ssize_t capacity_;
};
