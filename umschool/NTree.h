#pragma once
#include "Tree.h"
#include <initializer_list>
#define right children[1]
#define left children[0]

template<class T>
class AVLTree {
	
private:
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
	Tree<T>* remove(Tree<T>* p, int k) {
		if (!p || !p->height) return 0;
		if (k < p->key)
			p->left = remove(p->left, k);
		else if (k > p->key)
			p->right = remove(p->right, k);
		else {
			Tree<T>* q = p->left;
			Tree<T>* r = p->right;
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
	}
	AVLTree(initializer_list<T> init_list) {
		for (auto i : init_list) {
			root = insert(root, i);
		}
	}

	void push(T key) {
		root = insert(root, key);
	}
	string to_str() {
		return root->to_str("К(1)(2)");
	}
	void erase(T key) {
		root = remove(root, key);
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
};