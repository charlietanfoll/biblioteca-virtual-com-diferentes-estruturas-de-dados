#include <string>
#include <memory>
using namespace std;

struct Node {
    int isbn;
    int ano_publicacao;
    string titulo;
    string autor;
    unique_ptr<Node> left;
    unique_ptr<Node> right;
};
