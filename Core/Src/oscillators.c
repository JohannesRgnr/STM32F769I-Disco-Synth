/**
 * @file oscillators.c
 * @author Johannes R.
 * @brief 
 * @version 
 * @date 10.09.25
 * @note
 */


#include <stdint.h>
#include "help_func.h"
#include "consts.h"
#include "oscillators.h"
#include "LUTs.h"

uint16_t harmonics = 50;

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

/**
 * An oscillator for additive synthesis
 * @param osc
 * @return Sum of sines
 */
float cordicAdditive(oscillator_t *osc)
{
    osc->phase = wrap(osc->phase, 1);

    const float sinphase = osc->phase;
    const float cosphase = wrap(sinphase + 0.25f, 1);

    const float fx = lutLerp(lut_sine, LUT_SINE_SIZE,LUT_SINE_SIZE * (sinphase)); // linear-interpolated sinewave
    const float fy = lutLerp(lut_sine, LUT_SINE_SIZE,LUT_SINE_SIZE * (cosphase)); // linear-interpolated sinewave

    // const float fx = sinf(TWOPI * sinphase);
    // const float fy = cosf(TWOPI * sinphase);

    float x = 0.f, y = 1.f;
    float sumx = 0.f;

    for (int i = 1; i <= harmonics; i++)
    {
        const float level = osc->amp * oneoverx[i];
        const float oldx = x;

        x = x*fx - y*fy;
        y = oldx*fy + y*fx;
        sumx = sumx + (x * level);
    }
    osc->output = sumx * ONEOVERPI;

    osc->phase += TS * osc->freq;  // increment phase (phase normalized from 0 to 1)
    return osc->output;
}


float sineAdditive(oscillator_t *osc)
{
    osc->phase = wrap(osc->phase, 1);
    float sumSines = 0.f;

    for (int i = 1; i <= harmonics; i++)
    {
        const float phase = wrap(osc->phase * i, 1);
        const float level = osc->amp * oneoverx[i];

        float sine = lutLerp(lut_sine, LUT_SINE_SIZE,LUT_SINE_SIZE * (phase)); // linear-interpolated sinewave

        sine *= level;
        sumSines += sine;
    }

    osc->output = sumSines * ONEOVERPI;

    osc->phase += TS * osc->freq;  // increment phase (phase normalized from 0 to 1)

    return osc->output;
}


