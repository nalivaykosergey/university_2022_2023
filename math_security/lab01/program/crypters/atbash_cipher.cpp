#include "atbash_cipher.h"

namespace crypters {
    std::string Atbash_Cipher::crypt(const std::string &text) {
        std::stringstream str;
        int index;
        for(char i : text) {
            index = ALPHABET_SIZE - (i - ' ') - 1 + ' ';
            str << static_cast<char>(index);
        }
        return str.str();
    }
}


