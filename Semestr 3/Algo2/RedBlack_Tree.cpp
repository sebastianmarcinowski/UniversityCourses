
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <random>
#include <string>
using namespace std;

int indeks = 0;
int leftHeight = 0;
int rightHeight = 0;

template<typename T>
struct TreeNode{
	T data;
	TreeNode<T>* parent;
	TreeNode<T>* left;
	TreeNode<T>* right;
	int id;
	bool color; // 1->czerwony, 0->czarny
	TreeNode() {
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}
};

template<typename T>
class RBT {
public:
	TreeNode<T>* root;
	int size = 0;
	void insert(T data); //f
	TreeNode<T>* newNode(TreeNode<T>* node, T data); //f
	TreeNode<T>* insertFix(TreeNode<T>* node, T data); //pomocniczna
	TreeNode<T>* findandprint(TreeNode<T>* node, T data); //b
	TreeNode<T>* find(TreeNode<T>* node, T data);
	void preorder(TreeNode<T>* node); //b
	void inorder(TreeNode<T>* node); //c
	void clear(TreeNode<T>* node); //d
	int height(TreeNode<T>* node); //e
	void printout(TreeNode<T>* node); //g
	void rotateLeft(TreeNode<T>* node, TreeNode<T>* nodeParent); //h
	void rotateRight(TreeNode<T>* node, TreeNode<T>* nodeParent); //i
	void test(int liczba); //dodawanie wielu elementow
	TreeNode<T>* findMin(TreeNode<T>* node); //pomocnicza
	TreeNode<T>* findMax(TreeNode<T>* node); //pomocnicza
	TreeNode<T>* remove(TreeNode<T>* node, T data); //pomocnicza
};

