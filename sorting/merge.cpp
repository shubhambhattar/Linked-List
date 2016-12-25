#include <algorithm>
#include <iostream>
#include <random>
#include <vector>


void merge(std::vector <int>& values, int start, int mid, int end) {

    /* 
    Create a `left` vector for values[start, ..., mid] and `right` vector
    for values[mid+1, ..., end]. Then merge these two parts in the original
    vector `values`.
    */

    std::vector <int>::const_iterator it1 = values.begin();
    std::vector <int> left (it1+start, it1+mid+1);
    std::vector <int> right (it1+mid+1, it1+end+1);
    
    int index = start, left_size = mid-start+1, right_size = end-mid, i = 0, j = 0;
    while(i < left_size && j < right_size) {
        if(left[i] <= right[j]) {
            values[index] = left[i];
            ++i;
        }
        else {
            values[index] = right[j];
            ++j;
        }
        ++index;
    }

    while(i < left_size) {
        values[index] = left[i];
        ++index;
        ++i;
    }

    while(j < right_size) {
        values[index] = right[j];
        ++index;
        ++j;
    }
}

void merge_sort(std::vector <int>& values, int start, int end) {
    if(start < end) {
        int mid = start + (end-start)/2;
        merge_sort(values, start, mid);
        merge_sort(values, mid+1, end);
        merge(values, start, mid, end);
    }

}

int main() {

    // n = size of the test vector.
    int n = 10, mod = 15;
    std::vector <int> values (n);

    // Generates `n` random numbers each in the range [0, mod-1].
    std::generate(values.begin(), values.end(), [mod](){
        return rand() % mod;
    });

    std::cout << "Before sorting:" << std::endl;
    for(int element: values)
        std::cout << element << ' ';
    std::cout << std::endl;

    merge_sort(values, 0, n-1);
    
    std::cout << "After sorting:" << std::endl;
    for(int element: values)
        std::cout << element << ' ';
    std::cout << std::endl;
    
    return 0;
}
