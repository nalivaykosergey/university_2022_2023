#include "route_cipher.h"

namespace crypters {
    std::string Route_Cipher::crypt(const std::string &text,
                                    const std::string &key) {

        if(text.size() < key.size())
            throw std::invalid_argument("text_length must be bigger then password_length");

        std::map<char, size_t> ordered_pass;
        for(size_t i = 0; i < key.size(); ++i) {
            if(!ordered_pass.insert({tolower(key[i]), i}).second)
                throw std::invalid_argument("all password characters must be unique");
        }

        size_t col = key.size();
        size_t row = text.size() / col + (text.size() % col == 0  ? 0: 1);
        std::vector<std::vector<char>> matrix(row, std::vector<char>(col, 'a'));
        std::stringstream ss;

        for(size_t i = 0, k = 0; i < row; ++i) {
            for(size_t j = 0; j < col && k < text.length(); ++j, ++k)
                matrix[i][j] = text[i * col + j];
        }

        for(auto element: ordered_pass) {
            size_t j = element.second;
            for(size_t i = 0; i < row; ++i) {
                ss << matrix[i][j];
            }
        }

        return ss.str();
    }
}
