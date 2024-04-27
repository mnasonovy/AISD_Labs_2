#include <iostream>
#include <vector>
#include "main.cc"

bool contains(const std::vector<int>& vec, int value) {
    for (int num : vec) {
        if (num == value) {
            return true;
        }
    }
    return false;
}

std::vector<int> findDuplicates(const std::vector<int>& vec) {
    std::vector<int> duplicates;

    for (size_t i = 0; i < vec.size(); ++i) {
        for (size_t j = i + 1; j < vec.size(); ++j) {
            if (vec[i] == vec[j] && !contains(duplicates, vec[i])) {
                duplicates.push_back(vec[i]);
                break; 
            }
        }
    }

    return duplicates;
}



int main() {
    IntSet intSet;
    intSet.insert(3);
    intSet.insert(2);
    intSet.insert(2);
    intSet.insert(4);
    std::cout << "IntSet contains: ";
    intSet.print();
    std::vector<int> vec = { 3, 2, 2, 4 };
    std::vector<int> duplicates = findDuplicates(vec);
    std::cout << "Found duplicates: ";
    for (int i = 0; i < duplicates.size(); ++i) {
        std::cout << duplicates[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}