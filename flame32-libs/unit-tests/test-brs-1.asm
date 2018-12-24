#include "../../flame32.asm"

; Tests BRS
lod 0xFFFFFFFF
ldl B, 0
brs A, B

; 0xFFFFFFFE
