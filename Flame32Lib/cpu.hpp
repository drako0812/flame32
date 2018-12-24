#pragma once

namespace flame32 {

    class Cpu {

    public:
        u64 ticks;
        u32 stack_start;
        bool is_halted;
        u32 interrupt_ticks;
        bool interrupt_enabled;
        u32 interrupt_accum;
        u32 interrupt_address;
        bool in_error_handler;
        u32 error_handler_address;
        std::chrono::time_point<std::chrono::high_resolution_clock> last_proc;
        u32 A, B, C, D, E, F, G, H,
            X, Y, N, O, P, S, T, U;
        std::array<u32*, 16> reg;
        std::unique_ptr<std::array<u8, 1024 * 1024 * 10>> mem;
        std::array<void (Cpu::*)(Statement64 statement), Opcode::_Count> ops;
        std::unique_ptr<Gfx> gfx;

        std::ofstream debug_log;

        Cpu();

        bool load_binary(const std::string & file);
        bool load_binary(const std::string & rom, const std::string & program);

        void output_debug(Statement64 statement);

        void process();
        Statement64 fetch_statement();

        QWord get_mem64(u32 address);
        DWord get_mem32(u32 address);
        Word get_mem16(u32 address);
        Byte get_mem8(u32 address);

        void set_mem64(u32 address, QWord value);
        void set_mem32(u32 address, DWord value);
        void set_mem16(u32 address, Word value);
        void set_mem8(u32 address, Byte value);

        void push64(QWord value);
        void push32(DWord value);
        void push16(Word value);
        void push8(Byte value);

        QWord pop64();
        DWord pop32();
        Word pop16();
        Byte pop8();

        bool test(u32 flags);

        void op_nop(Statement64 statement);
        void op_lod(Statement64 statement);
        void op_ldl(Statement64 statement);
        void op_mov(Statement64 statement);
        void op_swp(Statement64 statement);
        void op_ldm(Statement64 statement);
        void op_sto(Statement64 statement);
        void op_inc(Statement64 statement);
        void op_dec(Statement64 statement);
        void op_add(Statement64 statement);
        void op_sub(Statement64 statement);
        void op_mul(Statement64 statement);
        void op_div(Statement64 statement);
        void op_mod(Statement64 statement);
        void op_mls(Statement64 statement);
        void op_dvs(Statement64 statement);
        void op_mds(Statement64 statement);
        void op_shl(Statement64 statement);
        void op_shr(Statement64 statement);
        void op_sli(Statement64 statement);
        void op_sri(Statement64 statement);
        void op_rtl(Statement64 statement);
        void op_rtr(Statement64 statement);
        void op_rli(Statement64 statement);
        void op_rri(Statement64 statement);
        void op_bor(Statement64 statement);
        void op_and(Statement64 statement);
        void op_xor(Statement64 statement);
        void op_bst(Statement64 statement);
        void op_brs(Statement64 statement);
        void op_bcp(Statement64 statement);
        void op_cmp(Statement64 statement);
        void op_cpz(Statement64 statement);
        void op_cpi(Statement64 statement);
        void op_jpr(Statement64 statement);
        void op_jmp(Statement64 statement);
        void op_jpc(Statement64 statement);
        void op_clr(Statement64 statement);
        void op_cal(Statement64 statement);
        void op_clc(Statement64 statement);
        void op_inp(Statement64 statement);
        void op_out(Statement64 statement);
        void op_inr(Statement64 statement);
        void op_otr(Statement64 statement);
        void op_psh(Statement64 statement);
        void op_pop(Statement64 statement);
        void op_psi(Statement64 statement);
        void op_hlt(Statement64 statement);
        void op_ppp(Statement64 statement);
        void op_ret(Statement64 statement);
        void op_lmr(Statement64 statement);
        void op_str(Statement64 statement);

        void op_blod(Statement64 statement);
        void op_bldm(Statement64 statement);
        void op_bsto(Statement64 statement);
        void op_binp(Statement64 statement);
        void op_bout(Statement64 statement);
        void op_binr(Statement64 statement);
        void op_botr(Statement64 statement);
        void op_bpsh(Statement64 statement);
        void op_bpop(Statement64 statement);
        void op_bpsi(Statement64 statement);
        void op_bppp(Statement64 statement);
        void op_blmr(Statement64 statement);
        void op_bstr(Statement64 statement);

        void op_kic(Statement64 statement);
        void op_kir(Statement64 statement);
        void op_krt(Statement64 statement);
        void op_kei(Statement64 statement);
        void op_kdi(Statement64 statement);
        void op_ksi(Statement64 statement);

        void op_ehr(Statement64 statement);
        void op_ssi(Statement64 statement);
        void op_ert(Statement64 statement);
    };

}
