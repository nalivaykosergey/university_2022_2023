#ifndef VIGENERE_CIPHER_H
#define VIGENERE_CIPHER_H

#include <string>
#include <sstream>


namespace crypters {
    class Vigenere_Cipher {
    private:
        Vigenere_Cipher() = delete;
    public:
        static std::string crypt(const std::string & text,
                                 const std::string & key);
    };

}

#endif
