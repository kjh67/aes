namespace aes{
// BLOCK SIZES ETC TO BE GIVEN IN BITS

typedef unsigned char byte;

class InitialisationError {};

class State {
    // allow AES class to access private attributes
    friend class AES;

    int nb;
    byte* state;
    bool inverse;

    public:
        State();
        State(int block_size);

        void SetState(byte* content);
        byte* GetState();
        void SetInverseCipher(bool inv);

        void SubBytes();
        void ShiftRows();
        void MixColumns();
        void AddRoundKey(byte* round_key);
};

class Key {
    // allow AES class to access private attributes
    friend class AES;

    int nk;
    bool inverse_schedule;
    int round_key_size;
    byte* secret;
    byte* expanded_key;

    // private default constructor
    Key();

    void GenerateKey(int key_length);
    void GenerateExpandedKey();

    public:
        Key(int key_length, int block_length);
        Key(int key_length, int block_length, byte* key);

        void ReplaceKey();
        void ReplaceKey(byte* key);
        void ResetExpandedKey();
        void SetInverseKeySchedule(bool inv);
        void GetNextRoundKey(byte* container);
        void GetKey(byte* container);
};

class AES {
    int rounds;
    State* state;
    Key* key;

    public:
        AES(int key_size, int block_size);
        ~AES();
        void SetKey(byte* key);
        void SetKey();

        byte* Encrypt(byte* content);
        byte* Decrypt(byte* content);
};

namespace mathfuncs {
class MathError {};

byte GaloisByteMultiplication(byte p, byte q);
byte GaloisMultiplicativeInverse(byte p);
void GaloisPolynomialMultiplication(byte* p, byte* q, byte* result);
byte AffineApplication(byte p, byte* affine_mat, byte affine_vec);
}

}