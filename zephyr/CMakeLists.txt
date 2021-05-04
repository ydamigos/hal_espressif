# SPDX-License-Identifier: Apache-2.0

message(STATUS "Selected SOC: ${CONFIG_SOC}")
add_subdirectory("${CONFIG_SOC}")
