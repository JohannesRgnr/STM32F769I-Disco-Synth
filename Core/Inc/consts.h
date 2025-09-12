/**
 * @file consts.h
 * @author Johannes R.
 * @brief 
 * @version 
 * @date 11.09.25
 * @note
 */

#ifndef MINIMAL_SAI_CONSTS_H
#define MINIMAL_SAI_CONSTS_H


#define FS                  44100.f     // selected samplerate
/*  Actual samplerate is actually 41666 Hz (derived from I2S clock)..
*   we take that into account for accurate tuning
*                 0.2% off...   not so crucial, but well ....... */

#define correctedFS         41666.f   // real samplerate (check STM32CubeMX configuration)



#define A0                  (FS/correctedFS)  // correcting factor for tuning
#define TS		            (1.f/FS)        // sampling period
#define NYQUIST		        (FS/2.f)         // Nyquist frequency



#define PI                  3.14159265359f
#define TWOPI               6.28318530718f
#define ONEOVERPI           (1.f/PI)

//#define MIDI_MAX            127.f
//#define MIDI_MAXi           127


#endif //MINIMAL_SAI_CONSTS_H