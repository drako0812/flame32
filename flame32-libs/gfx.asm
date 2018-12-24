#str "__FLAME32_GFX_BEGIN"

__GFX_RAM_START   = 0x200000
__GFX_MODE        = 0x200000
__GFX_BUFFER_LOCK = 0x200001
__GFX_FONT_LOCK   = 0x200002
__GFX_PALETTE     = 0x200003
__GFX_FONT1       = 0x200403
__GFX_FONT2       = 0x200C03
__GFX_FONT3       = 0x201403
__GFX_FONT4       = 0x201C03

__GFX_FONT_SIZE   = 2048 ; 2 KiB

__GFX_ATTR_FONT1 = 0b00000000
__GFX_ATTR_FONT2 = 0b00000001
__GFX_ATTR_FONT3 = 0b00000010
__GFX_ATTR_FONT4 = 0b00000011

; GFX Base API
; void __gfx_set_mode(byte mode);
; byte __gfx_get_mode();
; void __gfx_lock();
; void __gfx_unlock();
; bool __gfx_get_lock();
; void __gfx_font_unlock();
; void __gfx_set_palette(byte idx, byte r, byte g, byte b);
; byte __gfx_get_palette_r(byte idx);
; byte __gfx_get_palette_g(byte idx);
; byte __gfx_get_palette_b(byte idx);
; void __gfx_set_font_char(byte font, byte ch, byte data[8]);
; void __gfx_get_font_char(byte font, byte ch, byte & data[8]);

#str "__gfx_set_mode"
; void __gfx_set_mode(byte mode);
__gfx_set_mode:
    pop B ; pop return adress
    bpop A
    bsto A, __GFX_MODE
    psh B
    ret

#str "__gfx_get_mode"
; byte __gfx_get_mode();
__gfx_get_mode:
    pop B
    bldm A, __GFX_MODE
    bpsh A
    psh B
    ret

#str "__gfx_lock"
; void __gfx_lock();
__gfx_lock:
    blod A, 1
    bsto A, __GFX_BUFFER_LOCK
    ret

#str "__gfx_unlock"
; void __gfx_unlock();
__gfx_unlock:
    blod A, 0
    bsto A, __GFX_BUFFER_LOCK
    ret

#str "__gfx_get_lock"
; bool __gfx_get_lock();
__gfx_get_lock:
    pop B
    bldm A, __GFX_BUFFER_LOCK
    bpsi __GFX_BUFFER_LOCK
    psh B
    ret

#str "__gfx_font_unlock"
; void __gfx_font_unlock();
__gfx_font_unlock:
    blod A, 0
    bsto A, __GFX_FONT_LOCK
    ret

#str "__gfx_set_palette"
; void __gfx_set_palette(byte idx, byte r, byte g, byte b);
; TODO: Do error checking on the idx because it could be out of bounds
__gfx_set_palette:
    pop Y ; return
    bpop B ; b
    bpop C ; g
    bpop D ; r
    bpop E ; idx
    psh Y
    blod A, 4
    mul A, E ; offset = 4 * idx;
    blod Y, 0
    ldl X, __GFX_PALETTE
    add A, X ; offset = __GFX_PALETTE + offset;
    bstr A, Y ; mem[offset]   = 0;
    inc A
    bstr A, D ; mem[offset+1] = r;
    inc A
    bstr A, C ; mem[offset+2] = g;
    inc A
    bstr A, B ; mem[offset+3] = b;
    ret

#str "__gfx_get_palette_r"
; byte __gfx_get_palette_r(byte idx)
; TODO: Do error checking on the idx because it could be out of bounds
__gfx_get_palette_r:
    pop Y ; return
    bpop B ; idx
    blod A, 4
    mul A, B ; offset = 4 * idx;
    ldl X, __GFX_PALETTE
    add A, X ; offset = __GFX_PALETTE + offset
    inc A
    blmr A, A
    bpsh A
    psh Y
    ret

