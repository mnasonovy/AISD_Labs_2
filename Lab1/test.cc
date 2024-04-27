#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include "main.cc"

#include <cstdlib> 

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

void fillContainer(IntSet& container, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        container.insert(lcg());
    }
}

double testFillTime(IntSet& container, size_t size) {
    auto start = std::chrono::high_resolution_clock::now();
    fillContainer(container, size);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

double testSearchTime(const IntSet& container, size_t numTests) {
    double totalTime = 0.0;

    for (size_t i = 0; i < numTests; ++i) {
        size_t target = lcg();
        auto start = std::chrono::high_resolution_clock::now();
        container.contains(target);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        totalTime += duration.count();
    }

    return totalTime / numTests;
}

std::pair<double, double> testInsertDeleteTime(IntSet& container, size_t numTests) {
    double insertTime = 0.0;
    double eraseTime = 0.0;

    for (size_t i = 0; i < numTests; ++i) {
        size_t key = lcg();

        auto start = std::chrono::high_resolution_clock::now();
        container.insert(key);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        insertTime += duration.count();

        start = std::chrono::high_resolution_clock::now();
        container.erase(key);
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        eraseTime += duration.count();
    }

    return { insertTime / numTests, eraseTime / numTests };
}

int main() {
    size_t numTestsFill = 100;
    size_t numTestsSearch = 1000;
    size_t numTestsInsertDelete = 1000;

    std::cout << std::setw(15) << "Container Size" << std::setw(20) << "Fill Time (s)" << std::setw(20)
        << "Search Time (s)" << std::setw(20) << "Insert Time (s)" << std::setw(20) << "Delete Time (s)" << std::endl;

    for (size_t size : {1000, 10000, 100000}) {
        IntSet intSet;
        double fillTime = testFillTime(intSet, size);

        double searchTime = testSearchTime(intSet, numTestsSearch);
        auto insertDeleteTime = testInsertDeleteTime(intSet, numTestsInsertDelete);

        std::cout << std::setw(15) << size << std::setw(20) << fillTime << std::setw(20) << searchTime << std::setw(20)
            << insertDeleteTime.first << std::setw(20) << insertDeleteTime.second << std::endl;
    }

    std::cout << "\nComparison with std::vector<int>:\n";
    std::cout << std::setw(15) << "Container Size" << std::setw(20) << "Fill Time (s)" << std::setw(20)
        << "Search Time (s)" << std::setw(20) << "Insert Time (s)" << std::setw(20) << "Delete Time (s)" << std::endl;

    for (size_t size : {1000, 10000, 100000}) {
        std::vector<int> vec;
        double fillTime = 0.0;

        {
            auto start = std::chrono::high_resolution_clock::now();
            for (size_t i = 0; i < size; ++i) {
                vec.push_back(lcg());
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            fillTime = duration.count();
        }

        double searchTime = 0.0;
        {
            auto start = std::chrono::high_resolution_clock::now();
            for (size_t i = 0; i < numTestsSearch; ++i) {
                size_t target = lcg();
                std::find(vec.begin(), vec.end(), static_cast<int>(target));
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            searchTime = duration.count() / numTestsSearch;
        }

        double insertTime = 0.0;
        {
            auto start = std::chrono::high_resolution_clock::now();
            for (size_t i = 0; i < numTestsInsertDelete; ++i) {
                size_t key = lcg();
                vec.push_back(static_cast<int>(key));
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            insertTime = duration.count() / numTestsInsertDelete;
        }

        double deleteTime = 0.0;
        {
            auto start = std::chrono::high_resolution_clock::now();
            for (size_t i = 0; i < numTestsInsertDelete; ++i) {
                size_t index = lcg() % vec.size();
                vec.erase(vec.begin() + static_cast<int>(index));
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            deleteTime = duration.count() / numTestsInsertDelete;
        }

        std::cout << std::setw(15) << size << std::setw(20) << fillTime << std::setw(20) << searchTime << std::setw(20)
            << insertTime << std::setw(20) << deleteTime << std::endl;
    }

    std::cout << "Results printed to console." << std::endl;

    return 0;
}
