#pragma once
#include <string>
#include <vector>
#include <map>
#include <istream>
#include <iostream>
#include <algorithm>
#include <initializer_list>
#include "complex.h"
#include "Person.h"
//#include "AVLTree.h"
//#include "NTree.h"

#define ll long long 

using namespace std;

const ll none = ll(INT32_MAX) * 2 + 1;

std::string getTravelStep(std::string& s) {
	if (s == "") return "";
	int type1_open = s.find('(');
	int type2_open = s.find('[');
	int type3_open = s.find('{');
	int type1_close = s.find(')');
	int type2_close = s.find(']');
	int type3_close = s.find('}');
	
	int first = 1e9;
	int second = 1e9;
	first = type1_open != -1 ? min(first, type1_open) : first;
	first = type2_open != -1 ? min(first, type2_open) : first;
	first = type3_open != -1 ? min(first, type3_open) : first;
	second = type1_close != -1 ? min(second, type1_close) : second;
	second = type2_close != -1 ? min(second, type2_close) : second;
	second = type3_close != -1 ? min(second, type3_close) : second;

	if (first == 1e9 && second == 1e9) {
		if (s == "К" || s == "K") {
			s = "";
			return "К";
		}
		else {
			throw "IncorrectFormat";
		}
	}
	else if ((first == 1e9) ^ (second == 1e9)) {
		throw "IncorrectFormat";
	}
	else {
		std::string cur = "";
		if (first == 1) {
			cur = s[0];
			s.erase(s.begin(), s.begin() + 1);
			return cur;
		}
		if (s == "") {
			return cur;
		}
		cur = s.substr(first, second - first + 1);
		s.erase(s.begin() + first, s.begin() + second + 1);
		return cur;
	}
}

bool IsOpen(char s) {
	return s == '{' || s == '(' || s == '[';
}

bool IsClose(char s) {
	return s == '}' || s == ')' || s == ']';
}

string getReadStep(string& s) {
	if (s == "") {
		return s;
	}
	if (IsOpen(s[0]) || IsClose(s[0])) {
		throw "Incorrect Format";
		return "";
	}
	int first = min(min(s.find('('), s.find('[')), s.find('{'));
	s.erase(s.begin(), s.begin() + first - 1);
	int second = first;
	string res;
	int balance = 0;
	for (int i = first; i < s.size(); i++, second++) {
		if (IsOpen(s[i])) {
			balance += 1;
		}
		else if (IsClose(s[i])) {
			balance -= 1;
		}
		if (balance == 0) {
			break;
		}
	}
}

template<typename T>
class Tree {
	template<typename V> friend class AVLTree;
private:
	size_t n;
	T key;
	size_t number;
	unsigned char height;
	Tree** children;
	Tree* parent;
	Tree* makeNode(T data, size_t n);
	void make_tree(Tree*, Tree*); //yes
	void read_tree(Tree*, string, vector<T>&, size_t&); //yes
	Tree* getLowest(Tree*);//f[f[g[g]]]
	void erase(Tree*, T);

	void fixheight(Tree*);

	void pushItem(Tree*, std::string, T); //yes
	void pushItem(Tree*, size_t, T); //yes
	void travelsal(vector<Tree*>&, Tree*, string);//(1)К(2)
	void travelsal(vector<Tree*>&, Tree*);
	std::string to_str(Tree*, std::vector<std::pair<int, std::vector<char>>>&);

	vector<pair<int, vector<char>>>* travelSteps(string);

	bool Equals(Tree*, Tree*);
	bool IsSubTree(Tree*, Tree*);

