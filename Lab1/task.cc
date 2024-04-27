#include <iostream>
#include <vector>
#include "main.cc"

bool Contains(const std::vector<int>& vec, int value) {
    for (int num : vec) {
        if (num == value) {
            return true;
        }
    }
    return false;
}

std::vector<int> FindDuplicates(const std::vector<int>& vec) {
    std::vector<int> duplicates;

    for (size_t i = 0; i < vec.size(); ++i) {
        for (size_t j = i + 1; j < vec.size(); ++j) {
            if (vec[i] == vec[j] && !Contains(duplicates, vec[i])) {
                duplicates.push_back(vec[i]);
                break;
            }
        }
    }

    return duplicates;
}

int main() {
    IntSet intSet;
    intSet.Insert(3);
    intSet.Insert(2);
    intSet.Insert(2);
    intSet.Insert(4);
    std::cout << "IntSet contains: ";
    intSet.Print();
    std::vector<int> vec = { 3, 2, 2, 4 };
    std::vector<int> duplicates = FindDuplicates(vec);
    std::cout << "Found duplicates: ";
    for (int i = 0; i < duplicates.size(); ++i) {
        std::cout << duplicates[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
