#include <iostream>
#include <vector>
#include <chrono>
#include "main.cc"

size_t LCG() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

void FillContainer(IntSet& container, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        container.Insert(LCG());
    }
}

double TestFillTime(IntSet& container, size_t size) {
    auto start = std::chrono::high_resolution_clock::now();
    FillContainer(container, size);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

double TestSearchTime(const IntSet& container, size_t numTests) {
    double totalTime = 0.0;

    for (size_t i = 0; i < numTests; ++i) {
        size_t target = LCG();
        auto start = std::chrono::high_resolution_clock::now();
        container.Contains(target);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        totalTime += duration.count();
    }

    return totalTime / numTests;
}

std::pair<double, double> TestInsertDeleteTime(IntSet& container, size_t numTests) {
    double insertTime = 0.0;
    double eraseTime = 0.0;

    for (size_t i = 0; i < numTests; ++i) {
        size_t key = LCG();

        auto start = std::chrono::high_resolution_clock::now();
        container.Insert(key);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        insertTime += duration.count();

        start = std::chrono::high_resolution_clock::now();
        container.Erase(key);
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

    std::cout << "Container Size\tFill Time (s)\tSearch Time (s)\tInsert Time (s)\tDelete Time (s)" << std::endl;

    for (size_t size : {1000, 10000, 100000}) {
        IntSet intSet;
        double fillTime = TestFillTime(intSet, size);

        double searchTime = TestSearchTime(intSet, numTestsSearch);
        auto insertDeleteTime = TestInsertDeleteTime(intSet, numTestsInsertDelete);

        std::cout << size << "\t" << fillTime << "\t" << searchTime << "\t"
            << insertDeleteTime.first << "\t" << insertDeleteTime.second << std::endl;
    }

    std::cout << "\nComparison with std::vector<int>:\n";
    std::cout << "Container Size\tFill Time (s)\tSearch Time (s)\tInsert Time (s)\tDelete Time (s)" << std::endl;

    for (size_t size : {1000, 10000, 100000}) {
        std::vector<int> vec;
        double fillTime = 0.0;

        {
            auto start = std::chrono::high_resolution_clock::now();
            for (size_t i = 0; i < size; ++i) {
                vec.push_back(LCG());
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            fillTime = duration.count();
        }

        double searchTime = 0.0;
        {
            auto start = std::chrono::high_resolution_clock::now();
            for (size_t i = 0; i < numTestsSearch; ++i) {
                size_t target = LCG();
                for (const int& num : vec) {
                    if (num == static_cast<int>(target)) break;
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            searchTime = duration.count() / numTestsSearch;
        }

        double insertTime = 0.0;
        {
            auto start = std::chrono::high_resolution_clock::now();
            for (size_t i = 0; i < numTestsInsertDelete; ++i) {
                size_t key = LCG();
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
                size_t index = LCG() % vec.size();
                vec.erase(vec.begin() + static_cast<int>(index));
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            deleteTime = duration.count() / numTestsInsertDelete;
        }

        std::cout << size << "\t" << fillTime << "\t" << searchTime << "\t"
            << insertTime << "\t" << deleteTime << std::endl;
    }

    std::cout << "Results printed to console." << std::endl;

    return 0;
}
