#ifndef PROJECT_MSVECTOR_H
#define PROJECT_MSVECTOR_H
#include <iostream>

template<typename T>
class MSVector {
private:
    int currentCapacity;
    int currentSize;
    T* container;
public:
    class iterator{
        T *ptr;
    public:
        explicit iterator(T *ptr);
        iterator& operator++();
        const iterator operator++(T);
        T& operator*() const;
        T* operator->();
        int operator-(iterator another);
        iterator operator+(const int& value);
        iterator operator-(const int& value);
        friend bool operator== (const iterator& a, const iterator& b) {return a.ptr == b.ptr;};
        friend bool operator!= (const iterator& a, const iterator& b) {return a.ptr != b.ptr;};
        friend bool operator< (const iterator& a, const iterator& b) {return a.ptr < b.ptr;};
        friend bool operator> (const iterator& a, const iterator& b) {return a.ptr > b.ptr;};
        friend bool operator<= (const iterator& a, const iterator& b) {return a.ptr < b.ptr || a.ptr == b.ptr;};
        friend bool operator>= (const iterator& a, const iterator& b) {return a.ptr > b.ptr || a.ptr == b.ptr;};
    };
    iterator begin() {return iterator(&container[0]);}
    iterator end()   {return iterator(&container[currentSize]);}

    MSVector();
    explicit MSVector(int size);
    MSVector(std::initializer_list<T> list);
    MSVector(int size, T value);
    MSVector(const MSVector& anotherVector);
    MSVector(MSVector&& anotherVector) noexcept ;
    ~MSVector();
    MSVector& operator=(const MSVector& anotherVector);
    MSVector& operator=(MSVector&& anotherVector) noexcept ;
    T& operator[](int index);
    int push_back(T value); // return the size of the vector
    T pop_back(); // return first the top element before popping
    void erase(iterator position);
    void erase(iterator startPosition, iterator endPosition);
    void clear();
    void insert(iterator position, T value);
    int size();
    int capacity();
    void resize(int newSize);
    bool isEmpty();
    // comparisons
    bool operator==(const MSVector<T>& anotherVector); // Return true if ==
    bool operator< (const MSVector<T>& anotherVector); // Compares item by item
    bool operator> (const MSVector<T>& anotherVector); // Compares item by item
};

#endif