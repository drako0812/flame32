#include "flame32-bios-banks.asm"
#bank "bios"

ssi 0x1FFFFF
jmp __bios_boot

#str "__FLAME32_BIOS_BEGIN"

#str "__bios_print_raw"
; void __bios_print_raw(byte * str)
;
; Same as __bios_print except control characters besides '\0' are not interpreted
__bios_print_raw:
    pop Y
    pop A
    psh Y

.loop_start:
    blmr B, A
    cpz B
    jpc Z, .loop_end

        blmr B, A
        psh A
        bpsh B
        cal __bios_print_c_raw
        pop A
        inc A
        jmp .loop_start

.loop_end:
    ret

#str "__bios_print"
; void __bios_print(byte * str)
;
; Prints a null-terminated string to the mode0 screen
__bios_print:
    pop Y
    pop A
    psh Y

.loop_start:
    blmr B, A
    cpz B
    jpc Z, .loop_end

        blmr B, A
        psh A
        bpsh B
        cal __bios_print_c
        pop A
        inc A
        jmp .loop_start

.loop_end:
    ret

#str "__bios_print_c_raw"
; void __bios_print_c_raw(byte ch)
; 
; Same as __bios_print_c except there are no special effects do to control characters, and, instead,
; the raw character is outputted to the console (FYI good for using 'graphical characters' and still
; moving the cursor).
__bios_print_c_raw:
    ; __bios_put_c(ch);
    ; cursor_x++;
    ; if(cursor_x >= __GFX_MODE0_WIDTH) {
    ;     cursor_x = 0;
    ;     cursor_y++;
    ;     if(cursor_y >= __GFX_MODE0_HEIGHT) {
    ;         cursor_y = __GFX_MODE0_HEIGHT - 1;
    ;         __bios_scroll();
    ;     }
    ; }
    pop Y
    bpop C
    psh Y

    bpsh C
    cal __bios_put_c ; __bios_put_c(ch)
    ; byte x = __gfx_mode0_get_cursor_x();
    ; x++;
    cal __gfx_mode0_get_cursor_x
    bpop X
    inc X
    cpi X, __GFX_MODE0_WIDTH ; if(x >= __GFX_MODE0_WIDTH)
    bpsh X
    cal __gfx_mode0_set_cursor_x
    jpc GE, .if_newline
    ret

.if_newline:
    bpsi 0
    cal __gfx_mode0_set_cursor_x
    cal __gfx_mode0_get_cursor_y
    bpop Y
    inc Y

    cpi Y, __GFX_MODE0_HEIGHT ; if(y >= __GFX_MODE0_HEIGHT)
    bpsh Y
    cal __gfx_mode0_set_cursor_y
    jpc GE, .if_bottom
    ret

.if_bottom:
    blod Y, __GFX_MODE0_HEIGHT - 1
    bpsh Y
    cal __gfx_mode0_set_cursor_y
    cal __bios_scroll
    ret

#str "__bios_print_c"
; void __bios_print_c(byte ch)
; 
; Prints a character to the mode0 screen, and advances the cursor
__bios_print_c:
    ; switch(ch) {
    ; case 0x08:
    ;     if(cursor_x != 0) {
    ;         cursor_x--;
    ;     }
    ;     break;
    ; case 0x09:
    ;     cursor_x = (cursor_x + 4) & ~(4 - 1);
    ;     if(cursor_x >= __GFX_MODE0_WIDTH) {
    ;         cursor_x = 0;
    ;         cursor_y++;
    ;         if(cursor_y >= __GFX_MODE0_HEIGHT) {
    ;             cursor_y = __GFX_MODE0_HEIGHT - 1;
    ;             __bios_scroll();
    ;         }
    ;     }
    ;     break;
    ; case 0x0D:
    ;     cursor_x = 0;
    ;     break;
    ; case 0x0A:
    ;     cursor_x = 0;
    ;     cursor_y++;
    ;     if(cursor_y >= __GFX_MODE0_HEIGHT) {
    ;         cursor_y = __GFX_MODE0_HEIGHT - 1;
    ;         __bios_scroll();
    ;     }
    ;     break;
    ; case 0x07:
    ; case 0x0B:
    ; case 0x0C:
    ;     break;
    ; default:
    ;     __bios_put_c(ch);
    ;     cursor_x++;
    ;     if(cursor_x >= __GFX_MODE0_WIDTH) {
    ;         cursor_x = 0;
    ;         cursor_y++;
    ;         if(cursor_y >= __GFX_MODE0_HEIGHT) {
    ;             cursor_y = __GFX_MODE0_HEIGHT - 1;
    ;             __bios_scroll();
    ;         }
    ;     }
    ;     break;
    ; }
    pop Y
    bpop C
    psh Y
    cpi C, 0x08
    jpc EQ, .if_08
    cpi C, 0x09
    jpc EQ, .if_09
    cpi C, 0x0D
    jpc EQ, .if_0D
    cpi C, 0x0A
    jpc EQ, .if_newline
    cpi C, 0x07
    jpc EQ, .if_unprintable
    cpi C, 0x0B
    jpc EQ, .if_unprintable
    cpi C, 0x0C
    jpc EQ, .if_unprintable
    
    ; DEFAULT branch
    bpsh C
    cal __bios_put_c ; __bios_put_c(ch)
    ; byte x = __gfx_mode0_get_cursor_x();
    ; x++;
    cal __gfx_mode0_get_cursor_x
    bpop X
    inc X
    cpi X, __GFX_MODE0_WIDTH ; if(x >= __GFX_MODE0_WIDTH)
    bpsh X
    cal __gfx_mode0_set_cursor_x
    jpc GE, .if_newline
    ret

