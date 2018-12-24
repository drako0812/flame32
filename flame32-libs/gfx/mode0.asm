#str "__FLAME32_GFX_MODE0_BEGIN"

__GFX_MODE0_CURSOR_X     = 0x202403
__GFX_MODE0_CURSOR_Y     = 0x202404
__GFX_MODE0_CURSOR_ON    = 0x202405
__GFX_MODE0_CURSOR_COLOR = 0x202406
__GFX_MODE0_BUFFER       = 0x202407

__GFX_MODE0_BUFFER_SIZE  = 19200
__GFX_MODE0_CELL_ATTR    = 0
__GFX_MODE0_CELL_FG      = 1
__GFX_MODE0_CELL_BG      = 2
__GFX_MODE0_CELL_CH      = 3
__GFX_MODE0_WIDTH        = 80
__GFX_MODE0_HEIGHT       = 60
__GFX_MODE0_INDICES      = 80*60

; GFX Mode 0 API
; void __gfx_mode0_set_cursor_x(byte x)
; void __gfx_mode0_set_cursor_y(byte y)
; void __gfx_mode0_set_cursor_position(byte x, byte y)
; byte __gfx_mode0_get_cursor_x()
; byte __gfx_mode0_get_cursor_y()
; void __gfx_mode0_cursor_on()
; void __gfx_mode0_cursor_off()
; bool __gfx_mode0_is_cursor_on()
; void __gfx_mode0_set_cursor_color(byte color)
; byte __gfx_mode0_get_cursor_color()
; void __gfx_mode0_set_cell_attr(byte x, byte y, byte attr)
; void __gfx_mode0_set_cell_fg(byte x, byte y, byte color)
; void __gfx_mode0_set_cell_bg(byte x, byte y, byte color)
; void __gfx_mode0_set_cell_char(byte x, byte y, byte ch)
; void __gfx_mode0_set_cell(byte x, byte y, byte attr, byte fg, byte bg, byte ch)
; byte __gfx_mode0_get_cell_attr(byte x, byte y)
; byte __gfx_mode0_get_cell_fg(byte x, byte y)
; byte __gfx_mode0_get_cell_bg(byte x, byte y)
; byte __gfx_mode0_get_cell_char(byte x, byte y)
; void __gfx_mode0_get_cell(byte x, byte y, byte & cell[4])
; void __gfx_mode0_clear(byte attr, byte fg, byte bg, byte ch)

#str "__gfx_mode0_set_cursor_x"
; void __gfx_mode0_set_cursor_x(byte x)
__gfx_mode0_set_cursor_x:
    pop A
    bpop B
    psh A
    bsto B, __GFX_MODE0_CURSOR_X
    ret

#str "__gfx_mode0_set_cursor_y"
; void __gfx_mode0_set_cursor_y(byte y)
__gfx_mode0_set_cursor_y:
    pop A
    bpop B
    psh A
    bsto B, __GFX_MODE0_CURSOR_Y
    ret

#str "__gfx_mode0_set_cursor_position"
; void __gfx_mode0_set_cursor_position(byte x, byte y)
__gfx_mode0_set_cursor_position:
    pop A ; return
    bpop B ; y
    bpop C ; x
    psh A
    bsto C, __GFX_MODE0_CURSOR_X
    bsto B, __GFX_MODE0_CURSOR_Y
    ret

#str "__gfx_mode0_get_cursor_x"
; int __gfx_mode0_get_cursor_x()
__gfx_mode0_get_cursor_x:
    pop A ; return
    bldm B, __GFX_MODE0_CURSOR_X ; B = cursor_x
    bpsh B
    psh A
    ret

#str "__gfx_mode0_get_cursor_y"
; int __gfx_mode0_get_cursor_y()
__gfx_mode0_get_cursor_y:
    pop A ; return
    bldm B, __GFX_MODE0_CURSOR_Y ; B = cursor_y
    bpsh B
    psh A
    ret

