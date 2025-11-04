#pragma once

// QMK settings
#define TAPPING_TERM 200
#define TAP_CODE_DELAY 10

// Define the matrix configuration for your hand-wired keyboard
// Rows are doubled up
#define MATRIX_ROWS 8
#define MATRIX_COLS 5

// You can change these if you have a different number of rows/columns
#define MATRIX_ROW_PINS {D3, D2, D0, D4}
#define MATRIX_COL_PINS {B1, F7, F6, F5, F4}

#define DIODE_DIRECTION COL2ROW

#define USE_SERIAL
#define SOFT_SERIAL_PIN D1

#define MASTER_LEFT
/* #define MASTER_RIGHT */

#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2500

