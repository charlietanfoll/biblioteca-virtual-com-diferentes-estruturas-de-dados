#include <iostream>
#include <string>
#include "BinaryTree.hpp"
#include "Lista.hpp"

using namespace std;

struct booktemp {
    int isbn = 0;
    int ano_publicacao = 0;
    string titulo;
    string autor;
};


int main() {
    BinaryTree tree;
    ListaEstatica lista;
    hashTable hash;
    auto input = 0;




    while (input != 4) {
        cout << "O que deseja fazer? " << endl;
        cout << endl;
        cout << "1. Inserir um novo Livro" << endl;
        cout << "2. Consultar um novo Livro" << endl;
        cout << "3. Remover um Livro" << endl;
        cout << "4. Sair" << endl;
        cout << endl;

        cin >> input;
        cin.ignore();

        switch (input) {
            case 1: {
                booktemp booktemp = {};
                cout << "ISBN: ";
                cin >> booktemp.isbn;
                cout << "Ano de Publicacao: ";
                cin >> booktemp.ano_publicacao;
                cin.ignore();
                cout << "Titulo do livro: ";
                getline(cin, booktemp.titulo);
                cout << "Autor: " << endl;
                getline(cin, booktemp.autor);
                tree.insert(booktemp.isbn, booktemp.ano_publicacao, booktemp.titulo, booktemp.autor);
                lista.insert(booktemp.isbn, booktemp.ano_publicacao, booktemp.titulo, booktemp.autor);
                hash.insert(booktemp.isbn, booktemp.ano_publicacao, booktemp.titulo, booktemp.autor);
                cout << endl;
                break;
            }
            case 2: {
                cout << "ISBN: ";
                booktemp booktemp = {};
                cin >> booktemp.isbn;
                int treeresult = tree.search(booktemp.isbn);
                cout << "Comparações feitas: " << treeresult << endl;
                int listresult = lista.search(booktemp.isbn);
                cout << "Comparações feitas: " << listresult << endl;
                int hashresult = hash.search(booktemp.isbn);
                cout << "Comparações feitas: " << hashresult << endl;
                cout << endl;
                break;
            }
            case 3: {
                cout << "ISBN: ";
                booktemp booktemp = {};
                cin >> booktemp.isbn;
                tree.remove(booktemp.isbn);
                lista.remove(booktemp.isbn);
                hash.remove(booktemp.isbn);
                cout << endl;
                break;
            }
        }
    }


    return 0;
}