.if_08:
    ; Get X
    cal __gfx_mode0_get_cursor_x
    bpop X
    cpz X
    jpc Z, .if_not_leftmost
    ret

.if_09:
    ; Get X
    cal __gfx_mode0_get_cursor_x
    bpop X
    lod 4
    add X, A
    lod !(4 - 1)
    and X, A

    cpi X, __GFX_MODE0_WIDTH ; if(x >= __GFX_MODE0_WIDTH)
    bpsh X
    cal __gfx_mode0_set_cursor_x
    jpc GE, .if_newline
    ret

.if_0D:
    bpsi 0
    cal __gfx_mode0_set_cursor_x
    ret

.if_unprintable:
    ret

.if_newline:
    bpsi 0
    cal __gfx_mode0_set_cursor_x
    cal __gfx_mode0_get_cursor_y
    bpop Y
    inc Y

    cpi Y, __GFX_MODE0_HEIGHT ; if(y >= __GFX_MODE0_HEIGHT)
    bpsh Y
    cal __gfx_mode0_set_cursor_y
    jpc GE, .if_bottom
    ret

.if_not_leftmost:
    dec X
    bpsh X
    cal __gfx_mode0_set_cursor_x
    ret

.if_bottom:
    blod Y, __GFX_MODE0_HEIGHT - 1
    bpsh Y
    cal __gfx_mode0_set_cursor_y
    cal __bios_scroll
    ret
    
#str "__bios_put_c"
; void __bios_put_c(byte ch)
;
; Put a character on the mode0 screen, at the cursors location
__bios_put_c:
    pop X
    bpop C
    psh X
    bsto C, .tmp_ch

    ; X = __gfx_mode0_get_cursor_x()
    ; Y = __gfx_mode0_get_cursor_y()
    cal __gfx_mode0_get_cursor_x ; stack = X
    cal __gfx_mode0_get_cursor_y ; stack = X, Y
    bldm A, __bios_default_attr
    bpsh A
    bldm A, __bios_default_fg
    bpsh A
    bldm A, __bios_default_bg
    bpsh A
    bldm A, .tmp_ch
    bpsh A

    cal __gfx_mode0_set_cell ; __gfx_mode0_set_cell(x, y, attr, fg, bg, ch)
    ret

.tmp_ch:
    #res 1

#str "__bios_scroll"
; void __bios_scroll()
;
; Scrolls the contents of the mode0 screen up by one line
__bios_scroll:
    ; for(byte y = 0; y < __GFX_MODE0_HEIGHT - 1; y++) {
    ;     __bios_memcpy(__GFX_MODE0_BUFFER + (y * 4 * __GFX_MODE0_WIDTH), __GFX_MODE0_BUFFER + ((y + 1) * 4 * __GFX_MODE0_WIDTH), __GFX_MODE0_WIDTH * 4);
    ; }
    ; for(byte x = 0; x < __GFX_MODE0_WIDTH; x++) {
    ;     __gfx_mode0_set_cell(x, __GFX_MODE0_HEIGHT - 1, __bios_default_attr, __bios_default_fg, __bios_default_bg, ' ');
    ; }

    blod Y, 0

.loop1_start:
    cpi Y, __GFX_MODE0_HEIGHT - 1
    jpc GE, .loop1_end

        bpsh Y ; Save Y because of potential clobbering

        ; Calculate dest address
        lod 4 * __GFX_MODE0_WIDTH
        mul A, Y
        ldl B, __GFX_MODE0_BUFFER
        add A, B
        psh A

        ; Calculate source address
        mov X, Y
        inc X
        lod 4 * __GFX_MODE0_WIDTH
        mul A, X
        ldl B, __GFX_MODE0_BUFFER
        add A, B
        psh A

        ; Get size to copy
        psi __GFX_MODE0_WIDTH * 4

        cal __bios_memcpy

        bpop Y
        inc Y
        jmp .loop1_start

