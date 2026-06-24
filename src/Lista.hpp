#ifndef LISTAESTATICA_HPP
#define LISTAESTATICA_HPP

#include <cstdlib>
#include <iostream>
#include <string>

#include "Node.hpp"

typedef book ListEntry;

class ListaEstatica {
private:
    static const int MaxList = 100;
    int n;
    ListEntry entry[MaxList + 1];

public:
    ListaEstatica() : n(0) {}

    ~ListaEstatica() {
        std::cout << "Lista destruida\n";
    }

    bool empty() {
        return n == 0;
    }

    bool full() {
        return n == MaxList;
    }

    void insert(int isbn, int ano_publicacao, std::string &titulo, std::string &autor) {
        if (full()) {
            std::cout << "Lista cheia";
            std::abort();
        }

        ListEntry x;
        x.isbn = isbn;
        x.ano_publicacao = ano_publicacao;
        x.titulo = titulo;
        x.autor = autor;

        int p = 1;

        while (p <= n && entry[p].isbn < x.isbn) {
            p++;
        }

        for (int i = n; i >= p; i--) {
            entry[i + 1] = entry[i];
        }

        entry[p] = x;
        n++;
    }

    void remove(int isbn) {
        if (empty()) {
            std::cout << "Lista vazia" << std::endl;
            return;
        }

        int p = -1;
        for (int i = 1; i <= n; i++) {
            if (entry[i].isbn == isbn) {
                p = i;
                break;
            }
        }

        if (p == -1) {
            std::cout << "Livro com ISBN " << isbn << " não encontrado." << std::endl;
            return;
        }

        for (int i = p; i < n; i++) {
            entry[i] = entry[i + 1];
        }

        n--;
    }

    int search(int isbn) {
        int comparacoes = 0;

        for (int i = 1; i <= n; i++) {
            comparacoes++;

            if (entry[i].isbn == isbn) {
                return comparacoes;
            }

            if (entry[i].isbn > isbn) {
                std::cout << "Livro não encontrado" << std::endl;
                return comparacoes;
            }
        }

        std::cout << "Livro não encontrado" << std::endl;
        return comparacoes;
    }

    void print() {
        for (int i = 1; i <= n; i++) {
            std::cout
                << "ISBN: " << entry[i].isbn
                << " | Titulo: " << entry[i].titulo
                << " | Autor: " << entry[i].autor
                << " | Ano de Publicacao: " << entry[i].ano_publicacao
                << std::endl;
        }
    }
};

#endif