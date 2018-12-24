#include "stdafx.h"
#include "base.hpp"
#include "statement.hpp"
#include "opcodes.hpp"
#include "gfx.hpp"
#include "cpu.hpp"

const int codepoints[256] = {
    0x0000, 0x263A, 0x263B, 0x2665, 0x2666, 0x2663, 0x2660, 0x2022, 0x25D8, 0x25CB, 0x25D9, 0x2642, 0x2640, 0x266A, 0x266B, 0x263C,
    0x25BA, 0x25C4, 0x2195, 0x203C, 0x00B6, 0x00A7, 0x25AC, 0x21A8, 0x2191, 0x2193, 0x2192, 0x2190, 0x221F, 0x2194, 0x25B2, 0x25BC,
    ' ',    '!',    '"',    '#',    '$',    '%',    '&',    '\'',   '(',    ')',    '*',    '+',    ',',    '-',    '.',    '/',
    '0',    '1',    '2',    '3',    '4',    '5',    '6',    '7',    '8',    '9',    ':',    ';',    '<',    '=',    '>',    '?',
    '@',    'A',    'B',    'C',    'D',    'E',    'F',    'G',    'H',    'I',    'J',    'K',    'L',    'M',    'N',    'O',
    'P',    'Q',    'R',    'S',    'T',    'U',    'V',    'W',    'X',    'Y',    'Z',    '[',    '\\',   ']',    '^',    '_',
    '`',    'a',    'b',    'c',    'd',    'e',    'f',    'g',    'h',    'i',    'j',    'k',    'l',    'm',    'n',    'o',
    'p',    'q',    'r',    's',    't',    'u',    'v',    'w',    'x',    'y',    'z',    '{',    '|',    '}',    '~',    0x2302,
    0x00C7, 0x00FC, 0x00E9, 0x00E2, 0x00E4, 0x00E0, 0x00E5, 0x00E7, 0x00EA, 0x00EB, 0x00E8, 0x00EF, 0x00EE, 0x00EC, 0x00C4, 0x00C5,
    0x00C9, 0x00E6, 0x00C6, 0x00F4, 0x00F6, 0x00F2, 0x00FB, 0x00F9, 0x00FF, 0x00D6, 0x00DC, 0x00A2, 0x00A3, 0x00A5, 0x20A7, 0x0192,
    0x00E1, 0x00ED, 0x00F3, 0x00FA, 0x00F1, 0x00D1, 0x00AA, 0x00BA, 0x00BF, 0x2310, 0x00AC, 0x00BD, 0x00BC, 0x00A1, 0x00AB, 0x00BB,
    0x2591, 0x2592, 0x2593, 0x2502, 0x2524, 0x2561, 0x2562, 0x2556, 0x2555, 0x2563, 0x2551, 0x2557, 0x255D, 0x255C, 0x255B, 0x2510,
    0x2514, 0x2534, 0x252C, 0x251C, 0x2500, 0x253C, 0x255E, 0x255F, 0x255A, 0x2554, 0x2569, 0x2566, 0x2560, 0x2550, 0x256C, 0x2567,
    0x2568, 0x2564, 0x2565, 0x2559, 0x2558, 0x2552, 0x2553, 0x256B, 0x256A, 0x2518, 0x250C, 0x2588, 0x2584, 0x258C, 0x2590, 0x2580,
    0x03B1, 0x00DF, 0x0393, 0x03C0, 0x03A3, 0x03C3, 0x00B5, 0x03C4, 0x03A6, 0x0398, 0x03A9, 0x03B4, 0x221E, 0x03C6, 0x03B5, 0x2229,
    0x2261, 0x00B1, 0x2265, 0x2264, 0x2320, 0x2321, 0x00F7, 0x2248, 0x00B0, 0x2219, 0x00B7, 0x221A, 0x207F, 0x00B2, 0x25A0, 0x00A0,
};

