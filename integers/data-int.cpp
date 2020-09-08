#include <cmath>
#include <cassert>
#include <limits>
#include "purescript.h"

// Tested with package v4.0.0

FOREIGN_BEGIN(Data_Int)

exports["toNumber"] = [](const boxed &n) -> boxed {
    return static_cast<double>(unbox<int>(n));
};

//foreign import fromNumberImpl
//  :: (forall a. a -> Maybe a)
//  -> (forall a. Maybe a)
//  -> Number
//  -> Maybe Int

exports["fromNumberImpl"] = [](const boxed &f_) -> boxed {
    return [=](const boxed &m_) -> boxed {
        return [=](const boxed &n) -> boxed {
            return f_(static_cast<int>(unbox<double>(n)));
        };
    };
};

FOREIGN_END
