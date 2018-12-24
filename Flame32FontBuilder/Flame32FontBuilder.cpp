#include "pch.h"

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

int main(int argc, char * argv[]) {
    if(argc != 5) {
        using namespace std;
        cerr << "Flame32FontBuilder Usage:\n"
            << "Flame32FontBuilder <font_1.ttf> <font_2.ttf> <font_3.ttf> <font_4.ttf>\n\n"
            << "NOTE: the fonts can be any format that Allegro 5's TTF addon supports, but they must be 8x8 monospace fonts\n";
        return -1;
    }

    if(!al_init()) { std::cerr << "ERROR: Unable to initialize Allegro!\n"; return -2; }
    if(!al_init_image_addon()) { std::cerr << "ERROR: Unable to initialize Allegro image addon!\n"; return -3; }
    if(!al_init_font_addon()) { std::cerr << "ERROR: Unable to initialize Allegro font addon!\n"; return -4; }
    if(!al_init_ttf_addon()) { std::cerr << "ERROR: Unable to initialize Allegro ttf addon!\n"; return -5; }

    ALLEGRO_FONT * font1 = nullptr, * font2 = nullptr, * font3 = nullptr, * font4 = nullptr;
    ALLEGRO_BITMAP * bitmap = nullptr;

    if(font1 = al_load_ttf_font(argv[1], 16, ALLEGRO_TTF_MONOCHROME); font1 == nullptr) { std::cerr << "ERROR: Unable to load font #1 \"" << argv[1] << "\"!\n"; return -6; }
    if(font2 = al_load_ttf_font(argv[2], 16, ALLEGRO_TTF_MONOCHROME); font2 == nullptr) { std::cerr << "ERROR: Unable to load font #2 \"" << argv[2] << "\"!\n"; return -7; }
    if(font3 = al_load_ttf_font(argv[3], 16, ALLEGRO_TTF_MONOCHROME); font3 == nullptr) { std::cerr << "ERROR: Unable to load font #3 \"" << argv[3] << "\"!\n"; return -8; }
    if(font4 = al_load_ttf_font(argv[4], 16, ALLEGRO_TTF_MONOCHROME); font4 == nullptr) { std::cerr << "ERROR: Unable to load font #4 \"" << argv[4] << "\"!\n"; return -9; }

    if(bitmap = al_create_bitmap(8, 8); bitmap == nullptr) { std::cerr << "ERROR: Unable to create bitmap!\n"; return -10; }

    std::unique_ptr<std::array<std::array<std::array<std::bitset<8>, 8>, 256>, 4>> font_data = std::make_unique<std::array<std::array<std::array<std::bitset<8>, 8>, 256>, 4>>();

    for(int i = 0; i < 4; i++) {
        font_data->at(i) = {};
    }

    al_set_target_bitmap(bitmap);

    // Read Font 1
    for(int c = 0; c < 256; c++) { // For each character
        // Clear bitmap
        al_clear_to_color(al_map_rgb(0, 0, 0));

        // Draw to the bitmap
        al_draw_glyph(font1, al_map_rgb(255, 255, 255), 0, 0, codepoints[c]);

        // Read pixels
        for(int y = 0; y < 8; y++) {
            for(int x = 0; x < 8; x++) {
                auto color = al_get_pixel(bitmap, x, y);
                unsigned char r, g, b;
                al_unmap_rgb(color, &r, &g, &b);
                font_data->at(0).at(c).at(y).set(7 - x, (r == 255) && (g == 255) && (b == 255));
            }
        }
    }

    // Read Font 2
    for(int c = 0; c < 256; c++) { // For each character
        // Clear bitmap
        al_clear_to_color(al_map_rgb(0, 0, 0));

        // Draw to the bitmap
        al_draw_glyph(font2, al_map_rgb(255, 255, 255), 0, 0, codepoints[c]);

        // Read pixels
        for(int y = 0; y < 8; y++) {
            for(int x = 0; x < 8; x++) {
                auto color = al_get_pixel(bitmap, x, y);
                unsigned char r, g, b;
                al_unmap_rgb(color, &r, &g, &b);
                font_data->at(1).at(c).at(y).set(7 - x, (r == 255) && (g == 255) && (b == 255));
            }
        }
    }

    // Read Font 3
    for(int c = 0; c < 256; c++) { // For each character
        // Clear bitmap
        al_clear_to_color(al_map_rgb(0, 0, 0));

        // Draw to the bitmap
        al_draw_glyph(font3, al_map_rgb(255, 255, 255), 0, 0, codepoints[c]);

        // Read pixels
        for(int y = 0; y < 8; y++) {
            for(int x = 0; x < 8; x++) {
                auto color = al_get_pixel(bitmap, x, y);
                unsigned char r, g, b;
                al_unmap_rgb(color, &r, &g, &b);
                font_data->at(2).at(c).at(y).set(7 - x, (r == 255) && (g == 255) && (b == 255));
            }
        }
    }

    // Read Font 4
    for(int c = 0; c < 256; c++) { // For each character
        // Clear bitmap
        al_clear_to_color(al_map_rgb(0, 0, 0));

        // Draw to the bitmap
        al_draw_glyph(font4, al_map_rgb(255, 255, 255), 0, 0, codepoints[c]);

        // Read pixels
        for(int y = 0; y < 8; y++) {
            for(int x = 0; x < 8; x++) {
                auto color = al_get_pixel(bitmap, x, y);
                unsigned char r, g, b;
                al_unmap_rgb(color, &r, &g, &b);
                font_data->at(3).at(c).at(y).set(7 - x, (r == 255) && (g == 255) && (b == 255));
            }
        }
    }

    ALLEGRO_FILE * file = nullptr;

    if(file = al_fopen("gfx_fonts.asm", "w"); file == nullptr) { std::cerr << "ERROR: Unable to open output file \"gfx_fonts.asm\"\n"; return -11; }

    // Write data to file

    for(int f = 0; f < 4; f++) {
        al_fprintf(file, "__gfx_font%d:\n", f + 1);
        for(int c = 0; c < 256; c++) {
            al_fprintf(file, "    #d8 ");
            for(int y = 0; y < 8; y++) {
                al_fprintf(file, "0x%02x", font_data->at(f).at(c).at(y).to_ulong() & 0xFF);
                if(y < 7) {
                    al_fprintf(file, ", ");
                }
            }
            al_fprintf(file, "\n");
        }
        al_fprintf(file, "\n");
    }

    al_fclose(file);

    return 0;
    
}