const int ranges[] = {
    0x0000, 0x0000,
    0x263A, 0x263B,
    0x2665, 0x2666,
    0x2663, 0x2663,
    0x2660, 0x2660,
    0x2022, 0x2022,
    0x25D8, 0x25D8,
    0x25CB, 0x25CB,
    0x25D9, 0x25D9,
    0x2642, 0x2642,
    0x2640, 0x2640,
    0x266A, 0x266B,
    0x263C, 0x263C,
    0x25BA, 0x25BA,
    0x25C4, 0x25C4,
    0x2195, 0x2195,
    0x203C, 0x203C,
    0x00B6, 0x00B6,
    0x00A7, 0x00A7,
    0x25AC, 0x25AC,
    0x21A8, 0x21A8,
    0x2191, 0x2191,
    0x2193, 0x2193,
    0x2192, 0x2192,
    0x2190, 0x2190,
    0x221F, 0x221F,
    0x2194, 0x2194,
    0x25B2, 0x25B2,
    0x25BC, 0x25BC,
    ' ',    '~',
    0x2302, 0x2302,
    0x00C7, 0x00C7,
    0x00FC, 0x00FC,
    0x00E9, 0x00E9,
    0x00E2, 0x00E2,
    0x00E4, 0x00E4,
    0x00E0, 0x00E0,
    0x00E5, 0x00E5,
    0x00E7, 0x00E7,
    0x00EA, 0x00EB,
    0x00E8, 0x00E8,
    0x00EF, 0x00EF,
    0x00EE, 0x00EE,
    0x00EC, 0x00EC,
    0x00C4, 0x00C5,
    0x00C9, 0x00C9,
    0x00E6, 0x00E6,
    0x00C6, 0x00C6,
    0x00F4, 0x00F4,
    0x00F6, 0x00F6,
    0x00F2, 0x00F2,
    0x00FB, 0x00FB,
    0x00F9, 0x00F9,
    0x00FF, 0x00FF,
    0x00D6, 0x00D6,
    0x00DC, 0x00DC,
    0x00A2, 0x00A3,
    0x00A5, 0x00A5,
    0x20A7, 0x20A7,
    0x0192, 0x0192,
    0x00E1, 0x00E1,
    0x00ED, 0x00ED,
    0x00F3, 0x00F3,
    0x00FA, 0x00FA,
    0x00F1, 0x00F1,
    0x00D1, 0x00D1,
    0x00AA, 0x00AA,
    0x00BA, 0x00BA,
    0x00BF, 0x00BF,
    0x2310, 0x2310,
    0x00AC, 0x00AC,
    0x00BD, 0x00BD,
    0x00BC, 0x00BC,
    0x00A1, 0x00A1,
    0x00AB, 0x00AB,
    0x00BB, 0x00BB,
    0x2591, 0x2593,
    0x2502, 0x2502,
    0x2524, 0x2524,
    0x2561, 0x2562,
    0x2556, 0x2556,
    0x2555, 0x2555,
    0x2563, 0x2563,
    0x2551, 0x2551,
    0x2557, 0x2557,
    0x255D, 0x255D,
    0x255C, 0x255C,
    0x255B, 0x255B,
    0x2510, 0x2510,
    0x2514, 0x2514,
    0x2534, 0x2534,
    0x252C, 0x252C,
    0x251C, 0x251C,
    0x2500, 0x2500,
    0x253C, 0x253C,
    0x255E, 0x255F,
    0x255A, 0x255A,
    0x2554, 0x2554,
    0x2569, 0x2569,
    0x2566, 0x2566,
    0x2560, 0x2560,
    0x2550, 0x2550,
    0x256C, 0x256C,
    0x2567, 0x2568,
    0x2564, 0x2565,
    0x2559, 0x2559,
    0x2558, 0x2558,
    0x2552, 0x2553,
    0x256B, 0x256B,
    0x256A, 0x256A,
    0x2518, 0x2518,
    0x250C, 0x250C,
    0x2588, 0x2588,
    0x2584, 0x2584,
    0x258C, 0x258C,
    0x2590, 0x2590,
    0x2580, 0x2580,
    0x03B1, 0x03B1,
    0x00DF, 0x00DF,
    0x0393, 0x0393,
    0x03C0, 0x03C0,
    0x03A3, 0x03A3,
    0x03C3, 0x03C3,
    0x00B5, 0x00B5,
    0x03C4, 0x03C4,
    0x03A6, 0x03A6,
    0x0398, 0x0398,
    0x03A9, 0x03A9,
    0x03B4, 0x03B4,
    0x221E, 0x221E,
    0x03C6, 0x03C6,
    0x03B5, 0x03B5,
    0x2229, 0x2229,
    0x2261, 0x2261,
    0x00B1, 0x00B1,
    0x2265, 0x2265,
    0x2264, 0x2264,
    0x2320, 0x2321,
    0x00F7, 0x00F7,
    0x2248, 0x2248,
    0x00B0, 0x00B0,
    0x2219, 0x2219,
    0x00B7, 0x00B7,
    0x221A, 0x221A,
    0x207F, 0x207F,
    0x00B2, 0x00B2,
    0x25A0, 0x25A0,
    0x00A0, 0x00A0,
};

