#include "../../flame32.asm"

; Tests LDM
ldm A, TEST_VALUE

TEST_VALUE:
    #d32 0x12345678
