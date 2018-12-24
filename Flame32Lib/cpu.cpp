#include "stdafx.h"
#include "base.hpp"
#include "registers.hpp"
#include "opcodes.hpp"
#include "statement.hpp"
#include "opcode_table.hpp"
#include "gfx.hpp"
#include "cpu.hpp"

namespace flame32 {

    Cpu::Cpu() :
        ticks{0},
        stack_start{(1024 * 1024 * 10) - 1},
        is_halted{false},
        interrupt_ticks{0},
        interrupt_enabled{false},
        interrupt_accum{0},
        error_handler_address{0},
        in_error_handler{false},
        last_proc{std::chrono::high_resolution_clock::now()},
        A{0}, B{0}, C{0}, D{0}, E{0}, F{0}, G{0}, H{0},
        X{0}, Y{0}, N{0}, O{0}, P{0}, S{(1024 * 1024 * 10) - 1}, T{0}, U{0},
        reg{}
    {
        reg[0] = &A;
        reg[1] = &B;
        reg[2] = &C;
        reg[3] = &D;
        reg[4] = &E;
        reg[5] = &F;
        reg[6] = &G;
        reg[7] = &H;

        reg[8] = &X;
        reg[9] = &Y;
        reg[10] = &N;
        reg[11] = &O;
        reg[12] = &P;
        reg[13] = &S;
        reg[14] = &T;
        reg[15] = &U;

        ops[Opcode::Nop] = &Cpu::op_nop;
        ops[Opcode::Lod] = &Cpu::op_lod;
        ops[Opcode::Ldl] = &Cpu::op_ldl;
        ops[Opcode::Mov] = &Cpu::op_mov;
        ops[Opcode::Swp] = &Cpu::op_swp;
        ops[Opcode::Ldm] = &Cpu::op_ldm;
        ops[Opcode::Sto] = &Cpu::op_sto;
        ops[Opcode::Inc] = &Cpu::op_inc;
        ops[Opcode::Dec] = &Cpu::op_dec;
        ops[Opcode::Add] = &Cpu::op_add;
        ops[Opcode::Sub] = &Cpu::op_sub;
        ops[Opcode::Mul] = &Cpu::op_mul;
        ops[Opcode::Div] = &Cpu::op_div;
        ops[Opcode::Mod] = &Cpu::op_mod;
        ops[Opcode::Mls] = &Cpu::op_mls;
        ops[Opcode::Dvs] = &Cpu::op_dvs;
        ops[Opcode::Mds] = &Cpu::op_mds;
        ops[Opcode::Shl] = &Cpu::op_shl;
        ops[Opcode::Shr] = &Cpu::op_shr;
        ops[Opcode::Sli] = &Cpu::op_sli;
        ops[Opcode::Sri] = &Cpu::op_sri;
        ops[Opcode::Rtl] = &Cpu::op_rtl;
        ops[Opcode::Rtr] = &Cpu::op_rtr;
        ops[Opcode::Rli] = &Cpu::op_rli;
        ops[Opcode::Rri] = &Cpu::op_rri;
        ops[Opcode::Bor] = &Cpu::op_bor;
        ops[Opcode::And] = &Cpu::op_and;
        ops[Opcode::Xor] = &Cpu::op_xor;
        ops[Opcode::Bst] = &Cpu::op_bst;
        ops[Opcode::Brs] = &Cpu::op_brs;
        ops[Opcode::Bcp] = &Cpu::op_bcp;
        ops[Opcode::Cmp] = &Cpu::op_cmp;
        ops[Opcode::Cpz] = &Cpu::op_cpz;
        ops[Opcode::Cpi] = &Cpu::op_cpi;
        ops[Opcode::Jpr] = &Cpu::op_jpr;
        ops[Opcode::Jmp] = &Cpu::op_jmp;
        ops[Opcode::Jpc] = &Cpu::op_jpc;
        ops[Opcode::Clr] = &Cpu::op_clr;
        ops[Opcode::Cal] = &Cpu::op_cal;
        ops[Opcode::Clc] = &Cpu::op_clc;
        ops[Opcode::Inp] = &Cpu::op_inp;
        ops[Opcode::Out] = &Cpu::op_out;
        ops[Opcode::Inr] = &Cpu::op_inr;
        ops[Opcode::Otr] = &Cpu::op_otr;
        ops[Opcode::Psh] = &Cpu::op_psh;
        ops[Opcode::Pop] = &Cpu::op_pop;
        ops[Opcode::Psi] = &Cpu::op_psi;
        ops[Opcode::Hlt] = &Cpu::op_hlt;
        ops[Opcode::Ppp] = &Cpu::op_ppp;
        ops[Opcode::Ret] = &Cpu::op_ret;
        ops[Opcode::Lmr] = &Cpu::op_lmr;
        ops[Opcode::Str] = &Cpu::op_str;

        ops[Opcode::Blod] = &Cpu::op_blod;
        ops[Opcode::Bldm] = &Cpu::op_bldm;
        ops[Opcode::Bsto] = &Cpu::op_bsto;
        ops[Opcode::Binp] = &Cpu::op_binp;
        ops[Opcode::Bout] = &Cpu::op_bout;
        ops[Opcode::Binr] = &Cpu::op_binr;
        ops[Opcode::Botr] = &Cpu::op_botr;
        ops[Opcode::Bpsh] = &Cpu::op_bpsh;
        ops[Opcode::Bpop] = &Cpu::op_bpop;
        ops[Opcode::Bpsi] = &Cpu::op_bpsi;
        ops[Opcode::Bppp] = &Cpu::op_bppp;
        ops[Opcode::Blmr] = &Cpu::op_blmr;
        ops[Opcode::Bstr] = &Cpu::op_bstr;

        ops[Opcode::Kic] = &Cpu::op_kic;
        ops[Opcode::Kir] = &Cpu::op_kir;
        ops[Opcode::Krt] = &Cpu::op_krt;
        ops[Opcode::Kei] = &Cpu::op_kei;
        ops[Opcode::Kdi] = &Cpu::op_kdi;
        ops[Opcode::Ksi] = &Cpu::op_ksi;

        ops[Opcode::Ehr] = &Cpu::op_ehr;
        ops[Opcode::Ssi] = &Cpu::op_ssi;
        ops[Opcode::Ert] = &Cpu::op_ert;

        mem = std::make_unique<std::array<u8, 1024 * 1024 * 10>>();
        memset(mem->data(), 0, mem->size());

        gfx = std::make_unique<Gfx>();
    }

