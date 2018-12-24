#cpudef
{
    #bits 8

    #tokendef reg
    {
        A = 0
        B = 1
        C = 2
        D = 3
        E = 4
        F = 5
        G = 6
        H = 7
        X = 8
        Y = 9
        N = 10
        O = 11
        P = 12
        S = 13
        T = 14
        U = 15
    }

    #tokendef flag
    {
        Z  = 0b00000001
        NZ = 0b00000010
        EQ = 0b00000100
        NE = 0b00001000
        LT = 0b00010000
        GT = 0b00100000
        CA = 0b01000000
        NAN =0b10000000
        LE = 0b00010100
        GE = 0b00100100
    }

    #tokendef errcode
    {
        ERROR_STACK_OVERFLOW  = 0b00000001
        ERROR_STACK_UNDERFLOW = 0b00000010
    }

    ; Basic Instructions
    nop -> 0x00000000
    lod {i} -> 8'0x01 @ i[23:0]
    ldl {a: reg}, {i} -> 8'0x02 @ a[3:0] @ 20'0x00000 @ i[31:0]
    mov {a: reg}, {b: reg} -> 8'0x03 @ a[3:0] @ b[3:0] @ 16'0x0000
    swp {a: reg}, {b: reg} -> 8'0x04 @ a[3:0] @ b[3:0] @ 16'0x0000
    ldm {a: reg}, {i} -> 8'0x05 @ a[3:0] @ 20'0x00000 @ i[31:0]
    sto {a: reg}, {i} -> 8'0x06 @ a[3:0] @ 20'0x00000 @ i[31:0]
    inc {a: reg} -> 8'0x07 @ a[3:0] @ 20'0x00000
    dec {a: reg} -> 8'0x08 @ a[3:0] @ 20'0x00000
    add {a: reg}, {b: reg} -> 8'0x09 @ a[3:0] @ b[3:0] @ 16'0x0000
    sub {a: reg}, {b: reg} -> 8'0x0A @ a[3:0] @ b[3:0] @ 16'0x0000
    mul {a: reg}, {b: reg} -> 8'0x0B @ a[3:0] @ b[3:0] @ 16'0x0000
    div {a: reg}, {b: reg} -> 8'0x0C @ a[3:0] @ b[3:0] @ 16'0x0000
    mod {a: reg}, {b: reg} -> 8'0x0D @ a[3:0] @ b[3:0] @ 16'0x0000
    mls {a: reg}, {b: reg} -> 8'0x0E @ a[3:0] @ b[3:0] @ 16'0x0000
    dvs {a: reg}, {b: reg} -> 8'0x0F @ a[3:0] @ b[3:0] @ 16'0x0000
    mds {a: reg}, {b: reg} -> 8'0x10 @ a[3:0] @ b[3:0] @ 16'0x0000
    shl {a: reg} -> 8'0x11 @ a[3:0] @ 20'0x00000
    shr {a: reg} -> 8'0x12 @ a[3:0] @ 20'0x00000
    sli {a: reg}, {b: reg} -> 8'0x13 @ a[3:0] @ b[3:0] @ 16'0x0000
    sri {a: reg}, {b: reg} -> 8'0x14 @ a[3:0] @ b[3:0] @ 16'0x0000
    rtl {a: reg} -> 8'0x15 @ a[3:0] @ 20'0x00000
    rtr {a: reg} -> 8'0x16 @ a[3:0] @ 20'0x00000
    rli {a: reg}, {b: reg} -> 8'0x17 @ a[3:0] @ b[3:0] @ 16'0x0000
    rri {a: reg}, {b: reg} -> 8'0x18 @ a[3:0] @ b[3:0] @ 16'0x0000
    bor {a: reg}, {b: reg} -> 8'0x19 @ a[3:0] @ b[3:0] @ 16'0x0000
    and {a: reg}, {b: reg} -> 8'0x1A @ a[3:0] @ b[3:0] @ 16'0x0000
    xor {a: reg}, {b: reg} -> 8'0x1B @ a[3:0] @ b[3:0] @ 16'0x0000
    bst {a: reg}, {b: reg} -> 8'0x1C @ a[3:0] @ b[3:0] @ 16'0x0000
    brs {a: reg}, {b: reg} -> 8'0x1D @ a[3:0] @ b[3:0] @ 16'0x0000
    bcp {a: reg} -> 8'0x1E @ a[3:0] @ 20'0x00000
    cmp {a: reg}, {b: reg} -> 8'0x1F @ a[3:0] @ b[3:0] @ 16'0x0000
    cpz {a: reg} -> 8'0x20 @ a[3:0] @ 20'0x00000
    cpi {a: reg}, {i} -> 8'0x21 @ a[3:0] @ 20'0x00000 @ i[31:0]
    jpr {i} -> 8'0x22 @ i[23:0]
    jmp {i} -> 32'0x23000000 @ i[31:0]
    jpc {f: flag}, {i} -> 8'0x24 @ f[23:0] @ i[31:0]
    clr {i} -> 8'0x25 @ i[23:0]
    cal {i} -> 32'0x26000000 @ i[31:0]
    clc {f: flag}, {i} -> 8'0x27 @ f[23:0] @ i[31:0]
    inp {p} -> 8'0x28 @ p[23:0]
    out {p} -> 8'0x29 @ p[23:0]
    inr {a: reg} -> 8'0x2A @ a[3:0] @ 20'0x00000
    otr {a: reg} -> 8'0x2B @ a[3:0] @ 20'0x00000
    psh {a: reg} -> 8'0x2C @ a[3:0] @ 20'0x00000
    pop {a: reg} -> 8'0x2D @ a[3:0] @ 20'0x00000
    psi {i} -> 32'0x2E000000 @ i[31:0]
    hlt -> 32'0x2F000000
    ppp -> 32'0x30000000
    ret -> 32'0x31000000
    lmr {a: reg}, {b: reg} -> 8'0x32 @ a[3:0] @ b[3:0] @ 16'0x0000
    str {a: reg}, {b: reg} -> 8'0x33 @ a[3:0] @ b[3:0] @ 16'0x0000

    ; Byte Instructions
    blod {a: reg}, {i} -> 8'0x34 @ a[3:0] @ 12'0x000 @ i[7:0]
    bldm {a: reg}, {i} -> 8'0x35 @ a[3:0] @ 20'0x00000 @ i[31:0]
    bsto {a: reg}, {i} -> 8'0x36 @ a[3:0] @ 20'0x00000 @ i[31:0]
    binp {p} -> 8'0x37 @ p[23:0]
    bout {p} -> 8'0x38 @ p[23:0]
    binr {a: reg} -> 8'0x39 @ a[3:0] @ 20'0x00000
    botr {a: reg} -> 8'0x3A @ a[3:0] @ 20'0x00000
    bpsh {a: reg} -> 8'0x3B @ a[3:0] @ 20'0x00000
    bpop {a: reg} -> 8'0x3C @ a[3:0] @ 20'0x00000
    bpsi {i} -> 8'0x3D @ 16'0x0000 @ i[7:0]
    bppp -> 32'0x3E000000
    blmr {a: reg}, {b: reg} -> 8'0x3F @ a[3:0] @ b[3:0] @ 16'0x0000
    bstr {a: reg}, {b: reg} -> 8'0x40 @ a[3:0] @ b[3:0] @ 16'0x0000

    ; Kernel Support Instructions
    kic {i} -> 8'0x41 @ i[23:0]
    kir {a: reg} -> 8'0x42 @ a[3:0] @ 20'0x00000
    krt -> 32'0x43000000
    kei -> 32'0x44000000
    kdi -> 32'0x45000000
    ksi {i} -> 32'0x46000000 @ i[31:0]

    ; Miscellaneous Instructions
    ehr {i} -> 32'0x47000000 @ i[31:0]
    ssi {i} -> 32'0x48000000 @ i[31:0]
    ert -> 32'0x49000000
}

; #bankdef "bios"
; {
;     #addr 0x000000
;     #size 0x040000
;     #outp 0x000000
;     #fill
; }
; 
; #bankdef "stack"
; {
;     #addr 0x040000
;     #size 0x040000
; }
; 
; #bankdef "gfx"
; {
;     #addr 0x080000
;     #size 0x040000
; }
; 
; #bankdef "hw"
; {
;     #addr 0x0C0000
;     #size 0x040000
; }
; 
; #bankdef "os"
; {
;     #addr 0x100000
;     #size 0x080000
;     #outp 0x000000
;     #fill
; }
; 
; #bankdef "user"
; {
;     #addr 0x180000
;     #size 0x100000
;     #outp 0x000000
;     #fill
; }
