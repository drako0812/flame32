#cpudef
{
    #bits 8

    #tokendef reg
    {
        A = 0
        B = 1
        C = 2
        D = 3
        E = 4
        F = 5
        G = 6
        H = 7
        X = 8
        Y = 9
        N = 10
        O = 11
        P = 12
        S = 13
        T = 14
        U = 15
    }

    #tokendef flag
    {
        Z  = 0b00000001
        NZ = 0b00000010
        EQ = 0b00000100
        NE = 0b00001000
        LT = 0b00010000
        GT = 0b00100000
        CA = 0b01000000
        NAN =0b10000000
        LE = 0b00010100
        GE = 0b00100100
    }

}
