#include <iostream>
#include <vector>

std::vector <std::vector <int> > graph;
std::vector <bool> visited;
std::vector <int> component;

void dfs(const std::vector <std::vector <int> >& graph, int u, int component_no) {
    visited[u] = true;
    component[u] = component_no;
    for(size_t i = 0; i < graph[u].size(); i++) {
        if(!visited[graph[u][i]])
            dfs(graph, graph[u][i], component_no);
    }
}

int main() {

    int n = 8;          // number of nodes in this graph.
    graph = std::vector <std::vector <int> > (n);
    visited = std::vector <bool> (n, false);    
    component = std::vector <int> (n, -1);
    
    // The adjacency list of the Undirected graph.
    graph[0] = {1, 2};
    graph[1] = {0, 2, 3};
    graph[2] = {0, 1, 5, 6};
    graph[3] = {1, 2, 4};
    graph[4] = {3};
    graph[5] = {2};
    graph[6] = {2, 7};
    graph[7] = {6};

    // To find all the connected components
    int connected_components = 0;
    for(size_t i = 0; i < n; i++) {
        if(!visited[i]) {
            dfs(graph, i, connected_components);
            ++connected_components;
        }
    }

    std::cout << "#Connected Components in given Undirected Graph: " 
                << connected_components << std::endl;

    return 0;
}
