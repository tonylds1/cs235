/***********************************************************************
 * Component:
 *    Assignment 09, Binary Search Tree (BST)
 *    Brother <your instructor name here>, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    Create a binary search tree
 ************************************************************************/

#ifndef BST_H
#define BST_H

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
class BST
{
   public:
      class iterator;
      class const_iterator;
      
      // iterators
      iterator begin();
      iterator end() { return iterator (NULL); }
      iterator rbegin();
      iterator rend() { return iterator (NULL); }

      BST(): root(NULL), numElements(0) {};
      BST(const BST <T> & rhs) throw (const char *);
      
      bool  empty() { return numElements == 0; }
      int   size()  { return numElements; };
      void  clear();
      
      void  insert(const T & t) throw (const char *);
      iterator find(const T & t);
      
      
      class BNode;
      BNode * getRoot() { return root; };
      
      BST <T> & operator = (const BST <T> & rhs) throw (const char *);
      friend std::ostream & operator << (std::ostream & out, BNode & rhs)
      {
         out << rhs.data;
         
         return out;
      }
      
      void erase(iterator & it);
   private:
      
      BNode * root;
      int numElements;     // size
      
      BNode * copyBinaryTree(const BNode * src)
      {
         if (src == NULL)
            return NULL;

         BNode * dest = new BNode(src->data);
         dest->isRed = src->isRed;
         
         dest->pLeft = copyBinaryTree(src->pLeft);
         if (dest->pLeft != NULL)
            dest->pLeft->pParent = dest;
         
         dest->pRight = copyBinaryTree(src->pRight);
         if (dest->pRight != NULL)
            dest->pRight->pParent = dest;

         return dest;
      }
      
      void deleteBinaryTree(BNode * node);
};

/*******************************************
 * BST :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
BST <T> :: BST (const BST <T> & rhs) throw (const char *)
{
   this->root = this->copyBinaryTree(rhs.root); 
   this->numElements = rhs.numElements;
}

template <class T>
void BST <T> :: erase(BST <T> :: iterator & it)
{
   BNode * p = &*it;
   
   if (p->pLeft == NULL && p->pRight == NULL)
   {
      if (p->pParent != NULL && p->pParent->pRight == p) 
         p->pParent->pRight = NULL;
         
      if (p->pParent != NULL && p->pParent->pLeft == p) 
         p->pParent->pLeft = NULL;
         
      delete p;
      return;
   }
   
   if (p->pLeft == NULL && p->pRight != NULL)
   {
      p->pRight->pParent = p->pParent;
      if (p->pParent != NULL && p->pParent->pRight == p) 
         p->pParent->pRight = p->pRight;
         
      if (p->pParent != NULL && p->pParent->pLeft == p) 
         p->pParent->pLeft = p->pRight; 
         
      delete p;
      return;
   }
   
   if (p->pLeft != NULL && p->pRight == NULL)
   {
      p->pRight->pParent = p->pParent;
      if (p->pParent != NULL && p->pParent->pRight == p) 
         p->pParent->pRight = p->pLeft;
         
      if (p->pParent != NULL && p->pParent->pLeft == p) 
         p->pParent->pLeft = p->pLeft; 
         
      delete p;
      return;
   }  
   
   it++;
   BNode * pSuccessor = &*it;
   p->data = pSuccessor->data;
   
   erase(it);
}

/*******************************************
 * BST :: ASSIGN OPERATOR
 *******************************************/
template <class T>
BST <T> & BST <T> :: operator = (const BST <T> & rhs) throw (const char *)
{
   this->root = this->copyBinaryTree(rhs.root);   
   this->numElements = rhs.numElements;
   
   return *this;
}

/*******************************************
 * BST :: COPY BTREE (PRIVATE)
 *******************************************/
template <class T>
void BST <T> :: deleteBinaryTree(BNode * pNode)
{
   if (!pNode)
   {
      return;
   }
   
   deleteBinaryTree(pNode->pLeft);
   deleteBinaryTree(pNode->pRight);

   delete pNode;
   pNode = NULL; 
}

/*******************************************
 * BST :: INSERT
 *******************************************/
template <class T>
void BST <T> :: insert(const T & t) throw (const char *)
{
   //case1 - No Parent
   if (numElements == 0) {
      BNode * newNode = new BNode(t);
      root = newNode;
      root->isRed = false;
      numElements++;
      
      return;
   }
   
   BNode newNode = root->add(t);
   numElements++;
}

/*******************************************
 * BST :: CLEAR
 *******************************************/
template <class T>
void BST <T> :: clear()
{
   if (numElements > 0)
   {
      deleteBinaryTree(root);
      root = NULL;
   }
    
   numElements = 0;
}

/*******************************************
 * BST :: begin the left outermost value
 *******************************************/
template <class T>
typename BST <T> :: iterator BST <T> :: begin()
{
   if (root == NULL)
   {
      return NULL;   
   }
   
   BNode * leftmost = root;
   
   while (leftmost->pLeft)
   {
      leftmost = leftmost->pLeft;
   }
   
   return iterator(leftmost);
}

/*******************************************
 * BST :: RBEGIN - the right outmost value
 *******************************************/
template <class T>
typename BST <T> :: iterator BST <T> :: rbegin()
{
   BNode * rightmost = this->getRoot();
   
   while (rightmost->pRight)
   {
      rightmost = rightmost->pRight;
   }
   
   return iterator(rightmost);
}