	void where(bool(T), Tree*, vector<Tree*>&, size_t&);
	Tree(T, size_t); //yes
public:
	Tree(size_t); //yes
	Tree(const Tree<T>&); //yes
	Tree(string, vector<T>&, size_t); //yes
	Tree(string, initializer_list<T>, size_t); //yes
	~Tree();
	//Ntree(string, initializer_list);
	//Tree(size_t, std::istream&, std::string);
	void pushItem(std::string, T);// yes
	T findItem(std::string); 
	T findItem(Tree<T>*, std::string);
	Tree* findNode(Tree* cur, string&);
	Tree<T> GetSubTree(string);

	vector<Tree*> travelsal(string);
	vector<Tree*> travelsal();


	std::string to_str(std::string);
	bool Equals(Tree<T>&);
	bool operator ==(Tree<T>&);
	bool IsSubTree(Tree<T>&);
	bool operator >(Tree<T>&);
	friend ostream& operator << (ostream&, Tree<T>&);
	void map(T(T));
	Tree<T> where(bool(T)); //may be

	void erase(T key); //yes
	void remove(Tree<T>*); //yes
};

//конструкторы
template<typename T>
Tree<T>::Tree(size_t n) {
	this->n = n;
}

template<typename T>
Tree<T>::Tree(T data, size_t n) {
	key = data;
	this->n = n;
	children = new Tree<T>*[n];
	for (int i = 0; i < n; i++) children[i] = nullptr;
}

template<typename T>
Tree<T>::Tree(string treeorder, vector<T>& init, size_t n) {
	this->n = n;
	key = T();
	children = new Tree<T>*[n];
	for (int i = 0; i < n; i++) children[i] = nullptr;
	size_t start = 0;
	read_tree(this, treeorder, init, start);
}

template<typename T>
Tree<T>::Tree(string treeorder, initializer_list<T> init, size_t n) {
	this->n = n;
	key = T();
	children = new Tree<T>*[n];
	for (int i = 0; i < n; i++) children[i] = nullptr;
	size_t start = 0;
	vector<int> a;
	for (auto i : init) {
		a.push_back(i);
	}
	read_tree(this, treeorder, a, start);
}

template<typename T>
Tree<T>::~Tree() {
	for (int i = 0; i < n; i++) {
		delete children[i];
	}
	delete children;
}

template<typename T>
void Tree<T>::read_tree(Tree* cur, string s, vector<T>& init, size_t& j) {
	if (s == "") {
		return;
	}
	if (IsOpen(s[0]) || IsClose(s[0])) {
		throw "Format-String Incorrect Format";
	}
	if (j >= init.size()) {
		throw "Format-String and init_list size mismatch";
	}
	cur->key = init[j];
	j++;
	int first = min(min(s.find('('), s.find('[')), s.find('{'));
	size_t iteration = 0;
	while (first != -1) {
		int second = first;
		
		int balance = 0;
		for (int i = first; i < s.size(); i++, second++) {
			if (IsOpen(s[i])) {
				balance += 1;
			}
			else if (IsClose(s[i])) {
				balance -= 1;
			}
			if (balance == 0) {
				break;
			}
		}
		if (second - first > 1) {
			cur->children[iteration] = makeNode(T(), this->n);	
			cur->children[iteration]->parent = cur;
			cur->children[iteration]->number = iteration;
			cur->children[iteration]->height = 1;
			read_tree(cur->children[iteration], s.substr(first + 1, second - first - 1), init, j);
		}
		first = min(min(s.find('(',second+1), s.find( '[',second+1)), s.find('{',second+1));
		iteration++;
	}
	fixheight(cur);
}

template<typename T>
Tree<T>::Tree(const Tree<T>& tree) {
	if (&tree == nullptr) return;
	key = tree.key;
	this->n = tree.n;
	this->height = tree.height;
	children = new Tree<T>*[n];
	for (int i = 0; i < n; i++) children[i] = nullptr;
	for (int i = 0; i < n; i++) {
		if (tree.children[i]) {
			this->children[i] = makeNode(tree.children[i]->key, this->n);
			this->children[i]->height = tree.children[i]->height;
			this->children[i]->parent = this;
			this->children[i]->number = i;
			make_tree(children[i], tree.children[i]);
		}
	}
}


