#pragma once

namespace flame32 {

    enum Opcode : u8 {
        Nop,
        Lod,
        Ldl,
        Mov,
        Swp,
        Ldm,
        Sto,
        Inc,
        Dec,
        Add,
        Sub,
        Mul,
        Div,
        Mod,
        Mls,
        Dvs,
        Mds,
        Shl,
        Shr,
        Sli,
        Sri,
        Rtl,
        Rtr,
        Rli,
        Rri,
        Bor,
        And,
        Xor,
        Bst,
        Brs,
        Bcp,
        Cmp,
        Cpz,
        Cpi,
        Jpr,
        Jmp,
        Jpc,
        Clr,
        Cal,
        Clc,
        Inp,
        Out,
        Inr,
        Otr,
        Psh,
        Pop,
        Psi,
        Hlt,
        Ppp,
        Ret,
        Lmr,
        Str,

        Blod,
        Bldm,
        Bsto,
        Binp,
        Bout,
        Binr,
        Botr,
        Bpsh,
        Bpop,
        Bpsi,
        Bppp,
        Blmr,
        Bstr,

        Kic,
        Kir,
        Krt,
        Kei,
        Kdi,
        Ksi,

        Ehr,
        Ssi,
        Ert,

        _Count,
    };

    std::string opcode_to_string(Opcode op);

}
