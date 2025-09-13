/**
 * @file spectra.h
 * @author Johannes R.
 * @brief 
 * @version 
 * @date 13.09.25
 * @note
 */

#ifndef MINIMAL_SAI_SPECTRA_H
#define MINIMAL_SAI_SPECTRA_H

float Bell1Partials[16]= {0.5, 1.0, 1.183, 1.506, 2.0, 2.514, 2.662, 3.011, 4.166, 5.433, 6.796, 8.215, 0.5, 1.0, 1.183, 1.506}; // Bell 1 (Default)
float Bell2Partials[16]= {0.5, 1.0, 1.183, 1.506, 2.0, 2.514, 2.662, 3.011, 4.166, 5.433, 6.796, 8.215, 0.5, 1.0, 1.183, 1.506}; // Bell 2
float GongPartials[16]= {1.0, 1.59, 2.14, 2.3, 2.65, 2.92, 3.16, 3.5, 3.6, 3.65, 4.06, 4.15, 1.0, 1.59, 2.14, 2.3}; // Gong or Cymbal
float ChordPartials[16] = {1.0, 2.05, 2.98, 4.0, 5.03, 1.505, 3.01, 4.49, 6.05, 7.5, 1.2189, 2.378, 3.567, 4.756, 5.945}; // Minor Chord
float SawPartials[16] = {1, 1.01, 0.99, 2, 2.02, 1.98, 3, 3.03, 4, 3.97, 5 ,6 ,7, 8 ,9 , 10}; // Sawtooth (sort of...)
float CB808Partials[16] = {0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 0.71976, 2.159285, 3.59881, 5.03835, 6.47785, 7.9174, 9.3569, 10.7964}; // 808 Cowbell


#endif //MINIMAL_SAI_SPECTRA_H