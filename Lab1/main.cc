#include <iostream>

class IntSet {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;

        Node(int key) : key(key), left(nullptr), right(nullptr) {}
    };

    Node* root;

public:
    IntSet() : root(nullptr) {}

    ~IntSet() {
        destroy(root);
    }

    IntSet(const IntSet& other) {
        root = copy(other.root);
    }

    IntSet& operator=(const IntSet& other) {
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

    bool insert(int key) {
        return insertNode(root, key);
    }

    bool contains(int key)const {
        return search(root, key);
    }

    bool erase(int key) {
        return deleteNode(root, key);
    }

private:
    Node* copy(Node* node) {
        if (node == nullptr)
            return nullptr;
        Node* newNode = new Node(node->key);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
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
            std::cout << node->key << " ";
            printInOrder(node->right);
        }
    }

    bool insertNode(Node*& node, int key) {
        if (node == nullptr) {
            node = new Node(key);
            return true;
        }
        if (key == node->key)
            return false;
        if (key < node->key)
            return insertNode(node->left, key);
        else
            return insertNode(node->right, key);
    }

    bool search(Node* node, int key)const {
        if (node == nullptr)
            return false;
        if (key == node->key)
            return true;
        if (key < node->key)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

    bool deleteNode(Node*& node, int key) {
        if (node == nullptr)
            return false;
        if (key < node->key)
            return deleteNode(node->left, key);
        else if (key > node->key)
            return deleteNode(node->right, key);
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                node = temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                node = temp;
            }
            else {
                Node* successor = node->right;
                while (successor->left != nullptr)
                    successor = successor->left;
                node->key = successor->key;
                deleteNode(node->right, successor->key);
            }
            return true;
        }
    }
};