namespace flame32 {

    Gfx::Gfx() :
        display{nullptr}, eq{nullptr}, font{nullptr},
        gfx_font1{nullptr}, gfx_font2{nullptr}, gfx_font3{nullptr}, gfx_font4{nullptr},
        backbuffer{nullptr},
        tick_accum{16667}
    {

    }

    Gfx::~Gfx() {
        if(backbuffer) { al_destroy_bitmap(backbuffer); }
        if(gfx_font4) { al_destroy_font(gfx_font4); }
        if(gfx_font3) { al_destroy_font(gfx_font3); }
        if(gfx_font2) { al_destroy_font(gfx_font2); }
        if(gfx_font1) { al_destroy_font(gfx_font1); }
        if(font) { al_destroy_font(font); }
        if(eq) { al_destroy_event_queue(eq); }
        if(display) { al_destroy_display(display); }

        if(al_is_system_installed()) { al_uninstall_system(); }
    }

    bool Gfx::init(Cpu & c) {
        if(!al_init()) { std::cerr << rang::fgB::red << "ERROR: Unable to initialize Allegro!" << rang::style::reset << std::endl; return false; }
        if(!al_init_image_addon()) { std::cerr << rang::fgB::red << "ERROR: Unable to initialize Allegro image addon!" << rang::style::reset << std::endl; return false; }
        if(!al_init_font_addon()) { std::cerr << rang::fgB::red << "ERROR: Unable to initialize Allegro font addon!" << rang::style::reset << std::endl; return false; }
        if(!al_init_primitives_addon()) { std::cerr << rang::fgB::red << "ERROR: Unable to initialize Allegro primitives addon!" << rang::style::reset << std::endl; return false; }

        if(!al_install_keyboard()) { std::cerr << rang::fgB::red << "ERROR: Unable to initialize Allegro keyboard driver!" << rang::style::reset << std::endl; return false; }

        al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_OPENGL | ALLEGRO_OPENGL_3_0);
        al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
        if(display = al_create_display(640, 480); !display) { std::cerr << rang::fgB::red << "ERROR: Unable to create display!" << rang::style::reset << std::endl; return false; }
        if(font = al_create_builtin_font(); !font) { std::cerr << rang::fgB::red << "ERROR: Unable to create builtin font!" << rang::style::reset << std::endl; return false; }
        if(eq = al_create_event_queue(); !eq) { std::cerr << rang::fgB::red << "ERROR: Unable to create event queue!" << rang::style::reset << std::endl; return false; }
        al_register_event_source(eq, al_get_keyboard_event_source());
        al_register_event_source(eq, al_get_display_event_source(display));

        if(backbuffer = al_create_bitmap(640, 480); !backbuffer) { std::cerr << rang::fgB::red << "ERROR: Unable to create internal backbuffer!" << rang::style::reset << std::endl; return false; }

        load_state(c);

