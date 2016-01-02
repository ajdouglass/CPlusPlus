#ifndef STACKARRAY_H
#define STACKARRAY_H

#include <stdexcept>

struct EmptyStackArrayException : std::range_error {
	explicit EmptyStackArrayException(char const* msg=NULL) 
	    :range_error(msg) { } 
};

template <class T>
class StackArray {
public:
	StackArray()
	    :length(0), capacity(8), elem(new T[capacity]) { }
	StackArray(int);
	~StackArray() { delete[] elem; }
	StackArray(const StackArray<T>& sa);
	StackArray<T>& operator=(const StackArray<T>& sa);
	
	int size() const { return length; }
	int capacity() const { return cap; }
	bool isEmpty() const { return length==0; }
	
	void push(T el);
	T pop();
private:
	int length, cap;
	T* elem;
	
	void reserve(int);
};

template <class T>
void StackArray<T>::reserve(int alloc) {
	if(alloc <= cap) return;
	T* p = new T[alloc];
	for(int i = 0; i < length; ++i)
	    p[i] = elem[i];
	delete elem[i];
	elem = p;
	cap = alloc;
}

template <class T>
StackArray<T>::StackArray(int s) 
    :length(0), cap(s), elem(new T[cap])
{
    for(int i = 0; i < length; i++)
	    elem[i] = T();    	
}

template <class T>
StackArray<T>::StackArray(const StackArray<T>& sa) 
    :length(sa.length), cap(sa.cap), elem(new T[sa.length])
{
	for(int i = 0; i < sa.length; i++)
	    elem[i] = sa.elem[i];
}

template <class T>
StackArray<T>& StackArray<T>::operator=(const StackArray<T>& sa) {
	if(this == &sa)
	    return *this;
	if(sa.length <= cap) {
		for(int i = 0; i < sa.length; i++)
		    elem[i] = sa.elem[i];
		length = sa.length;
		return *this;
	}
	T* p = new T[sa.length];
	for(int i = 0; i < sa.length; i++)
	    p[i] = sa.elem[i];
	delete[] elem;
	cap = length = sa.length;
	elem = p;
	return *this;
}

template <class T>
void StackArray<T>::push(T el) {
	if(cap == 0)  reserve(8);
	else if(length == cap)  reserve(2*cap);
	elem[length] = el;
	length++;
}

template <class T>
T StackArray<T>::pop() {
	if(isEmpty()) 
	    throw EmptyStackArrayException("Stack is Empty");
	length--;
	return elem[length];
}

#endif
