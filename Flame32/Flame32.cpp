#include "pch.h"
#include "base.hpp"
#include "statement.hpp"
#include "opcodes.hpp"
#include "gfx.hpp"
#include "cpu.hpp"

int main(int argc, char * argv[]) {
    /*try {*/
        auto c = std::make_unique<flame32::Cpu>();

        if(argc == 2) {
            std::string bios = argv[1];
            if(!c->load_binary(bios)) {
                std::cerr << rang::fgB::red << "ERROR: Unable to load BIOS/OS binary! \"" << bios << "\"" << rang::style::reset << std::endl;
                return -1;
            }
        } else if(argc == 3) {
            std::string bios = argv[1];
            std::string prog = argv[2];
            if(!c->load_binary(bios)) {
                std::cerr << rang::fgB::red << "ERROR: Unable to load BIOS/OS binary! \"" << bios << "\"" << rang::style::reset << std::endl;
                return -1;
            }
            if(!c->load_binary(prog)) {
                std::cerr << rang::fgB::red << "ERROR: Unable to load program binary! \"" << prog << "\"" << rang::style::reset << std::endl;
                return -1;
            }
        }

        if(!c->gfx->init(*c)) {
            std::cerr << rang::fgB::red << "ERROR: Unable to create Gfx virtual hardware!" << rang::style::reset << std::endl;
            return -1;
        }

#if 1
        if(c->debug_log = std::ofstream("flame32-debug.log", std::ios::out); !c->debug_log) {
            std::cerr << rang::fgB::red << "ERROR: Unable to create \"flame32-debug.log\"" << rang::style::reset << std::endl;
            return -1;
        }
#endif

        while(!c->is_halted) {
            c->process();
        }

#if 1
        c->debug_log.close();
#endif
    /*} catch(std::exception & ex) {
        std::cerr << rang::fgB::red << ex.what() << rang::style::reset << std::endl;
        return -1;
    }*/

    return 0;
}
