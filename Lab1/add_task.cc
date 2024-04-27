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
        Node* parent;
        int count;
        Node(const T& key) : key(key), left(nullptr), right(nullptr), parent(nullptr), count(1) {}
    };
    Node* root;

public:
    Set() : root(nullptr) {}

    ~Set() {
        Destroy(root);
    }

    Set(const Set& other) {
        root = Copy(other.root);
    }

    Set& operator=(const Set& other) {
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

    bool Insert(const T& key) {
        return InsertNode(root, key);
    }

    bool Contains(const T& key) const {
        return Search(root, key);
    }

    size_t Count(const T& key) const {
        return CountNode(root, key);
    }

    size_t Depth() const {
        return CalculateDepth(root);
    }

    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node) : current(node) {}

        Iterator& operator++() {
            if (current == nullptr) return *this;
            if (current->right != nullptr) {
                current = current->right;
                while (current->left != nullptr) current = current->left;
            }
            else {
                Node* p = current->parent;
                while (p != nullptr && current == p->right) {
                    current = p;
                    p = p->parent;
                }
                current = p;
            }
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        const T& operator*() const {
            return current->key;
        }
    };

    Iterator begin() const {
        return Iterator(GetLeftmost(root));
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

private:

    Node* Copy(Node* node) {
        if (node == nullptr)
            return nullptr;
        Node* new_node = new Node(node->key);
        new_node->left = Copy(node->left);
        new_node->right = Copy(node->right);
        new_node->count = node->count;
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
            for (int i = 0; i < node->count; ++i)
                std::cout << node->key << " ";
            PrintInOrder(node->right);
        }
    }

    bool InsertNode(Node*& node, const T& key) {
        if (node == nullptr) {
            node = new Node(key);
            return true;
        }
        if (key == node->key) {
            node->count++;
            return true;
        }
        if (key < node->key) {
            if (node->left == nullptr) {
                node->left = new Node(key);
                node->left->parent = node;
                BalanceTree(node->left); 
                return true;
            }
            return InsertNode(node->left, key);
        }
        else {
            if (node->right == nullptr) {
                node->right = new Node(key);
                node->right->parent = node;
                BalanceTree(node->right); 
                return true;
            }
            return InsertNode(node->right, key);
        }
    }

    bool Search(Node* node, const T& key) const {
        if (node == nullptr)
            return false;
        if (key == node->key)
            return true;
        if (key < node->key)
            return Search(node->left, key);
        else
            return Search(node->right, key);
    }

    size_t CountNode(Node* node, const T& key) const {
        if (node == nullptr)
            return 0;
        if (key == node->key)
            return node->count;
        if (key < node->key)
            return CountNode(node->left, key);
        else
            return CountNode(node->right, key);
    }

    size_t CalculateDepth(Node* node) const {
        if (node == nullptr)
            return 0;
        size_t left_depth = CalculateDepth(node->left);
        size_t right_depth = CalculateDepth(node->right);
        return (left_depth > right_depth) ? (left_depth + 1) : (right_depth + 1);
    }

    Node* GetLeftmost(Node* node) const {
        if (node == nullptr)
            return nullptr;
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    void BalanceTree(Node*& node) {
        if (node == nullptr)
            return;

        int balance = CalculateBalance(node);

        if (balance > 1 && CalculateBalance(node->left) >= 0) {
            node = RotateRight(node);
            return;
        }

        if (balance < -1 && CalculateBalance(node->right) <= 0) {
            node = RotateLeft(node);
            return;
        }

        if (balance > 1 && CalculateBalance(node->left) < 0) {
            node->left = RotateLeft(node->left);
            node = RotateRight(node);
            return;
        }

        if (balance < -1 && CalculateBalance(node->right) > 0) {
            node->right = RotateRight(node->right);
            node = RotateLeft(node);
        }
    }

    int CalculateBalance(Node* node) const {
        if (node == nullptr)
            return 0;
        return CalculateDepth(node->left) - CalculateDepth(node->right);
    }

    Node* RotateRight(Node* node) {
        Node* new_root = node->left;
        node->left = new_root->right;
        if (new_root->right != nullptr)
            new_root->right->parent = node;
        new_root->right = node;
        new_root->parent = node->parent;
        node->parent = new_root;
        return new_root;
    }

    Node* RotateLeft(Node* node) {
        Node* new_root = node->right;
        node->right = new_root->left;
        if (new_root->left != nullptr)
            new_root->left->parent = node;
        new_root->left = node;
        new_root->parent = node->parent;
        node->parent = new_root;
        return new_root;
    }
};

bool operator<(const std::complex<double>& lhs, const std::complex<double>& rhs) {
    if (lhs.real() == rhs.real()) {
        return lhs.imag() < rhs.imag();
    }
    return lhs.real() < rhs.real();
}

bool operator<(const std::complex<float>& lhs, const std::complex<float>& rhs) {
    if (lhs.real() == rhs.real()) {
        return lhs.imag() < rhs.imag();
    }
    return lhs.real() < rhs.real();
}

bool operator<(const std::string& lhs, const std::string& rhs) {
    return lhs.compare(rhs) < 0;
}
