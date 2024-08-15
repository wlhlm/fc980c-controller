// Copyright 2024 Wilhelm Schuster
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#include "actuation_point.h"

typedef union {
    uint32_t raw;
    struct {
        int8_t actuation_point_value;
    };
} keyboard_config_t;

void fc980c_eeconfig_update_kb(void);
