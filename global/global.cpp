#include "purescript.h"

FOREIGN_BEGIN(Global)
exports["infinity"] = std::numeric_limits<double>::infinity();

FOREIGN_END
