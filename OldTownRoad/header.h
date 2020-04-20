#ifndef OLDTOWNROAD_HEADER_H
#define OLDTOWNROAD_HEADER_H


typedef struct Edge {
    int firstVertex;
    int secondVertex;
    int cost;
} Edge;

Edge *new(int size);

int *newBoolean(int size);

void print(Edge *array, int size);

int compare(Edge firstStruct, Edge SecondStruct);

Edge *merge(Edge *leftArray, Edge *rightArray, int leftSize, int rightSize);

Edge *mergeSort(Edge *array, int size);

Edge *kruskalAlgorithm(Edge *graph, int numberOfVertexes, int numberOfEdges);

#endif
