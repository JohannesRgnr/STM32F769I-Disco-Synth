A simple project to experiment with the SAI device on STM32F7, and some audio processing routines.

Implemented:
- Fast white noise generator
- Additive synthesis using Cordic algorithm (so far, 400 voices with -O3 optimization + LUTs)
- Additive synthesis using sum of sines (LUTs)