#str "__gfx_get_palette_g"
; byte __gfx_get_palette_g(byte idx)
; TODO: Do error checking on the idx because it could be out of bounds
__gfx_get_palette_g:
    pop Y ; return
    bpop B ; idx
    blod A, 4
    mul A, B ; offset = 4 * idx;
    ldl X, __GFX_PALETTE
    add A, X ; offset = __GFX_PALETTE + offset
    blod B, 2
    add A, B
    blmr A, A
    bpsh A
    psh Y
    ret

#str "__gfx_get_palette_b"
; byte __gfx_get_palette_b(byte idx)
; TODO: Do error checking on the idx because it could be out of bounds
__gfx_get_palette_b:
    pop Y ; return
    bpop B ; idx
    blod A, 4
    mul A, B ; offset = 4 * idx;
    ldl X, __GFX_PALETTE
    add A, X ; offset = __GFX_PALETTE + offset
    blod B, 3
    add A, B
    blmr A, A
    bpsh A
    psh Y
    ret

#str "__gfx_set_font_char"
; void __gfx_set_font_char(byte font, byte ch, byte data[8]);
; TODO: Do error checking on font because it might be out of bounds
; TODO: Do error checking on ch because it might be out of bounds
__gfx_set_font_char:
    ; int font_offset = __GFX_FONT1 + (font * __GFX_FONT_SIZE);
    ; int ch_offset = font_offset + ch;
    ; for(int idx = 0; idx < 8; idx++) {
    ;     ram[ch_offset + idx] = ram[data + idx];
    ; }

    ; UNPACK PARAMETERS
    pop A
    sto A, .return
    pop A
    sto A, .data
    bpop A
    sto A, .ch
    bpop A
    sto A, .font

    ; int font_offset = __GFX_FONT1 + (font * __GFX_FONT_SIZE);
    ldm B, .font
    lod __GFX_FONT_SIZE
    mul B, A
    lod __GFX_FONT1
    add A, B
    sto A, .font_offset

    ; int ch_offset = font_offset + ch;
    ldm A, .font_offset
    ldm B, .ch
    add A, B
    sto A, .ch_offset

    lod 0 ; idx = 0
    sto A, .idx

.loop_start:
    ldm A, .idx ; idx < 8
    cpi A, 8
    jpc GE, .loop_end

        ldm C, .ch_offset
        ldm D, .idx
        ldm E, .data

        add C, D ; ch_offset + idx
        add E, D ; data + idx
        blmr E, E ; ram[data + idx]
        bstr C, E ; ram[ch_offset + idx] = ram[data + idx];

        ldm A, .idx ; idx++
        inc A
        sto A, .idx

        jmp .loop_start

.loop_end:

    ; RETURN
    ldm A, .return
    psh A
    ret

    .font:
        #res 1
    .ch:
        #res 1
    .data:
        #res 4
    .font_offset:
        #res 4
    .ch_offset:
        #res 4
    .idx:
        #res 1
    .return:
        #res 4

#str "__gfx_get_font_char"
; void __gfx_get_font_char(byte font, byte ch, byte & data[8]);
; TODO: Do error checking on font because it might be out of bounds
; TODO: Do error checking on ch because it might be out of bounds
__gfx_get_font_char:
    ; int font_offset = __GFX_FONT1 + (font * __GFX_FONT_SIZE);
    ; int ch_offset = font_offset + ch;
    ; for(int idx = 0; idx < 8; idx++) {
    ;     ram[data + idx] = ram[ch_offset + idx];
    ; }

    ; UNPACK PARAMETERS
    pop A
    sto A, .return
    pop A
    sto A, .data
    bpop A
    sto A, .ch
    bpop A
    sto A, .font

    ; int font_offset = __GFX_FONT1 + (font * __GFX_FONT_SIZE);
    ldm B, .font
    lod __GFX_FONT_SIZE
    mul B, A
    lod __GFX_FONT1
    add A, B
    sto A, .font_offset

    ; int ch_offset = font_offset + ch;
    ldm A, .font_offset
    ldm B, .ch
    add A, B
    sto A, .ch_offset

    lod 0 ; idx = 0
    sto A, .idx

