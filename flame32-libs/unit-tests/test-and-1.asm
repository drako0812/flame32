#include "../../flame32.asm"

; Tests AND
lod 0x12345678
ldl B, 0x0x0000FFFF
and A, B

; 0x00005678
