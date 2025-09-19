/**
 * @file oscillator.h
 * @author Johannes R.
 * @brief 
 * @version 
 * @date 10.09.25
 * @note
 */

#ifndef MINIMAL_SAI_OSCILLATOR_H
#define MINIMAL_SAI_OSCILLATOR_H

#include <stdint.h>
#include <stdbool.h>


#define harmonics   300


enum osc_type
{
    sine = 0,
    saw,
    rect,
    supersaw,
    fm_2op
};

typedef struct
{
    float amp;
    float freq;
    float phase;
    float FMindex;
    float FMratio;
    float pw;
    float output;
} oscillator_t;

typedef struct
{
    float freq;
    float level[harmonics];
    float real[harmonics];
    float imag[harmonics];
    float realinc[harmonics];
    float imaginc[harmonics];
    float output;
} cordic_t;


void  osc_init(oscillator_t * osc, float amp, float freq, float FMindex, float FMratio, float pw);
float whiteNoise(oscillator_t *osc);
void cordicAdditiveInit(cordic_t *osc, float freq);
float cordicAdditiveProcess(cordic_t * osc);
float cordicAdditive(oscillator_t *osc);
float sineAdditive(oscillator_t *osc);



#endif //MINIMAL_SAI_OSCILLATOR_H