//template<typename T>
//Tree<T>::~Tree() {
//	delete this->children;
//	delete this->parent;
//}
//служебные методы

template<typename T>
Tree<T>* Tree<T>::makeNode(T data, size_t n) {
	Tree<T>* res = new Tree<T>(data, n);
	return res;
}
template<typename T>
void Tree<T>::make_tree(Tree* cur, Tree* curtree) {
	if (!curtree) return;
	for (int i = 0; i < n; i++) {
		if (curtree->children[i]) {
			pushItem(cur, i+1, curtree->children[i]->key);
			make_tree(cur->children[i], curtree->children[i]);
		}
	}
}

template<typename T>
std::vector<std::pair<int, std::vector<char>>>* Tree<T>::travelSteps(string travel) {
	std::vector<std::pair<int, std::vector<char>>>* res = new std::vector<std::pair<int, std::vector<char>>>;
	std::string curStep;
	while ((curStep = getTravelStep(travel)) != "") {
		int curPos;
		if (curStep == "К" || curStep == "K") {
			curPos = 0;
		}
		else {
			curPos = stoi(curStep.substr(1, curStep.size() - 2));
		}
		res->push_back({ curPos, { curStep[0], curStep[curStep.size() - 1] } });
	}
	return res;
}

template<typename T>
void Tree<T>::fixheight(Tree<T>* cur) {
	int mx = 0;
	for (int i = 0; i < n; i++) {
		if (cur->children[i] && cur->children[i]->height > mx) {
			mx = cur->children[i]->height;
		}
	}
	cur->height = mx + 1;
}

template<typename T>
void Tree<T>::remove(Tree<T>* node) {
	Tree<T>* newThisNode = (this->getLowest(node));
	node->key = newThisNode->key;
	newThisNode->parent->children[newThisNode->number] = nullptr;
	delete newThisNode;
}


template<typename T>
void Tree<T>::erase(Tree<T>* curNode, T key) {
	if (curNode->key == key) {
		int hg = curNode->height;
		if (curNode->height == 1)
			hg = curNode->height;
		while (curNode->key == key) {
			remove(curNode);
			if (curNode->height == 1)
				hg = curNode->height;
		}
		if (hg == 1)
			return;
	}
	for (int i = 0; i < n; i++) {
		if (curNode->children[i]) {
			Tree<T>* cur = curNode->children[i];
			erase(cur, key);
		}
	}
}

template<typename T>
void Tree<T>::erase(T key) {
	if (this->height == 1 && this->key == key) {
		this->key = T();
		height = 0;
		number = 0;
		delete children;
		n = 0;
		return;
	}
	this->erase(this, key);
}

template<typename T>
Tree<T>* Tree<T>::getLowest(Tree<T>* curNode) {
	if (curNode->height == 1) {
		curNode->parent->children[curNode->number] = nullptr;
		return curNode;
	}
	Tree<T>* lowest = curNode->children[0];
	size_t last_mx = 0;
	for (int i = 0; i < this->n; i++) {
		if (curNode->children[i] && (!lowest || curNode->children[i]->height > lowest->height)) {
			lowest = curNode->children[i];
			last_mx = i;
		}
	}
	if (lowest) {
		Tree<T>* res = getLowest(lowest);
		fixheight(curNode);
		return res;
	}
}

//(2)К(1)(4)(3)
template<typename T>
void Tree<T>::travelsal(vector<Tree<T>*>& vect, Tree<T>* cur, string travel) {
	string travelCur = travel;
	if (!cur) return;
	while (travelCur.size()) {
		string nextStep = getTravelStep(travelCur);
		if (nextStep == "K" || nextStep == "К") {
			vect.push_back(cur);
		}
		else {
			if (cur->children[stoi(nextStep.substr(1, nextStep.size() - 2)) - 1]) {
				travelsal(vect, cur->children[stoi(nextStep.substr(1, nextStep.size() - 2)) - 1], travel);
			}
		}
	}
}

