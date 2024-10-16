#include <algorithm>
#include "aes.h"

using namespace std;

namespace aes {

// Constructors

// COLUMN-MAJOR ORDER FOR STATE STORAGE

State::State() {
    nb = 4;
    state[16];
    inverse = false;
}

State::State(int block_size) {
    if (block_size >= 128 && block_size <= 256 && block_size%32 == 0) {
        nb = block_size/32;
        state[nb*4];
        inverse = false;
    }
    else {
        throw InitialisationError();
    }
}


// Getters and Setters

void State::SetState(byte* content) {
    // Check size compatibility
    if (sizeof(state) == sizeof(content)) {
        // Deep copy content to the state array
        std::copy(content, content+nb*4, state);
    }
}

byte* State::GetState() {
    byte to_return[nb*4];
    std::copy(state, state+nb*4, to_return);
    return state;
}

void State::SetInverse(bool inv) {
    inverse = inv;
}


// State manipulations

void State::SubBytes() {
    if (inverse) {
        for (int b=0; b<nb*4; b++) {
            //TODO: apply inverse affine
            state[b] = mathfuncs::GaloisMultiplicativeInverse(state[b]);
        }
    }
    else {
        for (int b=0; b<nb*4; b++) {
            // Apply s-box to each byte in the state
            byte inv = mathfuncs::GaloisMultiplicativeInverse(state[b]);
            //TODO: affine application
            state[b] = inv;
        }
    }
}

void State::ShiftRows() {
    // Set up shift offsets
    int shifts[4] = {0,1,2,3};
    if (nb == 8) { shifts[2] = 3, shifts[3] = 4; }
    // Reverse the normal shift if inverting the cipher
    if (inverse) { for (int i=1; i<4; i++) { shifts[i] = nb-shifts[i]; } }
    // Rotate each row in turn
    for (int row=1; row<4; row++) {
        // shift by one as many times as needed to achieve full shift
        for (int count=0; count<shifts[row]; count++) {
            // Save first item in the row
            byte temp = state[row];
            for (int col=0; col<nb-1; col++) {
                state[row+col*4] = state[row+(col+1)*4];
            }
            state[row+(nb-1)*4] = temp;
        }
    }
}

void State::MixColumns() {
    byte* fixed_poly;
    // Fixed polynomial coefficients from cipher definition
    if (inverse) {
        byte fixed_poly[4] = {0x0E, 0x09, 0x0D, 0x0B};
    }
    else {
        byte fixed_poly[4] = {0x02, 0x01, 0x01, 0x03};
    }
    // Number of columns in the state is nb; apply poly to each of these
    byte* column_poly;
    byte* column_result;
    for (int i=0; i<nb; i++) {
        byte column_poly[4] = {state[4*i], state[4*i+1], state[4*i+2], state[4*i+3]};
        mathfuncs::GaloisPolynomialMultiplication(column_poly, fixed_poly, column_result);
        state[4*i] = *column_result;
    }
}

void State::AddRoundKey(byte* round_key) {
    for (int i=0; i<nb*4; i++) {
        state[i] ^= round_key[i];
    }
}

}