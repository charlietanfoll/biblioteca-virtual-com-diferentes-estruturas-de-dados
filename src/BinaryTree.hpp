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
        // 1. Ponteiro para o unique_ptr atual (começa na raiz)
        std::unique_ptr<Node>* curr = &root;

        // 2. Busca iterativa pelo nó alvo
        while (*curr && (*curr)->isbn != key) {
            if (key < (*curr)->isbn) {
                curr = &((*curr)->left);
            } else {
                curr = &((*curr)->right);
            }
        }

        // Se o ponteiro apontado for nulo, o livro não existe
        if (!*curr) {
            cout << "Livro com ISBN {" << key << "} não encontrado!" << endl;
            return;
        }

        // 3. Fase de Remoção
        // Caso 1 e 2: Sem filho à esquerda ou sem filho à direita
        if (!(*curr)->left) {
            // Se a direita também for nula (folha), *curr recebe nullptr e deleta o nó.
            // Se houver filho à direita, ele assume a posição corretamente.
            *curr = std::move((*curr)->right);
        }
        else if (!(*curr)->right) {
            *curr = std::move((*curr)->left);
        }
        // Caso 3: O nó possui dois filhos
        else {
            // Buscamos o Sucessor In-ordem (o menor nó da subárvore direita)
            // Também usamos um ponteiro para unique_ptr para fazer a remoção iterativa dele depois
            std::unique_ptr<Node>* succ = &((*curr)->right);
            while ((*succ)->left) {
                succ = &((*succ)->left);
            }

            // Copiamos os dados de negócio do sucessor para o nó atual
            (*curr)->isbn = (*succ)->isbn;
            (*curr)->ano_publicacao = (*succ)->ano_publicacao;
            (*curr)->titulo = std::move((*succ)->titulo);
            (*curr)->autor = std::move((*succ)->autor);

            // Como o sucessor é o MAIS À ESQUERDA daquela subárvore, ele NUNCA terá um filho esquerdo.
            // Portanto, para removê-lo, basta fazer o seu ponteiro direito assumir o lugar dele.
            *succ = std::move((*succ)->right);
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