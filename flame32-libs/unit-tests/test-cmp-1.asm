#include "../../flame32.asm"

; Tests CMP
lod 1
ldl B, 2
cmp A, B

; O = NE | LT
