#ifndef CARDANO_GRID_H
#define CARDANO_GRID_H

#include <string>
#include <vector>
#include <array>
#include <map>
#include <utility>
#include <iostream>
#include <sstream>

namespace crypters {
    typedef std::vector<std::vector<int>> matrix_t;
    typedef std::vector<std::vector<std::pair<bool, int>>> grid_t;
    class Cardano_Grid {
    private:
        Cardano_Grid() = delete;
        static grid_t generate_grid(const matrix_t & matrix, int k);
        static matrix_t rotate_matrix(const matrix_t &matr);
        static void rotate_grid(grid_t &grid);
        static matrix_t make_matrix(int k);
        static matrix_t fill_data(const std::string &text,
                                  const matrix_t & matrix,
                                  grid_t & grid);
    public:
        static std::string crypt(const std::string & text,
                                 const std::string & key, int k);
    };
}



#endif
