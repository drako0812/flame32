#pragma once

namespace flame32 {

    struct TableLine {
        int size;
        int ticks;
    };

    inline const TableLine opcode_table[Opcode::_Count] = {
        { 1, 1 }, // NOP
        { 1, 1 }, // LOD
        { 2, 1 }, // LDL
        { 1, 1 }, // MOV
        { 1, 1 }, // SWP
        { 2, 1 }, // LDM
        { 2, 1 }, // STO
        { 1, 1 }, // INC
        { 1, 1 }, // DEC
        { 1, 1 }, // ADD
        { 1, 1 }, // SUB
        { 1, 1 }, // MUL
        { 1, 1 }, // DIV
        { 1, 1 }, // MOD
        { 1, 1 }, // MLS
        { 1, 1 }, // DVS
        { 1, 1 }, // MDS
        { 1, 1 }, // SHL
        { 1, 1 }, // SHR
        { 1, 1 }, // SLI
        { 1, 1 }, // SRI
        { 1, 1 }, // RTL
        { 1, 1 }, // RTR
        { 1, 1 }, // RLI
        { 1, 1 }, // RRI
        { 1, 1 }, // BOR
        { 1, 1 }, // AND
        { 1, 1 }, // XOR
        { 1, 1 }, // BST
        { 1, 1 }, // BRS
        { 1, 1 }, // BCP
        { 1, 1 }, // CMP
        { 1, 1 }, // CPZ
        { 2, 1 }, // CPI
        { 1, 1 }, // JPR
        { 2, 1 }, // JMP
        { 2, 1 }, // JPC
        { 1, 1 }, // CLR
        { 2, 1 }, // CAL
        { 2, 1 }, // CLC
        { 1, 1 }, // INP
        { 1, 1 }, // OUT
        { 1, 1 }, // INR
        { 1, 1 }, // OTR
        { 1, 1 }, // PSH
        { 1, 1 }, // POP
        { 2, 1 }, // PSI
        { 1, 1 }, // HLT
        { 1, 1 }, // PPP
        { 1, 1 }, // RET
        { 1, 1 }, // LMR
        { 1, 1 }, // STR

        { 1, 1 }, // BLOD
        { 2, 1 }, // BLDM
        { 2, 1 }, // BSTO
        { 1, 1 }, // BINP
        { 1, 1 }, // BOUT
        { 1, 1 }, // BINR
        { 1, 1 }, // BOTR
        { 1, 1 }, // BPSH
        { 1, 1 }, // BPOP
        { 1, 1 }, // BPSI
        { 1, 1 }, // BPPP
        { 1, 1 }, // BLMR
        { 1, 1 }, // BSTR

        { 1, 1 }, // KIC
        { 1, 1 }, // KIR
        { 1, 1 }, // KRT
        { 1, 1 }, // KEI
        { 1, 1 }, // KDI
        { 2, 1 }, // KSI

        { 2, 1 }, // EHR
        { 2, 1 }, // SSI
        { 1, 1 }, // ERT
    };

}
