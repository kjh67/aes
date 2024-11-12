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

void Key::GenerateExpandedKey() {

}

// Constructors; will either generate key material using the above function, or use that provided

// key length must be either 128, 192, or 256
Key::Key(int key_length, int block_length) {
    if (key_length == 128 || key_length == 192 || key_length == 256) {
        nk = key_length / 32;
        secret[key_length/8];
        GenerateKey(key_length);
        expanded_key[32];
        round_key_size = block_length;
        inverse_schedule = false;
    }
    else {
        throw InitialisationError();
    }
}

Key::Key(int key_length, int block_length, byte* key) {
    if (key_length == 128 || key_length == 192 || key_length == 256) {
        nk = key_length / 32;
        secret[key_length/8];
        for (int i=0; i<key_length/8; i++) {
            secret[i] = key[i];
        }
        expanded_key[32];
        round_key_size = block_length;
        inverse_schedule = false;
    }
    else {
        throw InitialisationError();
    }
}


void Key::ReplaceKey() {
    GenerateKey(nk*32);
    GenerateExpandedKey();
}

void Key::ReplaceKey(byte* key) {
    for (int i=0; i<nk*4; i++) {
        secret[i] = key[i];
    }
    GenerateExpandedKey();
}

void Key::ResetExpandedKey() {
    // reset pointer to 0
}


// AES Key Schedule
void Key::GetNextRoundKey(byte* container) {
    // expand expanded key and return the round key in the container array
}


void Key::GetKey(byte* container){
    // return the secret in the container
}

}