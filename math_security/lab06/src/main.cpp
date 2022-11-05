#include <iostream>

#define ABS(a,b) (a > b ? a-b: b-a)

using std::cout, std::endl, std::cin, std::string;

uint64_t gcd(uint64_t a, uint64_t b);
uint64_t pollards_method(uint64_t n, uint64_t c, uint64_t (*f)(uint64_t));
uint64_t func(uint64_t i) {
    return (i * i + 5);
}


int main() {
    uint64_t n, c;
    cout << "Введите n: ";
    cin >> n;
    cout << "Введите c: ";
    cin >> c;
    uint64_t val = pollards_method(n, c, func);
    if (val == -1)
        cout << "Делитель не найден" << endl;
    else
        cout << "Нетривиальный делитель числа " << n << ": " << val << "\n";
    return 0;
}

uint64_t gcd(uint64_t a, uint64_t b) {
    return b == 0 ? a : gcd(b, a % b);
}

uint64_t pollards_method(uint64_t n, uint64_t c, uint64_t (*f)(uint64_t)) {

    uint64_t a = c, b = 1, p = -1;

    while (true) {
        uint64_t d;
        b = f(b) % n;
        a = f(f(a) % n) % n;
        d = gcd(ABS(a, b), n);
        if (d > 1 && d < n) {
            p = d;
        } else if (d == 1)
            continue;
        break;
    }
    return p;
}
