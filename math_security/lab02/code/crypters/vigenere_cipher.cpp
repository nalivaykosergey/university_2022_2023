#include "vigenere_cipher.h"

namespace crypters {
    std::string Vigenere_Cipher::crypt(const std::string &text, const std::string &key) {
        std::stringstream ss, nk;
        nk << key;
        int k = text.size() - key.size();
        for(int i = 0; i < k; ++i) {
            nk << (key[i % key.size()]);
        }
        std::string new_key{nk.str()};

        for(int i = 0; i < text.size(); ++i) {
            char letter = (text[i] - ' ' + new_key[i] - ' ') % 95 + ' ';
            ss << letter;
        }

        return ss.str();
    }
}
