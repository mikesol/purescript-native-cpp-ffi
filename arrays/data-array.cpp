#include <limits>
#include <cassert>
#include <algorithm>
#include "purescript.h"

// Tested with package v5.0.0

FOREIGN_BEGIN(Data_Array)

exports["range"] = [](const boxed &start_) -> boxed {
    const auto start = unbox<int>(start_);
    return [=](const boxed &end_) -> boxed {
        const auto end = unbox<int>(end_);
        const auto step = start > end ? -1 : 1;
        array_t ns;
        for (auto i = start; i != end; i += step)
        {
            ns.emplace_back(i);
        }
        ns.emplace_back(end);
        return ns;
    };
};

exports["replicate"] = [](const boxed &count_) -> boxed {
    const auto count = unbox<int>(count_);
    return [=](const boxed &value) -> boxed {
        return array_t(count < 0 ? 0 : count, value);
    };
};

exports["length"] = [](const boxed &xs) -> boxed {
    const long long len = unbox<array_t>(xs).size();
    assert(len <= std::numeric_limits<int>::max());
    return static_cast<int>(len);
};

exports["cons"] = [](const boxed &e) -> boxed {
    return [=](const boxed &l_) -> boxed {
        const auto &l = unbox<array_t>(l_);
        array_t result;
        result.reserve(l.size() + 1);
        result.insert(result.cend(), e);
        result.insert(result.cend(), l.cbegin(), l.cend());
        return result;
    };
};

exports["snoc"] = [](const boxed &l_) -> boxed {
    return [=](const boxed &e) -> boxed {
        const auto &l = unbox<array_t>(l_);
        array_t result;
        result.reserve(l.size() + 1);
        result.insert(result.cend(), l.cbegin(), l.cend());
        result.insert(result.cend(), e);
        return result;
    };
};

exports["zipWith"] = [](const boxed &f) -> boxed {
    return [=](const boxed &l1_) -> boxed {
        return [=](const boxed &l2_) -> boxed {
            const long long len1 = unbox<array_t>(l1_).size();
            assert(len1 <= std::numeric_limits<int>::max());
            const int len1_ = static_cast<int>(len1);
            const long long len2 = unbox<array_t>(l2_).size();
            assert(len2 <= std::numeric_limits<int>::max());
            const int len2_ = static_cast<int>(len2);
            const int bound = std::min(len1_, len2_);
            array_t ns;
            const auto &l1u = unbox<array_t>(l1_);
            const auto &l2u = unbox<array_t>(l2_);
            for (auto i = 0; i < bound; i++)
            {
                ns.emplace_back(f(l1u[i])(l2u[i]));
            }
            return ns;
        };
    };
};

exports["slice"] = [](const boxed &start_) -> boxed {
    const auto start = unbox<int>(start_);
    return [=](const boxed &end_) -> boxed {
        const auto end = unbox<int>(end_);
        return [=](const boxed &xs_) -> boxed {
            const auto &xs = unbox<array_t>(xs_);
            const long long size = xs.size();
            assert(size <= std::numeric_limits<decltype(start)>::max());
            const auto length = static_cast<decltype(start)>(size);
            const auto _start = std::min(start, length);
            const auto _end = std::min(end, length);
            return array_t(xs.cbegin() + _start, xs.cbegin() + _end);
        };
    };
};

exports["indexImpl"] = [](const boxed &just) -> boxed {
    return [=](const boxed &nothing) -> boxed {
        return [=](const boxed &xs_) -> boxed {
            return [=](const boxed &i_) -> boxed {
                const auto &xs = unbox<array_t>(xs_);
                const auto i = unbox<int>(i_);
                return i < 0 || i >= xs.size() ? nothing : just(xs[i]);
            };
        };
    };
};

exports["unsafeIndexImpl"] = [](const boxed &xs) -> boxed {
    return [=](const boxed &n) -> boxed {
        return unbox<array_t>(xs)[unbox<int>(n)];
    };
};

FOREIGN_END