.loop_start:
    ldm A, .idx ; idx < 8
    cpi A, 8
    jpc GE, .loop_end

        ldm C, .ch_offset
        ldm D, .idx
        ldm E, .data

        add C, D ; ch_offset + idx
        add E, D ; data + idx
        blmr C, C ; ram[ch_offset + idx]
        bstr E, C ; ram[data + idx] = ram[ch_offset + idx];

        ldm A, .idx ; idx++
        inc A
        sto A, .idx

        jmp .loop_start

.loop_end:

    ; RETURN
    ldm A, .return
    psh A
    ret

    .font:
        #res 1
    .ch:
        #res 1
    .data:
        #res 4
    .font_offset:
        #res 4
    .ch_offset:
        #res 4
    .idx:
        #res 1
    .return:
        #res 4

#include "gfx/mode0.asm"
#include "gfx/mode1.asm"

#str "__FLAME32_GFX_END"

#bank "gfx"
#res 3
__gfx_palette:
    #d32 0x00000000
    #d32 0x00008000
    #d32 0x00800000
    #d32 0x00808000
    #d32 0x80000000
    #d32 0x80008000
    #d32 0x80800000
    #d32 0x40404000
    #d32 0xC0C0C000
    #d32 0x0000FF00
    #d32 0x00FF0000
    #d32 0x00FFFF00
    #d32 0xFF000000
    #d32 0xFF00FF00
    #d32 0xFFFF0000
    #d32 0xFFFFFF00
    
    #d32 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    #d32 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    #d32 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    #d32 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    #d32 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    #d32 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    #d32 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    #d32 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    #d32 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    #d32 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    #d32 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    #d32 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    #d32 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    #d32 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    #d32 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

; include generated font file
#include "gfx/gfx_fonts.asm"

__gfx_mode0_cursor_x_data:
    #d8 0
__gfx_mode0_cursor_y_data:
    #d8 0
__gfx_mode0_cursor_on_data:
    #d8 1
__gfx_mode0_cursor_color_data:
    #d8 15
__gfx_mode0_buffer_data:
    ; FLAME32 GFX MODE0 BUFFER
    #d8 0x00, 0x0C, 0x00, 0x46
    #d8 0x00, 0x0C, 0x00, 0x4C
    #d8 0x00, 0x0C, 0x00, 0x41
    #d8 0x00, 0x0C, 0x00, 0x4D
    #d8 0x00, 0x0C, 0x00, 0x45
    #d8 0x00, 0x0C, 0x00, 0x33
    #d8 0x00, 0x0C, 0x00, 0x32

    #d8 0x00, 0x0F, 0x00, 0x20

    #d8 0x01, 0x0E, 0x00, 0x47
    #d8 0x01, 0x0E, 0x00, 0x46
    #d8 0x01, 0x0E, 0x00, 0x58

    #d8 0x00, 0x0F, 0x00, 0x20

    #d8 0x02, 0x0A, 0x00, 0x4D
    #d8 0x02, 0x0A, 0x00, 0x4F
    #d8 0x02, 0x0A, 0x00, 0x44
    #d8 0x02, 0x0A, 0x00, 0x45
    #d8 0x02, 0x0A, 0x00, 0x30

    #d8 0x00, 0x0F, 0x00, 0x20

    #d8 0x03, 0x0B, 0x00, 0x42
    #d8 0x03, 0x0B, 0x00, 0x55
    #d8 0x03, 0x0B, 0x00, 0x46
    #d8 0x03, 0x0B, 0x00, 0x46
    #d8 0x03, 0x0B, 0x00, 0x45
    #d8 0x03, 0x0B, 0x00, 0x52

#bank "bios"
