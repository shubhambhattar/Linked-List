#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

void insertion_sort(std::vector <int>& values) {
    int n = values.size();
    for(int i = 1; i < n; i++) {
        int current_element = values[i];
        int j = i;
        while(j > 0 && values[j-1] > current_element) {
            values[j] = values[j-1];
            j--;
        }
        values[j] = current_element;
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

    insertion_sort(values);
    
    std::cout << "After Insetion Sort:" << std::endl;
    for(const auto& item: values)
        std::cout << item << ' ';
    std::cout << std::endl;

    return 0;
}
