/***********************************************************************
 * Header:
 *    Deque
 * Summary:
 *    This is what a deque class might look like in the Standard Template
 *    Library.
 * Author
 *    Maximiliano Correa, Esteban Cabrera and Tony Moraes.
 ************************************************************************/
#ifndef DEQUE_H
#define DEQUE_H

#include <cassert>

template <class T>
class Deque
{
  private:
   int cap;
   int frontItem;
   int backItem;
   int numItems;
   T * data;
  public:
   /*****************************************************
    * Default Constructor
    *****************************************************/
  Deque() : numItems(0), cap(0),  frontItem(0), backItem(0), data(NULL) {}

   Deque(int capacity) throw (const char *);

   Deque(const Deque & rhs) throw (const char *);

   ~Deque();

   Deque<T> & operator = (const Deque<T> & rhs);
   /*****************************************************
    * empty() return if the stack is empty.
    *****************************************************/
   bool empty()   {return numItems == 0;}
   /*****************************************************
    *size() returns the size of the queue.
    *****************************************************/
   int size()     {return numItems;             }
   /*****************************************************
    * capacity() returns the capacity of the queue.
    *****************************************************/
   int capacity() { return cap;                 }
   /*****************************************************
    * clear() sets the size of the stack to 0.
    *****************************************************/
   void clear()   { numItems = 0;
      frontItem = 0;
      backItem = 0;}
   void push_front(const T & item) throw (const char *);
   void push_back(const T & item) throw (const char *);
   void pop_front() throw (const char *);
   void pop_back() throw (const char *);
   void resize(int newcap) throw (const char *);
   T & front() throw (const char *);
   T & back() throw(const char *);
};

/*****************************************************
 * NONDEFAULT CONSTRUCTOR
 * Create a Deque with a capacity parameter.
 *****************************************************/
   template <class T>
   Deque<T>::Deque(int capacity) throw (const char *)
   {
      numItems = 0;
      frontItem = 0;
      backItem = 0;
      cap = capacity;

            try
            {
               data = new T[cap];
            }
            catch (std::bad_alloc)
            {
               throw "ERROR: Unable to allocate buffer";
            }
   }

/*****************************************************
 * COPY CONSTRUCTOR
 * Copies the Deque so the lhs equals the rhs.
 *****************************************************/
   template <class T>
   Deque<T>::Deque(const Deque & rhs) throw (const char *)
   {
      assert(rhs.cap >= 0);

      // do nothing if there is nothing to do
      if (rhs.cap == 0)
      {
         cap = numItems = frontItem = backItem = 0;
         data = NULL;
         return;
      }

      // attempt to allocate
            try
            {
               this->data = new T[rhs.cap];
            }
            catch (std::bad_alloc)
            {
               throw "ERROR: Unable to allocate buffer";
            }

            // copy over the capacity and size
            assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
            cap = rhs.cap;
            numItems = rhs.numItems;
            frontItem = rhs.frontItem;
            backItem = rhs.backItem;

            // copy the items over one at a time using the assignment operator
            for (int i = 0; i < numItems; i++)
            {
               data[i] = rhs.data[(frontItem + i) % cap];
            }
            frontItem = 0;
            backItem = numItems;
   }

/*****************************************************
 * DESTRUCTOR-Frees memory
 *****************************************************/
   template<class T>
   Deque<T>::~Deque()
   {
      if (cap)
      {
         delete[] data;
      }
   }

/*****************************************************
 * Assignment Operator
 * Sets lhs equal to rhs.
 *****************************************************/
   template <class T>
   Deque<T> & Deque<T>::operator = (const Deque<T> & rhs)
   {
      assert(rhs.cap >= 0);

      // do nothing if there is nothing to do
      if (rhs.cap == 0)
      {
         cap = numItems = frontItem = backItem = 0;
         if (data != NULL)
         {
            delete[] data;
         }
         data = NULL;
         return *this;
      }

      // attempt to allocate
            try
      {
         if (data == NULL)
            data = new T[rhs.cap];
         else
         {
            delete[] data;
            data = new T[rhs.cap];
         }
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }

      // copy over the capacity and size
      assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
      cap = rhs.cap;
      numItems = rhs.numItems;
      frontItem = rhs.frontItem;
      backItem = rhs.backItem;

      // copy the items over one at a time using the assignment operator
      for (int i = 0; i < numItems; i++)
      {
         data[i] = rhs.data[(frontItem + i) % cap];
      }
      frontItem = 0;
      backItem = numItems - 1;
      return *this;
   }


   /*****************************************************
    * PUSH
    * Push the given item onto the top of the Deque.
    *****************************************************/
         template <class T>
         void Deque<T>::push_back(const T & item) throw (const char *)
         {

            //If the data isn't there or is full, then reallocate.
            if (data == NULL || (numItems == cap))
            {
               if (cap == 0)
               {
                  resize(1);
               }
               else
               {
                  resize(2 * cap);
               }
               //After realloacation, place the next item in the array.
               data[backItem++] = item;


            }
            //The array is NOT full, but backItem has reached the end of the array.
            else if (backItem == cap)
            {
               //So, the new location moves to 0.
               backItem = 0;
               data[backItem++] = item;

            }
            else
            {
               //If there are no special cases, just add the item to the array.
               data[backItem++] = item;

            }
            //Another item is added to the array, so numItems increases.
            numItems++;

         }

