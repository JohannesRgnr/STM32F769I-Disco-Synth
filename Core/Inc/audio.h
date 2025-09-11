/**
 * @file audio.h
 * @author Johannes R.
 * @brief 
 * @version 
 * @date 08.09.25
 * @note
 */

#ifndef MINIMAL_SAI_AUDIO_H
#define MINIMAL_SAI_AUDIO_H



#include <stdint.h>
#include "stm32f769i_discovery_audio.h"


extern SAI_HandleTypeDef haudio_out_sai;
extern SAI_HandleTypeDef haudio_in_sai;


#define BUFFER_SIZE         64             // size of the audio buffer (samples)
#define BUFFER_SIZE_DIV_2   (BUFFER_SIZE/2)
#define BUFFER_SIZE_DIV_4   (BUFFER_SIZE/4)

#define INITIAL_VOLUME      90              // initial volume level.. TODO: give user control of the volume


//
// extern DFSDM_Filter_HandleTypeDef       haudio_in_dfsdm_leftfilter;
// extern DFSDM_Filter_HandleTypeDef       haudio_in_dfsdm_rightfilter;


/**
 * @brief Init audio and start audio
 *
 */
void AUDIO_Init();


/**
 * @brief
 *
 * @param output
 * @param samples
 */
void audioBlock(int16_t *output, int32_t samples);





#endif //MINIMAL_SAI_AUDIO_H