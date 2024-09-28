#include <algorithm>
#include "aes.h"

using namespace std;

namespace aes {

// Constructors

State::State() {
    nb = 4;
    state[16];
}

State::State(int block_size) {
    if (block_size >= 128 && block_size <= 256 && block_size%32 == 0) {
        nb = block_size/32;
        state[nb*4];
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


// State manipulations

void SubBytes() {
    
}

void ShiftRows() {

}

void MixColumns() {

}

void AddRoundKey(byte* round_key) {

}

}