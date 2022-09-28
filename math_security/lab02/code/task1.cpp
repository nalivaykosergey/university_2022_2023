#include <iostream>
#include "crypters/cardano_grid.h"

using std::cout, std::endl, std::cin, std::string;
using crypters::Cardano_Grid;

int main() {
    string text, key;
    int k;
    cout << "Type text: ";
    getline(cin, text);
    cout << "Type key: ";
    getline(cin, key);
    cout << "Type k: ";
    cin >> k;
    cout << "Your input: " << text << "\n";
    cout << Cardano_Grid::crypt(text, key, k) << "\n";

    return 0;
}
