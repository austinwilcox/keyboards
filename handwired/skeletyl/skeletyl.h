#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT_5x6( \
    L00, L01, L02, L03, L04,                          R00, R01, R02, R03, R04,\
    L10, L11, L12, L13, L14,                          R10, R11, R12, R13, R14,\
    L20, L21, L22, L23, L24,                          R20, R21, R22, R23, R24,\
                   L40, L41, L42,                 R40, R41, R42) { \
    { L00, L01, L02, L03, L04 }, \
    { L10, L11, L12, L13, L14 }, \
    { L20, L21, L22, L23, L24 }, \
    { XXX, XXX, L40, L41, L42 }, \
\
    { R00, R01, R02, R03, R04 }, \
    { R10, R11, R12, R13, R14 }, \
    { R20, R21, R22, R23, R24 }, \
    { R40, R41, R42, XXX, XXX }, \
}