template<typename T>
void Tree<T>::travelsal(vector<Tree*>& vect, Tree* cur) {
	string travel = "К";
	for (int i = 1; i <= this->n; i++) {
		travel += "(" + to_string(i) + ")";
	}
	travelsal(vect, cur, travel);
}


template<typename T>
Tree<T>* Tree<T>::findNode(Tree<T>* cur, string& travel) {
	if (cur == nullptr) {
		return cur;
	}
	if (travel.size() == 0) {
		return cur;
	}
	string nextStep = getTravelStep(travel);
	int numNextStep = stoi(nextStep.substr(1, nextStep.size() - 2));
	return findNode(cur->children[numNextStep - 1], travel);
}




//методы
template<typename T>
void Tree<T>::pushItem(Tree* p, size_t pos, T data) {
	if (!p) {
		throw "IncorrectPosition";
	}
	if (pos > n) {
		throw "IncorrectPosition";
	}
	if (!p->children[pos - 1]) {
		p->children[pos - 1] = makeNode(data, n);
		p->children[pos - 1]->number = pos - 1;
		p->children[pos - 1]->height = 1;
	}
	else {
		Tree* curNode = makeNode(data, p->n);
		curNode->children[0] = p->children[pos - 1];
		p->children[pos - 1] = curNode;
		curNode->children[0]->parent = curNode;
		p->children[pos - 1]->number = pos - 1;
		curNode->children[0]->number = 0;
	}
	p->children[pos - 1]->parent = p;
	fixheight(p);
}

template<typename T>
void Tree<T>::pushItem(std::string path, T data) {
	if (path.size() == 0) {
		//Tree* nw = new Tree(data, n);
		key = data;
		this->n = n;
		children = new Tree<T>*[n];
		height = 1;
		number = 0;
		for (int i = 0; i < n; i++) children[i] = nullptr;
		return;
	}
	pushItem(this, path, data);
}

template<typename T>
void Tree<T>::pushItem(Tree* cur, std::string path, T data) {
	std::string curStepstr = getTravelStep(path);
	int curStep = stoi(curStepstr.substr(1, curStepstr.size() - 2));
	if (curStep > n) {
		throw "IncorrectPosition";
	}
	if (path.size() == 0) {
		pushItem(cur, curStep, data);
		return;
	}
	pushItem(cur->children[curStep - 1], path, data);
	fixheight(cur);
}

template<typename T>
T Tree<T>::findItem(std::string path) {
	return findNode(this, path) -> key;
}

template<typename T>
T Tree<T>::findItem(Tree<T>* start, std::string path) {
	return findNode(start, path) -> key;
}

template<typename T>
Tree<T> Tree<T>::GetSubTree(string s) {
	return Tree<T>(*findNode(this,s));
}

template<typename T>
std::string Tree<T>::to_str(std::string s) {
	std::vector<std::pair<int, std::vector<char>>> traversalSteps = *travelSteps(s);
	return to_str(this, traversalSteps);
}

std::string to_string(ll a) { return std::to_string(a); }
std::string to_string(double a) { return std::to_string(a); }
std::string to_string(std::string a) { return a; }
std::string to_string(complex a) { return std::to_string(a.getRe()) + std::to_string(a.getIm()); }
std::string to_string(Student a) { return a.getFirstName() + " " + a.getMiddleName() + " " + a.getLastName() + " " + a.group(); }
std::string to_string(Teacher a) { return a.getFirstName() + " " + a.getMiddleName() + " " + a.getLastName() + " " + to_string(a.dept()); }
//std::string to_string(string a) {return a;}