#str "__gfx_mode0_cursor_on"
; void __gfx_mode0_cursor_on()
__gfx_mode0_cursor_on:
    blod A, 1
    bsto A, __GFX_MODE0_CURSOR_ON
    ret

#str "__gfx_mode0_cursor_off"
; void __gfx_mode0_cursor_off()
__gfx_mode0_cursor_off:
    blod A, 0
    bsto A, __GFX_MODE0_CURSOR_ON
    ret

#str "__gfx_mode0_is_cursor_on"
; bool __gfx_mode0_is_cursor_on()
__gfx_mode0_is_cursor_on:
    pop A ; return
    bldm B, __GFX_MODE0_CURSOR_ON ; B = cursor_on
    bpsh B
    psh A
    ret

#str "__gfx_mode0_set_cursor_color"
; void __gfx_mode0_set_currsor_color(byte color)
__gfx_mode0_set_cursor_color:
    pop A ; return
    bpop B ; color
    bsto B, __GFX_MODE0_CURSOR_COLOR
    psh A
    ret

#str "__gfx_mode0_get_cursor_color"
; byte __gfx_mode0_get_cursor_color()
__gfx_mode0_get_cursor_color:
    pop A ; return
    bldm B, __GFX_MODE0_CURSOR_COLOR
    bpsh B
    psh A
    ret

#str "__gfx_mode0_set_cell_attr"
; void __gfx_mode0_set_cell_attr(byte x, byte y, byte attr)
__gfx_mode0_set_cell_attr:
    ; ram[__GFX_MODE0_BUFFER + ((x + (y * __GFX_MODE0_WIDTH)) * 4) + __GFX_MODE0_CELL_ATTR] = attr;
    pop X ; return
    bpop B ; attr
    bpop C ; y
    bpop D ; x
    psh X

    ; y * __GFX_MODE0_WIDTH
    ldl A, __GFX_MODE0_WIDTH
    mul A, C

    ; x + (ABOVE)
    add A, D

    ; (ABOVE) * 4
    ldl X, 4
    mul A, X

    ; (ABOVE) + __GFX_MODE0_BUFFER
    ldl X, __GFX_MODE0_BUFFER
    add A, X

    ; ram[(ABOVE)] = attr (AKA B)
    bstr A, B

    ret

#str "__gfx_mode0_set_cell_fg"
; void __gfx_mode0_set_cell_fg(byte x, byte y, byte color)
__gfx_mode0_set_cell_fg:
    ; ram[__GFX_MODE0_BUFFER + ((x + (y * __GFX_MODE0_WIDTH)) * 4) + __GFX_MODE0_CELL_FG] = color;
    pop X ; return
    bpop B ; color
    bpop C ; y
    bpop D ; x
    psh X

    ; y * __GFX_MODE0_WIDTH
    ldl A, __GFX_MODE0_WIDTH
    mul A, C

    ; x + (ABOVE)
    add A, D

    ; (ABOVE) * 4
    ldl X, 4
    mul A, X

    ; (ABOVE) + __GFX_MODE0_BUFFER
    ldl X, __GFX_MODE0_BUFFER
    add A, X
    inc A

    ; ram[(ABOVE)] = color (AKA B)
    bstr A, B

    ret

#str "__gfx_mode0_set_cell_bg"
; void __gfx_mode0_set_cell_bg(byte x, byte y, byte color)
__gfx_mode0_set_cell_bg:
    ; ram[__GFX_MODE0_BUFFER + ((x + (y * __GFX_MODE0_WIDTH)) * 4) + __GFX_MODE0_CELL_BG] = color;
    pop X ; return
    bpop B ; color
    bpop C ; y
    bpop D ; x
    psh X

    ; y * __GFX_MODE0_WIDTH
    ldl A, __GFX_MODE0_WIDTH
    mul A, C

    ; x + (ABOVE)
    add A, D

    ; (ABOVE) * 4
    ldl X, 4
    mul A, X

    ; (ABOVE) + __GFX_MODE0_BUFFER
    ldl X, __GFX_MODE0_BUFFER
    add A, X
    ldl Y, 2
    add A, Y

    ; ram[(ABOVE)] = color (AKA B)
    bstr A, B

    ret

