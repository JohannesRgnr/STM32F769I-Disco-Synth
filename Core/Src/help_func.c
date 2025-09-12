/**
 * @file help_func.c
 * @author Johannes R.
 * @brief 
 * @version 
 * @date 11.09.25
 * @note
 */

#include "help_func.h"


/**
 * @brief Constrain input value between lower and upper limits
 *
 * @param input
 * @param lower
 * @param upper
 * @return
 */
float clip(float input, float lower, float upper) {
    return max(lower, min(input, upper));
}


/**
 * @brief Linear interpolation within a given lookup table. Useful for wavetable oscillators.
 *
 * @param index
 * @param table_size
 * @param table
 * @return float
 */
float lutLerp(const float *table, uint16_t table_size, float index){
    uint32_t trunc = (uint32_t)index; // truncate the index but don't overwrite
    const float frac = index - (float)trunc; // get the fractional part

    while (trunc > table_size)
        trunc = trunc - table_size;

    // if (trunc == table_size-1)
    //     diff = table[0] - table[trunc]; // wrap
    // else
    const float diff = table[trunc + 1] - table[trunc]; // no need to check and wrap, table size is 1025

    // get the interpolated output
    return table[trunc] + (diff * frac);
}