    bool Cpu::load_binary(const std::string & file) {
        if(auto ifs = std::ifstream(file.c_str(), std::ios::binary | std::ios::in | std::ios::ate); ifs) {
            auto size = ifs.tellg();
            if(size > mem->size()) {
                ifs.close();
                return false;
            }
            ifs.seekg(0);
            ifs.read((char*)(mem->data()), size);
            ifs.close();
            return true;
        } else {
            return false;
        }
    }

    bool Cpu::load_binary(const std::string & rom, const std::string & program) {
        if(auto from = std::ifstream(rom.c_str(), std::ios::binary | std::ios::in | std::ios::ate); from) {
            auto size = from.tellg();
            if(size > mem->size() - 0x400000) {
                from.close();
                return false;
            }
            from.seekg(0);
            from.read((char *)(mem->data()), size);
            from.close();
        } else {
            return false;
        }

        if(auto fprog = std::ifstream(program.c_str(), std::ios::binary | std::ios::in | std::ios::ate); fprog) {
            auto size = fprog.tellg();
            if(size > 0x400000) {
                fprog.close();
                return false;
            }
            fprog.seekg(0);
            fprog.read((char *)(mem->data() + 0x600000), size);
            fprog.close();

            return true;
        } else {
            return false;
        }
    }

    void Cpu::output_debug(Statement64 statement) {
        // Output Opcode and arguments
        debug_log << "OP: " << opcode_to_string((Opcode)(statement.H.H.H.U)) << " ";
        debug_log << std::hex << std::setw(6) << std::setfill('0') << statement.H.Get24Bit() << ", ";
        debug_log << std::hex << std::setw(8) << std::setfill('0') << statement.L.U() << std::endl;

        // Output Registers
        debug_log << "A: " << std::hex << std::setw(8) << std::setfill('0') << A << " ";
        debug_log << "B: " << std::hex << std::setw(8) << std::setfill('0') << B << " ";
        debug_log << "C: " << std::hex << std::setw(8) << std::setfill('0') << C << " ";
        debug_log << "D: " << std::hex << std::setw(8) << std::setfill('0') << D << " ";
        debug_log << "E: " << std::hex << std::setw(8) << std::setfill('0') << E << " ";
        debug_log << "F: " << std::hex << std::setw(8) << std::setfill('0') << F << " ";
        debug_log << "G: " << std::hex << std::setw(8) << std::setfill('0') << G << " ";
        debug_log << "H: " << std::hex << std::setw(8) << std::setfill('0') << H << std::endl;

        debug_log << "X: " << std::hex << std::setw(8) << std::setfill('0') << X << " ";
        debug_log << "Y: " << std::hex << std::setw(8) << std::setfill('0') << Y << " ";
        debug_log << "N: " << std::hex << std::setw(8) << std::setfill('0') << N << " ";
        debug_log << "O: " << std::hex << std::setw(8) << std::setfill('0') << O << " ";
        debug_log << "P: " << std::hex << std::setw(8) << std::setfill('0') << P << " ";
        debug_log << "S: " << std::hex << std::setw(8) << std::setfill('0') << S << " ";
        debug_log << "T: " << std::hex << std::setw(8) << std::setfill('0') << T << " ";
        debug_log << "U: " << std::hex << std::setw(8) << std::setfill('0') << U << std::endl;

        // Output up to 100 bytes of the stack
        debug_log << "STACK:" << std::endl;
        for(long long addr = S + 1, y = 0; (addr < stack_start) && (y < 10); y++) {
            for(long long x = 0; (addr < stack_start) && (x < 10); x++, addr++) {
                debug_log << std::hex << std::setw(2) << std::setfill('0') << static_cast<u32>(get_mem8(addr).U) << " ";
            }
            debug_log << std::endl;
        }
        debug_log << std::endl;
    }

