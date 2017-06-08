#include <iostream>
#include <vector>
#include <queue>

std::vector <bool> visited;
std::vector <int> ans, indegree;

void topological(const std::vector <std::vector <int> >& graph, std::queue <int> q) {

    while(!q.empty()) {
        
        // pop the front vertex and add it to ans
        int u = q.front(); q.pop();
        visited[u] = true;
        ans.push_back(u);
            
        // For all the non visited neighboring vertices of u, decrement
        // their corresponding indegree.
        for(size_t v = 0; v < graph[u].size(); v++) {
            if(!visited[graph[u][v]]) {
                indegree[graph[u][v]]--;
                
                // if indegree of any vertex becomes 0, push it in the queue.
                if(indegree[graph[u][v]] == 0) {
                    q.push(graph[u][v]);
                    visited[graph[u][v]] = true;
                }
            }
        }    
    }
}


int main() {
    // number of vertices in the graph.
    int n, m, x, y;
    std::cin >> n >> m;

    std::vector <std::vector <int> > graph(n);
    visited = std::vector <bool> (n, false);
    indegree = std::vector <int> (n, 0);

    // 1-based indexing assumed
    for(size_t i = 0; i < m; i++) {
        std::cin >> x >> y;
        graph[x-1].push_back(y-1);
        indegree[y-1]++;
    }

    // insert all the vertices in the queue that has indegree 0
    std::queue <int> q;
    for(size_t i = 0; i < n; i++) {
        if(indegree[i] == 0)
            q.push(i);
    }

    topological(graph, q);
    for(size_t i = 0; i < ans.size(); i++)
        std::cout << ans[i] << ' ';
    std::cout << std::endl;

    return 0;
}
