#include "MSVector.h"

/**
 * Empty copy constructor
 * Make the MSVector has capacity = 1, size = 0
 * @tparam T
 */
template<typename T>
MSVector<T>::MSVector() {
    this->currentSize = 0;
    this->currentCapacity = 1;
    this->container = new T[1];
}
/**
 * Make the MSVector has a given initial size and without any initial values (garbage values)
 * @tparam T
 * @param size
 */
template<typename T>
MSVector<T>::MSVector(int size) {
    this->currentSize = size;
    this->currentCapacity = size;
    this->container = new T[size];
}

/**
 * Make the MSVector has a given initial size with a given value
 * @tparam T
 * @param size
 * @param value
 */
template<typename T>
MSVector<T>::MSVector(int size, T value) {
    this->currentSize = size;
    this->currentCapacity = size;
    this->container = new T[size];
    for (int i = 0; i < size; ++i) {
        this->container[i] = value;
    }
}
/**
 * Copy MSVector from another MSVector (for lvalue) using copy constructor
 * @tparam T
 * @param anotherVector
 */
template<typename T>
MSVector<T>::MSVector(const MSVector &anotherVector) {
    if (this == &anotherVector) return;
    this->container = new T[anotherVector.currentCapacity];
    this->currentCapacity = anotherVector.currentCapacity;
    this->currentSize = anotherVector.currentSize;
    for (int i = 0; i < this->currentSize; ++i) {
        this->container[i] = anotherVector.container[i];
    }
}
/**
 * Copy MSVector from another MSVector (for rvalue) using copy constructor
 * @tparam T
 * @param anotherVector
 */
template<typename T>
MSVector<T>::MSVector(MSVector &&anotherVector) noexcept{
    if (this == &anotherVector) return;
    delete[] this->container;
    this->container = new T[anotherVector.currentCapacity];
    this->currentCapacity = anotherVector.currentCapacity;
    this->currentSize = anotherVector.currentSize;
    for (int i = 0; i < this->currentSize; ++i) {
        this->container[i] = anotherVector.container[i];
    }
    delete anotherVector;
}
/**
 * Destructor for the MSVector to delete the container array pointer
 * @tparam T
 */
template<typename T>
MSVector<T>::~MSVector() {
    delete[] this->container;
}

/**
 * Copy MSVector from another MSVector (lvalue) using (=) operator
 * @tparam T
 * @param anotherVector
 * @return
 */
template<typename T>
MSVector<T> &MSVector<T>::operator=(const MSVector &anotherVector) {
    if (this == &anotherVector) return *this;
    delete[] this->container;
    this->container = new T[anotherVector.currentCapacity];
    this->currentCapacity = anotherVector.currentCapacity;
    this->currentSize = anotherVector.currentSize;
    for (int i = 0; i < this->currentSize; ++i) {
        this->container[i] = anotherVector.container[i];
    }
    return *this;
}
/**
 * Copy MSVector from another MSVector (rvalue) using (=) operator
 * @tparam T
 * @param anotherVector
 * @return
 */
template<typename T>
MSVector<T> &MSVector<T>::operator=(MSVector &&anotherVector) noexcept{
    if (this == &anotherVector) return *this;
    delete[] this->container;
    this->container = new T[anotherVector.currentCapacity];
    this->currentCapacity = anotherVector.currentCapacity;
    this->currentSize = anotherVector.currentSize;
    for (int i = 0; i < this->currentSize; ++i) {
        this->container[i] = anotherVector.container[i];
    }
    return *this;
}
/**
 * Access a valid element from the container with position = given index
 * @tparam T
 * @param index
 * @return
 */
template<typename T>
T &MSVector<T>::operator[](int index) {
    try{
        if(index < 0 || index >= this->currentSize)
            throw 0;
        return this->container[index];
    }catch (int error){
        std::cout << "You cannot access out of range!\n";
    }
}
/**
 * Push a given value to the back of this MSVector
 * @tparam T
 * @param value
 * @return
 */

template<typename T>
int MSVector<T>::push_back(T value) {
    if (this->currentSize == this->currentCapacity) {
        T *tmpContainer = new T[this->currentCapacity *= 2];
        for (int i = 0; i < this->currentSize; ++i) {
            tmpContainer[i] = this->container[i];
        }
        delete[] this->container;
        this->container = tmpContainer;
    }
    this->container[currentSize++] = value;
    return this->currentSize;
}

