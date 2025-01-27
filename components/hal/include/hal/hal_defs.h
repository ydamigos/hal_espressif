// Copyright 2010-2018 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "esp_log.h"

#if defined(__ZEPHYR__)
#include "stubs.h"
#endif

// platform related stuff

#define HAL_SWAP32(word) __builtin_bswap32(word)
#define HAL_SWAP64(word) __builtin_bswap64(word)

#define HAL_LOGE(...)    ESP_LOGE(__VA_ARGS__)
#define HAL_LOGW(...)    ESP_LOGW(__VA_ARGS__)
#define HAL_LOGI(...)    ESP_LOGI(__VA_ARGS__)
#define HAL_LOGD(...)    ESP_LOGD(__VA_ARGS__)
#define HAL_LOGV(...)    ESP_LOGV(__VA_ARGS__)

#define STATIC_HAL_REG_CHECK(TAG, ENUM, VAL) _Static_assert((ENUM) == (VAL), #TAG" "#ENUM" definition no longer matches register value")

/** @cond */    //Doxy command to hide preprocessor definitions from docs */

/**
 * @brief Macro to force a 32-bit read, modify, then write on a peripheral register
 *
 * Due to a GCC bug, the compiler may still try to optimize read/writes to peripheral register fields by using 8/16 bit
 * access, even if they are marked volatile (i.e., -fstrict-volatile-bitfields has no effect).
 *
 * For ESP chips, the peripheral bus only allows 32-bit read/writes. The following macro works around the compiler issue
 * by forcing a 32-bit read/modify/write.
 *
 * @note This macro should only be called on register fields of xxx_struct.h type headers, as it depends on the presence
 *       of a 'val' field of the register union.
 * @note Current implementation reads into a uint32_t instead of copy base_reg direclty to temp_reg. The reason being
 *       that C++ does not create a copy constructor for volatile structs.
 */
#define HAL_FORCE_MODIFY_U32_REG_FIELD(base_reg, reg_field, field_val)    \
{                                                           \
    uint32_t temp_val = base_reg.val;                       \
    typeof(base_reg) temp_reg;                              \
    temp_reg.val = temp_val;                                \
    temp_reg.reg_field = (field_val);                       \
    (base_reg).val = temp_reg.val;                          \
}

/**
 * @brief Macro to force a 32-bit read on a peripheral register
 *
 * @note This macro should only be called on register fields of xxx_struct.h type headers. See description above for
 *       more details.
 * @note Current implementation reads into a uint32_t. See description above for more details.
 */
#define HAL_FORCE_READ_U32_REG_FIELD(base_reg, reg_field) ({    \
    uint32_t temp_val = base_reg.val;                       \
    typeof(base_reg) temp_reg;                              \
    temp_reg.val = temp_val;                                \
    temp_reg.reg_field;                                     \
})

/** @endcond */
