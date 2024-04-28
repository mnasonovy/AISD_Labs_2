template<typename K, typename T>
class MyUnorderedMap {
public:
    MyUnorderedMap(int size); 
    MyUnorderedMap(int size, int seed); 
    MyUnorderedMap(const MyUnorderedMap& other); 
    ~MyUnorderedMap(); 

    MyUnorderedMap& operator=(const MyUnorderedMap& other); 

    void print() const; 
    void insert(const K& key, const T& value); 
    void insert_or_assign(const K& key, const T& value); 
    bool contains(const T& value) const; 
    T* search(const K& key) const; 
    bool erase(const K& key); 
    int count(const K& key) const; 

};
