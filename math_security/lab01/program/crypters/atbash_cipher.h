#ifndef ATBASH_H
#define ATBASH_H

#include <string>
#include <sstream>

namespace crypters {
    class Atbash_Cipher {
    private:
        static const int ALPHABET_SIZE = 95;
        Atbash_Cipher() = delete;
    public:
        static std::string crypt(const std::string & text);
    };
}

#endif
