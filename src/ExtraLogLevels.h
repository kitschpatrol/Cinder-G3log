#pragma once

#include "g3log/g3log.hpp"

// Extra levels to match Cinder's
const LEVELS VERBOSE{g3::kDebugVaulue - 1, {"VERBOSE"}};
const LEVELS G3_ERROR{g3::kWarningValue + 1, {"ERROR"}};