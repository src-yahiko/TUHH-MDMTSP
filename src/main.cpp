#include "graph.cpp"

int main() {
    Graph g = Graph(5);
    Node a = g.addNode(1, 1);
    Node b = g.addNode(2, 2);
    double d = g.addEdge(a, b);
    std::cout << a.id << std::endl;
    std::cout << b.id << std::endl;
    std::cout << d << std::endl;
    return 0;
}