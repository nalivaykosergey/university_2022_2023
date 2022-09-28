#include <iostream>
#include "crypters/route_cipher.h"

using std::cout, std::endl, std::cin, std::string;
using crypters::Route_Cipher;

int main() {
    string text, key;
    cout << "Type text: ";
    getline(cin, text);
    cout << "Type key: ";
    getline(cin, key);
    cout << "Your input: " << text << "\n";
    cout << "Your Route Cipher: " << Route_Cipher::crypt(text, key) << "\n";

    return 0;
}
