#pragma once

typedef unsigned char Byte;

// New pattern format:
// Each byte corresponds to 8 pixel values, so in total we will have 8 bytes per frame.
// The bits in each byte are arranged MSB -> LSB so the last bit corresponds to the last pixel in that byte.
// {{Byte, ... 8 times}, up to nth frame}
Byte pat_template[][8] = {{0b01001001, 0b00100101, 0b10010010, 0b01001001, 0b10010010, 0b01001001, 0b10100100, 0b10010010}};
