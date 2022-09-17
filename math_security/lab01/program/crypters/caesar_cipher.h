#ifndef CAESAR_CIPHER_H
#define CAESAR_CIPHER_H

#include <map>
#include <string>
#include <sstream>
#include <algorithm>

namespace crypters {
    class Caesar_Cipher {
        private:
            static const int ALPHABET_SIZE = 95;
            Caesar_Cipher() = delete;
        public:
            static std::string crypt(const std::string & text, int k);
    };
}

#endif
