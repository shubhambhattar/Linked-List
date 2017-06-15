#include <iostream>
#include <vector>
#include <queue>

std::vector <bool> visited;
std::vector <int> d, parent;

void initialize_single_source(size_t graph_size, int source) {
    d = std::vector <int> (graph_size, 1e9);
    parent = std::vector <int> (graph_size, -1);
    visited = std::vector <bool> (graph_size, false);
    d[source] = 0;
    parent[source] = 0;
}

int prim(const std::vector <std::vector <std::pair <int, int> > >& graph, int source) {
    size_t n = graph.size();
    initialize_single_source(n, source);

    // make a min-priority queue and initialize it - {distance, vertex}
    std::priority_queue <std::pair <int, int>, std::vector <std::pair <int, int> >, std::greater <std::pair <int, int> > > pq;
    pq.push({d[source], source});

    // repeatedly add the vertex from the lightest edge and push all the adjacent
    // vertices to the priority_queue untill all the vertices are in MST.
    int mst_cost = 0, mst_size = 0;
    while(mst_size != n) {
        std::pair <int, int> p = pq.top(); pq.pop();
        if(visited[p.second])
            continue;
        ++mst_size;
        mst_cost += p.first;
        
        int u = p.second;
        visited[u] = true;
        for(size_t v = 0; v < graph[u].size(); v++) {
            if(!visited[graph[u][v].first])
                pq.push({graph[u][v].second, graph[u][v].first});
        }
    }
    return mst_cost;
}

int main() {

    // n = number of vertices
    // m = number of directed edges
    int n, m, x, y, w;
    std::cin >> n >> m;
    std::vector <std::vector <std::pair <int, int> > > graph(n);

    // assuming 1-based indexing
    for(size_t i = 0; i < m; i++) {
        std::cin >> x >> y >> w;
        graph[x-1].push_back({y-1, w});
        graph[y-1].push_back({x-1, w});
    }
    int source = 0;
    int mst_cost = prim(graph, source);

    std::cout << "The cost of MST is: " << mst_cost << std::endl;

    return 0;
}
