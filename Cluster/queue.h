#pragma once
#include <stack>

template <class T> 
class TStackQueue {
	size_t sz;
	std::stack<T> leftStack;
	std::stack<T> rightStack;

public:
	TStackQueue() :sz(0) {}

	size_t size() const { return sz; }

	bool IsEmpty() const { return sz == 0; }

	void Push(const T& val) {
		leftStack.push(val);
		sz++;
	}
	
	void Pop() {
		if (sz == 0) throw "Cannot pop from an empty queue";
		if (rightStack.empty())
			while (!leftStack.empty()) {
				rightStack.push(leftStack.top());
				leftStack.pop();
			}

		rightStack.pop();
		sz--;
	}

	T Top() {
		if (sz == 0) throw "Cannot get element from an empty queue";
		if (rightStack.empty())
			while (!leftStack.empty()) {
				rightStack.push(leftStack.top());
				leftStack.pop();
			}

		T val = rightStack.top();
		return val;
	}

};