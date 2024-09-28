#include "aes.h"

namespace aes::mathfuncs {

byte GaloisMuliplication(byte p, byte q) {
    return p;
}

byte GaloisEuclidExtended(byte a0, byte b0) {
    byte a = a0;
    byte b = b0;
    byte aa = 1;
    byte ab = 0;
    byte ba = 0;
    byte bb = 1;

    while (1) {
        byte q = a / b;
        if (a == GaloisMuliplication(b,q)) {

        }
    }
    return a0;
}

byte GaloisMultiplicativeInverse(byte p) {
    return p;
}

// In-place multiplication
void GaloisPolynomialMultiplication(byte* p, byte* q, byte* modulus) {
    
}

byte AffineApplication(byte p, byte* affine_mat, byte affine_vec) {
    // matmul: XOR together all the bitwise ANDs
    // addition; XOR in the vector?
    return p;
}

void XORByteArrays(byte* p, byte* q) {

}

}
