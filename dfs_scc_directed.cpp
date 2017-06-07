#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

std::vector <bool> visited;
std::vector <std::pair <int, int> > post;
std::vector <int> component;

int count = 0;

void dfs_visit(const std::vector <std::vector <int> >& graph, int u, int c) {
    visited[u] = true;
    component[u] = c;       // Vertex `u` added to component `c`

    for(size_t v = 0; v < graph[u].size(); ++v) {
        if(!visited[graph[u][v]])
            dfs_visit(graph, graph[u][v], c);
    }

    ++count;                        // For postvisit timer
    post.push_back({count, u});     // vector of pair containing {postvisit time, vertex}
}

int dfs(const std::vector <std::vector <int> >& graph, const std::vector <std::vector <int> >& graph_rev) {
   
    // Running DFS on G and calculating postvisit times for each vertex.
    // The third argument to dfs_visit does not serve any purpose in this loop.
    // It will be used to mark the component of each vertex in the next DFS.
    for(size_t v = 0; v < graph.size(); ++v) {
        if(!visited[v])
            dfs_visit(graph, v, 0);
    }
    
    // Remark all vertices as not visited and sort them
    // in descending order of postvisit times.
    std::fill(visited.begin(), visited.end(), false);
    std::sort(post.begin(), post.end(), std::greater <std::pair <int, int> >());
    
    // cc stores the number of connected components.
    int cc = 0;
    for(size_t v = 0; v < post.size(); v++) {
        if(!visited[post[v].second]) {
            dfs_visit(graph_rev, post[v].second, cc);
            ++cc;
        }
    }
    return cc;
}

int main() {

    // n = number of vertices
    // m = number of directed edges
    int n, m, x, y;
    std::cin >> n >> m;
    
    std::vector <std::vector <int> > graph(n), graph_rev(n);
    visited = std::vector <bool> (n, false);
    component = std::vector <int> (n, -1);

    // 1-based indexing of vertex numbers assumed.
    for(size_t i = 0; i < m; i++) {
        std::cin >> x >> y;
        graph[x-1].push_back(y-1);
        graph_rev[y-1].push_back(x-1);
    }

    int cc = dfs(graph, graph_rev);
    std::cout << "# Connected Components in the given Directed Graph: " << cc << std::endl;
}
