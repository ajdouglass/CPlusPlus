/******************************************************************************
 *
 * Andrew Douglass
 * Sept. 18 2017
 * main.cpp
 * 
 * This program is designed to implement Dijkstra's algorithm for the 
 * graph specified. It involves finding the shortest weighted
 * path from the specified starting node (START) to the ending node (ENDING). 
 *
 * The distance vector shows the distances from the starting node to every 
 * other node. The index of each value in distance corresponds to the node 
 * number. In other words, if the starting node is 6, then distance[0] will 
 * contain the total weighted distance from node 6 to node 1 (notice that 
 * the index is off from the node number by 1 because of 0 indexed arrays).
 *
 * prevNums is an array that contains the previous node for every respective 
 * node so that the path to each node can be obtained. You can therefore 
 * backtrack and obtain the path because each index in prevNums corresponds 
 * to the node number. 
 *
 *****************************************************************************/
 
#include <iostream>
#include <limits.h>
#include <vector>
#include <stack>

#define NODES 8     // Number of nodes in the graph
#define START 6     // Starting node in the graph
#define ENDING 8    // Destination node in the graph

using namespace std;

// Return true if the node indicated by nodeNum has already been 
// visited (i.e. the value nodeNum is contained in the visited 
// vector) 
bool alreadyVisited(vector<int> visited, int nodeNum) {
	// Perform a linear search through all visited nodes
	for(int i = 0; i < visited.size(); i++) {
		if(visited[i] == nodeNum) {
			// The node indicated by nodeNum has already been visited 
			return true;
		}
	}
	// The node nodeNum has not been visited 
	return false; 
}

// Return the index of the least distance located in the distance 
// vector that has not already been visited. This index corresponds
// to the next node that should be evaluated in the graph. 
int getMinIndex(vector<int> visited, vector<int> distance) {
	// Store the index of the node and the min distance value
	int index;
	int min = INT_MAX;
	// Search through the current total distances from the starting 
	// node to every other node
	for(int i = 0; i < distance.size(); i++) {
		// Check if the distance to the node is the minimum and the node 
		// has not been visited yet
		if(!alreadyVisited(visited, i) && distance[i] < min) {
			min = distance[i];
			index = i;
		}
	}
	return index;
}

// Print the path from the starting node to the ending node 
// that will minimize the weighted path cost
void printPath(int prevNums[], int endNode) {
	// Use a stack to reverse the order of the path in order to 
	// print from the start node to the end node
	stack<int> pathStack; 
	int next = endNode;
	while(next != -1) {
		pathStack.push(next+1);
		// Get the current nodes previous node
		next = prevNums[next];
	}
	cout << "Path from " << START << " to " << (endNode+1) << ": ";
	// Print the elements in the stack where the starting node 
	// is on top of the stack and ending node is at the bottom
	while(!pathStack.empty()) {
		if(pathStack.size() > 1) {
			cout << pathStack.top() << " -> ";
		}
		else {
		// This is the destination node, do not print another arrow
		cout << pathStack.top(); 
		}
		// Remove the top element from the stack
		pathStack.pop();
	}
	cout << endl;
}

void dijkstrasAlgo(int graph[NODES][NODES]) {
	// Used to store the visited nodes in the graph
	vector<int> visited;
	// Store the distances from the starting node to each of the
	// the remaining nodes
	vector<int> distance;
	for(int i = 0; i < NODES; i++) {
		// Initialize all the distances to "infinite"
		distance.push_back(INT_MAX);
	}
	// Distance to from the starting node to the starting node
	// should be zero
	distance[START-1] = 0;
  
	// Store each nodes previous node so that we can keep track
	// of the path from the starting node to every other node.
	// Initialize to -1 so we know when we reach the starting node.
	int prevNums[] = {-1, -1, -1, -1, -1, -1, -1, -1};
  
	int index = START-1;
	for(int i = 0; i < NODES; i++) {
		// Get the node that has the least weighted distance and has
		// not already been visited
		index = getMinIndex(visited, distance); 
		// Add this node to the visited list
		visited.push_back(index); 
		for(int j = 0; j < NODES; j++) {
			// Calculate the current distance to the node plus the new path
			int newDis = distance[index] + graph[index][j];
			// Check to update path weights that are not 0, that have not been 
			// visited, and that are less than the current calculated weights
			if(graph[index][j] != 0 && newDis < distance[j] && 
				!alreadyVisited(visited,j) && distance[index] < INT_MAX) {
				// Update the distance and the node that was taken to get here
				distance[j] = distance[index]+graph[index][j];
				prevNums[j] = index;
			}
		}
	}   

	// Print the weighted cost of the path taken
	cout << "Path length from " << START << " to " << ENDING << ": ";
	cout << distance[ENDING-1] << endl;

	// Print the path taken from the start to ending node 
	printPath(prevNums, ENDING-1);
}

int main() {
	// Store the weights from node to node in a matrix format
	// where the row/column index maps to the node number
	int graph[NODES][NODES] = {{0,3,4,7,0,7,8,0},
							   {3,0,4,1,8,0,3,0},
							   {4,4,0,6,0,3,0,0},
							   {7,1,6,0,2,0,5,0},
							   {0,8,0,2,0,0,4,6},
							   {7,0,3,0,0,0,0,0},
							   {8,3,0,5,4,0,0,9},
							   {0,0,0,0,6,0,9,0}};

	dijkstrasAlgo(graph); 

	return 0;
}
