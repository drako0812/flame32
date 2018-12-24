#include "flame32.asm"

#bankdef "bios"
{
    #addr 0x000000
    #size 0x040000
}

#bankdef "os"
{
    #addr 0x100000
    #size 0x080000
    #outp 0x000000
    #fill
}
