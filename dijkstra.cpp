#include <iostream>
#include <vector>
#include <queue>

std::vector <int> d, parent;
std::vector <bool> visited;

void initialize_single_source(size_t graph_size, int source) {
    d = std::vector <int> (graph_size, 1e9);
    parent = std::vector <int> (graph_size, -1);
    visited = std::vector <bool> (graph_size, false);
    d[source] = 0;
    parent[source] = source;
}

void dijkstra(const std::vector <std::vector <std::pair <int, int> > >& graph, int source) {
    size_t n = graph.size();
    initialize_single_source(n, source);

    // make a min-priority queue and initialize it - {distance, vertex}
    std::priority_queue <std::pair <int, int>, std::vector <std::pair <int, int> >, std::greater <std::pair <int, int> > > pq;
    pq.push({d[source], source});

    // repeatedly remove the vertex with the shortest distance
    // and relax all its adjacent edges.
    while(!pq.empty()) {
        std::pair <int, int> p = pq.top(); pq.pop();
        if(visited[p.second])
            continue;
        int u = p.second;
        visited[u] = true;

        for(size_t i = 0; i < graph[u].size(); i++) {
            if(d[graph[u][i].first] > d[u] + graph[u][i].second) {
                d[graph[u][i].first] = d[u] + graph[u][i].second;
                parent[graph[u][i].first] = u;
                pq.push({d[graph[u][i].first], graph[u][i].first});
            }
        }
    }
}

int main() {

    // n = number of vertices
    // m = number of directed edges
    int n, m, x, y, w, source;
    std::cin >> n >> m;
    std::vector <std::vector <std::pair <int, int> > > graph(n);
        
    // assuming 1-based indexing
    for(int i = 0; i < m; i++) {
        std::cin >> x >> y >> w;
        graph[x-1].push_back({y-1, w});
    }
    std::cin >> source;
    source -= 1;

    dijkstra(graph, source);
    for(size_t i = 0; i < n; i++)
        std::cout << d[i] << ' ';
    std::cout << std::endl;
}

