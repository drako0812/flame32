#include "flame32.asm"

#bankdef "bios"
{
    #addr 0x000000
    #size 0x100000
    #outp 0x000000
    #fill
}

#bankdef "stack"
{
    #addr 0x100000
    #size 0x100000
    #outp 0x100000
    #fill
}

#bankdef "gfx"
{
    #addr 0x200000
    #size 0x100000
    #outp 0x200000
    #fill
}

#bankdef "hw"
{
    #addr 0x300000
    #size 0x100000
    #outp 0x300000
    #fill
}

#bankdef "os"
{
    #addr 0x400000
    #size 0x200000
    #outp 0x400000
    #fill
}

#bankdef "user"
{
    #addr 0x600000
    #size 0x400000
}
