#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

std::stack <int> post;
std::vector <bool> visited;

// Do a DFS traversal starting from node `u`
void dfs_visit(const std::vector <std::vector <int> >& graph, int u) {
    visited[u] = true;
    for(size_t v = 0; v < graph[u].size(); v++) {
        if(!visited[graph[u][v]])
            dfs_visit(graph, graph[u][v]);
    }
    post.push(u);
}

// Calls DFS on the all the components.
void dfs(const std::vector <std::vector <int> >& graph) {
    for(size_t u = 0; u < graph.size(); u++) {
        if(!visited[u])
            dfs_visit(graph, u);
    }
}

int main() {

    // number of vertices in the graph.
    const int n = 6;
    visited = std::vector <bool> (n, false);
    std::vector <std::vector <int> > graph = {
        {1, 3},
        {2, 3},
        {4, 3, 5},
        {4, 5},
        {5},
        {}
    };

    dfs(graph);
    while(!post.empty()) {
        int v = post.top(); post.pop();
        std::cout << v << ' ';
    }
    std::cout << std::endl;

    return 0;
}