/**
 * Pop the back element from this MSVector
 * If the currentSize of the MSVector = 0, then cannot pop from back
 * @tparam T
 * @return
 */
template<typename T>
T MSVector<T>::pop_back() {
    try {
        if (this->currentSize == 0)
            throw 0;
        return this->container[--this->currentSize];
    } catch (int size) {
        std::cout << "The vector is already empty!\n";
    }
}

/**
 * Erase a certain position from this MSVector
 * The given iterator must be greater than or equal to the beginning iterator
 * and smaller than the ending iterator
 * @tparam T
 * @param position
 */
template<typename T>
void MSVector<T>::erase(iterator position) {
    try{
        if (position < this->begin() || position > this->end() - 1)
            throw 0;
        T *tmpContainer = new T[this->currentCapacity];
        for (auto i = this->begin(); i < position; ++i) {
            if (i == this->end()) break;
            tmpContainer[i - this->begin()] = *i;
        }
        for (auto i = position + 1; i < this->end(); ++i) {
            tmpContainer[i - this->begin() - 1] = *i;
        }
        delete[] this->container;
        this->container = tmpContainer;
        this->currentSize--;
    }catch (int error){
        std::cout << "You can't erase!\n";
    }
}
/**
 * Erase a range of elements that between startPosition and endPosition
 * The endPosition isn't inclusive
 * This range should be between the beginning iterator and the ending iterator
 * @tparam T
 * @param startPosition
 * @param endPosition
 */
template<typename T>
void MSVector<T>::erase(iterator startPosition, iterator endPosition) {
    try{
        if (startPosition < this->begin() || startPosition > this->end() - 1
            || endPosition < this->begin() || endPosition > this->end() - 1) {
            throw 0;
        }
        T *tmpContainer = new T[this->currentCapacity];
        int difference = endPosition - startPosition;
        for (auto i = this->begin(); i < startPosition; ++i) {
            tmpContainer[i - this->begin()] = *i;
        }
        for (auto i = endPosition; i < this->end(); ++i) {
            tmpContainer[i - this->begin() - difference] = *i;
        }
        delete[] this->container;
        this->container = tmpContainer;
        this->currentSize -= difference;
    }catch (int error){
        std::cout << "You cannot erase!\n";
    }
}
/**
 * Clear all MSVector entries
 * @tparam T
 */
template<typename T>
void MSVector<T>::clear() {
    delete[] this->container;
    this->currentSize = 0;
    this->currentCapacity = 1;
}
/**
 * Insert a given value to a certain position
 * @tparam T
 * @param position
 * @param value
 */
template<typename T>
void MSVector<T>::insert(iterator position, T value) {
    try{
        if(position < this->begin() || position > this->end())
            throw 0;
        T *tmpContainer = new T[this->currentCapacity *= 2];
        for (auto i = this->begin(); i < position; ++i) {
            tmpContainer[i - this->begin()] = *i;
        }
        tmpContainer[position - this->begin()] = value;
        for (auto i = position; i < this->end(); ++i) {
            tmpContainer[i - this->begin() + 1] = *i;
        }
        delete[] this->container;
        this->currentSize ++;
        this->container = tmpContainer;
    }catch (int error){
        std::cout << "You cannot insert here!\n";
    }
}
/**
 * Return the size of this MSVector
 * @tparam T
 * @return
 */
template<typename T>
int MSVector<T>::size() {
    return this->currentSize;
}
/**
 * Return the capacity of this MSVector
 * @tparam T
 * @return
 */
template<typename T>
int MSVector<T>::capacity() {
    return this->currentCapacity;
}
/**
 * Resize this MSVector with a given size
 * If the newSize is smaller than the MSVector size, then shrink the size to the new one
 * If is greater then make the size equal to the newSize and make the rest elements to have a garbage values
 * @tparam T
 * @param newSize
 */
template<typename T>
void MSVector<T>::resize(int newSize) {
    T *tmpContainer = new T[newSize];
    for (int i = 0; i < std::min(newSize, this->currentSize); ++i) {
        tmpContainer[i] = this->container[i];
    }
    this->currentSize = newSize;
    this->currentCapacity = newSize * 2;
    this->container = tmpContainer;
}
/**
 * Return if the MSVector size is equal to zero or not
 * @tparam T
 * @return
 */
