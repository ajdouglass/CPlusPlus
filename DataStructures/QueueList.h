#ifndef QUEUELIST_H
#define QUEUELIST_H

#include <stdexcept>

template <class T>
class QueueList;

struct EmptyQueueListException : std::range_error {
   explicit EmptyQueueListException(char const* msg=NULL)
      :range_error(msg) { }
};

template <class T>
class ListNode {
public:
   ListNode(T key=T(), ListNode<T>* n=NULL)
      :obj(key), next(n) { }
   T& getElem() const
      { return obj; }
   T& getElem()
      { return obj; }
   ListNode<T>* getNext() const
      { return next; }
private:
   T obj;
   ListNode<T>* next;
   friend class QueueList<T>;
};

template <class T>
class QueueList {
public:
   QueueList()
      :header(NULL), trailer(NULL), size(0) { }
   ~QueueList()
      { deleteList(); }
   QueueList(const QueueList<T>& ql);
   QueueList<T>& operator=(const QueueList<T>& ql);

   ListNode<T>* getFirst() const
      { return header; }
   ListNode<T>* getLast() const
      { return trailer; }
   bool isEmpty() const
      { return (header == NULL); }
   int getSize() const
      { return size; }

   void deleteList();
   T dequeue();
   void enqueue(T elem);

private:
   ListNode<T> *header, *trailer;
   int size;
};

template <class T>
QueueList<T>::QueueList(const QueueList<T>& ql) {
   ListNode<T>* iter = ql.header;
   ListNode<T>* temp = NULL;
   while(iter != NULL) {
      ListNode<T>* newNode = new ListNode<T>(iter->obj);
      if(temp == NULL) header = newNode;
      else  temp->next = newNode;
      temp = newNode;
      iter = iter->next;
   }
   size = ql.getSize();
}

template <class T>
QueueList<T>& QueueList<T>::operator=(const QueueList<T>& ql) {
   deleteList();
   ListNode<T>* iter = ql.header;
   ListNode<T>* temp = NULL;
   while(iter != NULL) {
      ListNode<T>* newNode = new ListNode<T>(iter->obj);
      if(temp == NULL) header = newNode;
      else  temp->next = newNode;
      temp = newNode;
      iter = iter->next;
   }
   size = ql.getSize();
}

template <class T>
void QueueList<T>::deleteList() {
   ListNode<T>* iter = header;
   ListNode<T>* temp;
   while(iter != NULL) {
      temp = iter;
      iter = iter->next;
      delete temp;
   }
   header = NULL;
   trailer = NULL;
}

template <class T>
T QueueList<T>::dequeue() {
   if(header == NULL)
      throw EmptyQueueListException("Can't dequeue from empty queue");
   ListNode<T>* temp = header;
   T elem = temp->obj;
   header = temp->next;
   delete temp;
   size--;
   if(header == NULL)
      trailer = NULL;
   return elem;
}

template <class T>
void QueueList<T>::enqueue(T elem) {
   ListNode<T>* newNode = new ListNode<T>(elem);
   if(header == NULL)
      header = newNode;
   if(trailer != NULL)
      trailer->next = newNode;
   trailer = newNode;
   size++;
}

#endif
