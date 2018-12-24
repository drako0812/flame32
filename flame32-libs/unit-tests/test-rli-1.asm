#include "../../flame32.asm"

; Tests RLI
lod 0x12345678
rli A, 8

; 0x23456781
