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

void makeSet(int v, int *parent);

int findSet(int v, int *parent);

void uniteSets(int v, int w, int *parent);

#endif