#str "__gfx_mode0_set_cell_char"
; void __gfx_mode0_set_cell_char(byte x, byte y, byte ch)
__gfx_mode0_set_cell_char:
    ; ram[__GFX_MODE0_BUFFER + ((x + (y * __GFX_MODE0_WIDTH)) * 4) + __GFX_MODE0_CELL_CH] = ch;
    pop X ; return
    bpop B ; ch
    bpop C ; y
    bpop D ; x
    psh X

    ; y * __GFX_MODE0_WIDTH
    ldl A, __GFX_MODE0_WIDTH
    mul A, C

    ; x + (ABOVE)
    add A, D

    ; (ABOVE) * 4
    ldl X, 4
    mul A, X

    ; (ABOVE) + __GFX_MODE0_BUFFER
    ldl X, __GFX_MODE0_BUFFER
    add A, X
    ldl Y, 3
    add A, Y

    ; ram[(ABOVE)] = ch (AKA B)
    bstr A, B

    ret

#str "__gfx_mode0_set_cell"
; void __gfx_mode0_set_cell(byte x, byte y, byte attr, byte fg, byte bg, byte ch);
__gfx_mode0_set_cell:
    pop Y ; return
    bpop B ; ch
    bpop C ; bg
    bpop D ; fg
    bpop E ; attr
    bpop F ; y
    bpop G ; x
    psh Y

    ; y * __GFX_MODE0_WIDTH
    ldl A, __GFX_MODE0_WIDTH
    mul A, F

    ; x + (ABOVE)
    add A, G

    ; (ABOVE) * 4
    ldl X, 4
    mul A, X

    ; (ABOVE) + __GFX_MODE0_BUFFER
    ldl X, __GFX_MODE0_BUFFER
    add A, X

    ; ram[(ABOVE)] = attr (AKA E)
    bstr A, E

    ; ram[(ABOVE+1)] = fg (AKA D)
    inc A
    bstr A, D

    ; ram[(ABOVE+1)] = bg (AKA C)
    inc A
    bstr A, C

    ; ram[(ABOVE+1)] = ch (AKA B)
    inc A
    bstr A, B

    ret

#str "__gfx_mode0_get_cell_attr"
; byte __gfx_mode0_get_cell_attr(byte x, byte y)
__gfx_mode0_get_cell_attr:
    pop Y ; return
    bpop B ; y
    bpop C ; x
    
    ; y * __GFX_MODE0_WIDTH
    ldl A, __GFX_MODE0_WIDTH
    mul A, F

    ; x + (ABOVE)
    add A, G

    ; (ABOVE) * 4
    ldl X, 4
    mul A, X

    ; (ABOVE) + __GFX_MODE0_BUFFER
    ldl X, __GFX_MODE0_BUFFER
    add A, X

    blmr X, A

    bpsh X ; result
    psh Y

    ret

#str "__gfx_mode0_get_cell_fg"
; byte __gfx_mode0_get_cell_fg(byte x, byte y)
__gfx_mode0_get_cell_fg:
    pop Y ; return
    bpop B ; y
    bpop C ; x
    
    ; y * __GFX_MODE0_WIDTH
    ldl A, __GFX_MODE0_WIDTH
    mul A, F

    ; x + (ABOVE)
    add A, G

    ; (ABOVE) * 4
    ldl X, 4
    mul A, X

    ; (ABOVE) + __GFX_MODE0_BUFFER
    ldl X, __GFX_MODE0_BUFFER
    add A, X
    inc A

    blmr X, A

    bpsh X ; result
    psh Y

    ret

