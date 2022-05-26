#pragma once
#include "AVLTree.h"
template<typename T>
class set {
private:
	AVLTree<T> avl;
public:
	set() {
	}
	set(initializer_list<T> init_list) {
		for (auto i : init_list) {
			avl.push(i);
		}
	}
	set(set<T>& another) {
		vector<T> another_vect = *(another.to_array());
		for (int i = 0; i < another_vect.size(); i++) {
			push(another_vect[i]);
		}
	}

	void push(T key) {
		avl.push(key);
	}

	size_t size() {
		return avl.size();
	}
	vector<T>* to_array() {
		return avl.to_array();
	}
	
	void erase(T key) {
		avl.erase(key);
	}
	
	bool find(T key) {
		return avl.find(key);
	}

	set<T>* concat(set<T>& another) {
		set<T>* res = new set<T>;
		vector<T> cur = *(this->to_array());
		for (auto i : cur) {
			res->push(i);
		}
		cur = *(another.to_array());
		for (auto i : cur) {
			res->push(i);
		}
		return res;
	}
	
	void clear() {
		avl.clear();
	}

	bool Equals(set<T>& another) {
		return this->avl.Equals(another.avl);
	}

	set<T>* intersect(set<T>& another) {
		set<T>* res = new set<T>;
		vector<T> cur = *(another.to_array());
		for (auto i : cur) {
			if (this->find(i)) {
				res->push(i);
			}
		}
		return res;
	}

	set<T>* difference(set<T>& another) {
		set<T>* res = new set<T>(another);
		vector<T> cur = *(this->to_array());
		for (auto i : cur) {
			if (res->find(i)) {
				res->erase(i);
			}
		}
		return res;
	}

	set<T>* where(bool f(T)) {
		set<T>* res = new set<T>;
		res->avl = this->avl->where(f);
		return res;
	}

	set<T>* map(bool f(T)) {
		set<T>* res = new set<T>;
		res->avl = this->avl->map(f);
		return res;
	}
	bool operator ==(set<T>&);
	bool operator >(set<T>&);
	bool operator <(set<T>&);
	set<T>* operator +(set<T>&);
	set<T>* operator -(set<T>&);
	set<T>* operator *(set<T>&);
	friend ostream& operator <<(ostream&, set<T>&);
};

template<typename T>
bool set<T>::operator==(set<T>& another) {
	return this->Equals(another);
}

template<typename T>
bool set<T>::operator > (set<T>& another) {
	return this->size() > another.size();
}

template<typename T>
bool set<T>::operator<(set<T>& another) {
	return this->size() > another.size();
}

template<typename T>
set<T>* set<T>::operator +(set<T>& another) {
	return this->concat(another);
}

template<typename T>
set<T>* set<T>::operator -(set<T>& another) {
	return this->difference(another);
}
template<typename T>
set<T>* set<T>::operator *(set<T>& another) {
	return this->intersect(another);
}