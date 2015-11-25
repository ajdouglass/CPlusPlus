/* Andrew Douglass *
 * 
 * Vector class designed with many different 
 * useful functions. It is designed for use in
 * many applications and different functions can 
 * be removed to best suit the needs of the project
 * while being as streamlined as possible. */

#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <stdexcept>

template <class T>
class vec {
public:
    vec()    //default constructor
        :Size(0), Capacity(8), elem(new T[Capacity]) { }
    vec(int);  //reserve constructor
    ~vec()     //destructor
        { delete[] elem; }
    vec(const vec<T>& v);   //copy constructor
    vec<T>& operator=(const vec<T>& v);   //copy assignment

    int size() const        
        { return Size; }
    int capacity() const    
        { return Capacity; }
    T& operator[](int i) const  
        { return elem[i]; }
    T& operator[](int i)        
        { return elem[i]; }
    bool is_empty() const       
        { return Size==0; }

    T& at(int p) const;       
    void push_back(T);
    void resize(int);
    void reserve(int);
    void insert(T&,int);
    T remove(int);
    int search(T&) const;
    bool contains(T&) const;
    void sort();
    int binary_search(T&) const;
    T& pop_end();
    void swap(int,int);
    void clear();
    void erase();
    void shrink_to_size();
private:
    int Size, Capacity;
    T* elem;
};

/* - Output Operator -
 * print the elements of the vector in square 
 * brackets and separated by commas. Ex:
 * [1, 2, 3, 4, 5]  */ 
template <class T>
std::ostream& operator<<(std::ostream& out, const vec<T>& v) {
    out << '[';
    for(int i = 0; i < v.size(); i++) {
        if(i == v.size()-1)  out << v[i];
        else                 out << v[i] << ", ";
    }
    return out << ']';
}

/* - Equal operator -
 * Compare vectors a and b to see if they are 
 * the same length and contain the same elements. */
template <class T>
bool operator==(const vec<T>& a, const vec<T>& b) {
    if(a.size() != b.size())
        return false;
    for(int i = 0; i < a.size(); i++)
        if(a[i] != b[i])
            return false;
    return true;
}

/* - Constructor with default capacity -
 * Create a vector with a size of 0, but allocate the 
 * space for s elements. These elements will be set to 
 * their default values. */
template <class T>
vec<T>::vec(int s)
    :Size(0), Capacity(s), elem(new T[Capacity]) 
{
    for(int i = 0; i < Size; ++i)
        elem[i] = T();
}

/* - Copy constructor -
 * Copy the elements from vector v into the current
 * vector. */
template <class T>
vec<T>::vec(const vec<T>& v) 
    :Size(v.Size), Capacity(v.Capacity), elem(new T[v.Size])
{
    for(int i = 0; i < v.Size; i++)
        elem[i] = v.elem[i];
}

/* - Copy Assignment -
 * Copy the elements from vector v into the current 
 * vector. First check to make sure a self copy is 
 * not occuring and then see if the current vector has 
 * the capacity to hold the elements stored in v. If it
 * does then there is no need to allocate more space. If
 * not, then more space must be allocated and the elements
 * reassigned to this new vector. */
template <class T>
vec<T>& vec<T>::operator=(const vec<T>& v) {
    if(this == &v)
        return *this;

    if(v.Size <= capacity) {
        for(int i = 0; i < v.Size; i++)
            elem[i] = v.elem[i];
        Size = v.Size;
        return *this;
    }

    T* p = new T[v.Size];
    for(int i = 0; i < v.Size; i++)
        p[i] = v.elem[i];
    delete[] elem;
    Capacity = Size = v.Size;
    elem = p;
    return *this;
} 

/* - Access Operator with range check -
 * Return the value at locaion p, but first do a 
 * range check to ensure the index p is in the range
 * vector's elements. */
template <class T>
T& vec<T>::at(int p) const {
    if(p >= Size || p < 0)
        throw std::range_error("Index out of range");
    return elem[p];
}

/* - Add element at the end -
 * Insert the new element a, at the end of the vector.
 * If there is not enough space to insert this element
 * then call the reserve function to allocate more 
 * memory to be able to store this element. */
template <class T>
void vec<T>::push_back(T a) {
    if(Capacity == 0)
        reserve(8);
    else if(Size == Capacity)
        reserve(2*Capacity);
    elem[Size] = a;
    ++Size;
}

/* - Resize the vector -
 * Increase the size of the current vector by first
 * allocating the necessary space and then copying
 * the default values for the new elements. */
template <class T>
void vec<T>::resize(int newsize) {
    reserve(newsize);
    for(int i = Size; i < newsize; ++i)
        elem[i] = T();
    Size = newsize;
}

/* - Allocating more memory space -
 * Create a new dynamic array with the space specified
 * by its parameter. This includes copying all the 
 * elements that are currently in the vector into the 
 * new vector that was just created. */
template <class T>
void vec<T>::reserve(int alloc) {
    if(alloc <= Capacity) return;
    T* p = new T[alloc];
    for(int i = 0; i < Size; ++i)
        p[i] = elem[i];
    delete[] elem;
    elem = p;
    Capacity = alloc;
}

