#include <iostream>
#include "crypters/caesar_cipher.h"
#include "crypters/atbash_cipher.h"

using std::cout, std::endl, std::cin, std::string;
using crypters::Caesar_Cipher, crypters::Atbash_Cipher;


int main() {
    string text;
    getline(cin, text);
    cout << "Your input: " << text << "\n";
    cout << "Caesar cipher for:\n";
    for(int i = 0; i < 25; ++i) {
        cout << "\tShift = " << i << ": " << Caesar_Cipher::crypt(text, i) << "\n";
    }

    cout << "Atbash cipher: " << Atbash_Cipher::crypt(text) << "\n";

    return 0;
}