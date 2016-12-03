#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <vector>
#include <list>

template<typename TEdge>
class Graph {
private:
	unsigned int n;

protected:
    std::vector<std::list<TEdge*>> edges;
public:
    typedef typename std::list<TEdge*>::iterator EdgeIterator;

    typedef TEdge EdgeType;

    void clear();

    void init(unsigned int _n);

    unsigned int size();

    Graph(void) {}

	Graph(unsigned int _n);

    void addEdge(TEdge* edge);

    std::list<TEdge*>& getEdgesFrom(unsigned int v);
};

template<typename TEdge>
void readGraph(Graph<TEdge> & g);


// IMPLEMENTATIONS :


template<typename TEdge>
Graph<TEdge>::Graph(unsigned int _n) {
    n = _n;
    edges.resize(n);
}

template<typename TEdge>
void Graph<TEdge>::clear() {}

template<typename TEdge>
void Graph<TEdge>::init(unsigned int _n) {
    n = _n;
    edges.resize(n);
}

template<typename TEdge>
unsigned int Graph<TEdge>::size() {
    return n;
}

template<typename TEdge>
void Graph<TEdge>::addEdge(TEdge* edge) {
    unsigned int from = edge -> getFrom();
    edges[from].push_back(edge);
}

template<typename TEdge>
std::list<TEdge*>& Graph<TEdge>::getEdgesFrom(unsigned int v) {
    return edges[v];
}

template<typename TEdge>
void readGraph(Graph<TEdge> & g) {
    long long a, b, c;
    unsigned int n, m;
    std::cin >> n >> m;
    g.clear();
    g.init(n);
    for (unsigned int i = 0; i < m; ++i) {
        std::cin >> a >> b >> c;
        g.addEdge(new TEdge(--a, --b, c));
    }

}

#endif

