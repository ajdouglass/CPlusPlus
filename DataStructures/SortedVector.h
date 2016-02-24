#ifndef SORTEDVECTOR_H
#define SORTEDVECTOR_H

#include <iostream>
#include <stdexcept>

template <class T>
class SortedVector { 
public:
   SortedVector();
   SortedVector(int);
   ~SortedVector();
   SortedVector(const SortedVector<T>&);
   SortedVector<T>& operator=(const SortedVector<T>&);

   int getSize() const;
   int getCapacity() const;
   T& operator[](int i) const;
   T& operator[](int i);
   bool isEmpty() const;
   T& at(int i) const;

   void add(T);
   void resize(int);
   void reserve(int);
   T remove(int);
   void clear();
   void erase();
   void updateOrder();
   bool contains(T&) const;
   int indexOf(T&) const;
   
private:
   int size, capacity;
   T* elem;
};

template <class T>
SortedVector<T>::SortedVector() 
   :size(0), capacity(4), elem(new T[capacity]) 
{ }

template <class T>
SortedVector<T>::SortedVector(int s)
   :size(0), capacity(s), elem(new T[capacity])
{
   for(int i = 0; i < capacity; i++) {
      elem[i] = T();
   }
}

template <class T>
SortedVector<T>::~SortedVector() {
   delete[] elem;
}

template <class T>
SortedVector<T>::SortedVector(const SortedVector<T>& copyVec) 
   :size(copyVec.size), capacity(copyVec.capacity), elem(new T[copyVec.capacity])
{
   for(int i = 0; i < copyVec.size; i++) {
      elem[i] = copyVec.elem[i];
   }
}

template <class T>
SortedVector<T>& SortedVector<T>::operator=(const SortedVector<T>& copyVec) {
   if(this == &copyVec)
      return *this;

   if(copyVec.size <= capacity) {
      for(int i = 0; i < copyVec.size; i++) 
         elem[i] = copyVec.elem[i];
      size = copyVec.size;
      return *this;
   }

   T* p = new T[copyVec.size];
   for(int i = 0; i < copyVec.size; i++) 
      p[i] = copyVec.elem[i];
   delete[] elem;
   capacity = size = copyVec.size;
   elem = p;
   return *this;
}

template <class T>
int SortedVector<T>::getSize() const {
   return size;
}

template <class T>
int SortedVector<T>::getCapacity() const {
   return capacity;
}

template <class T>
T& SortedVector<T>::operator[](int i) const {
   return elem[i];
}

template <class T>
T& SortedVector<T>::operator[](int i) {
   return elem[i];
}

template <class T>
bool SortedVector<T>::isEmpty() const {
   return (size == 0);
}

template <class T>
T& SortedVector<T>::at(int i) const {
   if(i < 0 || i >= size)
      throw std::range_error("Index out of range");
   return elem[i];
}

template <class T>
void SortedVector<T>::add(T newElem) {
   int i = 0;
   while(elem[i] < newElem && i < size) 
      i++;
   if(size == capacity)
      reserve(2*capacity);
   for(int j = size-1; j >= i; j--)
      elem[j+1] = elem[j];
   elem[i] = newElem;
   size++;
}

template <class T>
void SortedVector<T>::resize(int newSize) {
   reserve(newSize);
   for(int i = size; i < newSize; i++) 
      elem[i] = T();
   size = newSize;
}

template <class T>
void SortedVector<T>::reserve(int newCap) {
   if(newCap <= capacity)
      return;
   T* p = new T[newCap];
   for(int i = 0; i < size; i++) 
      p[i] = elem[i];
   delete[] elem;
   elem = p;
   capacity = newCap;
}

template <class T>
T SortedVector<T>::remove(int index) {
   if(index >= size || index < 0)
      throw std::range_error("Index out of range");
   T temp = elem[index];
   for(int i = index+1; i < size; i++) 
      elem[i-1] = elem[i];
   size--;
   return temp;
}

template <class T>
void SortedVector<T>::clear() {
   size = 0;
}

template <class T>
void SortedVector<T>::erase() {
   for(int i = 0; i < capacity; i++) 
      elem[i] = T();
   size = 0;
}

/* Bubble Sort */
template <class T>
void SortedVector<T>::updateOrder() {
   for(int k = 1; k < size; k++) {
      bool cont = false;
      for(int j = 0; j < (size-k); j++) {
         if(elem[j+1] < elem[j]) {
            T temp = elem[j];
            elem[j] = elem[j+1];
            elem[j+1] = temp;
            cont = true;
         }
      }
      if(!cont) break;
   }   
}

template <class T>
bool SortedVector<T>::contains(T& key) const {
   for(int i = 0; i < size; i++) {
      if(elem[i] == key) {
         return true;
      }
   }
   return false;
}

template <class T>
int SortedVector<T>::indexOf(T& key) const {
   for(int i = 0; i < size; i++) {
      if(elem[i] == key) {
         return i;
      }
   }
   return -1;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const SortedVector<T>& myVec) {
   out << '[';
   for(int i = 0; i < myVec.getSize(); i++) {
      if(i == myVec.getSize()-1)
         out << myVec[i];
      else
         out << myVec[i] << ", ";
   }
   return out << ']';
}

#endif
