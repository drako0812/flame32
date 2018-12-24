# Flame32 Architecture

[Registers](#registers) | [Memory](#memory) | [Opcodes](#opcodes)

## Registers

 Register | Code | Description
----------|------| ----------------
A         | 0x00 | General Purpose
B         | 0x01 | General Purpose
C         | 0x02 | General Purpose
D         | 0x03 | General Purpose
E         | 0x04 | General Purpose
F         | 0x05 | General Purpose
G         | 0x06 | General Purpose
H         | 0x07 | General Purpose
X         | 0x08 | General Purpose
Y         | 0x09 | General Purpose
N         | 0x0A | Flag Register
O         | 0x0B | Comparison Register
P         | 0x0C | Program Counter
S         | 0x0D | Stack Pointer
T         | 0x0E | Stack Boundary
U         | 0x0F | Error Register

## Memory

- 8-bit words
- 0xA00000 addresses (10,445,760) => 10 MiB of address space

### Memory Layout

Region Min | Region Max | Description
-----------|------------|------------
0x000000   | 0x0FFFFF   | BIOS/ROM program
0x100000   | 0x1FFFFF   | Default Stack
0x200000   | 0x2FFFFF   | Reserved for Graphics Device
0x300000   | 0x3FFFFF   | Reserved for Graphics Device / Other Memory-Mapped Hardware
0x400000   | 0x9FFFFF   | "User" Memory
*0x400000* | *0x5FFFFF* | *Probable OS Memory*
*0x600000* | *0x9FFFFF* | *Probable Program Memory*

## Opcodes

Statements are either 4 or 8 bytes long.

### Statement Layout

~~~
01234567 01234567 01234567 01234567 01234567 01234567 01234567 01234567
|        |                          |-Long Argument 2 (Optional)
|        |-Short Argument 1
|-Opcode
~~~

### List of Opcodes

Mnemonic | Opcode | Format              | Description
---------|--------|---------------------|------------
NOP      | 0x00   | `00000000`          | No-Operation
LOD      | 0x01   | `01iiiiii`          | Load 24-bit value into A
LDL      | 0x02   | `02a00000-iiiiiiii` | Load 32-bit value into a
MOV      | 0x03   | `03ab0000`          | Move value in b to a
SWP      | 0x04   | `04ab0000`          | Swap values in b and a
LDM      | 0x05   | `05a00000-iiiiiiii` | Load value from memory at i into a
STO      | 0x06   | `06a00000-iiiiiiii` | Store value in a to memory at i
INC      | 0x07   | `07a00000`          | a++
DEC      | 0x08   | `08a00000`          | a--
ADD      | 0x09   | `09ab0000`          | a = a + b
SUB      | 0x0A   | `0Aab0000`          | a = a - b
MUL      | 0x0B   | `0Bab0000`          | a = a * b
DIV      | 0x0C   | `0Cab0000`          | a = a / b
MOD      | 0x0D   | `0Dab0000`          | a = a % b
MLS      | 0x0E   | `0Eab0000`          | a = a * b (signed)
DVS      | 0x0F   | `0Fab0000`          | a = a / b (signed)
MDS      | 0x10   | `10ab0000`          | a = a % b (signed)
SHL      | 0x11   | `11a00000`          | a = a << 1
SHR      | 0x12   | `12a00000`          | a = a >> 1
SLI      | 0x13   | `13ab0000`          | a = a << b
SRI      | 0x14   | `14ab0000`          | a = a >> b
RTL      | 0x15   | `15a00000`          | a = rotate_left(a)
RTR      | 0x16   | `16a00000`          | a = rotate_right(a)
RLI      | 0x17   | `17ab0000`          | a = rotate_left(a, b)
RRI      | 0x18   | `18ab0000`          | a = rotate_right(a, b)
BOR      | 0x19   | `19ab0000`          | a = a | b
AND      | 0x1A   | `1Aab0000`          | a = a & b
XOR      | 0x1B   | `1Bab0000`          | a = a ^ b
BST      | 0x1C   | `1Cab0000`          | a[b] = 1
BRS      | 0x1D   | `1Dab0000`          | a[b] = 0
BCP      | 0x1E   | `1Ea00000`          | a = ~a
CMP      | 0x1F   | `1Fab0000`          | O = compare(a, b)
CPZ      | 0x20   | `20a00000`          | O = compare(a)
CPI      | 0x21   | `21a00000-iiiiiiii` | O = compare(a, i)
JPR      | 0x22   | `22iiiiii`          | P = P + i (i is signed)
JMP      | 0x23   | `23000000-iiiiiiii` | P = i
JPC      | 0x24   | `24ffffff-iiiiiiii` | if(O = f) { P = i }
CLR      | 0x25   | `25iiiiii`          | (Push P onto stack) P = P + i (i is signed)
CAL      | 0x26   | `26000000-iiiiiiii` | (Push P onto stack) P = i
CLC      | 0x27   | `27ffffff-iiiiiiii` | if(O = f) { (Push P onto stack) P = i }
INP      | 0x28   | `28pppppp`          | A = input(p)
OUT      | 0x29   | `29pppppp`          | output(p, A)
INR      | 0x2A   | `2Aa00000`          | A = input(a)
OTR      | 0x2B   | `2Ba00000`          | output(a, A)
PSH      | 0x2C   | `2Ca00000`          | push(a)
POP      | 0x2D   | `2Da00000`          | a = pop()
PSI      | 0x2E   | `2E000000-iiiiiiii` | push(i)
HLT      | 0x2F   | `2F000000`          | Halt CPU
PPP      | 0x30   | `30000000`          | pop()
RET      | 0x31   | `31000000`          | P = pop()
LMR      | 0x32   | `32ab0000`          | a = mem[b]
STR      | 0x33   | `33ab0000`          | mem[a] = b
BLOD     | 0x34   | `34a000ii`          | a = iu8
BLDM     | 0x35   | `35a00000-iiiiiiii` | a = mem[i].u8
BSTO     | 0x36   | `36a00000-iiiiiiii` | mem[i].u8 = a.u8
BINP     | 0x37   | `37pppppp`          | A = input_u8(p)
BOUT     | 0x38   | `38pppppp`          | output_u8(p, A.u8)
BINR     | 0x39   | `39a00000`          | A = input_u8(a)
BOTR     | 0x3A   | `3Aa00000`          | output_u8(a, A.u8)
BPSH     | 0x3B   | `3Ba00000`          | push_u8(a.u8)
BPOP     | 0x3C   | `3Ca00000`          | a = pop_u8()
BPSI     | 0x3D   | `3D0000ii`          | push_u8(i)
BPPP     | 0x3E   | `3E000000`          | pop_u8()
BLMR     | 0x3F   | `3Fab0000`          | a.u8 = mem[b].u8
BSTR     | 0x40   | `40ab0000`          | mem[a].u8 = b.u8
KIC      | 0x41   | `41iiiiii`          | kernel interrupt cycles (default to 0 AKA disabled)
KIR      | 0x42   | `42a00000`          | same as above but cycles fetched from register
KRT      | 0x43   | `43000000`          | return from kernel interrupt cycle (starts counting timer again)
KEI      | 0x44   | '44000000`          | re-enable interrupts
KDI      | 0x45   | `45000000`          | disable interrupts
KSI      | 0x46   | `46000000-iiiiiiii` | set interrupt handler address to i
EHR      | 0x47   | `47000000-iiiiiiii` | set error handling routine (called when U becomes non-zero) (U = 0 on entering error handler) (A = U on entering error handler)
SSI      | 0x48   | `48000000-iiiiiiii` | set stack start index (also sets S to SSI)
ERT      | 0x49   | `49000000`          | returns from error handler unpauses interrupts if they are active

# Peripherals

## Graphics Device

### Memory Layout

Region Min | Region Max | Description
-----------|------------|------------
0x200000   | 0x2FFFFF   | Minimum GFX RAM
0x200000   | 0x3FFFFF   | Maximum GFX RAM
0x200000   | 0x200000   | GFX Mode
0x200001   | 0x200001   | GFX Buffer Lock
0x200002   | 0x200002   | GFX Font Lock (Fonts only update when this becomes 0, GFX resets this automatically)
0x200003   | 0x200302   | 256-color Palette
0x200403   | 0x200B02   | Font #1
0x200C03   | 0x201302   | Font #2
0x201403   | 0x201B02   | Font #3
0x201C03   | 0x202302   | Font #4
.......... | ........   | .......
**MODE 0** | ........   | .......
0x202403   | 0x202303   | Cursor X
0x202404   | 0x202304   | Cursor Y
0x202405   | 0x202305   | Cursor On
0x202406   | 0x202306   | Cursor Palette Index
0x202407   | 0x206E06   | Buffer
.......... | ........   | ......
**MODE 1** | ........   | ......


### GFX_MODE_0

Graphics Mode 0 AKA Cell Display Mode is the default display mode of the
graphics device.

- 80x60 cells
- each cell is 32 bits
  - 8-bit attribute flags
  - 8-bit foreground palette index
  - 8-bit background palette index
  - 8-bit character
- Cell Buffer is 80x60x4 Bytes = 19,200 B = 18.75 KiB
- ?x Fonts 8x8 1-bit pixels x 256 characters = 2048 B = 2 KiB
- Cursor X, Cursor Y, Cursor On, Cursor Color
