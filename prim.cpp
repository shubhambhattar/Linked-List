/* This program implements Prim's Algorithm using Priority Queue.
   Since C++'s std::priority_queue has no decrease key operation,
   I have implemented my own priority queue which uses another container
   (an array `index_map[]` in this case) to store the index of different
   vertices in priority queue so as to facilitate decrease key operation.
   The code contains a sample graph for demonstrative purposes.
*/


// C++11 code
#include <iostream>
#include <vector>
#include <cstring>
#define SIZE 5          // number of vertices.
#define INF 100000000

/* This vector will contain a pair of integers where the first integer in
   the pair is value(cost) and the second is the vertex.
   This will be our priority queue.
*/
std::vector <std::pair <int, int> > pq (SIZE);
int size = SIZE;        // size of priority queue
int index_map[SIZE];

// Shift up the key with lower value.
void sift_up(int index) {
    int parent = (index-1)/2;
    while(index >= 0 && pq[index].first < pq[parent].first) {
        index_map[pq[index].second] = parent;
        index_map[pq[parent].second] = index;
        std::swap(pq[index], pq[parent]);
        index = parent;
        parent = (index - 1)/2;
    }
}

// Shift down the key with higher value.
void sift_down(int index) {
    int left = 2*index+1, right = 2*index+2;
    int min_index = index;
    if(left < size && pq[left].first < pq[min_index].first)
        min_index = left;
    if(right < size && pq[right].first < pq[min_index].first)
        min_index = right;
    if(min_index != index) {
        index_map[pq[index].second] = min_index;
        index_map[pq[min_index].second] = index;
        std::swap(pq[index], pq[min_index]);
        sift_down(min_index);
    }
}

// Extract the minimum element from priority queue.
std::pair <int, int> extract_min() {
    index_map[pq[0].second] = size-1;
    index_map[pq[size-1].second] = 0;
    std::swap(pq[0], pq[size-1]);
    size -= 1;
    sift_down(0);
    return pq[size];
}

// Change the value at index 'index' to 'value'.
void decrease_key(int index, int value) {
    int temp = pq[index].first;
    pq[index].first = value;
    if(value < temp)
        sift_up(index);
    else
        sift_down(index);
}

// Initialise and heapify the priority queue.
void make_heap(int start_index) {
    for(int i = 0; i < SIZE; i++) {
        pq[i].first = INF;
        pq[i].second = i;
    }
    pq[0].first = 0;
    pq[start_index].second = start_index;

    for(int i = SIZE-1; i >= 0; i--)
        sift_down(i);
}

int main() {

    /* Graph is represent using adjacency list. It takes the following form:
       graph[u] = {{v_1, c_1}, {v_2, c_2}, ..., {v_n, c_n}};
       The above line means that there is an undirected edge 
       between vertices 'u' and 'v_1' with cost 'c_1'. 
       Similarly for (u, v_2, c_2), ..., (u, v_n, c_n).
    */ 
    std::vector <std::vector <std::pair <int, int> > > graph (SIZE);
    
    graph[0] = {{1, 20}, {2, 50}, {3, 70}, {4, 90}};
    graph[1] = {{0, 20}, {2, 30}};
    graph[2] = {{0, 50}, {1, 30}, {3, 40}};
    graph[3] = {{0, 70}, {2, 40}, {4, 60}};
    graph[4] = {{0, 90}, {3, 60}};
    
    int visited[SIZE];
    memset(visited, 0, sizeof(visited));
    visited[0] = 1;
    make_heap(0);           // Assuming algorithm to start from vertex 0.
    
    for(int i = 0; i < SIZE; i++)
        index_map[pq[i].second] = i;

    int answer = 0;
    while(size != 0) {

        std::pair <int, int> p = extract_min();
        /* p.first will contain the cost of the next edge to be added in our
           answer and p.second will give the vertex number.
        */
        visited[p.second] = 1;
        answer += p.first;
        
        for(int i = 0; i < graph[p.second].size(); i++) {
            if(!visited[graph[p.second][i].first]) {
                if(graph[p.second][i].second < pq[index_map[graph[p.second][i].first]].first) {
                    decrease_key(index_map[graph[p.second][i].first], graph[p.second][i].second);
                }
            }
        }
        
    }
    std::cout << answer << "\n";
}
