#ifndef DSU
#define DSU

#include <stdio.h>

#define not !

void makeSet(int v, int *parent) {
	parent[v] = v;
}


int findSet(int v, int *parent) {
	if (parent[v] == v)
		return v;
	return findSet(parent[v], parent);
}


void uniteSets(int v, int w, int *parent) {
	if (not (findSet(v, parent) == findSet(w, parent)))
		parent[w] = v;
}

#endif
