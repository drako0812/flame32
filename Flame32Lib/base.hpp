#pragma once

namespace flame32 {

    using u8 = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;

    using i8 = std::int8_t;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;

    using f32 = float;
    using f64 = double;

    struct Byte {
        union {
            u8 U;
            i8 S;
        };

        inline Byte() : U{0} { }
        inline Byte(u8 u) : U{u} { }
        inline Byte(i8 s) : S{s} { }
        inline Byte(u8 h, u8 l) : U((h << 4) | (l & 0x0Fu)) { }

        inline u8 L() const { return U & 0x0F; }
        inline u8 H() const { return (U >> 4) & 0x0F; }
        inline void L(u8 l) { U = (U & 0xF0) | (l & 0x0F); }
        inline void H(u8 h) { U = (U & 0x0F) | (h << 4); }

        inline operator u8() const { return U; }
        inline operator i8() const { return S; }

        inline bool bit(int bit) const {
            return ((U >> bit) & (0x1)) == 1;
        }
        inline void bit(int bit, bool set) {
            if(set) {
                U |= 0x1 << bit;
            } else {
                U &= ~(0x1 << bit);
            }
        }
    };

    struct Word {
        Byte H;
        Byte L;

        inline Word() { U(0); }
        inline Word(u16 u) { U(u); }
        inline Word(i16 s) { S(s); }
        inline Word(u8 h, u8 l) { H.U = h; L.U = l; }

        inline u16 U() const { return ((u16)H.U << 8) | ((u16)L.U); }
        inline i16 S() const { 
            auto tmp = U();
            return *reinterpret_cast<i16*>(&tmp);
        }
        inline void U(u16 value) {
            H.U = value >> 8;
            L.U = value & 0xFF;
        }
        inline void S(i16 value) {
            U(*reinterpret_cast<u16*>(&value));
        }

        inline operator u16() const { return U(); }
        inline operator i16() const { return S(); }

        inline bool bit(int bit) const {
            return ((U() >> bit) & (0x1)) == 1;
        }
        inline void bit(int bit, bool set) {
            if(set) {
                U(U() | (0x1 << bit));
            } else {
                U(U() & ~(0x1 << bit));
            }
        }
    };

    struct DWord {
        Word H;
        Word L;

        inline DWord() { U(0); }
        inline DWord(u32 u) { U(u); }
        inline DWord(i32 s) { S(s); }
        inline DWord(f32 f) { F(f); }
        inline DWord(u16 h, u16 l) { H.U(h); L.U(l); }

        inline u32 U() const { return ((u32)H.U() << 16) | ((u32)L.U()); }
        inline i32 S() const {
            auto tmp = U();
            return *reinterpret_cast<i32*>(&tmp);
        }
        inline void U(u32 value) {
            H.U(value >> 16);
            L.U(value & 0xFFFF);
        }
        inline void S(i32 value) {
            U(*reinterpret_cast<u32*>(&value));
        }
        inline f32 F() const {
            auto tmp = U();
            return *reinterpret_cast<f32*>(&tmp);
        }
        inline void F(f32 value) {
            U(*reinterpret_cast<u32*>(&value));
        }

        inline operator u32() const { return U(); }
        inline operator i32() const { return S(); }
        inline operator f32() const { return F(); }

        inline bool bit(int bit) const {
            return ((U() >> bit) & (0x1)) == 1;
        }
        inline void bit(int bit, bool set) {
            if(set) {
                U(U() | (0x1 << bit));
            } else {
                U(U() & ~(0x1 << bit));
            }
        }

        inline u32 Get24Bit() {
            return U() & 0x00FFFFFF;
        }
    };

    struct QWord {
        DWord H;
        DWord L;

        inline QWord() { U(0); }
        inline QWord(u64 u) { U(u); }
        inline QWord(i64 s) { S(s); }
        inline QWord(f64 f) { F(f); }
        inline QWord(u32 h, u32 l) { H.U(h); L.U(l); }

        inline u64 U() const { return ((u64)H.U() << 32) | ((u64)L.U()); }
        inline i64 S() const {
            auto tmp = U();
            return *reinterpret_cast<i64*>(&tmp);
        }
        inline void U(u64 value) {
            H.U(value >> 32);
            L.U(value & 0xFFFFFFFF);
        }
        inline void S(i64 value) {
            U(*reinterpret_cast<u64*>(&value));
        }
        inline f64 F() const {
            auto tmp = U();
            return *reinterpret_cast<f64*>(&tmp);
        }
        inline void F(f64 value) {
            U(*reinterpret_cast<u64*>(&value));
        }

        inline operator u64() const { return U(); }
        inline operator i64() const { return S(); }
        inline operator f64() const { return F(); }

        inline bool bit(int bit) const {
            return ((U() >> bit) & (0x1ULL)) == 1;
        }
        inline void bit(int bit, bool set) {
            if(set) {
                U(U() | (0x1ULL << bit));
            } else {
                U(U() & ~(0x1ULL << bit));
            }
        }
    };

}
