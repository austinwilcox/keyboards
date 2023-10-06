/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

// wiring of each half
/* #define MATRIX_COL_PINS { F7, F6, B3, B1, B2, B6 } */
#define MATRIX_COL_PINS { B6, B2, B1, B3, F6, F7 }
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4, B5 }

#define DIODE_DIRECTION COL2ROW

#define USE_SERIAL
#define SOFT_SERIAL_PIN D1

#define MASTER_LEFT
/* #define MASTER_RIGHT */

#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2500

