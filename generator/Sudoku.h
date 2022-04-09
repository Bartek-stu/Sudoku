#ifndef SUDOKUSOLVERDLX_SUDOKU_H
#define SUDOKUSOLVERDLX_SUDOKU_H

#include <vector>
#include <array>
#include <string>
#include "DataStruct.h"

class Sudoku {
private:
    std::array<std::array<int, 9>, 9> tab{};

    bool check(size_t x, size_t y);

    void fill_first_values();

    void convert(DataStruct &dancingLinks);

    void save_to_file(std::string && filename, std::ios_base::openmode mode);

    void remove_values();

public:

    void print() const;

    Sudoku();

    friend void initialize(std::vector<std::vector<bool>> &sudoku_problem, Sudoku obj);

};


#endif //SUDOKUSOLVERDLX_SUDOKU_H
