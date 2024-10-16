#include "aes.h"
#include <random>

using std::random_device;

namespace aes{

void Key::GenerateKey(int key_length) {
    // Key generation; generate a (large) random number, then convert to bytes
    // Not Crypto secure!
    std::random_device source;
    for (int i=0; i<key_length/8; i++) {
        byte new_byte = source();
        secret[i] = new_byte;
    }
}

// Constructors; will either generate key material using the above function, or use that provided
Key::Key(int key_length) {
    if (key_length%8 != 0) {
        throw InitialisationError();
    }
    nk = 4;
    secret[key_length/8];
    GenerateKey(key_length);
    expanded_key[32];
}

Key::Key(int key_length, byte* key) {
    if (key_length == 16*8 || key_length == 24*8 || key_length == 32*8) {
        nk = key_length / 24;
        secret[key_length/8];
        for (int i=0; i<key_length/8; i++) {
            secret[i] = key[i];
        }
        expanded_key[32];
    }
    else {
        throw InitialisationError();
    }
}


void Key::ReplaceKey() {
    
}

void Key::ReplaceKey(byte* key) {

}

void Key::ResetExtendedKey() {

}


void Key::GetNextRoundKey(byte* container) {

}


void GetKey(byte* container){

}

}