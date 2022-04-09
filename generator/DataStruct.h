#ifndef SUDOKUSOLVERDLX_DATASTRUCT_H
#define SUDOKUSOLVERDLX_DATASTRUCT_H


#include <iostream>
#include <vector>


class DataStruct {
    struct Node {
        int value;
        int row;
        int column;
        Node *header;
        Node *up;
        Node *down;
        Node *right;
        Node *left;
    };
    Node *root;

    static void cover(Node *&column);

    static void uncover(Node *&column);

    Node *min_column();

    std::vector<Node *> solution;

public:
    std::vector<std::vector<Node *>> all_solutions{};

    explicit DataStruct(const std::vector<std::vector<bool>> &Problem);

    void search(int k);

    ~DataStruct();

};


#endif //SUDOKUSOLVERDLX_DATASTRUCT_H
