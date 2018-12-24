#include "stdafx.h"
#include "base.hpp"
#include "opcodes.hpp"

namespace flame32 {

    std::map<Opcode, std::string> OpcodeToString = {
        { Nop, "nop" },
        { Lod, "lod" },
        { Ldl, "ldl" },
        { Mov, "mov" },
        { Swp, "swp" },
        { Ldm, "ldm" },
        { Sto, "sto" },
        { Inc, "inc" },
        { Dec, "dec" },
        { Add, "add" },
        { Sub, "sub" },
        { Mul, "mul" },
        { Div, "div" },
        { Mod, "mod" },
        { Mls, "mls" },
        { Dvs, "dvs" },
        { Mds, "mds" },
        { Shl, "shl" },
        { Shr, "shr" },
        { Sli, "sli" },
        { Sri, "sri" },
        { Rtl, "rtl" },
        { Rtr, "rtr" },
        { Rli, "rli" },
        { Rri, "rri" },
        { Bor, "bor" },
        { And, "and" },
        { Xor, "xor" },
        { Bst, "bst" },
        { Brs, "brs" },
        { Bcp, "bcp" },
        { Cmp, "cmp" },
        { Cpz, "cpz" },
        { Cpi, "cpi" },
        { Jpr, "jpr" },
        { Jmp, "jmp" },
        { Jpc, "jpc" },
        { Clr, "clr" },
        { Cal, "cal" },
        { Clc, "clc" },
        { Inp, "inp" },
        { Out, "out" },
        { Inr, "inr" },
        { Otr, "otr" },
        { Psh, "psh" },
        { Pop, "pop" },
        { Psi, "psi" },
        { Hlt, "hlt" },
        { Ppp, "ppp" },
        { Ret, "ret" },
        { Lmr, "lmr" },
        { Str, "str" },

        { Blod, "blod" },
        { Bldm, "bldm" },
        { Bsto, "bsto" },
        { Binp, "binp" },
        { Bout, "bout" },
        { Binr, "binr" },
        { Botr, "botr" },
        { Bpsh, "bpsh" },
        { Bpop, "bpop" },
        { Bpsi, "bpsi" },
        { Bppp, "bppp" },
        { Blmr, "blmr" },
        { Bstr, "bstr" },

        { Kic, "kic" },
        { Kir, "kir" },
        { Krt, "krt" },
        { Kei, "kei" },
        { Kdi, "kdi" },
        { Ksi, "ksi" },
    
        { Ehr, "ehr" },
        { Ssi, "ssi" },
        { Ert, "ert" },
    };

    std::string opcode_to_string(Opcode op) {
        return OpcodeToString[op];
    }

}
