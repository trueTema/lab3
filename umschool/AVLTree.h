#pragma once
#include "Tree.h"
#include <initializer_list>
#define right children[1]
#define left children[0]

template<class T>
class AVLTree {

private:
	size_t sizeTree;
	Tree<T>* root;
	unsigned char height(Tree<T>* p)
	{
		return p ? p->height : 0;
	}
	int bfactor(Tree<T>* p)
	{
		return height(p->right) - height(p->left);
	}
	Tree<T>* rotateright(Tree<T>* p) {
		Tree<T>* q = p->left;
		p->left = q->right;
		q->right = p;
		root->fixheight(p);
		root->fixheight(q);
		return q;
	}
	Tree<T>* rotateleft(Tree<T>* q)
	{
		Tree<T>* p = q->right;
		q->right = p->left;
		p->left = q;
		root->fixheight(q);
		root->fixheight(p);
		return p;
	}
	Tree<T>* balance(Tree<T>* p) // балансировка узла p
	{
		root->fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p;
	}
	Tree<T>* insert(Tree<T>* p, T k) // вставка ключа k в дерево с корнем p
	{
		if (!p || !p->height) {
			Tree<T>* cur = root->makeNode(k, 2);
			cur->height = 1;
			sizeTree++;
			return cur;
		}
		if (k < p->key)
			p->left = insert(p->left, k);
		else if (k > p->key)
			p->right = insert(p->right, k);
		else return p;
		return balance(p);
	}
	bool find(T key, Tree<T>* p) {
		if (!p || !p->height) return false;
		if (p->key == key) {
			return true;
		}
		return find(key, p->left) || find(key, p->right);
	}
	Tree<T>* findmin(Tree<T>* p)
	{
		return p->left ? findmin(p->left) : p;
	}
	Tree<T>* removemin(Tree<T>* p)
	{
		if (p->left == nullptr)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}
	Tree<T>* remove(Tree<T>* p, T k) {
		if (!p || !p->height) return 0;
		if (k < p->key)
			p->left = remove(p->left, k);
		else if (k > p->key)
			p->right = remove(p->right, k);
		else {
			Tree<T>* q = p->left;
			Tree<T>* r = p->right;
			sizeTree--;
			delete p;
			if (!r) return q;
			Tree<T>* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}
public:
	AVLTree() {
		root = nullptr;
		sizeTree = 0;
	}
	AVLTree(initializer_list<T> init_list) {
		for (auto i : init_list) {
			root = insert(root, i);
		}
	}
	AVLTree(vector<T>& vect) {
		for (auto i : vect) {
			root = insert(i);
		}
	}

	void push(T key) {
		root = insert(root, key);
	}
	string to_str() {
		return root->to_str("К(1)(2)");
	}
	string to_str(string travel) {
		return root->to_str(travel);
	}
	void erase(T key) {
		root = remove(root, key);
	}
	size_t size() {
		return sizeTree;
	}
	void concat(AVLTree<T>& another) {
		vector<T> another_vect = *(another.to_array());
		for (int i = 0; i < another_vect.size(); i++) {
			push(another_vect[i]);
		}
	}
	vector<T>* to_array() {
		vector<Tree<T>*> x;
		x = root->travelsal("(1)К(2)");
		vector<T>* res = new vector<T>;
		for (int i = 0; i < x.size(); i++) {
			res->push_back(x[i]->key);
		}
		return res;
	}
	bool find(T key) {
		return find(key, root);
	}

	bool Equals(AVLTree<T>& another) {
		return root->Equals(*another.root);
	}

	bool IsSubTree(AVLTree<T>& another) {
		return root->IsSubTree(*another.root);
	}

	AVLTree<T>* where(bool f(T)) {
		vector<T> cur = *(this->to_array());
		AVLTree<T>* res = new AVLTree<T>;
		for (int i = 0; i < cur.size(); i++) {
			if (f(cur[i]))
			res->push(cur[i]);
		}
		return res;
	}

	AVLTree<T>* map(T change(T)) {
		vector<T> cur = *(this->to_array());
		AVLTree<T>* res = new AVLTree<T>;
		for (int i = 0; i < cur.size(); i++) {
			res->push(change(cur[i]));
		}
		return res;
	}

	bool operator ==(AVLTree<T>&);
	bool operator >(AVLTree<T>&);
};

template<typename T>
bool AVLTree<T>::operator ==(AVLTree<T>& another) {
	return this->Equals(another);
}
template<typename T>
bool AVLTree<T>::operator >(AVLTree<T>& another) {
	return this->IsSubTree(another);
}