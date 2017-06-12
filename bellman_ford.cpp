#include <iostream>
#include <vector>
#include <climits>

std::vector <int> d, parent;

// mark all initial distances as infinity except the source vertex.
void initialise_single_source(size_t graph_size, int source) {
    d = std::vector <int> (graph_size, 2e9);
    parent = std::vector <int> (graph_size, -1);
    d[source] = 0;
    parent[source] = source;
}

bool bellman_ford(const std::vector <std::vector <std::pair <int, int> > >& graph, int source) {
    size_t n = graph.size();
    initialise_single_source(n, source);
    
    for(size_t i = 0; i < n-1; i++) {
        for(size_t u = 0; u < n; u++) {
            for(size_t k = 0; k < graph[u].size(); k++) {
                if(d[graph[u][k].first] > d[u] + graph[u][k].second) {
                    d[graph[u][k].first] = d[u] + graph[u][k].second;
                    parent[graph[u][k].first] = u;
                }
            }
        }
    }

    // check for negative weight cycle
    for(size_t u = 0; u < n; u++) {
        for(size_t k = 0; k < graph[u].size(); k++) {
            if(d[graph[u][k].first] > d[u] + graph[u][k].second)
                return false;
        }
    }
    return true;
}

int main() {

    // n = number of vertices
    // m = number of edges
    int n, m, x, y, w, source;
    std::cin >> n >> m;

    // pair will contain {vertex, weight}
    std::vector <std::vector <std::pair <int, int> > > graph(n);
    

    // 1-based indexing assumed
    for(int i = 0; i < m; i++) {
        std::cin >> x >> y >> w;
        graph[x-1].push_back({y-1, w});
    }
    std::cin >> source;
    source -= 1;
    bool flag = bellman_ford(graph, source);
    if(flag) {
        for(int i = 0; i < n; i++)
            std::cout << d[i] << ' ';
        std::cout << std::endl;
    } else {
        std::cout << "Negative weight cycle found" << std::endl;
    }
}
