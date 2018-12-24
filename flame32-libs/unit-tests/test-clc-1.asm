#include "../../flame32.asm"

; Tests CLC
TEST_DEST = 0x050000
cpi A, 1
clc NE, TEST_DEST

; P = 0x050000
; STACK = 0x000010
