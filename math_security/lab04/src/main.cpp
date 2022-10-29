#include <iostream>
#include <exception>
#include <algorithm>

using std::cout, std::endl, std::cin, std::string;

int euclidean_algorithm(int a, int b) {
    return b == 0 ? a : euclidean_algorithm(b, a % b);
}

int bin_euclidean_algorithm(int a, int b) {
    if (b <= 0 || a <= 0)
        throw std::invalid_argument("numbers must be greater than zero");
    if(a < b)
        std::swap(a, b);
    int g = 1;
    while ((a % 2 == 0) && ( b % 2 == 0))
    {
        a /= 2;
        b /= 2;
        g *= 2;
    }
    int u = a, v = b;
    while (u != 0)
    {
        while (u % 2 == 0) u /= 2;
        while (v % 2 == 0) v /= 2;
        if (u >= v)
            u -= v;
        else
            v -= u;
    }
    return v * g;
}

int ext_euclidean_algorithm(int a, int b,  int &x, int &y) {
    if (b < 0 || a < 0)
        throw std::invalid_argument("numbers must be greater than zero");
    if(a < b)
        std::swap(a, b);

    int s, d;

    if (b == 0) {
        d = a;
        x = 1;
        y = 0;
        return d;
    }

    d = ext_euclidean_algorithm(b,a % b,x,y);
    s = y;
    y = x - (a / b) * (y);
    x = s;
    return d;

}

int ext_bin_euclidean_algorithm(int a, int b, int &x, int &y) {
    if (b <= 0 || a <= 0)
        throw std::invalid_argument("numbers must be greater than zero");
    if(a < b)
        std::swap(a, b);

    int g = 1;
    while ((a % 2 == 0) && ( b % 2 == 0))
    {
        a /= 2;
        b /= 2;
        g *= 2;
    }
    int u = a, v = b, A = 1, B = 0, C = 0, D = 1;
    while (u != 0)
    {
        while (u % 2 == 0) {
            u /= 2;

            if ((A % 2 == 0) && (B % 2 == 0)) {
                A /= 2;
                B /= 2;
            } else {
                A = (A + b) / 2;
                B = (B - a) / 2;
            }
        }
        while (v % 2 == 0) {
            v /= 2;

            if ((C % 2 == 0) && (D % 2 == 0)) {
                C /= 2;
                D /= 2;
            } else {
                C = (C + b) / 2;
                D = (D - a) / 2;
            }
        }
        if (u >= v) {
            u -= v;
            A -= C;
            B -= D;
        }
        else {
            v -= u;
            C -= A;
            D -= B;
        }
    }
    x = C;
    y = D;
    return v * g;
}

int main() {
    int x, y, a, b;
    cout << "Введите число а: ";
    cin >> a;
    cout << "Введите число b: ";
    cin >> b;

    cout << "НОД (Алгоритм Евклида) = " << euclidean_algorithm(a, b) << "\n";
    cout << "НОД (Бинарный алгоритм Евклида) = " << bin_euclidean_algorithm(a, b) << "\n";

    cout << "НОД (Расширенный алгоритм Евклида) = "
        << ext_euclidean_algorithm(a, b, x, y) << "; ax * by = d, где ";
    cout << "x = " << x << ", y = " << y << "\n";

    cout << "НОД (Расширенный бинарный алгоритм Евклида) = "
        << ext_bin_euclidean_algorithm(a, b, x, y) << "; ax * by = d, где ";
    cout << "x = " << x << ", y = " << y << "\n";

    return 0;
}
