#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <stdexcept>

template <class T>
class SinglyLinkedList;

struct EmptySLinkedListException : std::range_error {
    explicit EmptySLinkedListException(char const* msg=NULL) :range_error(msg) { }
};

template <class T>
class SNode {
public:
    SNode(T k=T(), SNode<T>* n=NULL)
        :obj(k), next(n) { }
    T& getElem() const
        { return obj; }
    T& getElem() 
        { return obj; }
    SNode<T>* getNext() const
        { return next; }
private:
    T obj;
    SNode<T>* next;
    friend class SinglyLinkedList<T>;
};

template <class T> 
class SinglyLinkedList {
public:
    SinglyLinkedList()
        :header(NULL), trailer(NULL), numNodes(0) { }
    ~SinglyLinkedList()
        { deleteList(); }
    SinglyLinkedList(const SinglyLinkedList<T>& sll);
    SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& sll);
    
    void deleteList();
    SNode<T>* getFirst() const
        { return header; }
    SNode<T>* getLast() const
        { return trailer; }
    bool isEmpty() const
        { return header==NULL; }
    void insertFirst(T newobj);
    void insertLast(T newobj);
    T removeFirst();
    T removeLast();
    int size() const
        { return numNodes; }
    SNode<T>* find(T key) const;
    void remove(T key);
private:
    SNode<T> *header, *trailer;
    int numNodes;
};

template <class T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& sll) {
    SNode<T>* iter = sll.header;
    SNode<T>* temp = NULL;
    while(iter != NULL) {
        SNode<T>* newnode = new SNode<T>(iter->obj);
        if(temp == NULL)  header = newnode;
        else  temp->next = newnode;
        temp = newnode;
        iter = iter->next;
    }
    numNodes = sll.size();
}

template <class T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& sll) {
    deleteList();
    SNode<T>* iter = sll.header;
    SNode<T>* temp = NULL;
    while(iter != NULL) {
        SNode<T>* newnode = new SNode<T>(iter->obj);
        if(temp == NULL)  header = newnode;
        else  temp->next = newnode;
        temp = newnode;
        iter = iter->next;
    }
    numNodes = sll.size();
}

template <class T>
void SinglyLinkedList<T>::deleteList() {
    while(!isEmpty()) 
        removeFirst();
    header = NULL;
}

template <class T>
void SinglyLinkedList<T>::insertFirst(T newobj) {
    SNode<T>* newnode = new SNode<T>(newobj,header);
    header = newnode;
    numNodes++;
}

template <class T>
void SinglyLinkedList<T>::insertLast(T newobj) {
    if(isEmpty()) {
        insertFirst(newobj);
        return;    
    }
    SNode<T>* iter = header;
    while(iter->next != NULL) 
        iter = iter->next;
    SNode<T>* newnode = new SNode<T>(newobj);
    iter->next = newnode;
    numNodes++;
}

template <class T>
T SinglyLinkedList<T>::removeFirst() {
    if(header == NULL) 
        throw EmptySLinkedListException("Empty Linked List");
    SNode<T>* temp = header;
    header = header->next;
    T p = temp->obj;
    delete temp;
    numNodes--;
    return p;
}

template <class T>
T SinglyLinkedList<T>::removeLast() {
    if(isEmpty()) 
        throw EmptySLinkedListException("Empty Linked List");
    SNode<T>* iter = header;
    if(iter->next == NULL) 
        return removeFirst();
    while(iter->next->next != NULL) 
        iter = iter->next;
    SNode<T>* temp = iter->next;
    iter->next = NULL;
    T p = temp->obj;
    delete temp;
    numNodes--;
    return p;
}

template <class T>
SNode<T>* SinglyLinkedList<T>::find(T key) const {
    SNode<T>* iter = header;
    while(iter != NULL) {
        if(iter->obj == key) 
            return iter;
        iter = iter->next;
    }
    return NULL;
}

template <class T>
void SinglyLinkedList<T>::remove(T key) {
    if(isEmpty())
        throw EmptySLinkedListException("Empty Linked List");
    SNode<T>* iter = header;
    if(iter->obj == key) {
        removeFirst();
        return;
    }
    while(iter->next != NULL) {
        if(iter->next->obj == key) {
            SNode<T>* temp = iter->next;
            iter->next = iter->next->next;
            delete temp;
            numNodes--;
            return;
        }
        iter = iter->next;
    }
}

template <class T>
bool operator==(const SinglyLinkedList<T>& s1, const SinglyLinkedList<T>& s2) {
    if(s1.size() != s2.size())
        return false;
    SNode<T>* iter1 = s1.getFirst();
    SNode<T>* iter2 = s2.getFirst();
    while(iter1 != NULL) {
        if(iter1->getElem() != iter2->getElem())
            return false;
         iter1 = iter1->getNext();
         iter2 = iter2->getNext();
    }
    return true;
}

template <class T>
bool operator!=(const SinglyLinkedList<T>& s1, const SinglyLinkedList<T>& s2) {
    return !(s1==s2);
}

template <class T>
std::ostream& operator<<(std::ostream& out, const SinglyLinkedList<T>& sll) {
    SNode<T>* iter = sll.getFirst();
    out << '[';
    while(iter != NULL) {
        out << iter->getElem();
        iter = iter->getNext();
        if(iter != NULL)
            out << ", ";
    }
    return out << ']';
}

#endif
