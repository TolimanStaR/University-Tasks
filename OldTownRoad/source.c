#include <stdio.h>
#include <stdlib.h>

#include "header.h"


#define repeat(x) for(int i = 0; i < (x); ++i)
#define True 1
#define False 0
#define and &&
#define or ||
#define is ==
#define not !


Edge *new(int size) {
     Edge *array;
     array = (Edge *) calloc(size, sizeof(Edge));
     return array;
}


int *newBoolean(int size) {
     int *array;
     array = (int *) calloc(size, sizeof(int));
     return array;
}


int *newInt(int size) {
     int *array;
     array = (int*) calloc(size, sizeof(int));
     return array;
}


void print(Edge *array, int size) {
     repeat(size) printf("Edge between vertexes %d and %d (Cost is %d)\n",
             array[i].firstVertex + 1, array[i].secondVertex + 1, array[i].cost);
     puts("\n");
}


int compare(Edge firstStruct, Edge SecondStruct) {
     return firstStruct.cost > SecondStruct.cost ? True : False;
}


Edge *merge(Edge *leftArray, Edge *rightArray, int leftSize, int rightSize) {
     Edge *arrayToReturn = new(leftSize + rightSize);

     int leftFlag, rightFlag, retIndex;
     leftFlag = rightFlag = retIndex = 0;


     while (leftFlag < leftSize and rightFlag < rightSize) {
          if (compare(leftArray[leftFlag], rightArray[rightFlag])) {
               arrayToReturn[retIndex++] = rightArray[rightFlag++];
          } else {
               arrayToReturn[retIndex++] = leftArray[leftFlag++];
          }
     }

     int repeatTimes = __max(rightSize - rightFlag, leftSize - leftFlag);

     if (leftSize is leftFlag) {
          repeat(repeatTimes) {
               arrayToReturn[retIndex++] = rightArray[rightFlag++];
          }
     } else {
          repeat(repeatTimes) {
               arrayToReturn[retIndex++] = leftArray[leftFlag++];
          }
     }

     return arrayToReturn;
}


Edge *mergeSort(Edge *array, int size) {
     if (size < 2) return array;

     int middle = size / 2;

     Edge *leftArray;
     Edge *rightArray;

     int leftSize = middle;
     int rightSize = size - leftSize;

     leftArray = new(leftSize);
     rightArray = new(rightSize);

     repeat(leftSize) leftArray[i] = array[i];
     repeat(rightSize) rightArray[i] = array[leftSize + i];

     leftArray = mergeSort(leftArray, leftSize);
     rightArray = mergeSort(rightArray, rightSize);

     return merge(leftArray, rightArray, leftSize, rightSize);
}


Edge *kruskalAlgorithm(Edge *graph, int numberOfVertexes, int numberOfEdges) {

     int *used = newBoolean(numberOfVertexes);
     int *parent = newInt(numberOfVertexes);
     Edge *newGraph = new(numberOfVertexes - 1);

     graph = mergeSort(graph, numberOfEdges);

     repeat(numberOfEdges) {
          graph[i].firstVertex -= 1;
          graph[i].secondVertex -= 1;
     }

     int graphIndex, newIndex;
     graphIndex = newIndex = 0;

     int numberOfTrees = numberOfVertexes;

     repeat(numberOfVertexes) makeSet(i, parent);

     while (numberOfTrees > 1) {
          if (findSet(graph[graphIndex].firstVertex, parent) != findSet(graph[graphIndex].secondVertex, parent)) {
               uniteSets(graph[graphIndex].firstVertex, graph[graphIndex].secondVertex, parent);
               newGraph[newIndex++] = graph[graphIndex];
               --numberOfTrees;
          }
          ++graphIndex;
     }

     return newGraph;
}
