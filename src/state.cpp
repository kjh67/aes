#include "aes.h"

namespace aes {

// CONSTRUCTORS

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

}