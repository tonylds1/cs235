/*******************************************************************************
* Header File
*    node
* Summary: 
*    BNode struct.
* Author:
*    Maximiliano Correa, Esteban Cabrera and Tony Moraes.
*******************************************************************************/
#include <stdlib.h>

#ifndef BNODE_H
#define BNODE_H
/*******************************************************************************
* NODE
* Linked list node.
*******************************************************************************/
template <class T>
class BNode
{
public:
   T data;
   BNode * pParent;
   BNode * pLeft;
   BNode * pRight;
   
   //Default Constructor
   BNode() : data(0), pParent(NULL), pLeft(NULL), , pRight(NULL) {}
   
   //Non Default Constructor
   BNode(const T &t) : data(t), pParent(NULL), pLeft(NULL), , pRight(NULL) {}
};

/*******************************************************************************
* FREE DATA (DELETE)
* Release all the memory contained in a given linked-list. 
* The one parameter is a pointer to the head of the list.
*******************************************************************************/
template <class T>
void freeData(BNode<T> * & pNode)
{
   if (!pNode) 
      return null;
   
   freeData(pNode->pLeft);
   freeData(pNode->pRight);
   
   delete pNode;
   pNode = NULL;
}

/*******************************************************************************
* COPY
* To copy a binary tree, it is necessary to traverse the entire tree.
*******************************************************************************/
template <class T>
BNode <T> * copy(BNode <T> * pSource)
{
   BNode<T> * pDestination = new BNode<T> (pSource->data);
   //BNode<T> * pDest = pDestination;
   
   pDestination->pLeft = copy(pSource->pLeft);
   pDestination->pRight = copy(pSource->pRight);
   
   if (pDestination->pLeft)
   {
      pDestination->pLeft->pParent = pDestination;
   }
   
   if (pDestination->pRight)
   {
      pDestination->pRight->pParent = pDestination;
   }
   
   // return head of copy node
   return pDestination;
}

/*******************************************************************************
* INSERT
* Inserts a new BNode into the current linked-list. The first parameter is the 
* BNode after the new BNode inserted into the list. The second parameter is the 
* value to be placed in the new BNode. An optional third parameter is set to true
* if the new element is to be at the head of the list. Returns a pointer to the 
* newly created BNode.
*******************************************************************************/
template <class T>
BNode <T> * insert(BNode <T> * pBNode, const T & data, bool after = false) throw (const char *)
{
   BNode <T> *pNew = new BNode <T> (data);
   
   if (pBNode == NULL)
   {
      return pNew;
   }
   
   if (after) 
   {
      pNew->pNext = pBNode->pNext;
      pNew->pPrev = pBNode;
      
      if (pBNode->pNext)
      {
         pBNode->pNext->pPrev = pNew;
      }

      pBNode->pNext = pNew;
      
      return pNew;
   }
   
   pNew->pNext = pBNode;
   pNew->pPrev = pBNode->pPrev;
   
   if (pBNode->pPrev)
   {
      pBNode->pPrev->pNext = pNew;
   }

   pBNode->pPrev = pNew;

   return pNew;
}

/************************************************
 * find
 * Helps the user find things within the node
 ***********************************************/
template <class T>
BNode<T> * find(BNode<T> * pHead, const T &t)
{
   // iterate through list and compare value to data
   for (BNode<T> * p = pHead; p; p = p->pNext)
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
BNode<T> * remove(BNode<T> * pBNode)
{	
   if (pBNode == NULL)
   {
   	std::cout << "The list is empty";
   }
   
   BNode <T> * pReturn;

   // Fix the pNext pointer from previos node
   if (pBNode->pPrev)
   {
      pBNode->pPrev->pNext = pBNode->pNext;
   }
   
   //fix the pPrev pointer from next node
   if (pBNode->pNext)
   {
   	pBNode->pNext->pPrev = pBNode->pPrev;
   }

   //returns previous, next or null;
   pReturn = pBNode->pPrev ? pBNode->pPrev : pBNode->pNext;
   
   delete pBNode;
   //returns who take its place
   return pReturn;
}

/************************************************
 * << Operator
 * Stream insertion operator
 ***********************************************/
template <class T>
std::ostream & operator<<(std::ostream & out, const BNode<T> * pHead)
{
   // operator overload to display the list
   for (const BNode<T> * p = pHead; p; p = p->pNext)
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

#endif // BNODE_H

