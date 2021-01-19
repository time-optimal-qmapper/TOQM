#ifndef LINKEDSTACK_HPP
#define LINKEDSTACK_HPP

template <class T>
class LinkedStack {
  public:
	T value;
	LinkedStack<T> * next;
	int size;
	int numRefs; //will be used to help with garbage collection
	
	LinkedStack() {
		this->value = NULL;
		this->size = 0;
		this->next = NULL;
		this->numRefs = 1;
	}
	
	//Create a new LinkedStack such that this one is its second element
	//Sets new node's reference count to 1
	//Returns the new LinkedStack
	LinkedStack<T> * push(T newVal) {
		LinkedStack<T> * ret = new LinkedStack<T>;
		ret->next = this;
		ret->size = this->size + 1;
		ret->value = newVal;
		ret->numRefs = 1;
		return ret;
	}
	
	LinkedStack<T> * newRef() {
		numRefs++;
		return this;
	}
	
	void clean() {
		this->numRefs--;
		if(this->numRefs > 0) {
			return;
		}
		
		if(this->next) {
			this->next->clean();
		}
		
		if(this->value) {
			delete this->value;
		}
		delete this;
	}
};

#endif