.loop1_end:

    blod X, 0

.loop2_start:
    cpi X, __GFX_MODE0_WIDTH
    jpc GE, .loop2_end

        bpsh X
        bpsh X ; x
        bpsi __GFX_MODE0_HEIGHT - 1 ; y
        bldm A, __bios_default_attr
        bpsh A ; attr
        bldm A, __bios_default_fg
        bpsh A ; fg
        bldm A, __bios_default_bg
        bpsh A ; bg
        bpsi 0x20 ; ch
        bpop X
        inc X
        jmp .loop2_start

.loop2_end:
    
    ret

#str "__bios_clear"
; void __bios_clear()
;
; Clears the mode0 screen and resets the cursor to the top left
__bios_clear:
    bldm A, __bios_default_attr
    bpsh A
    bldm A, __bios_default_fg
    bpsh A
    bldm A, __bios_default_bg
    bpsh A
    blod A, 0x20
    bpsh A
    cal __gfx_mode0_clear

    bpsi 0
    cal __gfx_mode0_set_cursor_x
    bpsi 0
    cal __gfx_mode0_set_cursor_y

    ret

__bios_default_attr:
    #d8 0x00
__bios_default_fg:
    #d8 0x0F
__bios_default_bg:
    #d8 0x00

#str "__bios_set_fg"
; void __bios_set_fg(byte fg)
;
; Sets the mode0 screen's default foreground color
__bios_set_fg:
    pop X
    bpop A
    psh X
    bsto A, __bios_default_fg
    ret

#str "__bios_set_bg"
; void __bios_set_bg(byte bg)
;
; Sets the mode0 screen's default background color
__bios_set_bg:
    pop X
    bpop A
    psh X
    bsto A, __bios_default_bg
    ret

#str "__bios_set_attr"
; void __bios_set_attr(byte attr)
;
; Sets the mode0 screen's default attributes
__bios_set_attr:
    pop X
    bpop A
    psh X
    bsto A, __bios_default_attr
    ret

#str "__bios_reset_console"
; void __bios_reset_console()
;
; Resets the mode0 screen's default attributes, foreground color, and background color to their default values
__bios_reset_console:
    blod A, 0x00
    bsto A, __bios_default_attr
    blod A, 0x0F
    bsto A, __bios_default_fg
    blod A, 0x00
    bsto A, __bios_default_bg
    ret

#str "__bios_memset"
; void __bios_memset(byte * dest, byte set, int count)
__bios_memset:
    ; for(int i = 0; i < count; i++) {
    ;     *(dest + i) = set;
    ; }

    pop Y ; return
    pop B ; count
    bpop C ; set
    pop D ; dest
    psh Y

    ldl X, 0 ; int idx = 0;

    ;while(idx < count) {
.loop_start:
    cmp X, B
    jpc GE, .loop_end

        ; *(dest + idx) = set
        bstr D, C

        inc X
        inc D
        jmp .loop_start

.loop_end:
    ret

#str "__bios_memcpy"
; void __bios_memcpy(byte * dest, byte * src, int count)
__bios_memcpy:
    ; for(int idx = 0; idx < count; idx++) {
    ;     *(dest + idx) = *(src + idx);
    ; }

    pop Y ; return
    pop B ; count
    pop C ; src
    pop D ; dest
    psh Y

    ldl X, 0 ; int i = 0;

    ; while(idx < count) {
.loop_start:
    cmp X, B
    jpc GE, .loop_end

        ; *(dest + idx) = *(src + idx);
        blmr H, C
        bstr D, H

        inc X
        inc C
        inc D

        jmp .loop_start

.loop_end:
    ret

#include "flame32-libs/gfx.asm"

__bios_boot:
    psi __BIOS_HELLO_WORLD
    cal __bios_print
    psi __BIOS_RAW_MESSAGE_1
    cal __bios_print_raw
    bpsi 0x0A
    cal __bios_print_c
    psi __BIOS_RAW_MESSAGE_2
    cal __bios_print_raw
    bpsi 0x0A
    cal __bios_print_c
    psi __BIOS_RAW_MESSAGE_3
    cal __bios_print_raw
    bpsi 0x0A
    cal __bios_print_c
.loop:
    jmp .loop

__BIOS_HELLO_WORLD:
    #str "Hello World!\n\0"

__BIOS_RAW_MESSAGE_1:
    #d8 0x01, 0xCB, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xBB, 0x00
__BIOS_RAW_MESSAGE_2:
    #str " "
    #d8 0xBA
    #str " Hello World! "
    #d8 0xBA, 0x00
__BIOS_RAW_MESSAGE_3:
    #str " "
    #d8 0xCB, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD, 0xBC, 0x00

#str "__FLAME32_BIOS_END"