template<typename T>
bool MSVector<T>::isEmpty() {
    return (this->currentSize == 0);
}
/**
 * Comparison operator (==) that compare the two MSVector elements and find if they have the same elements ans size
 * @tparam T
 * @param anotherVector
 * @return
 */
template<typename T>
bool MSVector<T>::operator==(const MSVector<T> &anotherVector) {
    for (int i = 0; i < std::min(this->currentSize, anotherVector.currentSize); ++i) {
        if(this->container[i] != anotherVector.container[i]){
            return false;
        }
    }
    return (this->currentSize == anotherVector.currentSize);
}
/**
 * Comparison operator (<) that compare the two MSVector elements and find first element has difference value
 * and return if the first MSVector is smaller than the second one
 * @tparam T
 * @param anotherVector
 * @return
 */
template<typename T>
bool MSVector<T>::operator<(const MSVector<T> &anotherVector) {
    for (int i = 0; i < std::min(this->currentSize, anotherVector.currentSize); ++i) {
        if(this->container[i] == anotherVector.container[i]) continue;
        if(this->container[i] > anotherVector.container[i]) return false;
        else return true;
    }
    return (this->currentSize < anotherVector.currentSize);
}
/**
 * Comparison operator (>) that compare the two MSVector elements and find first element has difference value
 * and return if the first MSVector is greater than the second one
 * @tparam T
 * @param anotherVector
 * @return
 */
template<typename T>
bool MSVector<T>::operator>(const MSVector<T> &anotherVector) {
    for (int i = 0; i < std::min(this->currentSize, anotherVector.currentSize); ++i) {
        if(this->container[i] == anotherVector.container[i]) continue;
        if(this->container[i] < anotherVector.container[i]) return false;
        else return true;
    }
    return (this->currentSize > anotherVector.currentSize);
}
/**
 * Initialize the MSVector from given list
 * @tparam T
 * @param list
 */
template<typename T>
MSVector<T>::MSVector(std::initializer_list<T> list) {
    this->currentSize = list.size();
    this->currentCapacity = list.size() * 2;
    this->container = new T[this->currentCapacity];
    auto itr = list.begin();
    for (int i = 0; i < list.size(); ++i, ++itr) {
        this->container[i] = *itr;
    }
}
/**
 * Make the iterator refer to the given pointer
 * @tparam T
 * @param ptr
 */
template<typename T>
MSVector<T>::iterator::iterator(T *ptr) {
    this->ptr = ptr;
}
/**
 * Prefix increment for the iterator
 * @tparam T
 * @return
 */
template<typename T>
typename MSVector<T>::iterator &MSVector<T>::iterator::operator++() {
    ptr++;
    return *this;
}
/**
 * Postfix increment for the iterator
 * @tparam T
 * @return
 */
template<typename T>
const typename MSVector<T>::iterator MSVector<T>::iterator::operator++(T) {
    iterator tmp = *this;
    ++(*this);
    return tmp;
}
/**
 * Return integer that result of the subtraction of two iterators
 * @tparam T
 * @param another
 * @return
 */
template<typename T>
int MSVector<T>::iterator::operator-(MSVector::iterator another) {
    return this->ptr - another.ptr;
}
/**
 * Return the element that this iterator refers to
 * @tparam T
 * @return
 */
template<typename T>
T &MSVector<T>::iterator::operator*() const {
    return *ptr;
}
/**
 * Return the iterator as a pointer
 * @tparam T
 * @return
 */
template<typename T>
T *MSVector<T>::iterator::operator->() {
    return ptr;
}
/**
 * Increase the iterator by a given value, this make the pointer refers to the next position at (pointer + value)
 * @tparam T
 * @param value
 * @return
 */
template<typename T>
typename MSVector<T>::iterator MSVector<T>::iterator::operator+(const int &value) {
    ptr += value;
    return *this;
}
/**
 * Decease the iterator by a given value, this make the pointer refers to the previous position at (pointer - value)
 * @tparam T
 * @param value
 * @return
 */
template<typename T>
typename MSVector<T>::iterator MSVector<T>::iterator::operator-(const int &value) {
    ptr -= value;
    return *this;
}
/**
 * Print this MSVector according to the ostream name
 * @tparam T
 * @param output
 * @param vector
 * @return
 */
template<typename T>
std::ostream & operator<<(std::ostream& output, MSVector<T>& vector){
    for (int i = 0; i < vector.size(); ++i) {
        output << vector[i] << ' ';
    }
    return output;
}