template<typename T>
std::string Tree<T>::to_str(Tree* cur, std::vector<std::pair<int, std::vector<char>>>& traversalSteps) {
	if (!cur) return "";
	if (traversalSteps.size() != n + 1) {
		throw "IncorrectTraversalType";
	}
	std::string res;
	for (int i = 0; i < n + 1; i++) {
		int curPos = traversalSteps[i].first;
		if (curPos == 0) {
			res += to_string(cur->key);
		}
		else if (cur->children[curPos - 1]) {
			res += traversalSteps[i].second[0];
			res += to_str(cur->children[curPos - 1], traversalSteps);
			res += traversalSteps[i].second[1];
		}
	}
	return res;
}

template<typename T>
bool Tree<T>::Equals(Tree<T>& tree) {
	if (tree.n != this->n) return false;
	return this->Equals(this, &tree);
}

template<typename T>
bool Tree<T>::Equals(Tree<T>* curthis, Tree<T>* curtree) {
	if ((!curthis) && (!curtree)) return true;
	if ((!curthis) ^ (!curtree)) return false;
	if (curthis->key != curtree->key) return false;
	bool f = true;
	for (int i = 0; i < this->n; i++) {
		f = f && (Equals(curthis->children[i], curtree->children[i]));
	}
	return f;
}

template<typename T>
bool Tree<T>::IsSubTree(Tree<T>& another) {
	return IsSubTree(this, &another);
}

template<typename T>
bool Tree<T>::IsSubTree(Tree<T>* cur, Tree<T>* another) {
	if (!another ^ !cur) return false;
	if (!another && !cur) return true;
	if (this->Equals(cur, another)) {
		return true;
	}
	bool f = false;
	for (int i = 0; i < n; i++) {
		f = f || IsSubTree(cur->children[i], another);
	}
	return f;
}

template<typename T>
void Tree<T>::map(T change(T)) {
	vector<Tree*> cur;
	travelsal(cur, this);
	for (int i = 0; i < cur.size(); i++) {
		cur[i]->key = change(cur[i]->key);
	}
}

template<typename T>
void Tree<T>::where(bool f(T), Tree<T>* cur, vector<Tree*>& src, size_t &src_pos) {
	if (src_pos >= src.size()) return;
	for (int i = 0; i < this->n; i++) {
		while (src_pos < src.size() && !f(src[src_pos]->key)) {
			src_pos++;
		}
		if (src_pos >= src.size()) return;
		cur->children[i] = makeNode(src[src_pos]->key, this->n);
		cur->children[i]->parent = cur;
		cur->children[i]->number = i;
		src_pos++;
		fixheight(cur);
	}

	for (int i = 0; i < this->n; i++) {
		where(f, cur->children[i], src, src_pos);
	}
}

template<typename T>
Tree<T> Tree<T>::where(bool f(T)) {
	vector<Tree<T>*> src;
	this->travelsal(src, this);
	Tree<T>* nw = nullptr;
	size_t src_pos = 0;
	while (src_pos < src.size() && !f(src[src_pos]->key)) {
		src_pos++;
	}
	if (src_pos >= src.size()) return *nw;
	nw = makeNode(src[src_pos]->key, this->n);
	src_pos++;
	where(f, nw, src, src_pos);
	return *nw;
}

template<typename T>
vector<Tree<T>*> Tree<T>::travelsal(string s) {
	vector<Tree<T>*> res;
	this->travelsal(res, this, s);
	return res;
}

template<typename T>
vector<Tree<T>*> Tree<T>::travelsal() {
	vector<Tree<T>*> res;
	this->travelsal(res, this);
	return res;
}

template<typename T>
bool Tree<T>::operator ==(Tree<T>& another) {
	return this->Equals(another);
}
template<typename T>
bool Tree<T>::operator >(Tree<T>&another) {
	return this->IsSubTree(another);
}

template<typename T>
ostream& operator <<(ostream& os, Tree<T>& tree) {
	string s = tree.to_str();
	os << s;
	return os;
}