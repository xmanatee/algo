#ifndef _BFS_H_
#define _BFS_H_

#include <vector>
#include <algorithm>

template<typename TGraph>
class Bfs {
private:
    std::vector<int> queue, dist, from;

	int start, finish;

public:
    Bfs(TGraph *g, int _start, int _finish);

    static const int NOT_VISITED;

    std::vector<int> getPath();

    std::vector<int>& getDistances();

    bool gotTarget();
};


// IMPLEMENTATIONS :



template<typename TGraph>
const int Bfs<TGraph>::NOT_VISITED = -1;


template<typename TGraph>
bool Bfs<TGraph>::gotTarget() {
    return (dist[finish] != NOT_VISITED);
}


template<typename TGraph>
std::vector<int> Bfs<TGraph>::getPath() {
    std::vector<int> path;
    int current = finish;

    if (from[finish] == NOT_VISITED) {
        return path;
    }

    path.push_back(finish);
    while (current != start) {
        current = from[current];
        path.push_back(current);
    }

    std::reverse(path.begin(), path.end());

    return path;
}


template<typename TGraph>
std::vector<int>& Bfs<TGraph>::getDistances() {
    return dist;
}


template<typename TGraph>
Bfs<TGraph>::Bfs(TGraph *g, int _start, int _finish) {
    start = _start;
    finish = _finish;
    unsigned int n = g->size();
    queue.resize(n);
    dist.resize(n, NOT_VISITED);
    from.resize(n, NOT_VISITED);
    int l = 0;
    int r = 0;
    queue[0] = start;
    dist[start] = 0;
    from[start] = start;

    while (l <= r) {
        int v = queue[l];
        typename TGraph::EdgeIterator itEnd = g->getEdgesFrom(v).end();
        for (typename TGraph::EdgeIterator it = g->getEdgesFrom(v).begin(); it != itEnd; ++it) {
            int to = (*it)->getTo();
            if (dist[to] == NOT_VISITED) {
                queue[++r] = to;
                from[to] = v;
                dist[to] = dist[v] + 1;
            }
        }
        if (dist[finish] + 1)
            break;
        ++l;
    }
}

#endif
