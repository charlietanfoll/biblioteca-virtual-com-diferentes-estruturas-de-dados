#pragma once
#ifndef TABELAHASH_HPP
#define TABELAHASH_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include "Node.hpp"

typedef book HashEntry;
typedef int HashKey;


class TabelaHash {

private:

    struct No {
        HashEntry info;
        No* prox;
    };


    static const int P = 101;

    No* tabela[P];

    int n;


    int hash(HashKey chave) {
        return (chave % P);
    }


public:


    TabelaHash() {

        n = 0;

        for(int i = 0; i < P; i++) {
            tabela[i] = NULL;
        }
    }


    ~TabelaHash() {

        clear();

        std::cout << "Tabela destruida\n";
    }


    bool empty() {

        return n == 0;
    }


    bool full() {

        return false;
    }


    float loadFactor() {

        return (float)n / P;
    }


    int size() {

        return n;
    }


    int insert(int isbn, int ano_publicacao, std::string& titulo, std::string& autor) {
        int pos = hash(isbn);

        No* novo = new No;
        novo->info.isbn = isbn;
        novo->info.ano_publicacao = ano_publicacao;
        novo->info.titulo = titulo;
        novo->info.autor = autor;
        novo->prox = tabela[pos];

        tabela[pos] = novo;

        n++;

        return pos;
    }



    int search(HashKey k) {
        int comparacoes = 0;
        int pos = hash(k);
        No* atual = tabela[pos];

        while (atual != NULL) {
            comparacoes++;
            if (atual->info.isbn == k) {
                return comparacoes;
            }
            atual = atual->prox;
        }

        std::cout << "Livro nao encontrado" << std::endl;
        return comparacoes;
    }



    void remove(HashKey k) {


        int pos = hash(k);


        No* atual = tabela[pos];

        No* anterior = NULL;



        while(atual != NULL) {


            if(atual->info.isbn == k) {


                if(anterior == NULL)
                    tabela[pos] = atual->prox;

                else
                    anterior->prox = atual->prox;


                delete atual;

                n--;

                return;
            }


            anterior = atual;

            atual = atual->prox;
        }


        std::cout << "Elemento nao encontrado\n";
    }



    void clear() {


        for(int i = 0; i < P; i++) {


            No* atual = tabela[i];


            while(atual != NULL) {


                No* aux = atual;


                atual = atual->prox;


                delete aux;
            }


            tabela[i] = NULL;
        }


        n = 0;
    }



    void print() {


        for(int i = 0; i < P; i++) {


            No* atual = tabela[i];


            if(atual != NULL) {


                std::cout << "Posicao " << i << ": ";


                while(atual != NULL) {


                    std::cout
                    << atual->info.isbn
                    << " -> ";


                    atual = atual->prox;
                }


                std::cout << "NULL\n";
            }
        }
    }

};


#endif