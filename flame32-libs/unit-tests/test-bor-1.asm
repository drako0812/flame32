#include "../../flame32.asm"

; Tests BOR
lod 1
ldl B, 0x80000000
bor A, B

; 0x80000001
