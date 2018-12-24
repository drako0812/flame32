#include "../../flame32.asm"

; Tests XOR
lod    0b10101010
ldl B, 0b10100101
xor A, B

; 0b00001111
