#pragma once

// Enable double-tap reset to enter bootloader (RP2040)
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

// Optional: status LED while waiting for second tap
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
