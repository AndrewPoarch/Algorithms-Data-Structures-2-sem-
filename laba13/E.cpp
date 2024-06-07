#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;


struct Node {
    string apple;
    int child_amount = 0;
    Node* left {};
    Node* right {};
    Node* parent {};

    Node(string t_apple):
        apple(t_apple) {}

    Node* Insert(Node* root, string value);

};

Node* Exists(Node* root, string value) {
    while (root != nullptr) {
        if (root->apple == value)
            return root;
        if (root->apple > value)
            root = root->left;
        else if (root->apple < value)
            root = root->right;
    }

    return nullptr;
}

Node* Node::Insert(Node* root, string value) {
    if (root == nullptr) {
        return new Node(value);
    }
    if (value > root->apple) {
        Node* t_node = Insert(root->right, value);
        root->right = t_node;
        t_node->parent = root;
    }
    else if (value <= root->apple) {
        Node* t_node = Insert(root->left, value);
        root->left = t_node;
        t_node->parent = root;
    }
    ++root->child_amount;

    return root;
}

Node* Next(Node* root, string value) {
    Node* answer = nullptr;
    while (root != nullptr) {
        if (root->apple > value) {
            answer = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return answer;
}

void KMax(Node* root,  int k) {
    int l_amount = 0;
    if (root->left != nullptr) {
        l_amount = root->left->child_amount + 1;
    }
    if (l_amount + 1 == k) {
        std::cout << root->apple << '\n';
    } else if (l_amount + 1 > k) {
        KMax(root->left, k);
    } else if (l_amount + 1 < k) {
        KMax(root->right, k - l_amount - 1);
    }
}

int main() {
    int n;
    std::cin >> n;
    Node* root = nullptr;

    for (int i = 0; i < n; ++i) {
        int action = INT_MIN;
        string x;
        std::cin >> x;

        bool is_int = std::all_of(x.begin(), x.end(), ::isdigit);

        if (is_int) {
            int kmax = std::stoi(x);
            KMax(root, kmax);
        } else {
            root = root->Insert(root, x);
        }
    }

    return 0;
}