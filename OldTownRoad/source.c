#include <stdlib.h>
#include <stdio.h>

#include "header.h"


#define repeat(x) for(int i = 0; i < (x); ++i)
#define True 1
#define False 0
#define and &&
#define or ||
#define is ==
#define not !


Edge *new(int size) {
     Edge* array;
     array = (Edge *) calloc(size, sizeof(Edge));
     return array;
}


int *newBoolean(int size) {
	int* array;
	array = (int*)calloc(size, sizeof(int));
	return array;
}


void print(Edge *array, int size) {
     repeat(size) printf("Edge between vertexes %d and %d (Cost is %d)\n", array[i].firstVertex + 1, array[i].secondVertex + 1, array[i].cost);
     puts("\n");
}


int compare(Edge firstStruct, Edge SecondStruct) {
     return firstStruct.cost > SecondStruct.cost ? True : False;
}


Edge *merge(Edge *leftArray, Edge *rightArray, int leftSize, int rightSize) {
     Edge *arrayToReturn = new(leftSize + rightSize);

     int leftFlag = 0;
     int rightFlag = 0;
     int retIndex = 0;

     while (leftFlag < leftSize and rightFlag < rightSize) {
          if (compare(leftArray[leftFlag], rightArray[rightFlag])) {
               arrayToReturn[retIndex] = rightArray[rightFlag];
               ++rightFlag;
          } else {
               arrayToReturn[retIndex] = leftArray[leftFlag];
               ++leftFlag;
          }
          ++retIndex;
     }

     if (leftSize is leftFlag) {
          int rep = rightSize - rightFlag;
          repeat(rep) {
               arrayToReturn[retIndex] = rightArray[rightFlag];
               ++retIndex;
               ++rightFlag;
          }
     } else {
          int rep = leftSize - leftFlag;
          repeat(rep) {
               arrayToReturn[retIndex] = leftArray[leftFlag];
               ++retIndex;
               ++leftFlag;
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


Edge* kruskalAlgorithm(Edge*graph, int numberOfVertexes, int numberOfEdges) {
	int* used = newBoolean(numberOfVertexes);

	graph = mergeSort(graph, numberOfEdges);

	Edge *newGraph = new(numberOfVertexes - 1);
	int newIndex = 0;

	int numberOfTrees = numberOfVertexes;


	for (int i = 0; i < numberOfEdges; ++i) {
		graph[i].firstVertex -= 1;
		graph[i].secondVertex -= 1;

		if ((not used[graph[i].firstVertex] or not used[graph[i].secondVertex]) or numberOfTrees > 1) {
		     used[graph[i].firstVertex] = True;
		     used[graph[i].secondVertex] = True;
		     newGraph[newIndex++] = graph[i];
		     --numberOfTrees;
		}
		if (numberOfTrees == 1) return newGraph;
	}
}