/*******************************************
 * BST :: FIND
 *******************************************/
template <class T>
typename BST <T> :: iterator BST <T> :: find(const T & t)
{
   iterator it = iterator(this->root);
   
   while ((*it).data > t)
   {
      it--;
   }
   
   while ((*it).data < t)
   {
      it++;
   }
      
   if ((*it).data == t) 
      return it;
      
   return iterator();
}

/*******************************************
 * BST :: BNODE SECTION
 * From here until next section we will have 
 * BNode class implementations. 
 *******************************************/
template <class T>
class BST <T> :: BNode
{
public:
   T data;
   BNode * pParent;
   BNode * pLeft;
   BNode * pRight;
   bool isRed;
   
   //Default Constructor
   BNode() : data(NULL), pParent(NULL), pLeft(NULL), pRight(NULL), isRed(true) {}
   
   //Non Default Constructor
   BNode(const T & t) : data(t), pParent(NULL), pLeft(NULL), pRight(NULL), isRed(true) {}

   BNode & add(const T & t)  throw (const char *);
   
   // equals, not equals operator
   bool operator != (const BNode & rhs) const { return rhs.data != this->data; }
   bool operator == (const BNode & rhs) const { return rhs.data == this->data; }
   
private:
   bool verifyRB(int depth);
   bool verifyBST();
   void balance();
};

/*******************************************
 * BST :: ADD
 *******************************************/
template <class T>
typename BST <T> :: BNode & BST <T> :: BNode :: add(const T & t)   throw (const char *)
{
   if (data == t) 
   {
      return *this;
   }
   
   if (data > t && pLeft != NULL)
   {
      return pLeft->add(t);
   }
   
   
   if (data < t && pRight != NULL)
   {
      return pRight->add(t);
   }
   
   BNode * newNode = new BNode(t);
   if (data > t)
   {
      this->pLeft = newNode;
      this->pLeft->pParent = this;
   } 
   else
   {
      this->pRight = newNode;
      this->pRight->pParent = this;
   }
   
   return * newNode;
}

/*******************************************
 * BST :: verifyRB - (Same Number of Black Nodes)
 * Recursive, useful for verifying property 
 * "d" of a red-black tree.
 *******************************************/
template <class T>
bool BST <T> :: BNode :: verifyRB(int depth)
{
   return true;
}

/*******************************************
 * BST :: verifyBST - 
 * Ensures that the subtree under a given node 
 * is a valid BST .
 *******************************************/
template <class T>
bool BST <T> :: BNode :: verifyBST()
{
   return true;
}

/*******************************************
 * BST :: ITERATOR SECTION
 * From here until next section we will have 
 * Iterator class implementations. 
 *******************************************/
template <class T>
class BST <T> :: iterator
{
   public:
      // constructors, destructors, and assignment operator
      iterator()      : p(NULL)      {              }
      iterator(BNode * p) : p(p)         {              }
      iterator(const iterator & rhs) { p = rhs.p; }
      iterator & operator = (const iterator & rhs)
      {
         p = rhs.p;
         return *this;
      }
      
      // equals, not equals operator
      bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
      bool operator == (const iterator & rhs) const { return rhs.p == this->p; }
      
      // dereference operator
            BNode & operator * ()       { return *p; }
      const BNode & operator * () const { return *p; }
      
      // prefix decrement
      // iterators
      iterator & operator ++ ();
      iterator operator ++ (int postfix)
      {
         iterator itReturn = *this;
         ++(*this);
         
         return itReturn;
      }
      
      iterator & operator -- ();
      iterator operator -- (int postfix)
      {
         iterator itReturn = *this;
         --(*this);
         
         return itReturn;
      }
      
   private:
      BNode * p;
};

template <class T>
class BST <T> :: const_iterator
{
   
};

/**************************************************
 * BST ITERATOR :: INCREMENT PREFIX
 *************************************************/
template <class T>
typename BST <T> :: iterator & BST <T> :: iterator :: operator ++ ()
{
   // do nothing if we have nothing
   if (NULL == p)
   {
      return *this;
   }

   // if there is a right node, take it
   if (NULL != p->pRight)
   {
      // go right
      p = p->pRight;

      // jig left - there might be more left-most children
      while (p->pLeft)
      {
         p = p->pLeft;
      }
      
      return *this;
   }

   // there are no right children, the left are done
   assert(NULL == p->pRight);
   BNode * pSave = p;

   // go up
   p = p->pParent;

   // if we are the right-child, got to the parent.
   if (pSave == p->pRight)
   {
      while (NULL != p && pSave > p)
      {
         p = p->pParent;
      }
      
      return *this;
   }

   return *this;
}

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 *************************************************/
template <class T>
typename BST <T> :: iterator & BST <T> :: iterator :: operator -- ()
{
   // do nothing if we have nothing
   if (NULL == p)
      return *this;

   // if there is a left node, take it
   if (NULL != p->pLeft)
   {
      // go left
      p = p->pLeft;

      // jig right - there might be more right-most children
      while (p->pRight)
         p = p->pRight;
      return *this;
   }

   // there are no left children, the right are done
   assert(NULL == p->pLeft);
   BNode * pSave = p;

   // go up
   p = p->pParent;

   // if the parent is the NULL, we are done!
   if (NULL == p)
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == p->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (NULL != p && pSave == p->pLeft)
   {
      pSave = p;
      p = p->pParent;
   }

   return *this;
}

} // namespace custom

#endif // BST_H
