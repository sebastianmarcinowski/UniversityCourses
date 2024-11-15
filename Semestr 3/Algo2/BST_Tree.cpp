
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <random>

using namespace std;

int indeks = 0;
int leftHeight = 0;
int rightHeight = 0;

template <typename T>
struct TreeNode {
    T data;
    TreeNode<T>* parent;
    TreeNode<T>* left;
    TreeNode<T>* right;
    int id;
    TreeNode() {
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }
};

template<typename T>
class BST {
public:
    TreeNode<T>* root;
    int size = 0;
    void insert(T data);
    TreeNode<T>* newNode(TreeNode<T>* node, T data); //a
    TreeNode<T>* find(TreeNode<T>* node, T data); //b 
    TreeNode<T>* remove(TreeNode<T>* node, T data); //c
    TreeNode<T>* findMin(TreeNode<T>* node);
    TreeNode<T>* findMax(TreeNode<T>* node);
    void preorder(TreeNode<T>* node); //d
    void inorder(TreeNode<T>* node); //e
    void clear(TreeNode<T>* root); //f
    int height(TreeNode<T>* node); //g 
    void printout(TreeNode<T>* node); //h  
    void test(int liczba);
};

template<typename T>
TreeNode<T>* BST<T>::newNode(TreeNode<T>* node, T data) {
    if (node == nullptr) {
        node = new TreeNode<T>;
        node->data = data;
        node->left = nullptr;
        node->right = nullptr;
        node->parent = nullptr;
        node->id = indeks;
        size++;
        indeks++;
    }
    else if (node->data < data) {
        node->right = newNode(node->right, data);
        node->right->parent = node;
    }
    else if (node->data > data) {
        node->left = newNode(node->left, data);
        node->left->parent = node;
    }
    return node;
}
template<typename T>
void BST<T>::insert(T data) {
    root = newNode(root, data);
}

template<typename T>
TreeNode<T>* BST<T>::find(TreeNode<T>* node, T data) {
    string p, r, l;
    if (node == nullptr) {
        return nullptr;
    }
    else if (node->data == data) {
        if (node->parent == nullptr) {
            p = "NULL";
        }
        else {
            p = to_string(node->parent->data);
        }
        if (node->left == nullptr) {
            l = "NULL";
        }
        else {
            l = to_string(node->left->data);
        }
        if (node->right == nullptr) {
            r = "NULL";
        }
        else {
            r = to_string(node->right->data);
        }
        cout << node->id << ": [p: " << p << ", l: " << l << ", r: " << r << "], data: " << node->data << endl;
        return node;
    }
    else if (node->data > data) {
        find(node->left, data);
    }
    else {
        find(node->right, data);
    }
}

template<typename T>
TreeNode<T>* BST<T>::remove(TreeNode<T>* node, T data) {
    if (node == nullptr) return node;
    if (node->data > data) {
        node->left = remove(node->left, data);
        return node;
    }
    else if (node->data < data) {
        node->right = remove(node->right, data);
        return node;
    }
    if (node->left == nullptr && node->right == nullptr) {
        // brak potomka
        if (node->parent != nullptr) {
            TreeNode<T>* temp = node->parent;
            if (temp->right == node) {
                temp->right = nullptr;
            }
            else if (temp->left == node) {
                temp->left = nullptr;
            }
        }
        size--;
        delete node;
        node = nullptr;
        return node;
    }
    else if (node->left != nullptr && node->right == nullptr) {
        // potomek z lewej
        TreeNode<T>* temp = node->left;
        if (node->parent != nullptr) {
            temp->parent = node->parent;
            if (node->parent->right == node) node->parent->right = temp;
            else node->parent->left = node;
            size--;
        }
        delete node;
        return temp;
    }
    else if (node->right != nullptr && node->left == nullptr) {
        // potomek z prawej
        TreeNode<T>* temp = node->right;
        if (node->parent != nullptr) {
            temp->parent = node->parent;
            if (node->parent->right == node) node->parent->right = temp;
            else node->parent->left = node;
            size--;
        }
        delete node;
        return temp;
    }
    else {
        // 2 potomkow
        TreeNode<T>* temp = node;
        TreeNode<T>* successor = new TreeNode<T>;
        if (node->right != nullptr) {
            TreeNode<T>* successor = findMin(node->right);
            node->data = successor->data;
            node->right = remove(node->right, successor->data);
        }
        else {
            TreeNode<T>* successor = findMax(node->left);
            node->data = successor->data;
            node->right = remove(node->right, successor->data);
        }
        size--;
        return node;
    }
}

template<typename T>
void BST<T>::printout(TreeNode<T>* node) {
    string p, r, l;
    if (node != nullptr) {
        if (node->parent == nullptr) {
            p = "NULL";
        }
        else {
            p = to_string(node->parent->data);
        }
        if (node->left == nullptr) {
            l = "NULL";
        }
        else {
            l = to_string(node->left->data);
        }
        if (node->right == nullptr) {
            r = "NULL";
        }
        else {
            r = to_string(node->right->data);
        }
        cout << node->id << ": [p: " << p << ", l: " << l << ", r: " << r << "], data: " << node->data << endl;
        printout(node->left);
        printout(node->right);
    }
}