    void Cpu::process() {
        auto statement = fetch_statement();
        auto opcode = statement.H.H.H.U;
        std::cout << "P = " << std::hex << P << " OP = " << opcode_to_string((Opcode)(statement.H.H.H.U)) << " STATEMENT = " << (u64)statement << " STACK = " << get_mem32(S + 1).U() << std::endl;
#if 1
        output_debug(statement);
#endif

        // Run statement
        (this->*ops.at(opcode))(statement);

        // Handle errors 

        // Check if error-handling is turned on (AKA non-zero EHR)
        if(error_handler_address != 0) {
            // Check if there is an error
            if(U != 0) {
                in_error_handler = true;
                A = U;
                U = 0;

                push32(P);

                P = error_handler_address;
            }
        } else {
            U = 0;
        }

        // Handle interrupts

        // Check if handling interrupts
        if(interrupt_enabled) {
            interrupt_accum += ticks;

            // If we're not in an error handler
            if(!in_error_handler) {
                // If it's time for a Kernel Interrupt
                if(interrupt_accum >= interrupt_ticks) {
                    interrupt_accum = 0;
                    interrupt_enabled = false;

                    push32(P);

                    P = interrupt_address;
                }
            }
        }

        // Process hardware
        gfx->process(*this);

        // Process timing
        {
            using namespace std::chrono;
            auto now = high_resolution_clock::now();
            auto diff = now - last_proc;

            // If emulation has taken less time than "real" hardware
            if(diff < (1us * ticks)) {
                // If remaining time to wait is less than 5 milliseconds
                if(((1us * ticks) - diff) < 5ms) {
                    // Do a busy loop
                    do {
                        now = high_resolution_clock::now();
                        diff = now - last_proc;
                    } while(diff < (1us * ticks));
                } else {
                    // Else, sleep until its time (at this large of a sleep a little inaccuracy is ok)
                    std::this_thread::sleep_until(last_proc + (1us * ticks));
                }
                ticks = 0;
            }
            // Reset last_proc to current time
            last_proc = high_resolution_clock::now();
        }
        /*{
            using namespace std::chrono;
            std::this_thread::sleep_for(100ms);
        }*/
    }

