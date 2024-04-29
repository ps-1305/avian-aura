#define VERTICES 30
#define INF INT_MAX

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

/*
args = distance array, shortest path tree set 
returns = min_index , the index of the cheapest path
function = calculates the min distance between paths and returns the shortest among them all
*/
int minDistance(double dist[], bool spt[]){
    double min = INF;
	int min_index;

	for (int v = 0; v < VERTICES; v++)
		if (spt[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

/*
args = graph in which we need to find shortest path, source and destination integer, parent array
returns = double dist[dest] -> the shortest path from source to destination
function = it uses the dijsktra's algorithm to find the shortest path from source to destination
*/
double dijkstrasAlgorithm(double graph[VERTICES][VERTICES],int src, int dest, int parent[VERTICES]){
	// distance array
	double dist[VERTICES]; 

	// shortest path tree
	bool spt[VERTICES]; 

	// traversing each vertex and putting distance = INF on each of them
	// also every element of the spt set is false (ie, none of the nodes have been traversed)
	for (int i = 0; i < VERTICES; i++)
		dist[i] = INF, spt[i] = false;

	// the source distance is set to zero
	dist[src] = 0;

	// traversing the entire graph
	for (int count = 0; count < VERTICES - 1; count++) {
		// u comes out to be the minimum distance of a particular vertex from the source
		int u = minDistance(dist, spt);

		// since we traversed this node, we set it to true
		spt[u] = true;

		// traversing the entire graph
		for (int v = 0; v < VERTICES; v++)
		/*
		* now it needs to satisfy the following conditions
		1. the node has not been traversed (!spt == true for a non traversed node)
		2. the node exists 
		3. the distance to that particulat point is not INF
		4. if the path is shorter than what we have currently
		*/
			if (!spt[v] && graph[u][v]
				&& dist[u] != INF
				&& dist[u] + graph[u][v] < dist[v]){
				dist[v] = dist[u] + graph[u][v];
				parent[v] = u;
			}
	}

	// return the distance of the destination from the source
    return dist[dest];
}
