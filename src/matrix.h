#pragma once

#include <stdint.h>

struct MatrixLine{
    uint8_t index;
    uint8_t gpio;
};

inline constexpr MatrixLine ROWS[] = {
    {0, 8},
    {1, 9},
    {2, 12},
    {3, 14},
    {4, 13},
    {5, 15},
};

inline constexpr MatrixLine COLS[] = {
    {0, 5},
    {1, 6},
    {2, 7},
    {3, 10},
    {4, 11},
    {5, 22},
    {6, 19},
    {7, 20},
    {8, 21},
    {9, 16},
    {10, 17},
    {11, 18}
};

inline constexpr uint8_t MATRIX_ROW_COUNT = sizeof(ROWS) / sizeof(ROWS[0]);
inline constexpr uint8_t MATRIX_COL_COUNT = sizeof(COLS) / sizeof(COLS[0]);

inline constexpr uint8_t KEY_NONE = 0;
inline constexpr uint8_t MATRIX_KEY_COUNT = 73;

inline constexpr uint8_t KEY_ID[6][12] = {
    // col:     0    1   2   3   4   5   6   7   8   9  10  11
    /* row0 */ { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12},
    /* row1 */ {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,  0},
    /* row2 */ {25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36},
    /* row3 */ {37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48},
    /* row4 */ {49, 50, 51, 52, 53, 54, 55, 56, 57,  0,  0,  0},
    /* row5 */ {61, 62, 63, 64, 65, 66, 67, 68,  0,  0,  0,  0}
};

void matrix_init();
void matrix_task();

bool matrix_pressed(uint8_t key_id);
bool matrix_has_pressed_key();
bool matrix_changed();