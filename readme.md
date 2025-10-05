A simple project to experiment with the SAI device on STM32F7, and some audio processing routines.

Implemented:
- Fast white noise generator
- Additive synthesis using vector rotation (Cordic algorithm?) (2 versions, up to ~400 voices with -O3 optimization + LUTs)
- Additive synthesis using sum of sines (LUTs)