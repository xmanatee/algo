#ifndef _BITBOARD_H_
#define _BITBOARD_H_

#include "common.h"

class BitBoard8x8 {
private:
    unsigned char board[8];
public:
    BitBoard8x8(void);
    bool get(Int i, Int j) const;
    void set(Int i, Int j, Int bit);
    bool operator () (Int i, Int j) const;
    unsigned char operator [] (Int i) const;
};

BitBoard8x8::BitBoard8x8(void) {
    for (int i = 0; i < 8; ++i) {
        board[i] = 0;
    }
}

bool BitBoard8x8::get(Int i, Int j) const {
    return static_cast<bool>((board[i] >> j) & 1);
}


void BitBoard8x8::set(Int i, Int j, Int bit) {
    if (get(i, j) ^ bit) {
        board[i] ^= 1 << j;
    }
}

bool BitBoard8x8::operator()(Int i, Int j) const {
    return static_cast<bool>((board[i] >> j) & 1);
}

unsigned char BitBoard8x8::operator[] (Int i) const {
    return board[i];
}

#endif // _BITBOARD_H_