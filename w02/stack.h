/***********************************************************************
 * Header:
 *    STACK
 * Summary:
 *    This class implements an abstract data type which allows
 *    users to push any object into the data type. However, users may only
 *    remove or take objects in the reverse order of when the objects
 *    were entered into the stack.
 * Author
 *    Maximiliano Correa, Esteban Cabrera, Tony Moraes
 ************************************************************************/

#ifndef STACK_H
#define STACK_H
namespace custom
{
/************************************************
* STACK
* A class that holds stuff
***********************************************/
template <class T>
class stack {
public:
// constructors and destructors
stack() {this->numElements = 0; this->numCapacity = 0; this->data = NULL;}
stack(int capacity) throw (const char *);
stack(const stack & rhs) throw (const char *);
~stack();

// standard container interfaces
int  size()     const { return numElements;                 }
int  max_size() const { return numCapacity;                 }
int  capacity() const { return numCapacity;                 }
bool empty() const {return numElements == 0;}
void clear() {numElements = 0;}
void push(T data);
void pop();
T & top() throw (const char *);
T top() const throw (const char *);

// operators
stack & operator = (const stack & rhs) throw (const char *);

private:
T * data;     // dynamically allocated array of T
int numElements; // how many items the stack is holding
int numCapacity; // how many items the stck could hold
};

/*******************************************
* STACK :: Assignment
*******************************************/
template <class T>
stack <T> & stack <T> :: operator = (const stack <T> & rhs)
throw (const char *)
{
// we can only copy arrays of equal size.
if (rhs.size() != size())
           
// attempt to allocate memory
try
{
    data = new T[rhs.numElements];
}
catch (std::bad_alloc)
{
    throw "ERROR: Unable to allocate buffer";
}
    numElements = rhs.numElements;
    numCapacity = rhs.numCapacity;


    for (int i = 0; i < numElements; i++)
        data[i] = rhs.data[i];

        return *this;
}

/**********************************************
* STACK : NON-DEFAULT CONSTRUCTOR
* Preallocate the stack to capacity
**********************************************/
template <class T>
stack <T> :: stack(int capacity) throw (const char *)
{
// do nothing if there is nothing to do.
// since we can't grow an array, this is kinda pointless
if (numCapacity <= 0)
{
    this->numElements = 0;
    this->numCapacity = 0;
    this->data = NULL;
    return;
}

// attempt to allocate
try
{
    data = new T[capacity];
}
catch (std::bad_alloc)
{
    throw "ERROR: Unable to allocate buffer";
}

// initialize indices with 0
for (int i = 0; i < capacity; i++)
{
    this->data[i] = 0;
}

// copy over the stuff
this->numElements = 0;
this->numCapacity = capacity;
}

/*******************************************
* STACK :: COPY CONSTRUCTOR
*******************************************/
template <class T>
stack <T> :: stack(const stack <T> & rhs) throw (const char *)
{
// do nothing if there is nothing to do
if (rhs.numElements == 0)
{
     numElements = 0;
     data = NULL;
    return;
}

// attempt to allocate
try
{
    data = new T[rhs.numElements];
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
/*******************************************
* STACK :: DECONSTRUCTOR
*******************************************/
template <class T>
stack <T> :: ~stack()
{
    clear();
}
/*****************************************************
* STACK :: PUSH
* Adds an element to the stack.
* If the stack is full,
* then the capacity will be doubled.
* void --> void
*****************************************************/
template <class T>
void stack <T> :: push(T data)
{
    numElements++; // increments the element count

//---Create New Stack:---
//Checks whether the stack is empty
if (numCapacity <= 0)
{
    numElements = 1;
    numCapacity = 1;

try
{
    this->data = new T[1];
}
catch (std::bad_alloc)
{
    throw "ERROR: Unable to allocate a new buffer for Stack";
}

}
// end if for check for empty stack

//---Memory Allocation:---
// checks whether the capacity is full
if (numCapacity < numElements)
{
    numCapacity *= 2;

// attempt to allocate memory
try
{
    T * tempData = new T[numCapacity];

    // copy data to a new, larger array
    for (int i = 0; i < numElements -1; i++)
    {
        tempData[i] = this->data[i];
    }

    // save data to correct location
    this->data = tempData;
}
catch (std::bad_alloc)
{
    throw "ERROR: Unable to allocate a new buffer for Stack";
}
} // end if for capacity <= elements check

//---Add Element to Stack:---
//attempt to allocate memory
this->data[numElements - 1] = data;


//std::cerr << "elements = " << numElements << std::endl;
//std::cerr << "capacity = " << numCapacity << std::endl;
//std::cerr << "END PROCESSING STACK!\n";

    return;
}
/*****************************************************
* STACK :: POP
* Removes an element from the end of the stack,
* serving to reduce the size by one.
* void --> void
*****************************************************/
template <class T>
void stack <T> :: pop()
{
// if the stack is empty, there is nothing to do.
if(numElements == 0 || numCapacity <= 0)
    return;

    numElements--;
    return;
}
/*****************************************************
* STACK :: TOP
* Returns the element currently
* at the end of the stack.
* A non-constant method which returns by-reference.
* void --> Object Reference
*****************************************************/
template <class T>
T & stack <T> :: top() throw (const char *)
{
// if the stack is empty, throw an error.
if(numElements == 0 || numCapacity <= 0)
    throw "ERROR: Unable to reference the element from an empty Stack";

    return data[numElements-1];
}

/*****************************************************
* STACK :: TOP - CONST
* Returns the element currently
* at the end of the stack.
* A constant method which returns const by-reference.
* void --> Object
*****************************************************/
template <class T>
T stack <T> :: top() const throw (const char *)
{
// if the stack is empty, throw an error.
if(numElements == 0 || numCapacity <= 0)
throw "ERROR: Unable to reference the element from an empty Stack";

return data[numElements-1];
}
}; // end custom namespace
#endif // STACK_H