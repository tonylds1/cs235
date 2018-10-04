/***********************************************************************
 * Header:
 *    Vector
 * Summary:
 *    This class contains the notion of an vector: a bucket to hold
 *    data for the user.
 *
 *    This will contain the class definition of:
 *       vector             : similar to std::vector
 *       vector :: iterator : an iterator through the vector
 * Author
 *    Br. Tony Moraes
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cassert>  // because I am paranoid

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

/************************************************
 * VECTOR
 * A class that holds stuff
 ***********************************************/
template <class T>
class vector
{
public:
   // constructors and destructors
   vector(): numElements(0), numCapacity(0) { data = NULL; }
   vector(int numElements)                  throw (const char *);
   vector(int numElements, T & t)           throw (const char *);
   vector(const vector & rhs)        throw (const char *);
  ~vector()                         { delete [] data;   }
   vector & operator = (const vector & rhs) throw (const char *);
   
   // standard container interfaces
   int  size()     const { return numElements;                 }
   int  capacity() const { return numCapacity;             }
   bool empty()    const { return numElements == 0;            }
   void clear();
   void push_back (const T & t) throw (const char *);
   T & access(int index)  throw (const char *)
   {
      if (index > numElements) 
          throw "ERROR: intex out of bounds.";
      if (index < 0) 
          index = numElements - index;
   
      return data[index];
   }

   // vector-specific interfaces
   // what would happen if I passed -1 or something greater than size?
   T & operator [] (int index)       throw (const char *)
   {
      return access(index);
   }
   const T & operator [] (int index) const throw (const char *)
   {
      return data[index];
   }
   
   // the various iterator interfaces
   class iterator;
   iterator begin()      { return iterator (data); }
   iterator end();       

   // the various iterator interfaces
   class const_iterator;
   const_iterator cbegin() const     { return const_iterator (data); }
   const_iterator cend() const;

   // a debug utility to display the array
   // this gets compiled to nothing if NDEBUG is defined
   void display() const; 
   
private:
   T * data;               // dynamically allocated array of T
   int numElements;               // the number of elements
   int numCapacity;           // the capacity

   void resize(int newCapacity)
   {
      if (newCapacity > numElements)
         throw "ERROR: this resize will loose data.";
      
      numCapacity = newCapacity;
   }
};

/**************************************************
 * VECTOR ITERATOR
 * An iterator through vector
 *************************************************/
template <class T>
class vector <T> :: iterator
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
class vector <T> :: const_iterator
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
 * VECTOR :: PUSH_BACK
 * inserts an element in the collection and double the
 * object`s capacity when necessary.
 ********************************************/
template <class T>
void vector <T> :: push_back (const T & t) throw (const char*)
{
      assert(this->numElements <= this->numCapacity);
      if (numCapacity == numElements) 
            numCapacity = numCapacity * 2;
      
      data[numElements++] = t;
}

/********************************************
 * VECTOR :: CLEAR
 * erase all data
 ********************************************/
template <class T>
void vector <T> :: clear ()
{
   numElements = 0;
}

/********************************************
 * VECTOR :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename vector <T> :: iterator vector <T> :: end ()
{
   return iterator (data + numElements);
}

/********************************************
 * VECTOR :: CEND
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename vector <T> :: const_iterator vector <T> :: cend () const
{
   return const_iterator (data + numElements);
}

/*******************************************
 * VECTOR :: Assignment
 *******************************************/
template <class T>
vector <T> & vector <T> :: operator = (const vector <T> & rhs)
          throw (const char *)
{
   //avoid garbage content.
   delete[] data;

   for (int i = 0; i < numElements; i++)
      this->push_back(rhs.data[i]);

   return *this;
}

/*******************************************
 * VECTOR :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
vector <T> :: vector(const vector <T> & rhs) throw (const char *)
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
vector <T> :: vector(int numCapacity) throw (const char *)
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
   this->numElements = numElements;
   this->numCapacity = numCapacity;
}

/**********************************************
 * VECTOR : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "capacity" and a first element
 **********************************************/
template <class T>
vector <T> :: vector(int numCapacity, T & t) throw (const char *)
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
 * VECTOR : DISPLAY
 * A debug utility to display the contents of the array
 *******************************************/
template <class T>
void vector <T> :: display() const
{
#ifndef NDEBUG
   std::cerr << "vector<T>::display()\n";
   std::cerr << "\tnumElements = " << numElements << "\n";
   for (int i = 0; i < numElements; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
}

}; // namespace custom

#endif // VECTOR_H

