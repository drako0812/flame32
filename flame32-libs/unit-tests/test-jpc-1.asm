#include "../../flame32.asm"

; Tests JPC
TEST_DEST = 0x050000
cpi A, 1
jpc NE, TEST_DEST

; P = 0x050000
