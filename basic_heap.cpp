// Illustrates basic heap operations.

#include <iostream>

// Heap as an array
int a[100001];
int size = 0, maxSize = 100000;

void shift_up(int size) {

    // Get the last inserted element to its appropriate position by swapping with the parents.

    int i = size - 1;
    int parent = (i-1)/2;
    while(i > 0 && a[parent] < a[i]) {
        std::swap(a[parent], a[i]);
        i = parent;
        parent = (i-1)/2;
    }
}

void shift_down(int x) {
    
    /* Get the element at position 'x' to its appropritate position
       by comparing and swapping with the child nodes.              */

    int min_index = x;
    int l = 2*x+1, r = 2*x+2;
    if(l < size && a[l] > a[min_index])
        min_index = l;
    if(r < size && a[r] > a[min_index])
        min_index = r;
    if(x != min_index) {
        std::swap(a[x], a[min_index]);
        shift_down(min_index);
    }
}

int getMax() {

    // Return the max element.

    if(size == 0) {
        std::cout << "No element\n\n";
        return -1;
    }
    return a[0];
}


void insert(int element) {

    /* Insert a new element at the last index and then shift it to its
       appropritate position by swapping with the parent nodes when required.   */
    if(size == maxSize) {
        std::cout << "Space full!!\n\n";
        return;
    }
    a[size] = element;
    size++;
    shift_up(size);
}

void extract() {

    // Remove the max element from the heap.
    
    if(size == 0) {
        std::cout << "No element\n\n";
        return;
    }
    a[0] = a[size-1];
    size--;
    shift_down(0);
}

void remove(int index) {

    // Remoe the element at the given index.

    if(index < 0 || index >= size) {
        std::cout << "Wrong Index.\n\n";
        return;
    }
    a[index] = 2147483647;
    shift_up(index);
    extract();
}

void change(int index, int p) {

    // Change the priority of element at 'index' to p.

    int old = a[index];
    a[index] = p;
    if(a[(index-1)/2] < a[index])
        shift_up(index);
    else
        shift_down(index);
}

void menu() {

    bool run = true;
    while(run) {

        std::cout << "-----MENU-----\n";
        std::cout << "1. Insert an element.\n";
        std::cout << "2. Get the max element.\n";
        std::cout << "3. Extract the max element.\n";
        std::cout << "4. Remove an element.\n";
        std::cout << "5. Change the priority of an element.\n";
        std::cout << "6. Exit.\n";
        std::cout << "Enter your choice: ";
        int choice, element, priority, index, result;
        std::cin >> choice;
        switch(choice) {

            case 1:     std::cout << "Enter the element: ";
                        std::cin >> element;
                        insert(element);
                        break;

            case 2:     result = getMax();
                        if(result != -1)
                            std::cout << "Maximum element is: " << result << "\n";
                        break;
            
            case 3:     result = getMax();
                        if(result != -1) {
                            std::cout << "Maximum element is: " << result << "\n";
                            extract();
                        }
                        break;
            
            case 4:     std::cout << "Enter the index to be deleted: ";
                        std::cin >> index;
                        remove(index);
                        break;
            
            case 5:     std::cout << "Enter the index and it's new priority: ";
                        std::cin >> index >> priority;
                        change(index, priority);
                        break;
            
            case 6:     run = false; break;
            
            default:    std::cout << "Wrong Choice. Please try again\n\n";
        }
    }
}

int main() {

    menu();
    return 0;
}