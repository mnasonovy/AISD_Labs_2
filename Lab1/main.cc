#include <iostream>

class IntSet {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;

        explicit Node(int key) : key(key), left(nullptr), right(nullptr) {}
    };

    Node* root;

public:
    IntSet() : root(nullptr) {}

    ~IntSet() {
        Destroy(root);
    }

    IntSet(const IntSet& other) {
        root = Copy(other.root);
    }

    IntSet& operator=(const IntSet& other) {
        if (this != &other) {
            Destroy(root);
            root = Copy(other.root);
        }
        return *this;
    }

    void Print() {
        PrintInOrder(root);
        std::cout << std::endl;
    }

    bool Insert(int key) {
        return InsertNode(root, key);
    }

    bool Contains(int key) const {
        return Search(root, key);
    }

    bool Erase(int key) {
        return DeleteNode(root, key);
    }

private:
    Node* Copy(Node* node) {
        if (node == nullptr)
            return nullptr;
        Node* new_node = new Node(node->key);
        new_node->left = Copy(node->left);
        new_node->right = Copy(node->right);
        return new_node;
    }

    void Destroy(Node* node) {
        if (node != nullptr) {
            Destroy(node->left);
            Destroy(node->right);
            delete node;
        }
    }

    void PrintInOrder(Node* node) {
        if (node != nullptr) {
            PrintInOrder(node->left);
            std::cout << node->key << " ";
            PrintInOrder(node->right);
        }
    }

    bool InsertNode(Node*& node, int key) {
        if (node == nullptr) {
            node = new Node(key);
            return true;
        }
        if (key == node->key)
            return false;
        if (key < node->key)
            return InsertNode(node->left, key);
        else
            return InsertNode(node->right, key);
    }

    bool Search(Node* node, int key) const {
        if (node == nullptr)
            return false;
        if (key == node->key)
            return true;
        if (key < node->key)
            return Search(node->left, key);
        else
            return Search(node->right, key);
    }

    bool DeleteNode(Node*& node, int key) {
        if (node == nullptr)
            return false;
        if (key < node->key)
            return DeleteNode(node->left, key);
        else if (key > node->key)
            return DeleteNode(node->right, key);
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
                DeleteNode(node->right, successor->key);
            }
            return true;
        }
    }
};