template<typename T>
TreeNode<T>* RBT<T>::newNode(TreeNode<T>* node, T data) {
	if (node == nullptr) {
		node = new TreeNode<T>;
		node->data = data;
		node->left = nullptr;
		node->right = nullptr;
		node->parent = nullptr;
		node->id = indeks;
		node->color = 1;
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
	if (node == root) root->color = 0;

	return node;
}

template<typename T>
void RBT<T>::insert(T data) {
	root = newNode(root, data);
	insertFix(root, data);
	root->color = 0;
}

template<typename T>
TreeNode<T>* RBT<T>::insertFix(TreeNode<T>* node, T data) {
	node = find(root, data);
	if (node->parent == nullptr || node->parent->color == 0) {
		return nullptr;
	}
	else {
		while (node != nullptr && node != root && node->parent != nullptr && node->parent->color == 1) {
			TreeNode<T>* nodeParent = node->parent;
			TreeNode<T>* nodeUncle = nullptr;
			TreeNode<T>* nodeGP = node->parent->parent;
			if (nodeGP != nullptr && nodeParent == nodeGP->left) {
				nodeUncle = nodeGP->right;
			}
			else if (nodeGP != nullptr && nodeParent == nodeGP->right) {
				nodeUncle = nodeGP->left;
			}
			if (nodeUncle == nullptr || nodeUncle->color == 0) {
				if (nodeGP != nullptr && nodeParent == nodeGP->right && node == nodeParent->right) {
					rotateLeft(nodeParent, nodeGP);
					nodeParent->color = !(nodeParent->color);
					nodeGP->color = !(nodeGP->color);
				}
				else if (nodeGP != nullptr && nodeParent == nodeGP->right && node == nodeParent->left) {
					rotateRight(node, nodeParent);
					rotateLeft(node, nodeGP);
					node->color = !(node->color);
					nodeGP->color = !(nodeGP->color);
				}
				else if (nodeGP != nullptr && nodeParent == nodeGP->left && node == nodeParent->left) {
					rotateRight(nodeParent, nodeGP);
					nodeParent->color = !(nodeParent->color);
					nodeGP->color = !(nodeGP->color);
				}
				else if (nodeGP != nullptr && nodeParent == nodeGP->left && node == nodeParent->right) {
					rotateLeft(node, nodeParent);
					rotateRight(node, nodeGP);
					node->color = !(node->color);
					nodeGP->color = !(nodeGP->color);
				}
				if (node->parent != nullptr) {
					node = node->parent->parent;
				}
				else node = nullptr;
			}
			else if (nodeUncle != nullptr && nodeUncle->color == 1) {
				nodeParent->color = !nodeParent->color;
				nodeUncle->color = !nodeUncle->color;
				if (nodeGP != root) {
					nodeGP->color = !nodeGP->color;
				}
				if (node->parent != nullptr) {
					node = node->parent->parent;
				}
				else node = nullptr;
			}
		}
	}
	return node;
}


template<typename T>
void RBT<T>::rotateRight(TreeNode<T>* node, TreeNode<T>* nodeParent) {
	if (node == root || node->parent == nullptr) {
		return;
	}
	else {
		node->parent = nodeParent->parent;
		nodeParent->left = node->right;
		if (node->right != nullptr) {
			node->right->parent = nodeParent;
		}
		else node->right = nullptr;
		if (nodeParent->parent != nullptr && nodeParent->parent->right == nodeParent) {
			nodeParent->parent->right = node;
		}
		else if (nodeParent->parent != nullptr && nodeParent->parent->left == nodeParent) {
			nodeParent->parent->left = node;
		}
		nodeParent->parent = node;
		node->right = nodeParent;
		if (node->parent == nullptr) {
			root = node;
		}
	}
}
template<typename T>
void RBT<T>::rotateLeft(TreeNode<T>* node, TreeNode<T>* nodeParent) {
	if (node == root || node->parent == nullptr) {
		return;
	}
	else {
		node->parent = nodeParent->parent;
		nodeParent->right = node->left;
		if (node->left != nullptr) {
			node->left->parent = nodeParent;
		}
		else node->left = nullptr;
		if (nodeParent->parent != nullptr && nodeParent->parent->right == nodeParent) {
			nodeParent->parent->right = node;
		}
		else if (nodeParent->parent != nullptr && nodeParent->parent->left == nodeParent) {
			nodeParent->parent->left = node;
		}
		nodeParent->parent = node;
		node->left = nodeParent;
		if (node->parent == nullptr) {
			root = node;
		}
	}
}

template<typename T>
TreeNode<T>* RBT<T>::findandprint(TreeNode<T>* node, T data) {
	string p, l, r, c;
	if (node == nullptr) return nullptr;
	else if (node->data == data) {
		if (node->parent == nullptr) p = "NULL";
		else p = to_string(node->parent->data);

		if (node->left == nullptr) l = "NULL";
		else l = to_string(node->left->data);

		if (node->right == nullptr) r = "NULL";
		else r = to_string(node->right->data);

		if (node->color == true) c = "red";
		else c = "black";

		cout << node->id << ": [c: " << c << " p: " << p << ", l : " << l << ", r : " << r << "], data: " << node->data << endl;
	}
	else if (node->data > data) {
		findandprint(node->left, data);
	}
	else if (node->data < data) {
		findandprint(node->right, data);
	}
	return node;
}

template<typename T>
TreeNode<T>* RBT<T>::find(TreeNode<T>* node, T data) {
	if (node == nullptr) return nullptr;
	else if (node->data > data) {
		node = find(node->left, data);
	}
	else if (node->data < data) {
		node = find(node->right, data);
	}
	return node;
}

template<typename T>
TreeNode<T>* RBT<T>::findMin(TreeNode<T>* node) {
	while (node->left != nullptr) node = node->left;
	return node;
}
template<typename T>
TreeNode<T>* RBT<T>::findMax(TreeNode<T>* node) {
	while (node->right != nullptr) node = node->right;
	return node;
}

template<typename T>
void RBT<T>::preorder(TreeNode<T>* node) {
	if (node) {
		cout << node->data << " : ";
		preorder(node->left);
		preorder(node->right);
	}
}

template<typename T>
void RBT<T>::inorder(TreeNode<T>* node) {
	if (node) {
		inorder(node->left);
		cout << node->data << " : ";
		inorder(node->right);
	}
}
template<typename T>
TreeNode<T>* RBT<T>::remove(TreeNode<T>* node, T data) {
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
void RBT<T>::clear(TreeNode<T>* node) {
	if (size == 0) return;
	while (size > 0) {
		remove(node, node->data);
	}
	root = nullptr;
	indeks = 0;
	size = 0;
}

template<typename T>
int RBT<T>::height(TreeNode<T>* node) {
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
void RBT<T>::printout(TreeNode<T>* node) {
	string p, r, l, c;
	if (node != nullptr) {
		if (node->parent == nullptr) p = "NULL";
		else p = to_string(node->parent->data);

		if (node->left == nullptr) l = "NULL";
		else l = to_string(node->left->data);

		if (node->right == nullptr) r = "NULL";
		else r = to_string(node->right->data);

		if (node->color == true) c = "red";
		else if (node->color == false) c = "black";

		cout << node->id << ": [c: " << c << " p: " << p << ", l : " << l << ", r : " << r << "], data: " << node->data << endl;
		if(node->left != nullptr) printout(node->left);
		if(node->right != nullptr) printout(node->right);
	}
}

template<typename T>
void RBT<T>::test(int liczba) {
	for (int i = 0; i <= liczba; i++) {
		insert(rand() % 100000);
	}
}

int main() {
	RBT<int>* tree = new RBT<int>;

	/*tree->insert(10);
	tree->insert(18);
	tree->insert(7);
	tree->insert(15);
	tree->insert(16);
	tree->insert(30);
	tree->insert(25);
	tree->insert(40);
	tree->insert(60);
	tree->insert(2);
	tree->insert(1);
	tree->insert(70);
	tree->printout(tree->root);*/
	
	for (;;) {
		int user_choice;
		cout << "1.Add" << endl;
		cout << "2.Find" << endl;
		cout << "3.Preorder" << endl;
		cout << "4.Inorder" << endl;
		cout << "5.Clear" << endl;
		cout << "6.Height" << endl;
		cout << "7.Printout" << endl;
		cout << "8.Test add" << endl;
		cout << "0.Exit" << endl;
		cout << "Choose option: ";
		cin >> user_choice;
		if (user_choice == 1) {
			int data;
			cout << "Enter data to add: ";
			cin >> data;
			clock_t t1 = clock();
			tree->insert(data);
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Execution time: " << time << endl;
		}
		else if (user_choice == 2) {
			int data;
			cout << "Enter data to find: ";
			cin >> data;
			clock_t t1 = clock();
			tree->findandprint(tree->root,data);
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Execution time: " << time << endl;
		}
		else if (user_choice == 3) {
			clock_t t1 = clock();
			tree->preorder(tree->root);
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Execution time: " << time << endl;
		}
		else if (user_choice == 4) {
			clock_t t1 = clock();
			tree->inorder(tree->root);
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Execution time: " << time << endl;
		}
		else if (user_choice == 5) {
			clock_t t1 = clock();
			tree->clear(tree->root);
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Execution time: " << time << endl;
		}
		else if (user_choice == 6) {
			clock_t t1 = clock();
			cout << tree->height(tree->root) << endl;
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Execution time: " << time << endl;
		}
		else if (user_choice == 7) {
			clock_t t1 = clock();
			tree->printout(tree->root);
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Execution time: " << time << endl;
		}
		else if (user_choice == 8) {
			clock_t t1 = clock();
			tree->test(100000);
			cout << tree->size;
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Execution time: " << time << endl;
		}
		else {
			break;
		}
		system("pause");
		system("cls");
	}

	return 0;
}