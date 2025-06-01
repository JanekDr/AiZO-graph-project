#ifndef EDGE_HPP
#define EDGE_HPP


struct Edge{
    int from;
    int to;
    int weight;

    Edge(int f, int t, int w) : from(f), to(t), weight(w) {}

    Edge() : from(-1), to(-1), weight(-1) {}
};

#endif