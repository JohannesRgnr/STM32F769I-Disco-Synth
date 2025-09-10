/**
 * @file oscillators.c
 * @author Johannes R.
 * @brief 
 * @version 
 * @date 10.09.25
 * @note
 */

#include <math.h>
#include <stdint.h>
#include "oscillators.h"

void osc_init(oscillator_t *osc, float amp, float freq, float FM_index, float FM_ratio, float pw)
{
    osc->amp = amp;
    osc->freq = freq;
    osc->phase = 0;
    osc->FM_index = FM_index;
    osc->FM_ratio = FM_ratio;
    osc->pw = pw;
    osc->output = 0;
}




/**
 * @brief Fast white noise generator
 * @return random float value between -1 and 1
 * @note from https://www.musicdsp.org/en/latest/Other/273-fast-float-random-numbers.html
 */
float whiteNoise(oscillator_t *osc)
{
    static uint32_t seed = 1;
    seed *= 16807;
    osc->output = osc->amp * ((float)seed * 4.6566129e-010f - 1.f);
    return osc->output;
    // seed = (seed * 196314165) + 907633515;
    // return 0.5f*((float)seed * 0.000000000465661f + -1.0f);
}