/*****************************************************
 * PUSH
 * Push the given item onto the top of the Deque.
 *****************************************************/
   template <class T>
   void Deque<T>::push_front(const T & item) throw (const char *)
   {

      //If the data isn't there or is full, then reallocate.
      if (data == NULL || (numItems == cap))
      {
         if (cap == 0)
         {
            resize(1);
         }
         else
         {
            resize(2 * cap);
         }

      }
      //The array is NOT full, but backItem has reached the end of the array.
      if (frontItem == 0)
      {
         //So, the new location moves to 0.
         frontItem = cap - 1;
         data[frontItem] = item;
      }
      else
      {
         //If there are no special cases, just add the item to the array.
         data[--frontItem] = item;

      }
      //Another item is added to the array, so numItems increases.
      numItems++;

   }
/*****************************************************
 * POP_FRONT
 * Error check, then remove the front item by decrement
 * the frontItem index by one.
 *****************************************************/
template <class T>
void Deque<T>::pop_front() throw (const char *)
{
   if (numItems == 0)
   {
      throw "ERROR: unable to pop from the front of empty deque";
   }
   else
   {
      //subtract the number of items and add to the frontItem
      //to "eliminate" the space that is being used
      if (frontItem != cap - 1)
      {
         frontItem++;
         numItems--;
      }
      //If the frontItem has reached the end,
      //restart at the beginning.
      else
      {
         frontItem = 0;
         numItems--;
      }
   }
}

/*****************************************************
 * POP_BACK
 * Error check, then remove the back item by decrementing
 * the backItem index by one.
 *****************************************************/
template <class T>
void Deque<T>::pop_back() throw (const char *)
{
   if (numItems == 0)
   {
      throw "ERROR: unable to pop from the back of empty deque";
   }
   else
   {
      //subtract the number of items and add to the frontItem
      //to "eliminate" the space that is being used
      if (backItem != 0)
      {
         backItem--;
         numItems--;
      }
      //If the frontItem has reached the end,
      //restart at the beginning.
      else
      {
         backItem = cap - 1;
         numItems--;
      }
   }
}
/*****************************************************
 * FRONT
 * Return the Front item.
 *****************************************************/
template <class T>
T & Deque<T>::front() throw (const char *)
{
   if (numItems != 0)
      return data[frontItem];
   else
      throw "ERROR: unable to access data from an empty deque";

}

/*****************************************************
 * BACK
 * Return the Back item.
 *****************************************************/
template <class T>
T & Deque<T>::back() throw (const char *)
{
   if (numItems != 0)
   {
      if (backItem == 0)
      {
         return data[cap - 1];
      }
      else
      {
         return data[backItem - 1];
      }
   }
   else
      throw "ERROR: unable to access data from an empty deque";

}

/*****************************************************
 * RESIZE
 * Reallocate the memory to allow for a bigger Deque.
 *****************************************************/
template <class T>
void Deque<T>::resize(int newcap) throw (const char *)
{
   T * tempdata;
      try
      {
         tempdata = new T[newcap];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for queue";
      }
      //Read items into the array that will be used for data.
      for (int i = 0; i < numItems; i++)
      {
         tempdata[i] = data[(frontItem + i) % cap];
      }
      frontItem = 0;
      backItem = numItems;
      if (data != NULL)
      {
         delete[] data;
         data = NULL;
      }
      data = tempdata;
      tempdata = NULL;
      cap = newcap;
}


#endif //STACK_H
