#include <iostream>
#include "crypters/vigenere_cipher.h"

using std::cout, std::endl, std::cin, std::string;
using crypters::Vigenere_Cipher;

int main() {
    string text, key;
    cout << "Type text: ";
    getline(cin, text);
    cout << "Type key: ";
    getline(cin, key);
    cout << "Your input: " << text << "\n";
    cout << "Your Viegenere Cipher: " << Vigenere_Cipher::crypt(text, key) << "\n";

    return 0;
}
