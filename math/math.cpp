#include <cmath>
#include "purescript.h"
#include <iostream>

// Tested with package v2.1.1

FOREIGN_BEGIN(Math)

exports["abs"] = [](const boxed &x) -> boxed {
    return std::fabs(unbox<double>(x));
};

exports["floor"] = [](const boxed &x) -> boxed {
    const auto r = std::round(unbox<double>(x) - 0.5);
    return r;
};

exports["pow"] = [](const boxed &n_) -> boxed {
    const auto n = unbox<double>(n_);
    return [=](const boxed &p) -> boxed {
        return std::pow(n, unbox<double>(p));
    };
};

FOREIGN_END
