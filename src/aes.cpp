#include "aes.h"

namespace aes{

// constructor
AES::AES(int key_size, int block_size=128) {
    state = new State(block_size);
    key = new Key(key_size, block_size);
    rounds = (state->nb==8 || key->nk==8) ? 14 : ((state->nb==4 && key->nk==4) ? 10 : 12);
}

// destructor; deallocate the state and key objects from the heap
AES::~AES() {
    delete state;
    delete key;
}


void AES::SetKey(byte* key) {
    this->key->ReplaceKey(key);
}

void AES::SetKey() {
    this->key->ReplaceKey();
}


byte* AES::Encrypt(byte* content) {
    // setup
    state->SetState(content);
    state->SetInverseCipher(false);
    key->SetInverseKeySchedule(false);
    key->ResetExpandedKey();

    // allocate container for round keys
    byte round_key[state->nb * 8];

    // initial round key application
    key->GetNextRoundKey(round_key);
    state->AddRoundKey(round_key);

    // r-1 cipher rounds
    for(int r=0; r<rounds-1; r++) {
        state->SubBytes();
        state->ShiftRows();
        state->MixColumns();
        key->GetNextRoundKey(round_key);
        state->AddRoundKey(round_key);
    }

    // final round
    state->SubBytes();
    state->ShiftRows();
    key->GetNextRoundKey(round_key);
    state->AddRoundKey(round_key);

    // return encrypted data
    return state->GetState();
}

byte* AES::Decrypt(byte* content) {
    // setup
    state->SetState(content);
    state->SetInverseCipher(true);
    key->SetInverseKeySchedule(true);
    key->ResetExpandedKey();

    // allocate container for round keys
    byte round_key[state->nb * 8];

    // r-1 inverse cipher rounds
    for(int r=0; r<rounds-1; r++) {
        key->GetNextRoundKey(round_key);
        state->AddRoundKey(round_key);
        state->MixColumns();
        state->ShiftRows();
        state->SubBytes();
    }

    // final round
    key->GetNextRoundKey(round_key);
    state->AddRoundKey(round_key);
    state->ShiftRows();
    state->SubBytes();

    // final round key application
    key->GetNextRoundKey(round_key);
    state->AddRoundKey(round_key);

    // return decrypted data
    return state->GetState();
}

}
