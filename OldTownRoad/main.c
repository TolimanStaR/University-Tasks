#include <stdio.h>
#include <stdlib.h>

#include "header.h"


int main() {

     puts("Please enter a two integers: N and K, \n"
          "where N is number of vertexes, and K is number of edges.");

     int n, k;
     scanf("%d%d", &n, &k);

     Edge *graph;
     graph = (Edge *) calloc(k, sizeof(Edge));

     puts("Please enter a three digits (a, b, c) K times, \n"
          "where a and b is numbers of connected vertexes, and c is cost of edge between them.");

     for (int i = 0; i < k; ++i)
          scanf("%d%d%d", &graph[i].firstVertex, &graph[i].secondVertex, &graph[i].cost);

     Edge *newGraph;
     newGraph = kruskalAlgorithm(graph, n, k);

     print(newGraph, n - 1);

     return 0;
}
