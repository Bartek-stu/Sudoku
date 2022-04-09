#include "Sudoku.h"
#include "DataStruct.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>
#include <vector>

using namespace std;

void Sudoku::print() const {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (tab[i][j]) {
                cout << tab[i][j];
            } else {
                cout << "x";
            }
            if (!((j + 1) % 3)) cout << "    ";
        }
        cout << endl;
        if (!((i + 1) % 3)) cout << endl;
    }
}

bool Sudoku::check(size_t x, size_t y) {
    // this function checks whether randomly selected value satisfies conditions
    // to be a part of the solution

    int value = tab[y][x];
    // check row and column
    for (int i = 0; i < 9; ++i) {
        if (i != x && tab[y][i] == value ||
            i != y && tab[i][x] == value)
            return false;
    }
    size_t yy = y - y % 3;
    size_t xx = x - x % 3;
    // check box
    for (size_t i = yy; i < yy + 3; ++i) {
        for (size_t j = xx; j < xx + 3; ++j) {
            if (i != y && j != x && tab[i][j] == value)
                return false;
        }
    }
    return true;
}

void Sudoku::fill_first_values() {
    // this function fills sudoku with 3 initial values, based on which
    // complete sudoku is generated with the search algorithm
    random_device rd;
    uniform_int_distribution<size_t> range(0, 8);

    for (int i = 0; i < 3;) {
        size_t pos_x = range(rd);
        size_t pos_y = range(rd);
        int value = range(rd) + 1;
        if (!tab[pos_y][pos_x]) {
            tab[pos_y][pos_x] = value;
            if (!check(pos_x, pos_y)) {
                tab[pos_y][pos_x] = 0;
            } else {
                ++i;
            }
        }
    }
}


void Sudoku::convert(DataStruct &dancingLinks){
    // this function is responsible for converting solution from dancing links structure to
    // corresponding fields of the sudoku array
    for (auto &solution: dancingLinks.all_solutions) {
        vector<int> v{};
        for (auto node: solution)
            v.push_back(node->row);
        sort(v.begin(), v.end());
        auto it = v.begin();
        for (int j = 0; j < v.size(); ++j) {
            if (it[j] == 730) v.erase(it + j);
        }
        int l{};
        for (int k = 0; k < 9; ++k) {
            for (int m = 0; m < 9; ++m) {
                int value = ((v[l] + 8) % 9) + 1;
                if (!tab[k][m]) {
                    tab[k][m] = value;
                    ++l;
                }
            }
        }
    }
}

void Sudoku::remove_values() {
    //this function removes randomly selected values so that sudoku still has one unique solution
    //well, otherwise it wouldn't be a sudoku
    vector<pair<size_t, size_t>> positions;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            positions.emplace_back(make_pair(i, j));
        }
    }

    shuffle(positions.begin(), positions.end(), std::mt19937(std::random_device()()));

    for (const auto &position: positions) {
        auto value = tab[position.first][position.second];
        if (value) {
            tab[position.first][position.second] = 0;
            vector<vector<bool>> sudoku_problem{};
            initialize(sudoku_problem, *this);
            DataStruct dancingLinks(sudoku_problem);
            dancingLinks.search(0);
            if (dancingLinks.all_solutions.size() != 1) {
                tab[position.first][position.second] = value;
            }
        }
    }
}

void Sudoku::save_to_file(string &&filename, ios_base::openmode mode) {
    // this function saves solution to file, so it can be used by gui in python
    fstream file;
    if(file.good()){
        file.open("sudoku.txt", mode);
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                file << tab[i][j] << " ";
            }
            file << endl;
        }
        file.close();
    }
}

Sudoku::Sudoku() {
    fill_first_values();
    vector<vector<bool>> sudoku_problem{};
    initialize(sudoku_problem, *this);
    DataStruct dancingLinks(sudoku_problem);
    dancingLinks.search(0);
    convert(dancingLinks);
    save_to_file("sudoku.txt", ios::out);
    remove_values();
    save_to_file("sudoku.txt", ios::app);
}
