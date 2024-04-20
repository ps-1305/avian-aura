#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#define VERTICES 30
#define INF INT_MAX


int minDistance(int dist[], bool sptSet[]){
	// Initialize min value
	int min = INF, min_index;

	for (int v = 0; v < VERTICES; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

int dijkstrasAlgorithm(int graph[VERTICES][VERTICES], int src, int dest){
	int dist[VERTICES]; 

	bool sptSet[VERTICES]; 

	for (int i = 0; i < VERTICES; i++)
		dist[i] = INF, sptSet[i] = false;

	dist[src] = 0;

	for (int count = 0; count < VERTICES - 1; count++) {
		int u = minDistance(dist, sptSet);

		sptSet[u] = true;

		for (int v = 0; v < VERTICES; v++)

			if (!sptSet[v] && graph[u][v]
				&& dist[u] != INF
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

    return dist[dest];
}

