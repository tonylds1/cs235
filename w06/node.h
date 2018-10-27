/*******************************************************************************
* Header File
*    node
* Summary: 
*    Node struct.
* Author:
*    Maximiliano Correa, Esteban Cabrera and Tony Moraes.
*******************************************************************************/
#include <stdlib.h>

#ifndef NODE_H
#define NODE_H
/*******************************************************************************
* NODE
* Linked list node.
*******************************************************************************/
template <class T>
class Node
{
public:
   T data;
   Node * pPrev;
   Node * pNext;
   
   //Default Constructor
   Node() : data(0), pNext(NULL), pPrev(NULL) {}
   
   //Non Default Constructor
   Node(const T &t) : data(t), pPrev(NULL), pNext(NULL) {}
};

/*******************************************************************************
* FREE DATA
* Release all the memory contained in a given linked-list. 
* The one parameter is a pointer to the head of the list.
*******************************************************************************/
template <class T>
void freeData(Node<T> * & pHead)
{

   // delete items from the list
   while (pHead != NULL)
   {
      Node<T> * p = pHead->pNext;
      delete pHead;
      pHead = p;
   }
   
   pHead = NULL;
}

/*******************************************************************************
* COPY
* Copies a linked-list. Takes a pointer to a Node as a parameter and returns a 
* newly created linked-list containing a copy of all the nodes below the list 
* represented by the parameter.
*******************************************************************************/
template <class T>
Node <T> * copy(Node <T> * pSource)
{
	/*	
   Node <T> *pDestination = new Node <T> (pSource->data);
   Node <T> *pS = pSource;
   Node <T> *pD = pDestination;
   for (pS = pS->pNext; pS; pS = pS->pNext, pD = pD->pNext)
      pD = insert(pD, pS->data, true);
   return pDestination;*/
   

	
   // create new node
   Node<T> * pNew = new Node<T>;
   // point to the new copy of node
   Node<T> * pCopy = pNew;
   
   // copy first data item
   pNew->data = pSource->data;
   pSource = pSource->pNext;
   
   // if head has data, copy the data over
   while (pSource != NULL)
   {
      // create new node with data
      pNew->pNext = new Node<T>(pSource->data);
      // advance nodes a step
      pSource = pSource->pNext;
      pNew = pNew->pNext;
   }
   
   // return head of copy node
   return pCopy;
}

/*******************************************************************************
* INSERT
* Inserts a new Node into the current linked-list. The first parameter is the 
* Node after the new Node inserted into the list. The second parameter is the 
* value to be placed in the new Node. An optional third parameter is set to true
* if the new element is to be at the head of the list. Returns a pointer to the 
* newly created Node.
*******************************************************************************/
template <class T>
Node <T> * insert(Node <T> * pNode, const T & data, bool after = false) throw (const char *)
{
   Node <T> *pNew = new Node <T> (data);
   
   if (!pNode) // if passed node is uninitialized
      pNew->data = data; //to revert, change pNode to pNew
   else if(pNode != NULL && !after) // insert before
   {
      if (pNode->pPrev)
      {
         pNew->pPrev = pNode->pPrev;
         pNode->pPrev->pNext = pNew;
      }
      pNew->pNext = pNode;
      pNode->pPrev = pNew;
   }
   else // insert after
   {
      if(pNode->pNext)
      {
         pNew->pNext = pNode->pNext;
         pNode->pNext = pNew;
      }
      pNew->pPrev = pNode;
      pNode->pNext = pNew;
   }
   return pNew;
   /*
   try
   {
   	if (after || pNode == NULL)
   	{
   		pNew->pNext = pNode;
   		pNode = pNew;
   	}
   	else
   	{
   		pNew->pNext = pNode->pNext;
   		pNode->pNext = pNew;
   	}
   }
   catch(std::string pNode)
   {
   		throw "Error: Unable to allocate a new Node";
   }
   return pNode;
/*
   Node<T> *pNew = new Node <T> (data);
   if (pNode != NULL && !after)
   {
      pNew->pNext = pNode;
      pNew->pPrev = pNode->pPrev;
      pCurrent.pPrev = pNew;
      if (pNew->pPrev)
         pNew->pPrev->pNext = pNew;
   }
   if (pNode != Null && after)
   {
   }
   */

}

/************************************************
 * find
 * Helps the user find things within the node
 ***********************************************/
template <class T>
Node<T> * find(Node<T> * pHead, const T &t)
{
   // iterate through list and compare value to data
   for (Node<T> * p = pHead; p; p = p->pNext)
   {
      if (p->data == t)
         return p;
   }

   return NULL;
}

/************************************************
 * remove
 * Removes a node from a list
 ***********************************************/
template <class T>
Node<T> * remove(Node<T> * pNode)
{	
   if (pNode == NULL)
   {
   	std::cout << "The list is empty";
   }
   
   Node <T> * pReturn;

   // Fix the pNext pointer from previos node
   if (pNode->pPrev)
   {
      pNode->pPrev->pNext = pNode->pNext;
   }
   
   //fix the pPrev pointer from next node
   if (pNode->pNext)
   {
   	pNode->pNext->pPrev = pNode->pPrev;
   }

   //returns previous, next or null;
   pReturn = pNode->pPrev ? pNode->pPrev : pNode->pNext;
   
   delete pNode;
   //returns who take its place
   return pReturn;
}

/************************************************
 * << Operator
 * Stream insertion operator
 ***********************************************/
template <class T>
std::ostream & operator<<(std::ostream & out, const Node<T> * pHead)
{
   // operator overload to display the list
   for (const Node<T> * p = pHead; p; p = p->pNext)
   {
      if(p->pNext != NULL)
      {
         out << p->data << ", ";
      }
      else
      {
         out << p->data;
      }
   }
   return out;
}
#endif // NODE_H