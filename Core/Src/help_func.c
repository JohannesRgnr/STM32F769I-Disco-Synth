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
 * @return float
 */
float clip(float input, float lower, float upper) {
    return max(lower, min(input, upper));
}
