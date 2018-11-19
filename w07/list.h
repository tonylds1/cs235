/***********************************************************************
 * Header:
 *    list
 * Summary:
 *    This class contains the notion of a list: a bucket to hold
 *    data for the user.
 *
 *    This will contain the class definition of:
 *       list            
 *       list :: iterator 
 * Author
 *    Maximiliano Correa, Esteban Cabrera, Tony Moraes
 ************************************************************************/

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cassert>  // because I am paranoid
#include "node.h"

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

/************************************************
 * 
 * A class that holds stuff
 ***********************************************/
template <class T>
class list
{
public:
   // constructors and destructors (Create)
   list(): numElements(0), pTail(NULL), pHead(NULL);
   list(const list & rhs)                 throw (const char *);
  ~list()                                 { freeData(pHead)   }

   //Assignment
   list & operator = (const list & rhs) throw (const char *);
   
   // standard container interfaces
   int  size()     const { return numElements;             }
   bool empty()    const { return numElements == 0;        }
   void clear()    { numElements = 0;                      };
   
   // the various iterator interfaces
   class iterator;
   iterator begin()      { return iterator (pHead);               }
   iterator end()        { return iterator (pTail); };

   // the various iterator interfaces
   class const_iterator;
   const_iterator cbegin() const     { return const_iterator (pHead);         }
   const_iterator cend() const       { return const_iterator (pTail); }

   iterator find(const T & t) throw (const char *);
   const_iterator find(const T & t) const throw (const char *);

   void push_back(const T & t)   throw (const char *);
   void push_front(const T & t)   throw (const char *);
   void pop_back(const T & t)   throw (const char *);
   void pop_front(const T & t)   throw (const char *);
   
   T & front()      { return numElements ? pHead->data : NULL; }
   T & back()       { return numElements ? pTail->data : NULL; }
   
   iterator insert(iterator & it, const T & data) throw (const char *);
   
   void erase(T & t) throw (const char *);
   void erase(iterator & it) throw (const char *);

   // a debug utility to display the array
   // this gets compiled to nothing if NDEBUG is defined
   void display() const; 
   
private:
   Node <T> * pHead;               
   Node <T> * pTail;               
   int numElements;               // the number of elements
};

/**************************************************
 * LIST ITERATOR
 * An iterator through vector
 *************************************************/
template <class T>
class list <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator()      : p(NULL)      {              }
   iterator(T * p) : p(p)         {              }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
         T & operator * ()       { return *p; }
   const T & operator * () const { return *p; }

   // prefix increment
   iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      p++;
      return tmp;
   }
   
   // prefix decrement
   iterator & operator -- ()
   {
      p--;
      return *this;
   }

   // postfix decrement
   iterator operator -- (int postfix)
   {
      iterator tmp(*this);
      p--;
      return tmp;
   }

private:
   T * p;
};

/**************************************************
 * VECTOR CONST ITERATOR
 * An iterator through vector
 *************************************************/
