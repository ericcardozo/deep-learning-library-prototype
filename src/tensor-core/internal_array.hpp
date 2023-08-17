#ifndef INTERNAL_ARRAY_HPP
#define INTERNAL_ARRAY_HPP

#include <iostream>
#include <vector>
#include <memory>

namespace internal {

class Array {
    public:
    using scalar_type = float;
    using pointer = scalar_type*;
    using const_pointer = const scalar_type*;
    using size_type = std::size_t;
    using shape_type = std::vector<size_type>;
    using storage_type = std::vector<scalar_type>;
    using iterator = storage_type::iterator;
    using const_iterator = storage_type::const_iterator;

    virtual ~Array() = default;

    virtual void copy(const Array* other) {
        size_ = other->size_;
        shape_ = other->shape_;
        storage_ = other->storage_;
    };

    virtual void move(Array* other) {
        size_ = other->size_;
        shape_ = std::move(other->shape_);
        storage_ = std::move(other->storage_);
        other->size_ = 0;
        other->shape_.clear();
        other->storage_.clear();
    };

    Array() = default;
    Array(const Array* other) { copy(other); }
    Array(shape_type shape)
    :   shape_(shape) {
        size_ = 1; for (size_type dimension : shape) size_ *= dimension;
        storage_.resize(size_);
    }

    size_type size() const { return size_; }
    shape_type shape() const { return shape_; }
    pointer data() { return storage_.data(); }
    const_pointer data() const { return storage_.data(); }

    iterator begin() { return storage_.begin(); }
    iterator end() { return storage_.end(); }
    const_iterator begin() const { return storage_.cbegin(); }
    const_iterator end() const { return storage_.cend(); }
    const_iterator cbegin() const { return storage_.cbegin(); }
    const_iterator cend() const { return storage_.cend(); }

    void add(const Array* other);
    void multiply(const Array* other);
    void divide(const Array* other);
    void subtract(const Array* other);

    private:
    size_type size_;
    shape_type shape_;
    storage_type storage_;
};

// implement with eigen.

void Array::add(const Array* other) {
    if(shape_ != other->shape_) throw std::runtime_error("shape mismatch");
    for(size_type i = 0; i < size_; ++i) storage_[i] += other->storage_[i];
}

void Array::multiply(const Array* other) {
    if(shape_ != other->shape_) throw std::runtime_error("shape mismatch");
    for(size_type i = 0; i < size_; ++i) storage_[i] *= other->storage_[i];
}

void Array::divide(const Array* other) {
    if(shape_ != other->shape_) throw std::runtime_error("shape mismatch");
    for(size_type i = 0; i < size_; ++i) storage_[i] /= other->storage_[i];
}

void Array::subtract(const Array* other) {
    if(shape_ != other->shape_) throw std::runtime_error("shape mismatch");
    for(size_type i = 0; i < size_; ++i) storage_[i] -= other->storage_[i];
}

} // namespace internal

#endif // INTERNAL_ARRAY_HPP