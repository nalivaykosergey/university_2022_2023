#include "caesar_cipher.h"

namespace crypters{
    std::string Caesar_Cipher::crypt(const std::string &text, int k) {
        std::stringstream str;
        int index;
        k %= ALPHABET_SIZE;
        for(char i : text) {
            index = (i - ' ' + k) % ALPHABET_SIZE + ' ';
            str << static_cast<char>(index);
        }
        return str.str();
    }

}