template<typename T>
void BST<T>::preorder(TreeNode<T>* node) {
    // pierw przejscie przez lewe poddrzewo nastepnie przez prawe
    if (node) {
        cout << node->data << " : ";
        preorder(node->left);
        preorder(node->right);
    }
}

template<typename T>
void BST<T>::inorder(TreeNode<T>* node) {
    //od najwiekszego elementu do najmniejszego
    if (node) {
        inorder(node->left);
        cout << node->data << " : ";
        inorder(node->right);
    }
}

template<typename T>
int BST<T>::height(TreeNode<T>* node) {
    if (node == nullptr) {
        return -1;
    }
    else {
        leftHeight = height(node->left);
        rightHeight = height(node->right);
    }
    return max(leftHeight, rightHeight) + 1;
}

template<typename T>
void BST<T>::clear(TreeNode<T>* node) {
    if (size == 0) return;
    while (size > 0) {
        remove(node, node->data);
    }
    root = nullptr;
    indeks = 0;
    size = 0;
}

template<typename T>
TreeNode<T>* BST<T>::findMin(TreeNode<T>* node) {
    while (node->left != nullptr) node = node->left;
    return node;
}
template<typename T>
TreeNode<T>* BST<T>::findMax(TreeNode<T>* node) {
    while (node->right != nullptr) node = node->right;
    return node;
}

template<typename T>
void BST<T>::test(int liczba) {
    for (int i = 0; i <= liczba; i++) {
        insert(rand() % 1000000);
    }
}


int main()
{
    BST<int>* tree = new BST<int>;
    tree->insert(10);
    tree->insert(15);
    tree->insert(12);
    tree->insert(5);
    tree->insert(20);
    tree->insert(30);
    tree->insert(25);
    tree->insert(35);
    tree->insert(7);
    tree->insert(-2);
    tree->insert(33);
    tree->insert(8);


    for (;;) {
        int user_choice;
        cout << "1.Add node" << endl;
        cout << "2.Find node" << endl;
        cout << "3.Remove node" << endl;
        cout << "4.Preorder" << endl;
        cout << "5.Inorder" << endl;
        cout << "6.Clear tree" << endl;
        cout << "7.Tree height" << endl;
        cout << "8.String representation" << endl;
        cout << "9.Test add" << endl;
        cout << "0.Exit" << endl;
        cout << "What you want to do: ";
        cin >> user_choice;
        if (user_choice == 1) {
            int value;
            cout << "Enter value to add: ";
            cin >> value;
            clock_t t1 = clock();
            tree->insert(value);
            clock_t t2 = clock();
            double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
            cout << "Czas wykonania: " << time << endl;
        }
        else if (user_choice == 2) {
            int value;
            cout << "Enter value to find: ";
            cin >> value;
            clock_t t1 = clock();
            tree->find(tree->root, value);
            clock_t t2 = clock();
            double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
            cout << "Czas wykonania: " << time << endl;
        }
        else if (user_choice == 3) {
            int value;
            cout << "Enter value to remove: ";
            cin >> value;
            clock_t t1 = clock();
            tree->remove(tree->root, value);
            clock_t t2 = clock();
            double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
            cout << "Czas wykonania: " << time << endl;
        }
        else if (user_choice == 4) {
            clock_t t1 = clock();
            if (tree->size == 0) cout << "Tree is empty" << endl;
            else tree->preorder(tree->root);
            clock_t t2 = clock();
            double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
            cout << "Czas wykonania: " << time << endl;
        }
        else if (user_choice == 5) {
            clock_t t1 = clock();
            if (tree->size == 0) cout << "Tree is empty" << endl;
            else tree->inorder(tree->root);
            clock_t t2 = clock();
            double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
            cout << "Czas wykonania: " << time << endl;
        }
        else if (user_choice == 6) {
            clock_t t1 = clock();
            tree->clear(tree->root);
            tree->size = 0;
            clock_t t2 = clock();
            double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
            cout << "Czas wykonania: " << time << endl;
        }
        else if (user_choice == 7) {
            clock_t t1 = clock();
            if (tree->size == 0) cout << "Tree is empty" << endl;
            else cout << "Tree height: " << tree->height(tree->root)-1 << endl;
            clock_t t2 = clock();
            double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
            cout << "Czas wykonania: " << time << endl;
        }
        else if (user_choice == 8) {
            clock_t t1 = clock();
            if (tree->size == 0) cout << "Tree is empty" << endl;
            else {
                cout << "Tree size: " << tree->size << endl;
                tree->printout(tree->root);
            }
            clock_t t2 = clock();
            double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
            cout << "Czas wykonania: " << time << endl;
        }
        else if (user_choice == 9) {
            int liczba = 0;
            cout << "How many elements you want to add: " << endl;
            cin >> liczba;
            clock_t t1 = clock();
            tree->test(liczba);
            clock_t t2 = clock();
            double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
            cout << "Czas wykonania: " << time << endl;
        }
        else {
            break;
        }
        system("pause");
        system("cls");
    }
    delete tree;
    return 0;
}