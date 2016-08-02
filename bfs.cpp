/* This program implements Breadth First Search using Queue data structure.
   The distance of the node 'i' from 'start' will be stored in dist[i].
   The parent of each node 'i' is given in parent[i] and parent of 
   start is assumed to be 'start'. seen[] is used to counteract with 
   cycles (if present in graph).
*/

// C++11 code.
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

// Tha adjacency list representation of the graph.
std::vector <std::vector <int> > graph;

// Breadth First Search sub-routine.
void bfs(int start, int parent[], int dist[], int seen[], int visited[]) {
    std::queue <int> q;
    int v;
    
    q.push(start);
    parent[start] = start;      // Parent of start is assumed to be start.
    dist[start] = 0;            // Distance of start from itself is 0.
    seen[start] = 1;

    while(!q.empty()) {
        v = q.front(); q.pop();
        if(visited[v])          // If node already visited, continue.
            continue;
        visited[v] = 1;
        
        // Print the order in which nodes are being visited.
        std::cout << v << '\n';

        // Traverse all the nodes adjacent to the current node.
        for(int i = 0; i < graph[v].size(); i++) {

            // If the node has not been visited, it implies that the
            // node has never been in the queue.
            if(!visited[graph[v][i]]) {

                // If the node has not been visited but the node is
                // present in the queue, waiting to be visited, then
                // seen[graph[v][i]] = 1, else 0.
                if(!seen[graph[v][i]]) {
                    q.push(graph[v][i]);
                    dist[graph[v][i]] = 1 + dist[v];
                    parent[graph[v][i]] = v;

                    // Once the node has been entered in the queue 
                    // waiting to be visited, this value is marked 1, to
                    // not get stuck in closed loops (cycles).
                    seen[graph[v][i]] = 1;
                }
            }
            else {

                // If the node has been visited and there are multiple ways
                // to reach the node, then select the one with smallest 
                // distance from the start node.
                if(dist[v] + 1 < dist[graph[v][i]]) {
                    dist[graph[v][i]] = 1 + dist[graph[v][i]];
                    parent[graph[v][i]] = v;
                }
            }
        }
    }
}

int main() {

    int n = 8;          // number of nodes in this graph.
    graph = std::vector <std::vector <int> > (n);
    
    // The adjacency list of the graph.
    graph[0] = {1, 2};
    graph[1] = {0, 2, 3};
    graph[2] = {0, 1, 5, 6};
    graph[3] = {1, 2, 4};
    graph[4] = {3};
    graph[5] = {2};
    graph[6] = {2, 7};
    graph[7] = {6};

    /* - parent[i] = parent of 'i' in BFS traversal.
       - dist[i] = shortest distance of 'i' from 'start'.
       - If seen[i] == 1, 'i' has entered the queue once
         else, not yet entered the queue.
       - If visited[i] == 1, 'i' has been completely visited and 
         all the adjacent nodes has been seen, otherwise not.
    */
    int parent[n+1], dist[n+1], seen[n+1], visited[n+1];
    memset(parent, -1, sizeof(parent));
    memset(dist, -1, sizeof(dist));
    memset(seen, 0, sizeof(seen));
    memset(visited, 0, sizeof(visited));

    int start = 0;      // start node in BFS.
    bfs(start, parent, dist, seen, visited);

    return 0;
}
