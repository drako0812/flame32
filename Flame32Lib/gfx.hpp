#pragma once

namespace flame32 {

    class Cpu;

    class Gfx {
    public:
        static constexpr u32 GFX_MODE = 0x200000;
        static constexpr u32 GFX_BUFFER_LOCK = 0x200001;
        static constexpr u32 GFX_FONT_LOCK = 0x200002;
        static constexpr u32 GFX_PALETTE = 0x200003;
        static constexpr u32 GFX_FONT1 = 0x200403;
        static constexpr u32 GFX_FONT2 = 0x200C03;
        static constexpr u32 GFX_FONT3 = 0x201403;
        static constexpr u32 GFX_FONT4 = 0x201C03;

        static constexpr u32 GFX_MODE0_CURSOR_X = 0x202403;
        static constexpr u32 GFX_MODE0_CURSOR_Y = 0x202404;
        static constexpr u32 GFX_MODE0_CURSOR_ON = 0x202405;
        static constexpr u32 GFX_MODE0_CURSOR_COLOR = 0x202406;
        static constexpr u32 GFX_MODE0_BUFFER = 0x202407;

        static constexpr int GFX_MODE0_BUFFER_WIDTH = 80;
        static constexpr int GFX_MODE0_BUFFER_HEIGHT = 60;
        static constexpr u8 GFX_MODE0_ATTR_FONT1 = 0b0000'0000;
        static constexpr u8 GFX_MODE0_ATTR_FONT2 = 0b0000'0001;
        static constexpr u8 GFX_MODE0_ATTR_FONT3 = 0b0000'0010;
        static constexpr u8 GFX_MODE0_ATTR_FONT4 = 0b0000'0011;

        ALLEGRO_DISPLAY * display;
        ALLEGRO_EVENT_QUEUE * eq;
        ALLEGRO_FONT * font;

        u32 tick_accum;

        std::array<ALLEGRO_COLOR, 256> palette;
        ALLEGRO_FONT * gfx_font1;
        ALLEGRO_FONT * gfx_font2;
        ALLEGRO_FONT * gfx_font3;
        ALLEGRO_FONT * gfx_font4;
        ALLEGRO_BITMAP * backbuffer;

        Gfx();
        ~Gfx();

        bool init(Cpu & c);
        void process(Cpu & c);
        void rebuild_fonts(Cpu & c);
        void load_state(Cpu & c);
        void render_mode0(Cpu & c);

        void draw_debug(Cpu & c);
    };

}
