/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Maximiliano Correa, Esteban Cabrera and Tony Moraes.
 ************************************************************************/

#ifndef SORTINSERTION_H
#define SORTINSERTION_H
/*******************************************************************************
* SORT INSERTION 
* Sort the elements in the array.
*******************************************************************************/
template <class T>
void sortInsertion(T array[], int num)
{
    if (num == 0) {
        return;
    }
    
    Node <T> * pHead = new Node<T> (array[0]);
    Node <T> * pNew = NULL;
    Node <T> * p = NULL;
    
    // load array values into unsorted list
    for (int i = 1; i < num; i++)
    {
        pNew = NULL;
        for (p = pHead; p; p = p->pNext)
        {
            if (p->data > array[i])
            {
                pNew = insert(p, array[i]);
                
                if (p == pHead)
                {
                    pHead = pNew;
                }
                
                break;
            }
            
            if (!p->pNext)
            {
                break;
            }
        }
        
        // If was not inserted means that it is greater than the others
        if (!pNew)
        {
            insert(p, array[i], true);
        }
    }
    
    p = pHead;
    for (int i = 0; i < num; i++) 
    {
        array[i] = p->data;
        p = p->pNext;
    }

    // clear the lists
    freeData(pHead);
}

/***********************************************
 * insertSort
 * Sort the insertion
 **********************************************/
template <class T>
void insertSort(Node<T> ** list, Node<T> * pNode)
{
    // create current node pointer
    Node<T> * current;

    // comparing node values
    if (*list == NULL || (*list)->data >= pNode->data)
    {
        pNode->pNext = *list;
        *list = pNode;
    }
    else
    {
        current = *list;
        while (current->pNext != NULL && current->pNext->data < pNode->data)
            current = current->pNext;
        
        pNode->pNext = current->pNext;
        current->pNext = pNode;
    }
}
#endif // SORTINSERTION_H

