#include <iostream>
#include <sstream>
#include <stdexcept>

using std::cout, std::endl, std::cin, std::string;

string gamma_encrypt(const string & text, const string & key) {
    std::stringstream ss;
    size_t key_size = key.size();
    if (text.size() < key.size())
        throw std::invalid_argument("the length of the key must be equal or less to the length of the text");
    for (size_t i = 0; i < text.size(); ++i) {
        ss << static_cast<char>((text[i] ^ key[i % key_size]));
    }
    return ss.str();
}

int main() {
    string text, key;
    cout << "Enter text: ";
    getline(cin, text);
    cout << "Enter key: ";
    getline(cin, key);
    string enc = gamma_encrypt(text, key);
    cout << "Your new text: " << enc << "\n";


    return 0;
}
