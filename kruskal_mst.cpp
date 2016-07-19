/* 
   This programs implements Kruskal's Algorithm to find
   Minimum Spanning Tree of a given graph. This uses Disjoint Set
   Union Find data structure with Union by Rank and Path 
   Compression to minimise complexity. 
   This code contains a sample graph for demonstrative purposes.
*/

// C++11 code
#include <iostream>
#include <algorithm>
#include <vector>

// This structure implements dijoint set data structure with 
// union and find operations.
struct union_find {
    std::vector <int> parent, rank;

    // Constructor to initialse 'parent' and 'rank' vector.
    union_find(int n) {
        parent = std::vector <int> (n);
        rank = std::vector <int> (n, 0);        // initialse rank vector with 0.
        for(int i = 0; i < n; i++)
            parent[i] = i;
    }

    // Find with Path Compression Heuristic.
    int find_(int a) {
        if(a == parent[a])
            return a;
        return parent[a] = find_(parent[a]);
    }

    // Union by checking rank to keep the depth of the tree as shallow as possible.
    void union_(int a, int b) {
        int aa = find_(a), bb = find_(b);
        if(rank[aa] < rank[bb])
            parent[aa] = bb;
        else
            parent[bb] = aa;
        if(rank[aa] == rank[bb])
            ++rank[aa];
    }
};

// Used as a comparator function to sort the 'edge_list' vector.
bool cmp(std::pair <std::pair <int, int>, int> p1, std::pair <std::pair <int, int>, int> p2) {
    return p1.second < p2.second;
}


int main() {

    int n = 5;         // number of vertices in the smaple graph.
    /* The input graph is represented using Edge List representation.
       It takes the following form:

       {cost_1, {vertex_1, vertex_2}},
       
       The above line means that there is an undirected edge from 'vertex_1' to
       'vertex_2' with cost 'cost_1'.
       The output graph 'mst' follows similar convention.
    */
    std::vector <std::pair <std::pair <int, int>, int> > edge_list, mst; 
    edge_list = {
        {{0, 1}, 20}, 
        {{0, 2}, 50}, 
        {{0, 3}, 70}, 
        {{0, 4}, 90},
        {{1, 2}, 30},
        {{2, 3}, 40},
        {{3, 4}, 60},
    };

    int mst_cost = 0;
    sort(edge_list.begin(), edge_list.end(), cmp);

    union_find ds(n);
    std::vector <std::pair <std::pair <int, int>, int> >::iterator it = edge_list.begin();
    
    // Check for every edge in sorted order whether they should be added to mst or not.
    for(; it != edge_list.end(); ++it) {

        // Break this loop as soon as the number of edges in the final 'mst' equals 'n-1'.
        if(mst.size() == n-1)
            break;

        int cost = it->second, vertex_1 = it->first.first, vertex_2 = it->first.second;
        // If the two vertices of this edge is not in the same group, then union them.
        if(ds.find_(vertex_1) != ds.find_(vertex_2)) {
            mst.push_back({{vertex_1, vertex_2}, cost});
            mst_cost += cost;
            ds.union_(vertex_1, vertex_2);
        }
    }

    // Print the final results.
    std::cout << "The Minimum Spanning Tree graph is: \n";
    for(int i = 0; i < mst.size(); i++)
        std::cout << "{" << mst[i].first.first << ", " << mst[i].first.second << "}: " << mst[i].second << '\n';
    std::cout << "The cost of Minimum Spanning Tree is: " << mst_cost << '\n';
    return 0;
}
