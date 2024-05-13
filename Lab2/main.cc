#include <iostream>
#include <string>
#include <cstdlib>      

template<typename K, typename T>
class MyUnorderedMap {
private:
    static const int DEFAULT_SIZE = 100;
    int size;
    std::pair<K, T>* table;

    size_t getHash(const K& key) const {
        return static_cast<size_t>(key) % size;
    }

    size_t pearsonHash(const std::string& text) const {
        size_t hashValue = 0;
        for (char c : text) {
            hashValue = c + (hashValue * 31);
        }
        return hashValue;
    }

public:
    MyUnorderedMap(int size = DEFAULT_SIZE) : size(size), table(new std::pair<K, T>[size]) {}

    MyUnorderedMap(int size, int maxRandomValue) : size(size), table(new std::pair<K, T>[size]) {
        for (int i = 0; i < size; ++i) {
            K key = static_cast<K>(i);
            T value = static_cast<T>(rand() % maxRandomValue); 
            insert(key, value);
        }
    }

    MyUnorderedMap(const MyUnorderedMap& other) : size(other.size), table(new std::pair<K, T>[other.size]) {
        for (int i = 0; i < size; ++i)
            table[i] = other.table[i];
    }

    ~MyUnorderedMap() {
        delete[] table;
    }

    MyUnorderedMap& operator=(const MyUnorderedMap& other) {
        if (this != &other) {
            delete[] table;
            size = other.size;
            table = new std::pair<K, T>[size];
            for (int i = 0; i < size; ++i)
                table[i] = other.table[i];
        }
        return *this;
    }

    void print() const {
        for (int i = 0; i < size; ++i) {
            if (table[i].first != K())
                std::cout << table[i].first << ": " << table[i].second << std::endl;
        }
    }

    void insert(const K& key, const T& value) {
        size_t index = getHash(key);
        while (table[index].first != K()) {
            index = (index + 1) % size; 
        }
        table[index] = std::make_pair(key, value);
    }

    void insert_or_assign(const K& key, const T& value) {
        size_t index = getHash(key);
        while (table[index].first != K() && table[index].first != key) {
            index = (index + 1) % size; 
        }
        table[index] = std::make_pair(key, value);
    }

    bool contains(const T& value) const {
        for (int i = 0; i < size; ++i) {
            if (table[i].second == value)
                return true;
        }
        return false;
    }

    T* search(const K& key) const {
        size_t index = getHash(key);
        while (table[index].first != key && table[index].first != K()) {
            index = (index + 1) % size;
        }
        if (table[index].first == key) {
            return &table[index].second;
        }
        else {
            return nullptr;
        }
    }

    bool erase(const K& key) {
        size_t index = getHash(key);
        size_t originalIndex = index;
        while (table[index].first != key && table[index].first != K()) {
            index = (index + 1) % size; 
            if (index == originalIndex)
                return false;
        }
        table[index].first = K();
        return true;
    }

    int count(const K& key) const {
        int count = 0;
        for (int i = 0; i < size; ++i) {
            if (table[i].first == key)
                ++count;
        }
        return count;
    }

    size_t hashString(const std::string& text) const {
        return pearsonHash(text);
    }

    bool compareHashes(size_t savedHash, const std::string& newText) const {
        size_t newHash = pearsonHash(newText);
        return savedHash == newHash;
    }
};
