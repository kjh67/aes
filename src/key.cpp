#include "aes.h"
#include <random>

using std::random_device;

namespace aes{

byte* Key::GenerateKey(int key_length) {
    // Key generation; generate a (large) random number, then convert to bytes
    // Not Crypto secure!
    std::random_device source;
    byte key[key_length/8];
    for (int i=0; i<key_length/8; i++) {
        byte new_byte = source();
        key[i] = new_byte;
    };
    int x = key_length;
};

Key::Key(int key_length) {
    nk = 4;
    secret = GenerateKey(key_length);
    expanded_key[32];
};

Key::Key(byte* key) {
    if (sizeof(key) == 16 || sizeof(key) == 24 || sizeof(key) == 32) {
        nk = sizeof(key) / 4;
        secret = key;

    };
};

}