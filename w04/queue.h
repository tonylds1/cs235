/*************************************************************************
 * Header:
 *    Queue
 * Summary:
 *    This class contains the notion of a queue.
 * Authors:
 *    Maximiliano Correa, Esteban Cabrera and Tony Moraes
 ************************************************************************/
#ifndef Queue_h
#define Queue_h

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <new>          // for NEW and DELETE
#include <cassert>      // for ASSERT

/*****************************************
 * Queue
 * This class will add and take away data
 ****************************************/
template <class T>
class Queue
{
  public:

   // Default constructor and non-default constructor
   Queue(int in_capacity = 0) throw (const char *);

   // copy constructor
   Queue(const Queue<T> & source) throw (const char *);

   // destructor
   ~Queue() {
      if (m_capacity > 0) // If this is true, we have an allocated buffer
         delete[] m_data;
   }

   // assignment operator
   Queue<T> & operator = (const Queue<T> & rhs) throw (const char *);
   // check and see if empty
   bool empty() const { return m_numPush == m_numPop; }

   // returns the size
   int size() const { return m_numPush - m_numPop; }

   // gives us the capacity
   int capacity() const { return m_capacity; }

   // will clear the board
   void clear() { m_numPush = m_numPop; }

   // add a value to the top
   void push(const T & value) throw (const char *);

   // pull a value from the top
   void pop() throw (const char*);

   // gets the value from the front
   T & front() const throw (const char*);

   // gets the value from the front
   T & back() const throw (const char*);

   // displays the contents of the queue to an ostream
   void display(std::ostream & out) const;

  private:

   int m_capacity;                                       // capacity of queue
   T * m_data;                                           // array to store element
   int m_numPop;                                           // number of times a value has been popped
   int m_numPush;                                          // number of times a value has been pushed
   void resize() throw (const char *);                   // resize the stack
   int iTail() const { return (m_numPush - 1) % m_capacity; }  // returns the back of the queue
   int iHead() const { return m_numPop % m_capacity; }         // returns the front of the queue
};

/***********************************************************************
 * QUEUE :: DEFAULT / NON_DEFAULT CONSTRUCTOR
 * Creates an instance of the queue. If the caller provides a capacity
 * we create a Queue with enough storage to hold that capacity
 ************************************************************************/
template <class T>
Queue<T> :: Queue(int in_capacity) throw (const char *)
: m_capacity(0), m_numPush(0), m_numPop(0), m_data(NULL)
{
   assert(in_capacity >= 0);
   // First, assure the user specified a valid capacity; if capacity
   // is < 0, we just exit, we've already initialized our values
   // to defaults
   if (in_capacity <= 0)
      return;

   // If we've reached this point, we have an input capacity > 0
   // so we'll try allocating our array.
   m_capacity = in_capacity;
   m_data = new (std::nothrow) T[m_capacity];

   // Check to see if we failed to allocate, and if so, throw
   // an error
   if (NULL == m_data)
      throw "ERROR: Unable to allocate a new buffer for Queue";
}

/**********************************************************************
 * QUEUE :: COPY CONSTRUCTOR
 * Creates a new Queue by copying the contents of another
 **********************************************************************/
template <class T>
Queue<T> :: Queue(const Queue<T> & source) throw (const char *)
: m_capacity(source.m_capacity), m_numPush(source.m_numPush), m_numPop(source.m_numPop)
{

   // Now we try to allocate our array
   m_data = new (std::nothrow) T[m_capacity];

   // If we failed, we throw an error
   if (NULL == m_data)
      throw "ERROR: Unable to allocate a new buffer for Queue";

   // If the source is empty, we shouldn't try to copy anything
   if (source.empty())
      return;

   // If we reach this point, we've successfully allocated
   // our buffer, so let's copy the data
   for (int i = source.m_numPop; i < source.m_numPush; i++)
      m_data[i % m_capacity] = source.m_data[i % source.m_capacity];
}

/**********************************************************************
 * QUEUE :: ASSIGNMENT
 * Assigns one Queue to another, creating a copy of the source
 **********************************************************************/
template <class T>
Queue<T> & Queue<T> :: operator =
   (const Queue<T> & rhs) throw (const char *)
{
   // Check to see if we're self-assigning and quit if we are
   if (this == &rhs)
      return *this;

   // Now, check to see if our capacities are the same; if they aren't
   // then we need to delete our existing buffer and (potentially)
   // copy in the new one
   if (m_capacity != rhs.m_capacity)
   {
      // We only delete our data array if we have data
      // note that we're assuming that m_data is not null if m_capacity
      // is not zero.
      if (m_capacity)
         delete[] m_data;

      m_capacity = rhs.m_capacity;

      // We only create a new array if our source had one (i.e.
      // it had capacity)
      if (m_capacity)
      {
         m_data = new (std::nothrow) T[m_capacity];

         if (NULL == m_data)
            throw "ERROR: Unable to allocate a new buffer for Queue.";
      }
   }

   // And now we copy over the data
   m_numPush = m_numPop = 0;

   for (int i = rhs.m_numPop; i < rhs.m_numPush; i++)
      push(rhs.m_data[i % rhs.m_capacity]);

   return *this;
}

/****************************************************************
 * QUEUE :: PUSH
 * Adds  a value to the back of the queue
 ****************************************************************/
      template <class T>
      void Queue <T> :: push(const T & value) throw (const char *)
      {
         if (size() == capacity())
            resize();
         m_numPush++;
         m_data[iTail()] = value;
      }

/****************************************************************
 * QUEUE :: FRONT
 * Will check what value is at the front of the queue
 ****************************************************************/
template <class T>
T & Queue <T> :: front() const throw (const char*)
{
   if (!empty())
      return (m_data[iHead()]);
   else
   {
      throw "ERROR: attempting to access an element in an empty queue";
   }
}

/****************************************************************
 * QUEUE :: BACK
 * Will check what value is at the back of the queue
 ****************************************************************/
template <class T>
T & Queue <T> :: back() const throw (const char*)
{
   if (!empty())
      return (m_data[iTail()]);
   else
   {
      throw "ERROR: attempting to access an element in an empty queue";
   }
}


/**********************************************************
 * QUEUE :: POP
 * Pulls off an item from the front
 *********************************************************/
template <class T>
void Queue <T> :: pop() throw (const char*)
{
   // if queue is not empty, pop off first element
   if (!empty())
      m_numPop++;
   //else
   // throw "ERROR: attempting to pop from an empty queue";
}

/**********************************************************
 * QUEUE :: RESIZE
 * Resizes the Queue
 *********************************************************/
template <class T>
void Queue <T> :: resize() throw (const char *)
{
   // Lets make sure we have an array and if we do not
   // have an array, lets create one.
   if (!m_capacity)
   {
      m_data = new (std::nothrow) T[1];

      if (NULL == m_data)
         throw "ERROR: Unable to allocate a new buffer for Queue";

      m_capacity = 1;
      return;
   }

   // From here we have a full Queue and we will size it accordingly
   T * new_data = new (std::nothrow) T[m_capacity * 2];
   if (new_data == NULL)
      throw "ERROR: Unable to allocate a new buffer for Queue";

   T * old_data = m_data;

   m_data = new_data;
   int old_numPop = m_numPop;
   int old_numPush = m_numPush;
   int old_m_capacity = m_capacity;
   m_capacity *= 2;
   m_numPush = m_numPop = 0;
   for (int i = old_numPop; i < old_numPush; i++)
      push(old_data[i % old_m_capacity]);


   delete[] old_data;
}

#endif /* Queue_h */
