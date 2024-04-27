#include <iostream>
#include <complex>
#include <string>

template<typename T>
class Set {
private:
    struct Node {
        T key;
        Node* left;
        Node* right;
        int count;

        Node(const T& key) : key(key), left(nullptr), right(nullptr), count(1) {}
    };

    Node* root;

public:
    Set() : root(nullptr) {}

    ~Set() {
        destroy(root);
    }

    Set(const Set& other) {
        root = copy(other.root);
    }

    Set& operator=(const Set& other) {
        if (this != &other) {
            destroy(root);
            root = copy(other.root);
        }
        return *this;
    }

    void print() {
        printInOrder(root);
        std::cout << std::endl;
    }

    bool insert(const T& key) {
        return insertNode(root, key);
    }

    bool contains(const T& key) const {
        return search(root, key);
    }

    size_t count(const T& key) const {
        return countNode(root, key);
    }

    class Iterator {
    private:
        Node* current;
        std::stack<Node*> parents;

    public:
        Iterator(Node* root) {
            current = root;
            while (current != nullptr) {
                parents.push(current);
                current = current->left;
            }
            if (!parents.empty()) {
                current = parents.top();
                parents.pop();
            }
        }

        Iterator& operator++() {
            if (current == nullptr && !parents.empty()) {
                current = parents.top();
                parents.pop();
            }
            if (current != nullptr && current->right != nullptr) {
                Node* temp = current->right;
                while (temp != nullptr) {
                    parents.push(temp);
                    temp = temp->left;
                }
            }
            if (!parents.empty()) {
                current = parents.top();
                parents.pop();
            }
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        const T& operator*() const {
            return current->key;
        }
    };

    Iterator begin() const {
        return Iterator(getLeftmost(root));
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

private:
    Node* copy(Node* node) {
        if (node == nullptr)
            return nullptr;
        Node* newNode = new Node(node->key);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        newNode->count = node->count;
        return newNode;
    }

    void destroy(Node* node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    void printInOrder(Node* node) {
        if (node != nullptr) {
            printInOrder(node->left);
            for (int i = 0; i < node->count; ++i)
                std::cout << node->key << " ";
            printInOrder(node->right);
        }
    }

    bool insertNode(Node*& node, const T& key) {
        if (node == nullptr) {
            node = new Node(key);
            return true;
        }
        if (key == node->key) {
            node->count++;
            return true;
        }
        if (key < node->key)
            return insertNode(node->left, key);
        else
            return insertNode(node->right, key);
    }

    bool search(Node* node, const T& key) const {
        if (node == nullptr)
            return false;
        if (key == node->key)
            return true;
        if (key < node->key)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

    size_t countNode(Node* node, const T& key) const {
        if (node == nullptr)
            return 0;
        if (key == node->key)
            return node->count;
        if (key < node->key)
            return countNode(node->left, key);
        else
            return countNode(node->right, key);
    }

    Node* getLeftmost(Node* node) const {
        if (node == nullptr)
            return nullptr;
        while (node->left != nullptr)
            node = node->left;
        return node;
    }
};
