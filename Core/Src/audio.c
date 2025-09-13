/**
 * @file audio.c
 * @author Johannes R.
 * @brief 
 * @version 
 * @date 08.09.25
 * @note
 */



#include<stdint.h>
#include "audio.h"
#include "oscillators.h"



/**
 * @brief Audio Buffer - x samples X 2 channels = 2 * x samples
 * @note Channels are interleaved - LRLRLRLRLRLRLRLRLRLRLR - audioBuffer[frame << 1] audioBuffer[(frame << 1) + 1]
 */
int16_t codecBuffer[BUFFER_SIZE]; // x samples X 2 channels (interleaved)


float saw1, saw2;
uint16_t saw1_freq = 55;
uint16_t saw2_freq = 55;
oscillator_t osc1, osc2;


/**
 * @brief Init audio
 *
 */
void AUDIO_Init()
{
    // initialize board audio device
    BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_HEADPHONE, 30, BSP_AUDIO_FREQUENCY_44K);
    BSP_AUDIO_OUT_SetAudioFrameSlot(CODEC_AUDIOFRAME_SLOT_02); // slots 0 and 2 activated for headphones out
    
    BSP_AUDIO_OUT_Play((uint16_t *)codecBuffer, BUFFER_SIZE * 2);

    // initialize audio objects
 //   osc_init(&osc1, 1.0f, 1000, 0, 0, 0);
    osc_init(&osc1, 1.0f, 110, 0, 0, 0);
    osc_init(&osc2, 1.0f, 110, 0, 0, 0);
}

void audioBlock(int16_t *output, int32_t samples)
{
    // int16_t* out = output;
    // 0.0000226757 is 1.0/44100.0
    // const float increment1 = (float)saw1_freq * 2.0f * 0.0000226757f;
    // const float increment2 = (float)saw2_freq * 2.0f * 0.0000226757f;
    for (int i = 0; i < samples; i++)
    {
        // saw1 += increment1;
        // if (saw1 > 1.0f)
        //     saw1 = saw1 - 2.0f;
        // saw2 += increment2;
        // if (saw2 > 1.0f)
        //     saw2 = saw2 - 2.0f;

        float sampleL = sineAdditive(&osc1);  // LEFT
        float sampleR = cordicAdditive(&osc2);  // RIGHT

        output[i << 1] = ((int16_t) ((32767.0f) * sampleL));
        output[(i << 1) + 1]  = ((int16_t) ((32767.0f) * sampleR));
    }
}



void BSP_AUDIO_OUT_HalfTransfer_CallBack(void)
{
    audioBlock((int16_t *)(codecBuffer), BUFFER_SIZE_DIV_4);
}

void BSP_AUDIO_OUT_TransferComplete_CallBack(void)
{
    audioBlock((int16_t *)(codecBuffer + BUFFER_SIZE_DIV_2), BUFFER_SIZE_DIV_4);
}

void BSP_AUDIO_OUT_Error_CallBack(void)
{
    /* Stop the program with an infinite loop */
    while (1)
    {
    }
}

void AUDIO_OUT_SAIx_DMAx_IRQHandler(void)
{
    HAL_DMA_IRQHandler(haudio_out_sai.hdmatx);
}

void AUDIO_IN_SAIx_DMAx_IRQHandler(void)
{
    HAL_DMA_IRQHandler(haudio_in_sai.hdmarx);
}