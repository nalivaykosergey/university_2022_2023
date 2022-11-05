#include <iostream>
#include <string>
#include <exception>
#include <cstring>

using std::cout, std::cin, std::string;

class BigUnsigned {

private:
    size_t base;
    size_t size;
    char * number;
    char operator[](int i) const {
        return number[i - 1];
    }
public:
    BigUnsigned(const char * number,  size_t base = 10) {
        int i = 0, j = 0;

        while(number[i] != '\0' && number[i]== '0') {
            ++i;
        }
        if(number[i] == '\0') {
            this->number = new char[2]{'0'};
            this->number[1] = '\0';
            size = 1;
        } else {
            size = strlen(number);
            this->number = new char[size - i + 1]{'0'};
            this->number[size - i] = '\0';
            while(i < size) {
                this->number[j] = number[i];
                ++j;
                ++i;
            }
            size = size - (size - j);
        }

        this->base = base;
    }
    BigUnsigned& operator = (const BigUnsigned & right) {
        if(this == &right)
            return *this;
        base = right.base;
        size = right.size;
        delete [] number;
        number = new char[size + 1]{'0'};
        number[size] = '\0';
        for(int i = 0; i < size; ++i)
            number[i] = right.number[i];
        return *this;
    }
    BigUnsigned(const BigUnsigned & right) {
        base = right.base;
        size = right.size;
        number = new char[size + 1]{'0'};
        number[size] = '\0';
        for (int i = 0; i <= size; ++i)
            number[i] = right.number[i];
    }

    size_t get_base() const {
        return base;
    }
    size_t get_size() const {
        return size;
    }

    char * get_number() {
        return number;
    }
    ~BigUnsigned() {
        delete[] number;
    }
    bool operator == (const BigUnsigned & right) const {
        if(size != right.size)
            return false;
        else {
            for(int i = 0; i < size; ++i) {
                if(number[i] != right.number[i])
                    return false;
            }
            return true;
        }
    }
    bool operator < (const BigUnsigned & right) const {
        if (size < right.size)
            return true;
        else if (size > right.size)
            return false;
        else {
            for(int i = 0; i < size; ++i) {
                if(number[i] == right.number[i])
                    continue;
                if(number[i] < right.number[i])
                    return true;
                else
                    return false;
            }
            return false;
        }
    }

    /////Реализация алгоритмов

    BigUnsigned operator + (const BigUnsigned & right) const {
        if (this->base != right.base)
            throw std::invalid_argument("Разные базы слагаемых");
        int i = size - 1, j = right.size - 1, z, k = 0;
        size_t mx_size = std::max(size, right.size);
        z = mx_size;
        char * new_number = new char[mx_size + 2]{'0'};
        new_number[mx_size] = '\0';
        for(; i >= 0 && j >= 0; --j, --i, --z) {
            int n1 = number[i] - 48, n2 = right.number[j] - 48;
            new_number[z] = static_cast<char>((n1 + n2 + k) % base + 48);
            k = (n1 + n2 + k) / static_cast<int>(base);
        }
        while(i >= 0) {
            int n1 = number[i] - 48;
            new_number[z] = static_cast<char>((n1 + k) % base + 48);
            k = (n1 + k) / static_cast<int>(base);
            --z;
            --i;
        }
        while(j >= 0) {
            int n1 = right.number[j] - 48;
            new_number[z] = static_cast<char>((n1 + k) % base + 48);
            k = (n1 + k) / static_cast<int>(base);
            --z;
            --j;
        }
        new_number[0] = static_cast<char>(k + 48);
        BigUnsigned tmp(new_number, base);
        delete [] new_number;
        return tmp;
    }

    BigUnsigned operator - (const BigUnsigned & right) {

        if (this->base != right.base)
            throw std::invalid_argument("Разные базы слагаемых");
        if ((*this) < right) {
            throw std::invalid_argument("Уменьшаемое должно быть больше, чем вычитаемое");
        }

        int i = size - 1, j = right.size - 1, z, k = 0;
        size_t mx_size = std::max(size, right.size);
        z = mx_size - 1;
        char * new_number = new char[mx_size + 1]{'0'};
        new_number[mx_size] = '\0';
        for(; i >= 0 && j >= 0; --j, --i, --z) {
            int n1 = number[i] - 48 + base, n2 = right.number[j] - 48;
            new_number[z] = static_cast<char>((n1 - n2 + k) % base + 48);
            k = ((n1 - n2 + k) / base) == 0 ? -1 : 0;
        }

        while(i >= 0) {
            int n1 = base + number[i] - 48;
            new_number[z] = static_cast<char>((n1 + k) % base + 48);
            k = ((n1 + k) / base) == 0 ? -1 : 0;
            --z;
            --i;
        }
        BigUnsigned tmp(new_number, base);
        delete [] new_number;
        return tmp;
    }
    BigUnsigned operator * (const BigUnsigned & right) {
        if (this->base != right.base)
            throw std::invalid_argument("Разные базы слагаемых");

        size_t n = size, m = right.size;
        char * new_number = new char[n+m + 1];
        new_number[n+m] = '\0';
        int j = m;
        for(; j < m + n; ++j)
            new_number[j] = '0';
        j = m - 1;
        while(j >= 0) {
            if(right.number[j] != '0') {
                int i = n - 1, k = 0, t;
                while(i >= 0) {
                    int n1  = number[i] - 48, n2 = right.number[j] - 48, n3 = new_number[i + j + 1] - 48;
                    t = n1 * n2 + n3 + k;
                    new_number[i + j + 1] = static_cast<char>((t % base) + 48);
                    k = t / static_cast<int>(base);
                    --i;
                }
                new_number[j] = static_cast<char>(k + 48);
            } else {
                new_number[j] = '0';
            }
            --j;
        }
        BigUnsigned tmp(new_number, base);
        delete [] new_number;
        return tmp;
    }

};


int main() {
    string n1_s, n2_s;
    cout << "Введите число n1: ";
    cin >> n1_s;
    cout << "Введите число n2: ";
    cin >> n2_s;
    BigUnsigned n1(n1_s.c_str(), 10), n2(n2_s.c_str(), 10);
    cout << "Число " << n1.get_number() << " * " << n2.get_number() << " = " << (n1 * n2).get_number() << "\n";
    cout << "Число " << n1.get_number() << " - " << n2.get_number() << " = " << (n1 - n2).get_number() << "\n";
    cout << "Число " << n1.get_number() << " + " << n2.get_number() << " = " << (n1 + n2).get_number() << "\n";
}