template <class T>
class list <T> :: const_iterator
{
public:
   // constructors, destructors, and assignment operator
   const_iterator()      : p(NULL)      {              }
   const_iterator(T * p) : p(p)         {              }
   const_iterator(const const_iterator & rhs) { *this = rhs; }
   const_iterator & operator = (const const_iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const const_iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const const_iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
   const T & operator * () const { return *p; }

   const_iterator & operator + (int value) { p = p + value; return *this; }
   const_iterator & operator - (int value) { p = p - value; return *this; }

   // prefix increment
   const_iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   const_iterator operator ++ (int postfix)
   {
      const_iterator tmp(*this);
      p++;
      return tmp;
   }
   
   // prefix decrement
   const_iterator & operator -- ()
   {
      p--;
      return *this;
   }

   // postfix decrement
   const_iterator operator -- (int postfix)
   {
      const_iterator tmp(*this);
      p--;
      return tmp;
   }

private:
   T * p;
};

/********************************************
 * LIST :: FIND
 * returns a iterator pointed to the given element
 ********************************************/
template <class T>
typename list <T> :: iterator list <T> :: find(const T & t) throw (const char *)
{
    return begin();
}

/********************************************
 * LIST :: FIND FOR CONST
 * returns a iterator pointed to the given element
 ********************************************/
template <class T>
typename list <T> :: const_iterator list <T> :: find(const T & t) const throw (const char *)
{
    return cbegin();
}

/********************************************
 * LIST :: INSERT
 * inserts an element in the collection and double the
 * object`s capacity when necessary.
 ********************************************/
template <class T>
iterator list <T> list<T> :: insert(iterator & it, const T & data) throw (const char *)
{
    return pTail->insert(data);
}

/********************************************
 * LIST :: ERASE (VALUE)
 * delete the given element and re-arrange the others
 ********************************************/
template <class T>
void list <T> :: erase(T & t) throw (const char *)
{
    int indexErase = findIndex(t);

    if (indexErase == numElements)
    {
        return;
    }

    for (int i = indexErase; i < numElements - 1; i++)
    {
        data[i] = data[i + 1];
    }

    numElements--;
}

/********************************************
 * LIST :: ERASE (ITERATOR)
 * delete the given element and re-arrange the others
 ********************************************/
template <class T>
void list <T> :: erase(iterator & it) throw (const char *)
{
    erase(*it);
}

/*******************************************
 * LIST :: Assignment
 *******************************************/
template <class T>
list <T> & list <T> :: operator = (const list <T> & rhs)
          throw (const char *)
{
   //avoid garbage content.
   this->clear();

   if (this->capacity() < rhs.size())
      this->resize(rhs.size());

   for (int i = 0; i < rhs.size(); i++)
      this->insert(rhs.data[i]);

   return *this;
}

/*******************************************
 * LIST :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
list <T> :: list(const list <T> & rhs) throw (const char *)
{
   assert(rhs.numCapacity >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.numCapacity == 0)
   {
      numCapacity = 0;
      numElements = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity
   numElements = rhs.numElements;
   numCapacity = rhs.numCapacity;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
      data[i] = rhs.data[i];
}

/**********************************************
 * VECTOR : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "capacity"
 **********************************************/
template <class T>
list <T> :: list(int numCapacity) throw (const char *)
{
   assert(numCapacity >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an array, this is kinda pointless
   if (numCapacity == 0)
   {
      this->numElements = 0;
      this->numCapacity = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   // copy over the stuff
   this->numElements = 0;
   this->numCapacity = numCapacity;
}

/**********************************************
 * LIST : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "capacity" and a first element
 **********************************************/
template <class T>
list <T> :: list(int numCapacity, T & t) throw (const char *)
{
   assert(numCapacity >= 1);
   
   this->numCapacity = numCapacity;
   this->numElements = 1;

   // attempt to allocate
   try
   {
      data = new T[numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   data[0] = t;
}

/********************************************
 * LIST : RESIZE
 * Increase the capacity, alocting new memory
 *******************************************/
template <class T>
void list <T> ::resize(int newCapacity)  throw (const char *)
{
    if (newCapacity < numElements)
    {
        throw "ERROR: this resize will loose data.";
    }

    T * newData;
    try
    {
        newData = new T[newCapacity];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate buffer";
    }

    for (int i = 0; i < numElements; i++)
    {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    numCapacity = newCapacity;
}

/********************************************
 * LIST : FINDINDEX (SORTED)
 * return the position in the list of the given element
 *******************************************/
template <class T>
int list <T> ::findIndex(const T & t) const throw (const char *)
{
    int indexBegin = 0;
    int indexEnd = numElements - 1;

    while (indexBegin <= indexEnd)
    {
        int indexMiddle = (indexBegin + indexEnd) / 2;

        if (t == data[indexMiddle])
        {
            return indexMiddle;
        }

        if (t < data[indexMiddle])
        {
            indexEnd = indexMiddle - 1;
        }
        else
        {
            indexBegin = indexMiddle + 1;
        }
    }

    return numElements;
}

/********************************************
 * LIST : UNION
 * return the position in the list of the given element
 *******************************************/
template <class T>
list <T> list<T> :: operator || (list <T> & rhs) throw (const char *)
{
    list <T> sUnion;
    for (int i = 0; i < size(); i++)
    {
        sUnion.insert(data[i]);
    }

    for (int i = 0; i < rhs.size(); i++)
    {
        sUnion.insert(rhs[i]);
    }

    return sUnion;
}

/********************************************
 * LIST : INTERSECTION
 * return the position in the list of the given element
 *******************************************/
template <class T>
list <T> list<T> :: operator && (list <T> & rhs) throw (const char *)
{
    list <T> intersection;
    int indexLhs = 0;
    int indexRhs = 0;

    while (indexLhs < numElements && indexRhs < rhs.numElements)
    {
        if (data[indexLhs] == rhs.data[indexRhs])
        {
            intersection.insert(data[indexLhs]);
            indexRhs++;
            indexLhs++;
        }
        else if (data[indexLhs] < rhs.data[indexRhs])
        {
            indexLhs++;
        }
        else
        {
            indexRhs++;
        }
    }

    return intersection;
}

/********************************************
 * LIST : DIFFERENCE
 * return the position in the list of the given element
 *******************************************/
template <class T>
list <T> list<T> :: operator - (list <T> & rhs) throw (const char *)
{
    list <T> difference;
    int indexLhs = 0;
    int indexRhs = 0;

    while (indexLhs < numElements)
    {
        if (indexRhs >= rhs.size())
        {
            difference.insert(data[indexLhs]);
            indexLhs++;
        }

        if (data[indexLhs] == rhs.data[indexRhs])
        {
            indexRhs++;
            indexLhs++;

            continue;
        }

        if (data[indexLhs] > rhs.data[indexRhs])
        {
            indexRhs++;
        }
        else
        {
            difference.insert(data[indexLhs]);
            indexLhs++;
        }
    }



    return difference;
}


/********************************************
 * LIST : DISPLAY
 * A debug utility to display the contents of the array
 *******************************************/
template <class T>
void list <T> :: display() const
{
#ifndef NDEBUG
   std::cerr << "list<T>::display()\n";
   std::cerr << "\tnumElements = " << numElements << "\n";
   for (int i = 0; i < numElements; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
}

}; // namespace custom

#endif // LIST_H

