#include <iostream>
#include <vector>
#include "main.cc"

std::vector<int> findDuplicates(const std::vector<int>& vec) {
    IntSet intSet;
    std::vector<int> duplicates;

    for (int num : vec) {

        if (intSet.Contains(num)) {
            duplicates.push_back(num);
        }
        else {
            intSet.Insert(num);
        }
    }

    return duplicates;
}

int main() {
    std::vector<int> vec = { 3, 2, 2, 4 };

    std::vector<int> duplicates = findDuplicates(vec);

    std::cout << "Duplicate elements: ";
    for (int num : duplicates) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
