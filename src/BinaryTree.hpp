#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "NodeTree.hpp"

using namespace std;

class BinaryTree {

    public:

    BinaryTree() = default;
    ~BinaryTree() = default;

    void search(int isbn) {
        Node * current = root.get();
        if (root == nullptr) {
            return;
        }
        while (current != nullptr) {
            if (current->isbn == isbn) {
                printnode(current);
                return;
            } else if (isbn < current->isbn) {
                current = current->left.get();
            } else {
                current = current->right.get();
            }
        }
        cout << "Livro não encontrado";
    };

    void insert(int key, int ano_publicacao, string & titulo, string & autor) {

        Node * current = root.get();

        if (root == nullptr) {
            root = make_unique<Node>(key, ano_publicacao, titulo, autor);
            return;
        }

        Node * parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (key < current->isbn) {
                current = current->left.get();
            } else if (key > current->isbn) {
                current = current->right.get();
            } else {
                cout << "Livro já existe" << endl;
                return;
            }
        }
        if (key < parent->isbn) {
            parent->left = make_unique<Node>(key, ano_publicacao, titulo, autor);
        } else {
            parent->right = make_unique<Node>(key, ano_publicacao, titulo, autor);
        }
    };

    void remove(int key) {
        // 1. Ponteiro para o unique_ptr raiz
        std::unique_ptr<Node>* current = &root;

        // 2. Busca iterativa pelo nó alvo
        while (*current && (*current)->isbn != key) {
            if (key < (*current)->isbn) {
                current = &((*current)->left);
            } else {
                current = &((*current)->right);
            }
        }

        // Se o ponteiro apontado for nulo, o livro não existe
        if (!*current) {
            cout << "Livro com ISBN {" << key << "} não encontrado!" << endl;
            return;
        }

        // 3. Fase de Remoção
        // Caso 1 e 2: Sem filho à esquerda ou sem filho à direita
        if (!(*current)->left) {
            // Se a direita também for nula (folha), *current recebe nullptr e deleta o nó.
            // Se houver filho à direita, ele assume a posição corretamente.
            *current = move((*current)->right);
        }
        else if (!(*current)->right) {
            *current = move((*current)->left);
        }
        // Caso 3: O nó possui dois filhos
        else {
            // Buscamos o Sucessor In-ordem (o menor nó da subárvore direita)
            // Também usamos um ponteiro para unique_ptr para fazer a remoção iterativa dele depois
            std::unique_ptr<Node>* successor = &((*current)->right);
            while ((*successor)->left) {
                successor = &((*successor)->left);
            }

            // Copiamos os dados de negócio do sucessor para o nó atual
            (*current)->isbn = (*successor)->isbn;
            (*current)->ano_publicacao = (*successor)->ano_publicacao;
            (*current)->titulo = move((*successor)->titulo);
            (*current)->autor = move((*successor)->autor);

            // Como o sucessor é o MAIS À ESQUERDA daquela subárvore, ele NUNCA terá um filho esquerdo.
            // Portanto, para removê-lo, basta fazer o seu ponteiro direito assumir o lugar dele.
            *successor = move((*successor)->right);
        }
    }

    private:

    unique_ptr<Node> root = nullptr;

    void printnode(Node * node) {
        if (node == nullptr) {
            return;
        }
        cout << "----Livro: " << endl;
        cout << "ISBN: " << node->isbn << endl;
        cout << "Titulo: " << node->titulo << endl;
        cout << "Autor: " << node->autor << endl;
        cout << "Ano de Publicacao: " << node->ano_publicacao << endl;
        cout << "----" << endl;
    }

};