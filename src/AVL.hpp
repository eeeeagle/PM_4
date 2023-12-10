#pragma once
#ifndef AVL_TREE
#define AVL_TREE
#include <iostream>

template <typename T>
class AVL
{
private:
    class Node
    {
    public:
        T value;
        Node* left, * right;
        int height;

        Node(const T& value)
            : left(nullptr), right(nullptr), value(value), height(0)
        {}

        Node(const Node& node)
            : value(node.value), left(nullptr), right(nullptr), height(node.height)
        {}
    }*root;

    int height(Node* node)
    {
        int t;
        if (node == NULL)
        {
            return -1;
        }
        else
        {
            t = node->height;
            return t;
        }
    }

    Node* rotate_l(Node*& root)
    {
        Node* root2 = root->left;
        root->left = root2->right;
        root2->right = root;
        root->height = std::max(height(root->left), height(root->right)) + 1;
        root2->height = std::max(height(root2->left), root->height) + 1;
        return root2;
    }

    Node* rotate_r(Node*& root)
    {
        Node* root2 = root->right;
        root->right = root2->left;
        root2->left = root;
        root->height = std::max(height(root->left), height(root->right)) + 1;
        root2->height = std::max(root->height, height(root2->right)) + 1;
        return root2;
    }

    Node* b_rotate_left(Node*& root)
    {
        root->left = rotate_r(root->left);
        return rotate_l(root);
    }

    Node* b_rotate_right(Node*& root)
    {
        root->right = rotate_l(root->right);
        return rotate_r(root);
    }

    Node* insert(T value, Node*& node)
    {
        if (node == nullptr)
        {
            node = new Node(value);
            return node;
        }

        if (value < node->value)
        {
            insert(value, node->left);
            if ((height(node->left) - height(node->right)) == 2)
            {
                if (value < (node->left)->value)
                    node = rotate_l(node);
                else
                    node = b_rotate_left(node);
            }
        }
        else if (value > node->value)
        {
            insert(value, node->right);
            if ((height(node->right) - height(node->left)) == 2)
            {
                if (value > (node->right)->value)
                    node = rotate_r(node);
                else
                    node = b_rotate_right(node);
            }
        }
        else
            return nullptr;

        node->height = std::max(height(node->left), height(node->right)) + 1;
        return node;
    }

    T delete_min(Node*& root)
    {
        if (root->left == NULL)
        {
            T temp = root->value;
            root = root->right;
            return temp;
        }
        else
            return delete_min(root->left);
    }

    void erase(T value, Node*& root)
    {
        Node* temp;
        if (root == NULL)
            return;
        else if (value < root->value)
            erase(value, root->left);
        else if (value > root->value)
            erase(value, root->right);
        else if ((root->left == NULL) && (root->right == NULL))
        {
            temp = root;
            delete temp;
            root = NULL;
        }
        else if (root->left == NULL)
        {
            temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL)
        {
            temp = root;
            root = root->left;
            delete temp;
        }
        else
            root->value = delete_min(root->right);
    }

    void print(Node* ptr, int space = 0) const
    {
        if (ptr == NULL)
            return;

        print(ptr->right, space + 1);

        std::cout << std::endl;
        for (int i = 0; i < space; i++)
            std::cout << "     ";
        std::cout << '[' << ptr->value << ']' << std::endl;

        print(ptr->left, space + 1);
    }

    Node* copy_tree(Node* node)
    {
        if (node == nullptr)
            return nullptr;
        Node* new_node = new Node(*node);
        new_node->left = copy_tree(node->left);
        new_node->right = copy_tree(node->right);
        return new_node;
    }

    void delete_tree(Node* node)
    {
        if (node)
        {
            delete_tree(node->left);
            delete_tree(node->right);
            delete node;
        }
    }

public:

    AVL()
        : root(nullptr)
    {}

    AVL(const AVL<T>& tree)
        : root(nullptr)
    {
        root = copy_tree(tree.root);
    }

    ~AVL()
    {
        delete_tree(root);
    }

    AVL<T>& operator =(const AVL<T>& tree)
    {
        AVL res(tree);
        std::swap(root, res.root);
        return *this;
    }

    bool insert(T value)
    {
        if (insert(value, root))
            return true;
        return false;
    }

    void print() const
    {
        print(root);
    }

    void erase(T value)
    {
        erase(value, root);
    }
};
#endif