/* - Insert key into the index loc -
 * Insert the element key into the location loc.
 * This is done by shifting all the elements from loc
 * to the end of the vector to the right by one. This 
 * will free up the location at loc for the new element
 * to be inserted. The size is then incremented. */
template <class T>
void vec<T>::insert(T& key, int loc) {
    if(loc < 0 || loc > size)
        throw std::range_error("Index out of range");
    if(loc == Size && Size == Capacity)
        reserve(2*Capacity);
    for(int i = Size-1; i >= loc; i--)
        elem[i+1] = elem[i];
    elem[loc] = key;
    Size++;
}

/* - Remove the element at loc -
 * Remove the element located at loc and return 
 * this element. This is done by shifting all the 
 * elements to the right of the element to be 
 * removed. The size is then decremented. */
template <class T>
T vec<T>::remove(int loc) {
    if(loc >= size || loc < 0) 
        throw std::range_error("Index out of range");
    T temp = elem[loc];
    for(int i = loc+1; i < Size; i++) 
        elem[i-1] = elem[i];
    Size--;
    return temp;
}

/* - Search for an element -
 * Search for the element key and return the index
 * it is located at. This is done using a linear 
 * search, so the vector does not have to be sorted. 
 * A -1 is returned if key is not contained in the 
 * vector. */
template <class T>
int vec<T>::search(T& key) const {
    for(int i = 0; i < Size; i++) 
        if(elem[i] == key)
            return i;
    return -1; 
}

/* - See if vector contains an element -
 * Return true if the element key is contained in 
 * the vector. Return false if the element key is 
 * not contained in the vector. Done using a linear
 * search so the vector does not have to be in order. */
template <class T>
bool vec<T>::contains(T& key) const {
    for(int i = 0; i < Size; i++)
        if(elem[i] == key)
            return true;
    return false;
}

/* - Sort the vector in increasing order -
 * Sort the vector using a shell sort. This provides
 * a fast sort method that sorts the vector in 
 * increasing order of the elements it contains. */
template <class T>
void vec<T>::sort() {
    for(int gap = Size/2; gap > 0; gap = (gap==2) ? 1 : (int)(gap/2.2)) {
        for(int i = gap; i < size; i++) {
            int temp = elem[i];
            int j = i;
            while(j >= gap && temp < elem[j-gap]) {
                elem[j] = elem[j-gap];
                j -= gap;
            }
            elem[j] = temp;
        }
    }
}

/* - Binary Search the vector -
 * Use a binary search to find the element key in 
 * the vector. This is a fast way of finding an 
 * element in the vector, but the vector must be 
 * sorted for it to work. The function will return 
 * the index of the element and will return -1 if 
 * the element could not be found in the vector. */
template <class T>
int vec<T>::binary_search(T& key) const {
    int m = 0;
    int start = 0;
    int end = Size;
    while(start < end) {
        m = (start + end) / 2;
        if(key > elem[m])  start = m + 1;
        else               end = m;
    }
    if(key == elem[start])
        return start;
    return -1;
}

/* - Remove and return the last element -
 * Remove the last element from the vector and return
 * it. The size is decremented. An error is thrown if 
 * the vector is empty. */
template <class T>
T& vec<T>::pop_end() {
    if(Size == 0)
        throw std::range_error("Vector is empty");
    Size--;
    return elem[Size+1];
}

/* - Swap the elements at loc1 and loc2 -
 * Switches the position of the elements located at 
 * loc1 and loc2. This is done by making sure that
 * both loc1 and loc2 are in the range of elements 
 * and that they are not the same. */
template <class T>
void vec<T>::swap(int loc1, int loc2) {
    if(loc1 < 0 || loc2 < 0 || loc1 >= Size || loc2 >= Size) 
        throw std::range_error("Index out of range");
    if(loc1 != loc2) {
        T temp = elem[loc1];
        elem[loc1] = elem[loc2];
        elem[loc2] = temp;
    }
}

/* - Reset the size to zero -
 * Reset the size of the vector to zero to act
 * as if the vector no longer contains any elements. */
template <class T>
void vec<T>::clear() {
    Size = 0;
}

/* - Reset size and elements to default value -
 * Reset the size of the vector to zero while overwriting
 * the values of the previous elements to their default 
 * value. This is known as a safe erase, but can be
 * significantly slower than the clear function. */
template <class T>
void vec<T>::erase() {
    for(int i = 0; i < Capacity; i++)
        elem[i] = T();
    Size = 0;
}

/* - Adjust capacity to fit size -
 * Adjust the capacity of the vector to fit the size
 * of the vector. This makes sure that there is no 
 * extra memory space that the vector is taking up than
 * what is needed. */
template <class T>
void vec<T>::shrink_to_size() {
    T* p = new T[Size];
    for(int i = 0; i < Size; i++) 
        p[i] = elem[i];
    delete[] elem;
    elem = p;
    Capacity = Size;
}

#endif
