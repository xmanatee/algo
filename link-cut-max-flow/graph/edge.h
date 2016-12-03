#ifndef _EDGE_H_
#define _EDGE_H_

class Edge;

class Edge {
private:
    unsigned int from, to;
public:
    Edge(unsigned int _from, unsigned int _to);

    unsigned int getFrom();

    unsigned int getTo();

};

#endif
