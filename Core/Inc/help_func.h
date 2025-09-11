/**
 * @file help_func.h
 * @author Johannes R.
 * @brief 
 * @version 
 * @date 11.09.25
 * @note
 */

#ifndef MINIMAL_SAI_HELP_FUNC_H
#define MINIMAL_SAI_HELP_FUNC_H


#include <math.h>
#include <stdint.h>

#ifndef NOMINMAX

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#endif  /* NOMINMAX */

/**
 * @brief Keep value between 0 and max
 *
 * @param value
 * @param max
 * @return float
 */
static inline float wrap(float value, float max)
{
    if (value < 0.f)
        value += max;
    if (value >= max)
        value -= max;

    return value;
}

static inline float Crossfade(float a, float b, float fade)
{
    return a + (b - a) * fade;
}


/**
 * @brief Pade-approximation of tanh for soft clipping
 * @ from https://www.musicdsp.org/en/latest/Other/238-rational-tanh-approximation.html
 * @param x
 * @return float
 */
static inline float SoftClip(float x)
{
    if (x < -3.0f)
    {
        return -1.0f;
    }
    else if (x > 3.0f)
    {
        return 1.0f;
    }
    else
    {
        return x * (27.0f + x * x) / (27.0f + 9.0f * x * x);
    }
}

/**
 * @brief Constrain input value between lower and upper limits
 *
 * @param input
 * @param lower
 * @param upper
 * @return float
 */
float clip(float input, float lower, float upper);



#endif //MINIMAL_SAI_HELP_FUNC_H