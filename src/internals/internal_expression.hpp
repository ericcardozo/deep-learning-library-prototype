#ifndef INTERNAL_EXPRESSION_HPP
#define INTERNAL_EXPRESSION_HPP

#include "internal_tensor.hpp"

namespace internal {

struct Expression : public Tensor {
    ~Expression() override = default;

    protected:
    Expression() { is_leaf(false); }
 };

} // namespace internal

#endif // INTERNAL_EXPRESSION_HPP