#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdexcept>

template <class T>
class DoublyLinkedList;

// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

template <class T>
class Node {
public:
    Node(T k=T(), Node<T>* p=NULL, Node<T>* n=NULL)
        :obj(k), prev(p), next(n) { }
    T getElem() const
        { return obj; }
    Node<T>* getNext() const
        { return next; }
    Node<T>* getPrev() const
        { return prev; }
private:
    T obj;
    Node<T> *prev, *next;
    friend class DoublyLinkedList<T>;
};

template <class T> class DoublyLinkedList {
public:
    DoublyLinkedList() 
        :header(NULL), trailer(NULL), numNodes(0) { }
    DoublyLinkedList(const DoublyLinkedList& dll);
    ~DoublyLinkedList()
        { deleteList(); } 
    DoublyLinkedList& operator=(const DoublyLinkedList& dll);
    void deleteList();
    Node<T>* getFirst() const;
    Node<T>* getLast() const;
    bool isEmpty() const
        { return header==trailer; } 
    void insertFirst(T newobj);
    void insertLast(T newobj);
    T removeFirst();
    T removeLast();
    int size() const;
    Node<T>* find(T key) const;
    
protected:
    Node<T>* header, trailer;

private:
    int numNodes;
};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& dll) {
    Node<T>* iter = dll.header;
    while(iter != NULL) {
        insertLast(iter->obj);
        iter = iter->next;
    }
    numNodes = dll.size();
}

template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& dll) {
    Node<T>* iter = header;
    while(iter != NULL) {
        iter = iter->next;
        removeFirst();
    }

    iter = dll.header;
    while(iter != NULL) {
        insertLast(iter->obj);
        iter = iter->next;
    }
    numNodes = dll.size();
}

template <class T>
void DoublyLinkedList<T>::deleteList() {
    Node<T>* prev;
    Node<T>* iter = header;
    while(iter != NULL) {
        prev = iter;
        iter = iter->next;
        delete prev; 
    }
    header = NULL;
    trailer = NULL;
    numNodes = 0;
}

template <class T>
Node<T>* DoublyLinkedList<T>::getFirst() const {
    if(isEmpty())
        throw EmptyDLinkedListException("Empty Linked List");
    return header;
}

template <class T>
Node<T>* DoublyLinkedList<T>::getLast() const {
    if(isEmpty())
        throw EmptyDLinkedListException("Empty Linked List");
    return trailer;
}

template <class T> 
void DoublyLinkedList<T>::insertFirst(T newobj) {
    Node<T>* newnode = new Node<T>(newobj,header,header->next);
    if(header->next != NULL)
        header->next->prev = newnode;
    header = newnode;
    numNodes++;
}

template <class T>
void DoublyLinkedList<T>::insertLast(T newobj) {
    Node<T>* newnode = new Node<T>(newobj,trailer->prev,trailer);
    if(trailer->prev != NULL)
        trailer->prev->next = newnode;
    trailer = newnode;
    numNodes++;
}

template <class T>
T DoublyLinkedList<T>::removeFirst() {
	if(isEmpty())
        throw EmptyDLinkedListException("Empty Linked List");
	Node<T>* temp = header;
    if(header->next != NULL)
        header->next->prev = NULL;
    header = header->next;
    delete temp;
    numNodes--;
}

template <class T>
T DoublyLinkedList<T>::removeLast() {
    if(isEmpty())
        throw EmptyDLinkedListException("Empty Linked List");
	Node<T>* temp = trailer;
	if(trailer->prev != NULL)
	    trailer->prev->next = NULL;
	trailer = trailer->prev;
	delete temp;
	numNodes--;
}

template <class T>
int DoublyLinkedList<T>::size() const {
    return numNodes;
}

template <class T>
Node<T>* DoublyLinkedList<T>::find(T key) const {
    Node<T>* iter = header;
    while(iter != NULL) {
    	if(iter->getElem() == key)
    	    return iter;
        iter = iter->next;
    }
    return NULL;
}

template <class T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll) {
    Node<T>* iter = dll.getFirst();
    out << '[';
    while(iter != NULL) {
        out << iter->obj;
        if(iter->next != NULL)
            out << ", ";
        iter = iter->next;
    }
    return out << ']';
}

#endif
