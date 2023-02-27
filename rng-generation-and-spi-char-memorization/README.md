# rng-generation-and-spi
This project showcases using the SPI spec with the mbed LPC1768 microcontroller to create a character-memorization game. This project also demonstrates a few utility classes I wrote, although some of these have a dependency on the mbed library. See other projects for examples without such a dependency.

## Usage
Displays five characters with repetition from {A, B, C} to the PC terminal. Players then repeat the sequence using the configured pushbuttons.

## Libraries
### DEMRandom
Provides cyclic-group-based RNG generation.
### DEMUtils
A variety of classes to facilitate mbed functionality (setting up pins, etc.). Differs from some later projects in that it relies on the MBED library.
### mbed
A library of microprocessor functionality provided by mbed. My early projects with the LPC1768, such as this project, relied on using the mbed library as a backend to, i.e., configure the appropriate hardware registers.