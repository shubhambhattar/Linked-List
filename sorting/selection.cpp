#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

void selection_sort(std::vector <int>& values) {
    int n = values.size();
    for(int i = 0; i < n-1; i++) {
        int min_pos = i;
        for(int j = i+1; j < n; j++) {
            if(values[j] < values[min_pos])
                min_pos = j;
        }
        std::swap(values[i], values[min_pos]);
    }
}

int main() {

    // n = size of values vector.
    int n = 10, mod = 15;

    std::vector <int> values (n);

    // Generated `n` random numbers each in the range [0, mod-1].
    std::generate(values.begin(), values.end(), [mod](){
        return rand() % mod;
    });

    std::cout << "Before Sorting:" << std::endl;
    for(const auto& item: values)
        std::cout << item << ' ';
    std::cout << std::endl;

    selection_sort(values);
    
    std::cout << "After Selection Sort:" << std::endl;
    for(const auto& item: values)
        std::cout << item << ' ';
    std::cout << std::endl;

    return 0;
}
