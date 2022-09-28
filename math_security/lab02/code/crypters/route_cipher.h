#ifndef ROUTE_CIPHER_H
#define ROUTE_CIPHER_H

#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <stdexcept>

namespace crypters {
    class Route_Cipher {
    private:
        Route_Cipher() = delete;
    public:
        static std::string crypt(const std::string & text, const std::string & key);
    };
}

#endif
