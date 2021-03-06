/*
 * Copyright (C) 2017-2018 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
#include "runtime/helpers/engine_node.h"
#include <cstdint>

namespace OCLRT {
typedef uint64_t FlushStamp;
struct CompletionStamp {
    uint32_t taskCount;
    uint32_t taskLevel;
    FlushStamp flushStamp;
    uint32_t deviceOrdinal;
    EngineType engineType;
};
} // namespace OCLRT
