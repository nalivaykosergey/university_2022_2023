#include <iostream>
#include <algorithm>
#include <ctime>
#include <cmath>

#define TEST_ITERATIONS 100

using std::cout, std::endl, std::cin, std::string;

int euclidean_algorithm(int a, int b);
int jacobi(int a, int b);
bool ferma_test(ulong n);
bool s_sh_test(ulong n);
bool m_r_test(ulong n);
void tester(ulong n, bool(*func)(ulong n), const string & test_name);

int main() {
    ulong n;
    cout << "Введите n: ";
    cin >> n;

    tester(n, ferma_test, "Тест Ферма");
    tester(n, s_sh_test, "Тест Соловэя-Штрассена");
    tester(n, m_r_test, "Тест Миллера-Рабина");


    return 0;
}

void tester(ulong n, bool(*func)(ulong n), const string & test_name) {
    cout << test_name << ":\n";
    if(func(n) == 1)
        cout << "\tЧисло " << n << ", вероятно, простое\n";
    else
        cout << "\tЧисло " << n << " составное\n";
}

int euclidean_algorithm(int a, int b) {
    return b == 0 ? a : euclidean_algorithm(b, a % b);
}

int jacobi(int a, int b) {

    int g;
    if (a >= b) a %= b;
    if (a == 0) return 0;
    if (a == 1) return 1;
    if (a < 0) {
        if ((b-1)/2 % 2 == 0)
            return jacobi(-a,b);
        else
            return -jacobi(-a,b);
    }
    if (a % 2 == 0) {
        if (((b*b - 1)/8) % 2 == 0)
            return jacobi(a/2,b);
        else
            return -jacobi(a/2,b);
    }
    g = euclidean_algorithm(a,b);
    if (g == a)
        return 0;
    else if (g != 1)
        return jacobi(g,b)*jacobi(a/g,b);

    else if (((a-1)*(b-1)/4) % 2 == 0)
        return jacobi(b,a);
    else
        return -jacobi(b,a);
}

bool ferma_test(uint_fast64_t n) {
    if (n < 5)
        throw std::invalid_argument("n >= 5!");
    if (n % 2 == 0)
        return false;
    std::srand(std::time(nullptr));
    for(int i = 0; i < TEST_ITERATIONS; ++i) {
        uint_fast64_t a = (std::rand() % (n - 3) + 2);
        uint_fast64_t r = 1;
        for(int j = 1; j < n; ++j) r *= a;
        r %= n;
        if(r == 1)
            return true;
    }
    return false;
}

bool s_sh_test(ulong n) {
    if (n < 5)
        throw std::invalid_argument("n >= 5!");
    if (n % 2 == 0)
        return false;
    std::srand(std::time(nullptr));
    for(int i = 0; i < TEST_ITERATIONS; ++i) {
        uint_fast64_t a = (std::rand() % (n - 3) + 2);
        if(euclidean_algorithm(a, n) > 1)
            return false;
        uint_fast64_t r = 1;
        for(int j = 1; j <= ((n - 1)/2); ++j)
            r *= a;
        int s = jacobi(a, n);

        if(((r - s) % n) != 0)
            return false;

    }

    return true;
}



ulong mulmod(ulong a, ulong b, ulong mod)
{
    ulong x = 0,y = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}


ulong modulo(ulong base, ulong exponent, ulong mod)
{
    ulong x = 1;
    ulong y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}

bool m_r_test(ulong p)
{
    if (p < 2)
    {
        return false;
    }
    if (p != 2 && p % 2==0)
    {
        return false;
    }
    ulong s = p - 1;
    while (s % 2 == 0)
    {
        s /= 2;
    }
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        ulong a = rand() % (p - 1) + 1, temp = s;
        ulong mod = modulo(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1)
        {
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0)
        {
            return false;
        }
    }
    return true;
}