    Statement64 Cpu::fetch_statement() {
        auto ret = get_mem64(P);
        u64 tmp = ret.U();
        return ret;
    }

    QWord Cpu::get_mem64(u32 address) {
        DWord a, b;
        u32 aa, bb;
        a = get_mem32(address % mem->size());
        b = get_mem32((address + 4) % mem->size());
        aa = a.U();
        bb = b.U();
        return QWord(
            a,
            b
        );
    }

    DWord Cpu::get_mem32(u32 address) {
        Word a, b;
        u16 aa, bb;
        a = get_mem16(address % mem->size());
        b = get_mem16((address + 2) % mem->size());
        aa = a.U();
        bb = b.U();
        return DWord(
            a,
            b
        );
    }

    Word Cpu::get_mem16(u32 address) {
        Byte a, b;
        u8 aa, bb;
        a = get_mem8(address % mem->size());
        b = get_mem8((address + 1) % mem->size());
        aa = a.U;
        bb = b.U;
        return Word(
            a.U,
            b.U
        );
    }

    Byte Cpu::get_mem8(u32 address) {
        return Byte(mem->at(address % mem->size()));
    }

    void Cpu::set_mem64(u32 address, QWord value) {
        set_mem32(address % mem->size(), value.H);
        set_mem32((address + 4) % mem->size(), value.L);
    }

    void Cpu::set_mem32(u32 address, DWord value) {
        set_mem16(address & mem->size(), value.H);
        set_mem16((address + 2) % mem->size(), value.L);
    }

    void Cpu::set_mem16(u32 address, Word value) {
        set_mem8(address % mem->size(), value.H);
        set_mem8((address + 1) % mem->size(), value.L);
    }

    void Cpu::set_mem8(u32 address, Byte value) {
        mem->at(address % mem->size()) = value.U;
    }

    void Cpu::push64(QWord value) {
        // Check for overflow first (we don't want to overwrite the top of the stack)
        if((i64)S < (i64)T + 7) { // Stack overflow [Hey I've got a question! ;-) ]
            U = 0b0000'0001;
            return;
        }

        push32(value.L);
        push32(value.H);
    }

    void Cpu::push32(DWord value) {
        // Check for overflow first (we don't want to overwrite the top of the stack)
        if((i64)S < (i64)T + 3) { // Stack overflow [Hey I've got a question! ;-) ]
            U = 0b0000'0001;
            return;
        }

        push16(value.L);
        push16(value.H);
    }

    void Cpu::push16(Word value) {
        // Check for overflow first (we don't want to overwrite the top of the stack)
        if((i64)S < (i64)T + 1) { // Stack overflow [Hey I've got a question! ;-) ]
            U = 0b0000'0001;
            return;
        }

        push8(value.L);
        push8(value.H);
    }

    void Cpu::push8(Byte value) {
        // Check for overflow first (we don't want to overwrite the top of the stack)
        if((i64)S < (i64)T) { // Stack overflow [Hey I've got a question! ;-) ]
            U = 0b0000'0001;
            return;
        }

        set_mem8(S, value);
        S--;
    }

    QWord Cpu::pop64() {
        // Check for underflow first
        if((i64)(S + 8) > (i64)stack_start) {
            U = 0b0000'0010;
            return QWord();
        }

        auto tmp = ++S;
        S += 7;
        return get_mem64(tmp);
    }

    DWord Cpu::pop32() {
        // Check for underflow first
        if((i64)(S + 4) > (i64)stack_start) {
            U = 0b0000'0010;
            return DWord();
        }

        auto tmp = ++S;
        S += 3;
        return get_mem32(tmp);
    }

    Word Cpu::pop16() {
        // Check for underflow first
        if((i64)(S + 2) > (i64)stack_start) {
            U = 0b0000'0010;
            return Word();
        }

        auto tmp = ++S;
        S++;
        return get_mem16(tmp);
    }

    Byte Cpu::pop8() {
        // Check for underflow first
        if((i64)(S + 1) > (i64)stack_start) {
            U = 0b0000'0010;
            return Byte();
        }

        auto tmp = ++S;
        return get_mem8(tmp);
    }

    bool Cpu::test(u32 flags) {
        return (O & flags) != 0;
    }

}
