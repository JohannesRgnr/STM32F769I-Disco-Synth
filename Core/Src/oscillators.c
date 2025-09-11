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
#include "help_func.h"
#include "consts.h"
#include "oscillators.h"


void osc_init(oscillator_t *osc, float amp, float freq, float FMindex, float FMratio, float pw)
{
    osc->amp = amp;
    osc->freq = freq;
    osc->phase = 0;
    osc->FMindex = FMindex;
    osc->FMratio = FMratio;
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


float cordicSine(oscillator_t *osc)
{
     osc->phase = wrap(osc->phase, 1);
    float phase = TWOPI * osc->phase;
     float fx = cosf(phase);
     float fy = sinf(phase);
    osc->phase += TS * osc->freq;  // increment phase (phase normalized from 0 to 1)

    float x = 0.f, y = 1.f;
    float sumx = 0.f, sumy = 0.f;

    for (int i = 1; i <= 128; i++)
    {
        const float level = osc->amp / (float)i;
        float oldx = x;
        float oldy = y;
        x = (oldx*fx - oldy*fy);
        y = (oldx*fy + oldy*fx);
        sumx = sumx + (x * level);
       // sumy = sumy + (y * level);
    }
    osc->output = sumx * ONEOVERPI;


    return osc->output;
}


