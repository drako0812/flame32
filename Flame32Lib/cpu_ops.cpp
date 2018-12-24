#include "stdafx.h"
#include "base.hpp"
#include "registers.hpp"
#include "opcodes.hpp"
#include "statement.hpp"
#include "opcode_table.hpp"
#include "gfx.hpp"
#include "cpu.hpp"

namespace flame32 {

    void Cpu::op_nop(Statement64 statement) {
        // Nothing to do
        P += opcode_table[Opcode::Nop].size * 4;
        ticks += opcode_table[Opcode::Nop].ticks;
    }
    void Cpu::op_lod(Statement64 statement) {
        A = statement.H.Get24Bit();
        P += opcode_table[Opcode::Lod].size * 4;
        ticks += opcode_table[Opcode::Lod].ticks;
    }
    void Cpu::op_ldl(Statement64 statement) {
        auto r = statement.H.H.L.H();
        auto v = statement.L.U();

        *(reg[r]) = v;

        P += opcode_table[Opcode::Ldl].size * 4;
        ticks += opcode_table[Opcode::Ldl].ticks;
    }
    void Cpu::op_mov(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        *(reg[a]) = *(reg[b]);

        P += opcode_table[Opcode::Mov].size * 4;
        ticks += opcode_table[Opcode::Mov].ticks;
    }
    void Cpu::op_swp(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        auto tmp = *(reg[b]);
        *(reg[b]) = *(reg[a]);
        *(reg[a]) = tmp;

        P += opcode_table[Opcode::Swp].size * 4;
        ticks += opcode_table[Opcode::Swp].ticks;
    }
    void Cpu::op_ldm(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto i = statement.L.U();

        *(reg[a]) = get_mem32(i).U();

        P += opcode_table[Opcode::Ldm].size * 4;
        ticks += opcode_table[Opcode::Ldm].ticks;
    }
    void Cpu::op_sto(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto i = statement.L.U();

        set_mem32(i, *(reg[a]));

        P += opcode_table[Opcode::Sto].size * 4;
        ticks += opcode_table[Opcode::Sto].ticks;
    }
    void Cpu::op_inc(Statement64 statement) {
        auto a = statement.H.H.L.H();

        *(reg[a])++;

        P += opcode_table[Opcode::Inc].size * 4;
        ticks += opcode_table[Opcode::Inc].ticks;
    }
    void Cpu::op_dec(Statement64 statement) {
        auto a = statement.H.H.L.H();

        *(reg[a])--;

        P += opcode_table[Opcode::Dec].size * 4;
        ticks += opcode_table[Opcode::Dec].ticks;
    }
    void Cpu::op_add(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        *(reg[a]) += *(reg[b]);

        P += opcode_table[Opcode::Add].size * 4;
        ticks += opcode_table[Opcode::Add].ticks;
    }
    void Cpu::op_sub(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        *(reg[a]) -= *(reg[b]);

        P += opcode_table[Opcode::Sub].size * 4;
        ticks += opcode_table[Opcode::Sub].ticks;
    }
    void Cpu::op_mul(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        *(reg[a]) *= *(reg[b]);

        P += opcode_table[Opcode::Mul].size * 4;
        ticks += opcode_table[Opcode::Mul].ticks;
    }
    void Cpu::op_div(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        *(reg[a]) /= *(reg[b]);

        P += opcode_table[Opcode::Div].size * 4;
        ticks += opcode_table[Opcode::Div].ticks;
    }
    void Cpu::op_mod(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        *(reg[a]) %= *(reg[b]);

        P += opcode_table[Opcode::Mod].size * 4;
        ticks += opcode_table[Opcode::Mod].ticks;
    }
    void Cpu::op_mls(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        *((i32*)reg[a]) += *((i32*)reg[b]);

        P += opcode_table[Opcode::Mls].size * 4;
        ticks += opcode_table[Opcode::Mls].ticks;
    }
    void Cpu::op_dvs(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        *((i32*)reg[a]) /= *((i32*)reg[b]);

        P += opcode_table[Opcode::Dvs].size * 4;
        ticks += opcode_table[Opcode::Dvs].ticks;
    }
    void Cpu::op_mds(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        *((i32*)reg[a]) %= *((i32*)reg[b]);

        P += opcode_table[Opcode::Mds].size * 4;
        ticks += opcode_table[Opcode::Mds].ticks;
    }
    void Cpu::op_shl(Statement64 statement) {
        auto a = statement.H.H.L.H();

        *(reg[a]) <<= 1;

        P += opcode_table[Opcode::Shl].size * 4;
        ticks += opcode_table[Opcode::Shl].ticks;
    }
    void Cpu::op_shr(Statement64 statement) {
        auto a = statement.H.H.L.H();

        *(reg[a]) >>= 1;

        P += opcode_table[Opcode::Shr].size * 4;
        ticks += opcode_table[Opcode::Shr].ticks;
    }
    void Cpu::op_sli(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        *(reg[a]) <<= *(reg[b]);

        P += opcode_table[Opcode::Sli].size * 4;
        ticks += opcode_table[Opcode::Sli].ticks;
    }
    void Cpu::op_sri(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        *(reg[a]) >>= *(reg[b]);

        P += opcode_table[Opcode::Sri].size * 4;
        ticks += opcode_table[Opcode::Sri].ticks;
    }
    void Cpu::op_rtl(Statement64 statement) {
        auto a = statement.H.H.L.H();

        u32 tmp = *(reg[a]) & 0x80000000;
        tmp >>= 31;
        *(reg[a]) = (*(reg[a]) << 1) | tmp;

        P += opcode_table[Opcode::Rtl].size * 4;
        ticks += opcode_table[Opcode::Rtl].ticks;
    }
    void Cpu::op_rtr(Statement64 statement) {
        auto a = statement.H.H.L.H();

        u32 tmp = *(reg[a]) & 0x1;
        tmp <<= 31;
        *(reg[a]) = ((*(reg[a]) >> 1) & 0x7FFFFFFF) | tmp;

        P += opcode_table[Opcode::Rtr].size * 4;
        ticks += opcode_table[Opcode::Rtr].ticks;
    }
    void Cpu::op_rli(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        for(long long i = 0; i < b; i++) {
            u32 tmp = *(reg[a]) & 0x80000000;
            tmp >>= 31;
            *(reg[a]) = (*(reg[a]) << 1) | tmp;
        }

        P += opcode_table[Opcode::Rli].size * 4;
        ticks += opcode_table[Opcode::Rli].ticks;
    }
    void Cpu::op_rri(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        for(long long i = 0; i < b; i++) {
            u32 tmp = *(reg[a]) & 0x1;
            tmp <<= 31;
            *(reg[a]) = ((*(reg[a]) >> 1) & 0x7FFFFFFF) | tmp;
        }

        P += opcode_table[Opcode::Rri].size * 4;
        ticks += opcode_table[Opcode::Rri].ticks;
    }
    void Cpu::op_bor(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        *(reg[a]) |= *(reg[b]);

        P += opcode_table[Opcode::Bor].size * 4;
        ticks += opcode_table[Opcode::Bor].ticks;
    }
    void Cpu::op_and(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        *(reg[a]) &= *(reg[b]);

        P += opcode_table[Opcode::And].size * 4;
        ticks += opcode_table[Opcode::And].ticks;
    }
    void Cpu::op_xor(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        *(reg[a]) ^= *(reg[b]);

        P += opcode_table[Opcode::Xor].size * 4;
        ticks += opcode_table[Opcode::Xor].ticks;
    }
    void Cpu::op_bst(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        *(reg[a]) |= (1ul << b);

        P += opcode_table[Opcode::Bst].size * 4;
        ticks += opcode_table[Opcode::Bst].ticks;
    }
    void Cpu::op_brs(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        *(reg[a]) &= ~(1ul << b);

        P += opcode_table[Opcode::Brs].size * 4;
        ticks += opcode_table[Opcode::Brs].ticks;
    }
    void Cpu::op_bcp(Statement64 statement) {
        auto a = statement.H.H.L.H();

        *(reg[a]) = ~(*(reg[a]));

        P += opcode_table[Opcode::Bcp].size * 4;
        ticks += opcode_table[Opcode::Bcp].ticks;
    }
    void Cpu::op_cmp(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();
        auto ai = *(reg[a]);
        auto bi = *(reg[b]);

        O = 0;
        if(ai == bi) { O |= 0b0000'0100; }
        if(ai != bi) { O |= 0b0000'1000; }
        if(ai < bi) { O |= 0b0001'0000; }
        if(ai > bi) { O |= 0b0010'0000; }

        P += opcode_table[Opcode::Cmp].size * 4;
        ticks += opcode_table[Opcode::Cmp].ticks;
    }
    void Cpu::op_cpz(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto ai = *(reg[a]);

        O = 0;
        if(a == 0) { O |= 0b0000'0001; }
        if(a != 0) { O |= 0b0000'0010; }

        P += opcode_table[Opcode::Cpz].size * 4;
        ticks += opcode_table[Opcode::Cpz].ticks;
    }
    void Cpu::op_cpi(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto ai = *(reg[a]);
        auto bi = statement.L.U();

        O = 0;
        if(ai == bi) { O |= 0b0000'0100; }
        if(ai != bi) { O |= 0b0000'1000; }
        if(ai < bi) { O |= 0b0001'0000; }
        if(ai > bi) { O |= 0b0010'0000; }

        P += opcode_table[Opcode::Cpi].size * 4;
        ticks += opcode_table[Opcode::Cpi].ticks;
    }
    void Cpu::op_jpr(Statement64 statement) {
        auto it = statement.H.Get24Bit();
        auto i = *reinterpret_cast<i32*>(&it);

        P += i;
        ticks += opcode_table[Opcode::Jpr].ticks;
    }
    void Cpu::op_jmp(Statement64 statement) {
        auto i = statement.L.U();

        P = i;
        ticks += opcode_table[Opcode::Jmp].ticks;
    }
    void Cpu::op_jpc(Statement64 statement) {
        auto f = statement.H.Get24Bit();
        auto i = statement.L.U();

        if(test(f)) {
            P = i;
        } else {
            P += opcode_table[Opcode::Jpc].size * 4;
        }

        ticks += opcode_table[Opcode::Jpc].ticks;
    }
    void Cpu::op_clr(Statement64 statement) {
        auto it = statement.H.Get24Bit();
        auto i = *reinterpret_cast<i32*>(&it);

        push32(P + (opcode_table[Opcode::Clr].size * 4));

        P += i;
        ticks += opcode_table[Opcode::Clr].ticks;
    }
    void Cpu::op_cal(Statement64 statement) {
        auto i = statement.L.U();

        push32(P + (opcode_table[Opcode::Cal].size * 4));

        P = i;
        ticks += opcode_table[Opcode::Cal].ticks;
    }
    void Cpu::op_clc(Statement64 statement) {
        auto f = statement.H.Get24Bit();
        auto i = statement.L.U();

        if(test(f)) {
            push32(P + (opcode_table[Opcode::Clc].size * 4));

            P = i;
        } else {
            P += opcode_table[Opcode::Clc].size * 4;
        }

        ticks += opcode_table[Opcode::Clc].ticks;
    }
    void Cpu::op_inp(Statement64 statement) {
        auto p = statement.H.Get24Bit();
        A = 0; // TODO: Implement ports
        // A = get_port32(p);

        P += opcode_table[Opcode::Inp].size * 4;
        ticks += opcode_table[Opcode::Inp].ticks;
    }
    void Cpu::op_out(Statement64 statement) {
        auto p = statement.H.Get24Bit();
        // set_port32(p, A);

        P += opcode_table[Opcode::Out].size * 4;
        ticks += opcode_table[Opcode::Out].ticks;
    }
    void Cpu::op_inr(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto p = *(reg[a]);
        A = 0; // TODO: Implement ports
        // A = get_port32(p);

        P += opcode_table[Opcode::Inr].size * 4;
        ticks += opcode_table[Opcode::Inr].ticks;
    }
    void Cpu::op_otr(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto p = *(reg[a]);
        // set_port32(p, A);

        P += opcode_table[Opcode::Otr].size * 4;
        ticks += opcode_table[Opcode::Otr].ticks;
    }
    void Cpu::op_psh(Statement64 statement) {
        auto a = statement.H.H.L.H();

        push32(*(reg[a]));

        P += opcode_table[Opcode::Psh].size * 4;
        ticks += opcode_table[Opcode::Psh].ticks;
    }
    void Cpu::op_pop(Statement64 statement) {
        auto a = statement.H.H.L.H();

        *(reg[a]) = pop32().U();

        P += opcode_table[Opcode::Pop].size * 4;
        ticks += opcode_table[Opcode::Pop].ticks;
    }
    void Cpu::op_psi(Statement64 statement) {
        auto i = statement.L.U();

        push32(i);

        P += opcode_table[Opcode::Psi].size * 4;
        ticks += opcode_table[Opcode::Psi].ticks;
    }
    void Cpu::op_hlt(Statement64 statement) {
        is_halted = true;

        P += opcode_table[Opcode::Hlt].size * 4;
        ticks += opcode_table[Opcode::Hlt].ticks;
    }
    void Cpu::op_ppp(Statement64 statement) {
        pop32();

        P += opcode_table[Opcode::Ppp].size * 4;
        ticks += opcode_table[Opcode::Ppp].ticks;
    }
    void Cpu::op_ret(Statement64 statement) {
        auto r = pop32().U();

        P = r;
        ticks += opcode_table[Opcode::Ret].ticks;
    }
    void Cpu::op_lmr(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        *(reg[a]) = get_mem32(*(reg[b])).U();

        P += opcode_table[Opcode::Lmr].size * 4;
        ticks += opcode_table[Opcode::Lmr].ticks;
    }
    void Cpu::op_str(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        set_mem32(*(reg[a]), *(reg[b]));

        P += opcode_table[Opcode::Str].size * 4;
        ticks += opcode_table[Opcode::Str].ticks;
    }

    void Cpu::op_blod(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto i = statement.H.L.L.U;

        *(reg[a]) = i;

        P += opcode_table[Opcode::Blod].size * 4;
        ticks += opcode_table[Opcode::Blod].ticks;
    }
    void Cpu::op_bldm(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto i = statement.L.U();

        *(reg[a]) = get_mem8(i).U;

        P += opcode_table[Opcode::Bldm].size * 4;
        ticks += opcode_table[Opcode::Bldm].ticks;
    }
    void Cpu::op_bsto(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto i = statement.L.U();

        set_mem8(i, (u8)*(reg[a]));

        P += opcode_table[Opcode::Bsto].size * 4;
        ticks += opcode_table[Opcode::Bsto].ticks;
    }
    void Cpu::op_binp(Statement64 statement) {
        auto p = statement.H.Get24Bit();
        A = 0; // TODO: Implement ports
        // A = get_port8(p);

        P += opcode_table[Opcode::Binp].size * 4;
        ticks += opcode_table[Opcode::Binp].ticks;
    }
    void Cpu::op_bout(Statement64 statement) {
        auto p = statement.H.Get24Bit();
        // set_port8(p, A);

        P += opcode_table[Opcode::Bout].size * 4;
        ticks += opcode_table[Opcode::Bout].ticks;
    }
    void Cpu::op_binr(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto p = *(reg[a]);
        A = 0; // TODO: Implement ports
        // A = get_port8(p);

        P += opcode_table[Opcode::Binr].size * 4;
        ticks += opcode_table[Opcode::Binr].ticks;
    }
    void Cpu::op_botr(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto p = *(reg[a]);
        // set_port8(p, A);

        P += opcode_table[Opcode::Botr].size * 4;
        ticks += opcode_table[Opcode::Botr].ticks;
    }
    void Cpu::op_bpsh(Statement64 statement) {
        auto a = statement.H.H.L.H();

        push8((u8)*(reg[a]));

        P += opcode_table[Opcode::Bpsh].size * 4;
        ticks += opcode_table[Opcode::Bpsh].ticks;
    }
    void Cpu::op_bpop(Statement64 statement) {
        auto a = statement.H.H.L.H();

        *(reg[a]) = pop8().U;

        P += opcode_table[Opcode::Bpop].size * 4;
        ticks += opcode_table[Opcode::Bpop].ticks;
    }
    void Cpu::op_bpsi(Statement64 statement) {
        auto i = statement.H.L.L.U;

        push8(i);

        P += opcode_table[Opcode::Bpsi].size * 4;
        ticks += opcode_table[Opcode::Bpsi].ticks;
    }
    void Cpu::op_bppp(Statement64 statement) {
        pop8();

        P += opcode_table[Opcode::Bppp].size * 4;
        ticks += opcode_table[Opcode::Bppp].ticks;
    }
    void Cpu::op_blmr(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        *(reg[a]) = get_mem8(*(reg[b])).U;

        P += opcode_table[Opcode::Blmr].size * 4;
        ticks += opcode_table[Opcode::Blmr].ticks;
    }
    void Cpu::op_bstr(Statement64 statement) {
        auto a = statement.H.H.L.H();
        auto b = statement.H.H.L.L();

        set_mem8(*(reg[a]), (u8)*(reg[b]));

        P += opcode_table[Opcode::Bstr].size * 4;
        ticks += opcode_table[Opcode::Bstr].ticks;
    }

    void Cpu::op_kic(Statement64 statement) {
        auto i = statement.H.Get24Bit();

        interrupt_ticks = i;

        if(interrupt_ticks == 0) {
            interrupt_enabled = true;
        } else {
            interrupt_enabled = false;
        }

        interrupt_accum = 0;

        P += opcode_table[Opcode::Kic].size * 4;
        ticks += opcode_table[Opcode::Kic].ticks;
    }
    void Cpu::op_kir(Statement64 statement) {
        auto a = statement.H.H.L.H();

        interrupt_ticks = *(reg[a]);

        if(interrupt_ticks == 0) {
            interrupt_enabled = true;
        } else {
            interrupt_enabled = false;
        }

        interrupt_accum = 0;

        P += opcode_table[Opcode::Kir].size * 4;
        ticks += opcode_table[Opcode::Kir].ticks;
    }
    void Cpu::op_krt(Statement64 statement) {
        interrupt_enabled = true;
        interrupt_accum = 0;

        auto r = pop32().U();

        P = r;
        ticks += opcode_table[Opcode::Krt].ticks;
    }
    void Cpu::op_kei(Statement64 statement) {
        interrupt_enabled = true;
        interrupt_accum = 0;

        P += opcode_table[Opcode::Kei].size * 4;
        ticks += opcode_table[Opcode::Kei].ticks;
    }
    void Cpu::op_kdi(Statement64 statement) {
        interrupt_enabled = false;

        P += opcode_table[Opcode::Kdi].size * 4;
        ticks += opcode_table[Opcode::Kdi].ticks;
    }
    void Cpu::op_ksi(Statement64 statement) {
        auto i = statement.L.U();

        interrupt_address = i;

        P += opcode_table[Opcode::Ksi].size * 4;
        ticks += opcode_table[Opcode::Ksi].ticks;
    }

    void Cpu::op_ehr(Statement64 statement) {
        auto i = statement.L.U();

        error_handler_address = i;

        P += opcode_table[Opcode::Ehr].size * 4;
        ticks += opcode_table[Opcode::Ehr].ticks;
    }
    void Cpu::op_ssi(Statement64 statement) {
        auto i = statement.L.U();

        stack_start = i;
        S = i;

        P += opcode_table[Opcode::Ssi].size * 4;
        ticks += opcode_table[Opcode::Ssi].ticks;
    }

    void Cpu::op_ert(Statement64 statement) {
        in_error_handler = false;

        auto r = pop32().U();

        P = r;
        ticks += opcode_table[Opcode::Krt].ticks;
    }

}
