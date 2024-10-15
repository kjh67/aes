namespace aes{

typedef unsigned char byte;

class InitialisationError {};

class State {
    int nb;
    byte* state;

    public:
        State();
        State(int block_size);

        void SetState(byte* content);
        byte* GetState();

        void SubBytes();
        void ShiftRows();
        void MixColumns();
        void AddRoundKey(byte* round_key);
};

class Key {
    int nk;
    byte* secret;
    byte* expanded_key;

    byte* GenerateKey(int key_length);

    public:
        Key(int key_length);
        Key(byte* key);

        void ReplaceKey();
        void ReplaceKey(byte* key);
        void ResetExtendedKey();
        byte* GetNextRoundKey();
};

class AES {
    int rounds;

    public:
        AES(int key_size);
        AES(int block_size, int key_size);
        void SetKey(byte* key);

        byte* Encrypt(byte* content);
        byte* Decrypt(byte* content);
};

namespace mathfuncs {
class MathError {};

byte GaloisByteMultiplication(byte p, byte q);
byte GaloisMultiplicativeInverse(byte p);
byte* GaloisPolynomialMultiplication(byte* p, byte* q);
byte AffineApplication(byte p, byte* affine_mat, byte affine_vec);
void XORByteArrays(byte* p, byte* q);
}

}