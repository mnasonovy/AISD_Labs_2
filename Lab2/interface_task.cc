#include <iostream>
#include <string>
#include "main.cc"

struct HashChecker {
    MyUnorderedMap<size_t, std::string> map;

    size_t hashString(const std::string& text) {
        return map.hashString(text);
    }

    bool compareHashes(size_t hash1, size_t hash2) {
        return hash1 == hash2;
    }
};

int main() {
    HashChecker hashChecker;

    std::string text1, text2;
    std::cout << "Enter the first string: ";
    std::getline(std::cin, text1);

    std::cout << "Enter the second string: ";
    std::getline(std::cin, text2);

    size_t hash1 = hashChecker.hashString(text1);
    size_t hash2 = hashChecker.hashString(text2);

    std::cout << "Hash for the first string: " << hash1 << std::endl;
    std::cout << "Hash for the second string: " << hash2 << std::endl;

    bool result = hashChecker.compareHashes(hash1, hash2);
    std::cout << "Do the hashes match: " << std::boolalpha << result << std::endl;

    return 0;
}
