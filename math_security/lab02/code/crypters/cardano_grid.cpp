#include "cardano_grid.h"
namespace crypters {

    grid_t Cardano_Grid::generate_grid(const matrix_t & matrix, int k) {
        int l = 2 * k;
        grid_t grid(l, std::vector<std::pair<bool, int>>(l));
        for(int z = 1; z <= k * k; ++z) {
            bool from_bottom = rand() % 2 - 1;
            bool from_right = rand() % 2 - 1;
            bool flag = false;
            if(from_bottom) {
                if(from_right) {
                    for(int i = l - 1; i >=0 && !flag; --i) {
                        for(int j = l - 1; j >= 0; --j) {
                            if(matrix[i][j] == z) {
                                grid[i][j].first = true;
                                grid[i][j].second = z;
                                flag = true;
                                break;
                            }
                        }
                    }
                } else {
                    for(int i = l - 1; i >=0 && !flag; --i) {
                        for(int j = 0; j < l; ++j) {
                            if(matrix[i][j] == z) {
                                grid[i][j].first = true;
                                grid[i][j].second = z;
                                flag = true;
                                break;
                            }
                        }
                    }
                }
            } else {
                if(from_right) {
                    for(int i = 0; i < l && !flag; ++i) {
                        for(int j = l - 1; j >= 0; --j) {
                            if(matrix[i][j] == z) {
                                grid[i][j].first = true;
                                grid[i][j].second = z;
                                flag = true;
                                break;
                            }
                        }
                    }
                } else {
                    for(int i = 0; i < l && !flag; ++i) {
                        for(int j = 0; j < l; ++j) {
                            if(matrix[i][j] == z) {
                                grid[i][j].first = true;
                                grid[i][j].second = z;
                                flag = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
        return grid;
    }

    static void print_grid(const grid_t & grid) {
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[0].size(); ++j) {
                if(grid[i][j].first)
                    std::cout << grid[i][j].second << " ";
                else
                    std::cout << "* ";
            }
            std::cout << "\n";
        }
    }
    matrix_t Cardano_Grid::rotate_matrix(const matrix_t &matr) {
        int r = matr.size();
        int c = matr[0].size();
        matrix_t rotated(r, std::vector<int>(c));
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                rotated[j][i] = matr[r-i-1][j];
        return rotated;
    }

    void Cardano_Grid::rotate_grid(grid_t &grid) {
        int r = grid.size();
        int c = grid[0].size();
        grid_t rotated(r, std::vector<std::pair<bool, int>>(c));
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                rotated[j][i] = grid[r-i-1][j];
        grid = std::move(rotated);
    }

    matrix_t Cardano_Grid::make_matrix(int k) {
        int l = k * 2;

        matrix_t upper_left(k, std::vector<int>(k));
        for(int i = 0, z = 1; i < k; ++i) {
            for(int j = 0; j < k; ++j, ++z)
                upper_left[i][j] = z;
        }

        matrix_t upper_right = rotate_matrix(upper_left);
        matrix_t bottom_right = rotate_matrix(upper_right);
        matrix_t bottom_left = rotate_matrix(bottom_right);


        matrix_t fully_matrix(l, std::vector<int>(l));

        for(int i = 0, r = 0; i < k; ++i, ++r) {
            for(int j = 0, c = 0; j < k; ++j, ++c)
                fully_matrix[r][c] = upper_left[i][j];
        }

        for(int i = 0, r = 0; i < k; ++i, ++r) {
            for(int j = 0, c = k; j < k; ++j, ++c)
                fully_matrix[r][c] = upper_right[i][j];
        }

        for(int i = 0, r = k; i < k; ++i, ++r) {
            for(int j = 0, c = 0; j < k; ++j, ++c)
                fully_matrix[r][c] = bottom_left[i][j];
        }

        for(int i = 0, r = k; i < k; ++i, ++r) {
            for(int j = 0, c = k; j < k; ++j, ++c)
                fully_matrix[r][c] = bottom_right[i][j];
        }
        return fully_matrix;
    }

    matrix_t Cardano_Grid::fill_data(const std::string &text, const matrix_t &matrix, grid_t &grid) {
        int r = grid.size();
        int c = grid[0].size();
        matrix_t data(r, std::vector<int>(c, '_'));

        std::cout << "Your grid: \n";
        print_grid(grid);


        for(int k = 0; k < 4; ++k) {

            for(int i = 0; i < r; ++i) {
                for(int j = 0; j < c; ++j) {
                    if(grid[i][j].first) {
                        data[i][j] = text[k * 4 + grid[i][j].second - 1];
                    }
                }
            }
            rotate_grid(grid);
        }
        return data;
    }


    std::string Cardano_Grid::crypt(const std::string &text, const std::string &key, int k) {
        if(key.size() != k * 2)
            throw std::invalid_argument("key must be same size as k * 2");
        int l = k*2;
        matrix_t matr = make_matrix(k);
        std::stringstream ss;


        grid_t grid = generate_grid(matr, k);

        auto data = fill_data(text, matr, grid);
        std::map<char, int> ordered_pass;
        for(int i = 0; i < key.size(); ++i) {
            if(!ordered_pass.insert({tolower(key[i]), i}).second)
                throw std::invalid_argument("all password characters must be unique");
        }
        for(auto element: ordered_pass) {
            int j = element.second;
            for(int i = 0; i < l; ++i) {
                ss << static_cast<char>(data[j][i]);
            }
        }

        return ss.str();
    }

}