#str "__gfx_mode0_get_cell_bg"
; byte __gfx_mode0_get_cell_bg(byte x, byte y)
__gfx_mode0_get_cell_bg:
    pop Y ; return
    bpop B ; y
    bpop C ; x
    
    ; y * __GFX_MODE0_WIDTH
    ldl A, __GFX_MODE0_WIDTH
    mul A, F

    ; x + (ABOVE)
    add A, G

    ; (ABOVE) * 4
    ldl X, 4
    mul A, X

    ; (ABOVE) + __GFX_MODE0_BUFFER
    ldl X, __GFX_MODE0_BUFFER
    add A, X
    ldl X, 2
    add A, X

    blmr X, A

    bpsh X ; result
    psh Y

    ret

#str "__gfx_mode0_get_cell_char"
; byte __gfx_mode0_get_cell_char(byte x, byte y)
__gfx_mode0_get_cell_char:
    pop Y ; return
    bpop B ; y
    bpop C ; x
    
    ; y * __GFX_MODE0_WIDTH
    ldl A, __GFX_MODE0_WIDTH
    mul A, F

    ; x + (ABOVE)
    add A, G

    ; (ABOVE) * 4
    ldl X, 4
    mul A, X

    ; (ABOVE) + __GFX_MODE0_BUFFER
    ldl X, __GFX_MODE0_BUFFER
    add A, X
    ldl X, 3
    add A, X

    blmr X, A

    bpsh X ; result
    psh Y

    ret

#str "__gfx_mode0_get_cell"
; void __gfx_mode0_get_cell(byte x, byte y, byte & cell[4])
__gfx_mode0_get_cell:
    pop Y ; return
    pop B ; cell
    bpop C ; y
    bpop D ; x
    psh Y

    ; ram[__GFX_MODE0_BUFFER + ((x + (y * __GFX_MODE0_WIDTH)) * 4) + __GFX_MODE0_CELL_CH] = ch;
    ; memcpy(cell, __GFX_MODE0_BUFFER + ((x + (y * __GFX_MODE0_WIDTH)) * 4) * __GFX_MODE0_CELL_CH, 4);

    ; y * __GFX_MODE0_WIDTH
    ldl A, __GFX_MODE0_WIDTH
    mul A, F

    ; x + (ABOVE)
    add A, G

    ; (ABOVE) * 4
    ldl X, 4
    mul A, X

    ; (ABOVE) + __GFX_MODE0_BUFFER
    ldl X, __GFX_MODE0_BUFFER
    add A, X

    ; memcpy(cell, (ABOVE), 4);
    psh B
    psh A
    psi 4
    cal __bios_memcpy

    ret

#str "__gfx_mode0_clear"
; void __gfx_mode0_clear(byte attr, byte fg, byte bg, byte ch)
__gfx_mode0_clear:
    ; for(byte y = 0; y < __GFX_MODE0_HEIGHT; y++) {
    ;     for(byte x = 0; x < __GFX_MODE0_WIDTH; x++) {
    ;         __gfx_mode0_set_cell(x, y, attr, fg, bg, ch);
    ;     }
    ; }

    pop Y ; return
    bpop B ; ch
    bpop C ; bg
    bpop D ; fg
    bpop E ; attr
    psh Y

    blod Y, 0 ; byte y = 0;

.y_loop_start:
    cpi Y, __GFX_MODE0_HEIGHT ; y < __GFX_MODE0_HEIGHT
    jpc GE, .y_loop_end

    blod X, 0 ; byte x = 0;

    .x_loop_start:
        cpi X, __GFX_MODE0_WIDTH ; x < __GFX_MODE0_WIDTH
        jpc GE, .x_loop_end

            bpsh X
            bpsh Y
            bpsh B
            bpsh C
            bpsh D
            bpsh E

            bpsh E
            bpsh D
            bpsh C
            bpsh B
            bpsh Y
            bpsh X
            cal __gfx_mode0_set_cell

            bpop E
            bpop D
            bpop C
            bpop B
            bpop Y
            bpop X

            inc X
            jmp .x_loop_start

    .x_loop_end:

    inc Y
    jmp .y_loop_start

.y_loop_end:

#str "__FLAME32_GFX_MODE0_END"