        rebuild_fonts(c);
        return true;
    }

    void Gfx::rebuild_fonts(Cpu & c) {
        if(gfx_font1) {
            al_destroy_font(gfx_font1);
        }
        if(gfx_font2) {
            al_destroy_font(gfx_font2);
        }
        if(gfx_font3) {
            al_destroy_font(gfx_font3);
        }
        if(gfx_font4) {
            al_destroy_font(gfx_font4);
        }

        auto tmp_bmp_flags = al_get_new_bitmap_flags();
        al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
        ALLEGRO_BITMAP * font_bmp = al_create_bitmap(128 + 16 + 1, 128 + 16 + 1);
        al_set_new_bitmap_flags(tmp_bmp_flags);
        al_set_target_bitmap(font_bmp);

        // Font 1
        // Load data to bitmap
        al_clear_to_color(al_map_rgb(0, 0, 0));
        for(long long ch = 0, addr = GFX_FONT1; ch < 256; ch++) {
            for(long long y = 0; y < 8; y++, addr++) {
                for(long long x = 0; x < 8; x++) {
                    // get bits8 * 8 * sizeof(int));
                    auto bit = c.get_mem8(addr).bit(7 - x);
                    al_put_pixel(((ch % 16) * 9) + x + 1, ((ch / 16) * 9) + y + 1, bit ? al_map_rgb(255, 255, 255) : al_map_rgba(0, 0, 0, 0));
                }
            }
        }
        //const int ranges[2] = {0, 255};
        al_save_bitmap("font1.png", font_bmp);
        gfx_font1 = al_grab_font_from_bitmap(font_bmp, std::size(ranges) / 2, ranges);
        if(gfx_font1 == nullptr) {
            std::cerr << rang::fgB::red << "ERROR: Font1 could not be loaded!" << rang::style::reset << std::endl;
        }

        // Font 2
        // Load data to bitmap
        al_clear_to_color(al_map_rgb(0, 0, 0));
        for(long long ch = 0, addr = GFX_FONT2; ch < 256; ch++) {
            for(long long y = 0; y < 8; y++, addr++) {
                for(long long x = 0; x < 8; x++) {
                    // get bits8 * 8 * sizeof(int));
                    auto bit = c.get_mem8(addr).bit(7 - x);
                    al_put_pixel(((ch % 16) * 9) + x + 1, ((ch / 16) * 9) + y + 1, bit ? al_map_rgb(255, 255, 255) : al_map_rgba(0, 0, 0, 0));
                }
            }
        }
        //const int ranges[2] = {0, 255};
        al_save_bitmap("font2.png", font_bmp);
        gfx_font2 = al_grab_font_from_bitmap(font_bmp, std::size(ranges) / 2, ranges);
        if(gfx_font2 == nullptr) {
            std::cerr << rang::fgB::red << "ERROR: Font2 could not be loaded!" << rang::style::reset << std::endl;
        }

        // Font 3
        // Load data to bitmap
        al_clear_to_color(al_map_rgb(0, 0, 0));
        for(long long ch = 0, addr = GFX_FONT3; ch < 256; ch++) {
            for(long long y = 0; y < 8; y++, addr++) {
                for(long long x = 0; x < 8; x++) {
                    // get bits8 * 8 * sizeof(int));
                    auto bit = c.get_mem8(addr).bit(7 - x);
                    al_put_pixel(((ch % 16) * 9) + x + 1, ((ch / 16) * 9) + y + 1, bit ? al_map_rgb(255, 255, 255) : al_map_rgba(0, 0, 0, 0));
                }
            }
        }
        //const int ranges[2] = {0, 255};
        al_save_bitmap("font3.png", font_bmp);
        gfx_font3 = al_grab_font_from_bitmap(font_bmp, std::size(ranges) / 2, ranges);
        if(gfx_font3 == nullptr) {
            std::cerr << rang::fgB::red << "ERROR: Font3 could not be loaded!" << rang::style::reset << std::endl;
        }

        // Font 4
        // Load data to bitmap
        al_clear_to_color(al_map_rgb(0, 0, 0));
        for(long long ch = 0, addr = GFX_FONT4; ch < 256; ch++) {
            for(long long y = 0; y < 8; y++, addr++) {
                for(long long x = 0; x < 8; x++) {
                    // get bits8 * 8 * sizeof(int));
                    auto bit = c.get_mem8(addr).bit(7 - x);
                    al_put_pixel(((ch % 16) * 9) + x + 1, ((ch / 16) * 9) + y + 1, bit ? al_map_rgb(255, 255, 255) : al_map_rgba(0, 0, 0, 0));
                }
            }
        }
        //const int ranges[2] = {0, 255};
        al_save_bitmap("font4.png", font_bmp);
        gfx_font4 = al_grab_font_from_bitmap(font_bmp, std::size(ranges) / 2, ranges);
        if(gfx_font4 == nullptr) {
            std::cerr << rang::fgB::red << "ERROR: Font4 could not be loaded!" << rang::style::reset << std::endl;
        }

        al_set_target_backbuffer(display);
        
        c.set_mem8(GFX_FONT_LOCK, (u8)1);
    }

    void Gfx::load_state(Cpu & c) {
        // Read palette
        for(long long i = 0, addr = GFX_PALETTE; i < 256; i++, addr += 4) {
            u8 r, g, b;
            r = c.get_mem8(addr);
            g = c.get_mem8(addr + 1);
            b = c.get_mem8(addr + 2);
            palette.at(i) = al_map_rgb(r, g, b);
        }
    }

    void Gfx::process(Cpu & c) {
        // Check events
        ALLEGRO_KEYBOARD_STATE key_state;
        al_get_keyboard_state(&key_state);
        ALLEGRO_EVENT evt;
        while(al_get_next_event(eq, &evt)) {
            switch(evt.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                c.is_halted = true;
                break;
            default:
                break;
            }
        }

        // Accumulate ticks
        tick_accum += c.ticks;

        if(tick_accum < 16667) {
            return;
        }

        // Check if buffer is locked
        if(c.get_mem8(GFX_BUFFER_LOCK).U) {
            al_set_target_backbuffer(display);
            al_draw_bitmap(backbuffer, 0, 0, 0);

            if(al_key_down(&key_state, ALLEGRO_KEY_TAB)) {
                draw_debug(c);
            }

            al_flip_display();
            return;
        }

        load_state(c);

        // Check if fonts are unlocked
        if(!c.get_mem8(GFX_FONT_LOCK).U) {
            rebuild_fonts(c);
        }

        // Do different things based on mode
        switch(c.get_mem8(GFX_MODE).U) {
        case 0:
        default:
            // TODO: This is temporary
            render_mode0(c);
        }

        al_set_target_backbuffer(display);
        al_draw_bitmap(backbuffer, 0, 0, 0);

        if(al_key_down(&key_state, ALLEGRO_KEY_TAB)) {
            draw_debug(c);
        }

        al_flip_display();
    }

    void Gfx::render_mode0(Cpu & c) {
        al_set_target_bitmap(backbuffer);
        
        // Draw cell backgrounds
        for(long long y = 0, addr = GFX_MODE0_BUFFER; y < 60; y++) {
            for(int x = 0; x < 80; x++, addr += 4) {
                al_draw_filled_rectangle(
                    x * 8, y * 8,
                    (x * 8) + 8, (y * 8) + 8,
                    palette.at(c.get_mem8(addr + 2).U)
                );
            }
        }

        // Draw cell contents
        for(long long y = 0, addr = GFX_MODE0_BUFFER; y < 60; y++) {
            for(int x = 0; x < 80; x++, addr += 4) {
                // Get font
                ALLEGRO_FONT * f = gfx_font1;
                switch(c.get_mem8(addr).U & 0b11) {
                case 0b00:
                    f = gfx_font1;
                    break;
                case 0b01:
                    f = gfx_font2;
                    break;
                case 0b10:
                    f = gfx_font3;
                    break;
                case 0b11:
                    f = gfx_font4;
                    break;
                }
                al_draw_glyph(
                    f,
                    palette.at(c.get_mem8(addr + 1).U),
                    x * 8, y * 8,
                    codepoints[c.get_mem8(addr + 3).U]
                );
            }
        }

        // Draw cursor (maybe)
        if(c.get_mem8(GFX_MODE0_CURSOR_ON).U) {
            al_draw_text(
                gfx_font1,
                palette.at(c.get_mem8(GFX_MODE0_CURSOR_COLOR).U),
                c.get_mem8(GFX_MODE0_CURSOR_X).U,
                c.get_mem8(GFX_MODE0_CURSOR_Y).U,
                ALLEGRO_ALIGN_INTEGER,
                "_"
            );
        }
    }

    void Gfx::draw_debug(Cpu & c) {
        al_clear_to_color(al_map_rgba(64, 64, 64, 128));

        al_draw_multiline_textf(
            font,
            al_map_rgb(255, 255, 255),
            0, 0, 640, 8, ALLEGRO_ALIGN_INTEGER,
            "DEBUG\n"
            "A: %08x B: %08x C: %08x D: %08x\nE: %08x F: %08x G: %08x H: %08x\n"
            "X: %08x Y: %08x N: %08x O: %08x\nP: %08x S: %08x T: %08x U: %08x\n"
            "T: %8u SSI: %08x HLT: %1u\nKIT: %8u KIE: %1u KIA: %8u KIADR: %08x\n"
            "IEH: %1u EHA: %08x\n"
            "NEXT OP: %02x",
            c.A, c.B, c.C, c.D, c.E, c.F, c.G, c.H,
            c.X, c.Y, c.N, c.O, c.P, c.S, c.T, c.U,
            c.ticks, c.stack_start, c.is_halted, c.interrupt_ticks, c.interrupt_enabled, c.interrupt_accum, c.interrupt_address,
            c.in_error_handler, c.error_handler_address,
            c.fetch_statement().H.H.H.U
        );
        al_draw_text(font, al_map_rgb(255, 255, 255), 0, 8 * 9, 0, "STACK:");
        for(long long a = c.S, i = 0; (a < c.stack_start) && (i < 32); a++, i++) {
            al_draw_textf(font, al_map_rgb(255, 255, 255), 0, (10 + i) * 8, 0, "%02x", c.get_mem8(a).U);
        }
    }

}
