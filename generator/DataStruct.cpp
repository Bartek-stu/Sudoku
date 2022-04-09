#include "DataStruct.h"
#include <vector>

using namespace std;


DataStruct::DataStruct(const vector<vector<bool>> &Problem) : root(new Node{0, 0, 0}) {
    size_t width = Problem[0].size();
    size_t heigth = Problem.size();

    Node *current = root;
    for (int i = 0; i < width; ++i) {
        current->right = new Node{0, 0, i + 1};
        current->right->header = current->right;
        current->right->left = current;
        current = current->right;
    }
    current->right = root;
    root->left = current;

    vector<vector<Node *>> vec{(heigth)};
    current = root;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < heigth; ++j) {
            if (Problem[j][i]) {
                while (current->column != i + 1) {
                    current = current->right;
                }
                Node *temp = current;
                while (current->down) {
                    current = current->down;
                }
                current->down = new Node{1, j + 1, i + 1, temp};
                current->down->up = current;
                vec[j].push_back(current->down);
            }
            current = root;
        }
    }

    current = root->right;
    for (int i = 0; i < width; ++i) {
        Node *temp = current;
        int x{};
        while (current->down) {
            current = current->down;
            ++x;
        }
        current->down = temp;
        temp->up = current;
        current->header->value = x;
        current = temp->right;
    }

    for (auto &x: vec) {
        if (!x.empty()) {
            for (int j = 0; j < x.size() - 1; ++j) {
                x[j]->right = x[j + 1];
                x[j]->right->left = x[j];
            }
            x[x.size() - 1]->right = x[0];
            x[0]->left = x[x.size() - 1];
        }
    }
}

DataStruct::~DataStruct() {
    auto current = root->right;
    while (current != root) {
        auto temp = current->down;
        for (int i = 0; i < current->value + 1; ++i) {
            if (temp->up != current) {
                delete temp->up;
            }
            temp = temp->down;
        }
        current = current->right;
    }
    current = root->right;
    while (current != root) {
        auto next = current->right;
        delete current;
        current = next;
    }
    delete root;
}

void DataStruct::cover(Node *&column) {
    Node *current = column->header;
    current->right->left = current->left;
    current->left->right = current->right;

    current = column->header->down;
    while (current != column->header) {
        Node *current2 = current->right;
        while (current2 != current) {
            current2->up->down = current2->down;
            current2->down->up = current2->up;
            current2->header->value -= 1;
            current2 = current2->right;
        }
        current = current->down;
    }
}

void DataStruct::uncover(Node *&column) {
    Node *current = column->header->up;
    while (current != column->header) {
        Node *current2 = current->left;
        while (current2 != current) {
            current2->up->down = current2;
            current2->down->up = current2;
            current2->header->value += 1;
            current2 = current2->left;
        }
        current = current->up;
    }

    current = column->header;
    current->right->left = current;
    current->left->right = current;

}

DataStruct::Node *DataStruct::min_column() {
    Node *current = root->right;
    Node *min_column = root->right;
    unsigned int min_val = current->value;
    size_t tmp{};
    while (current != root) {
        if (current->value < min_val) {
            min_val = current->value;
            min_column = current;
        }
        tmp++;
        current = current->right;
    }

    return min_column;
}

void DataStruct::search(int k) {
    // modified DLX algorithm, which breaks after finding more than one solution
    if (all_solutions.size() < 2) {
        if (root->right == root) {
            all_solutions.push_back(solution);
            return;
        }
        Node *c = min_column();

        cover(c);
        Node *row = c->down;
        while (row != c->header) {
            solution.push_back(row);
            Node *ccr = row->right;
            while (ccr != row) {
                cover(ccr);
                ccr = ccr->right;
            }
            search(k + 1);
            solution.pop_back();
            c = row->header;
            Node *ccl = row->left;
            while (ccl != row) {
                uncover(ccl);
                ccl = ccl->left;
            }
            row = row->down;
        }
        uncover(c);
    } else {
        return;
    }
}



