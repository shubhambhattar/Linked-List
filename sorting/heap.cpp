#include <iostream>
// #include <algorithm>

// Stores the size of heap.
int size;

void heapify(int* a, int x) {
    
    int min_index = x;
    int l = 2*x+1, r = 2*x+2;
    if(l < size && a[l] > a[min_index])
        min_index = l;
    if(r < size && a[r] > a[min_index])
        min_index = r;
    if(x != min_index) {
        std::swap(a[x], a[min_index]);
        heapify(a, min_index);
    }
}

int extract(int* a) {

    // Swap the first element with the last element and then heapify.

    int result = a[0];
    a[0] = a[size - 1];
    size--;
    heapify(a, 0);
    return result;
}

int main() {

    /* STRESS TESTING CODE STARTS HERE */

    // bool run = true;
    // while(run) {
    //     int n = 1 + rand() % 10000000;
    //     int a[n];
    //     size = n;
    //     int b[n];
    //     for(int i = 0; i < n; i++) {
    //         a[i] = rand() % 10000000;
    //         b[i] = a[i];
    //         //std::cout << a[i] << " ";
    //     }
    //     //std::cout << "\n";

    //     for(int i = (n-1)/2; i >= 0; i--)
    //         heapify(a, i);
    //     for(int i = 0; i < n; i++)
    //         a[n-1-i] = extract(a);
    //     std::sort(b, b+n);
    //     for(int i = 0; i < n; i++) {
    //         if(a[i] != b[i]) {
    //             run = false;
    //             for(int j = 0; j < n; j++)
    //                 std::cout << a[i] << " ";
    //             std::cout << "\n";
    //         }
    //         if(!run)
    //             break;
    //     }
    //     std::cout << run << "\n\n";
    // }

    /* STRESS TESTING CODE ENDS HERE */

    int n;
    std::cin >> n;
    int a[n];
    size = n;
    for(int i = 0; i < n; i++)
        std::cin >> a[i];

    for(int i = (n-1)/2; i >= 0; i--)
        heapify(a, i);
    for(int i = 0; i < n; i++)
        a[n-1-i] = extract(a);
    
    for(int i = 0; i < n; i++)
        std::cout << a[i] << " ";
    std::cout << "\n";
}
