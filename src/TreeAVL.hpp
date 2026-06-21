#include <iostream>
#include <string>
#include <memory>
#include "NodeTree.hpp"

using namespace std;

class TreeAVL {
    public:
    void insert(int isbn, int ano_publicacao, std::string titulo, std::string autor) {
        Node novonode {isbn, ano_publicacao, titulo, autor, 0, nullptr, nullptr};
        Node *current = root.get();
        if (root == nullptr) {
            root = make_unique<Node>(novonode);
        } else {
            while (true) {
                if (isbn < current->isbn) {
                    if (current->left == nullptr) {
                        current->left = make_unique<Node>(novonode);
                        current->balance--;
                        break;
                    } else {
                        current = current->left.get();
                    }
                } 
            }
        }
    }
    void remove(int isbn) {
        // Implement the remove logic for AVL tree
    }
    void search(int isbn) {
        // Implement the search logic for AVL tree
    }

    private:
    
    unique_ptr<Node> root;


};
