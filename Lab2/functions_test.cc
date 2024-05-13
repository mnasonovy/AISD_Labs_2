#include <iostream>
#include <cassert>
#include <string>
#include "main.cc" 

int main() {
    {
        MyUnorderedMap<int, std::string> map;
        map.insert(1, "One");
        map.insert(2, "Two");
        map.insert(3, "Three");

        std::cout << "Test 1: Insertion" << std::endl;
        std::cout << "Result: " << std::endl;
        map.print();
        std::cout << std::endl;
    }

    {
        MyUnorderedMap<int, std::string> map;
        map.insert_or_assign(1, "One");
        map.insert_or_assign(2, "Two");
        map.insert_or_assign(3, "Three");
        map.insert_or_assign(1, "New One");

        std::cout << "Test 2: Insertion or Assignment" << std::endl;
        std::cout << "Result: " << std::endl;
        map.print();
        std::cout << std::endl;
    }

    {
        MyUnorderedMap<int, std::string> map;
        map.insert(1, "One");
        map.insert(2, "Two");
        map.insert(3, "Three");

        std::cout << "Test 3: Search\n";
        std::cout << "Result:\n";

        auto result = map.search(2);
        if (result != nullptr) {
            std::cout << "Key 2 is found. Value: " << *result << std::endl;
        }
        else {
            std::cout << "Key 2 is not found." << std::endl;
        }
        result = map.search(4);
        if (result != nullptr) {
            std::cout << "Key 4 is found. Value: " << *result << std::endl;
        }
        else {
            std::cout << "Key 4 is not found." << std::endl;
        }
        std::cout << std::endl;
    }

    {
        MyUnorderedMap<int, std::string> map;
        map.insert(1, "One");
        map.insert(2, "Two");
        map.insert(3, "Three");

        std::cout << "Test 4: Erase" << std::endl;
        std::cout << "Result: " << std::endl;
        map.erase(2);
        map.print();
        std::cout << std::endl;
    }

    {
        MyUnorderedMap<int, std::string> map;
        map.insert(1, "One");
        map.insert(2, "Two");
        map.insert(3, "Three");

        std::cout << "Test 5: Contains" << std::endl;
        std::cout << "Result: " << std::endl;
        if (map.contains("One")) {
            std::cout << "True, ";
        }
        else {
            std::cout << "False, ";
        }

        if (map.contains("Four")) {
            std::cout << "True" << std::endl;
        }
        else {
            std::cout << "False" << std::endl;
        }
        std::cout << std::endl;
    }

    {
        MyUnorderedMap<int, std::string> map;
        map.insert(1, "One");
        map.insert(2, "Two");
        map.insert(3, "Three");

        std::cout << "Test 6: Print" << std::endl;
        std::cout << "Result: " << std::endl;
        map.print();
        std::cout << std::endl;
    }

    {
        MyUnorderedMap<int, std::string> map;
        map.insert(1, "One");
        map.insert(2, "Two");
        map.insert(1, "One");

        std::cout << "Test 7: Count" << std::endl;
        std::cout << "Result: " << std::endl;
        std::cout << "1: " << map.count(1) << ", "
            << "2: " << map.count(2) << ", "
            << "3: " << map.count(3) << std::endl;
        std::cout << std::endl;
    }

    std::cout << "All tests passed successfully!" << std::endl;

    return 0;
}
