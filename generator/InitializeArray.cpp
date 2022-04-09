#include <vector>
#include "Sudoku.h"


using namespace std;

void initialize(vector<vector<bool>> &sudoku_problem, Sudoku obj) {
    // this function fills matrix (which represents sudoku as an exact cover problem) with 0s and 1s
    sudoku_problem.resize(729, vector<bool>(324));

    int k = -1;
    for (int i = 0; i < 729; ++i) {
        if (!((i) % 9)) k += 1;
        sudoku_problem[i][k] = true;
    }

    k = 0;
    for (int i = 0, j = -1; i < 728; ++i) {
        if (!(i % 81)) k += 9;
        sudoku_problem[i][i % 9 + 72 + k] = true;
        ++j;
    }
    sudoku_problem[728][80 + k] = true;

    for (int i = 0; i < 729; ++i) {
        sudoku_problem[i][i % 81 + 81 * 2] = true;
    }

    k = 0;
    for (int i = 0; i < 243; ++i) {
        if (!(i % 81)) k = 0;
        if (!((i) % 27)) k += 9;
        sudoku_problem[i][i % 9 + (81 * 3) + k - 9] = true;
    }
    k = 0;
    for (int i = 243; i < 486; ++i) {
        if (!(i % 81)) k = 0;
        if (!((i) % 27)) k += 9;
        sudoku_problem[i][i % 9 + (81 * 3) + k + 18] = true;
    }
    k = 0;
    for (int i = 486; i < 729; ++i) {
        if (!(i % 81)) k = 0;
        if (!((i) % 27)) k += 9;
        sudoku_problem[i][i % 9 + (81 * 3) + k + 45] = true;
    }

    bool *row[324]{};
    vector<int> to_delete{};

    int encounter{};
    for (auto &i: obj.tab) {
        for (int j: i) {
            if (j) {
                for (int l = 0; l < 324; ++l) {
                    row[l] += sudoku_problem[encounter * 9 + j - 1][l];
                }
                int x = (encounter * 9 + j - 1);
                x -= x % 9;
                to_delete.push_back(x);
            }
            encounter++;
        }
    }
    for (auto var: to_delete) {
        for (int i = var; i < var + 9; ++i) {
            for (auto &&x: sudoku_problem[i]) {
                x = false;
            }
        }
    }
    vector<bool> v;
    for (auto &i: row) {
        v.push_back(i);
    }
    sudoku_problem.push_back(v);
}