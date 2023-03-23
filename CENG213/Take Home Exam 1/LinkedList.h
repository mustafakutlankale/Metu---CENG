#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    int size;
};

template <class T>
LinkedList<T>::LinkedList()
{
    /* TODO */
    head = NULL;
    size = 0;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj)
{
    /* TODO */
    this->head = NULL;
    this->size = 0;
    Node<T> *curr = obj.head;

    while (curr->next != obj.head)
    {
        T value = curr->data;
        this->append(value);
        curr = curr->next;
    }
    T value = curr->data;
    this->append(value);
}

template <class T>
LinkedList<T>::~LinkedList()
{
    /* TODO */
    removeAllNodes();
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    /* TODO */
    if (this != &rhs)
    {
        this->removeAllNodes();

        Node<T> *curr = rhs.head;
        while (curr->next != rhs.head)
        {
            T value = curr->data;
            this->append(value);
            curr = curr->next;
        }
        T value = curr->data;
        this->append(value);
        this->size = rhs.size;
    }
    return *this;
}

template <class T>
int LinkedList<T>::getSize() const
{
    /* TODO */
    return size;
}

template <class T>
bool LinkedList<T>::isEmpty() const
{
    /* TODO */
    return head == NULL;
}

template <class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    /* TODO */
    if (head == NULL)
    {
        return false;
    }
    Node<T> *curr = head;
    while (curr->next != head)
    {
        if (curr == node)
        {
            return true;
        }
        curr = curr->next;
    }
    if (curr == node)
    {
        return true;
    }
    return false;
}

template <class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    /* TODO */
    return head;
}

template <class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    /* TODO */
    if (head == NULL)
    {
        return NULL;
    }
    Node<T> *curr = head;
    while (curr->next != head)
    {
        curr = curr->next;
    }
    return curr;
}

template <class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    /* TODO */
    if (head == NULL)
    {
        return NULL;
    }
    Node<T> *curr = head;
    while (curr->next != head)
    {
        if (curr->data == data)
        {
            return curr;
        }
        curr = curr->next;
    }
    if (curr->data == data)
    {
        return curr;
    }
    return NULL;
}

template <class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    /* TODO */
    if (head == NULL)
    {
        return NULL;
    }

    Node<T> *curr = head;
    int l_size = this->getSize();

    if (l_size <= index || index < 0)
    {
        return NULL;
    }

    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    return curr;
}

template <class T>
void LinkedList<T>::append(const T &data)
{
    /* TODO */
    Node<T> *new_node = new Node<T>(data);
    if (head == NULL)
    {
        head = new_node;
        new_node->next = head;
        new_node->prev = head;
    }
    else
    {
        Node<T> *temp = head;
        while (temp->next != head)
        {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->prev = temp;
        new_node->next = head;
        head->prev = new_node;
    }
    size++;
}

template <class T>
void LinkedList<T>::prepend(const T &data)
{
    /* TODO */
    Node<T> *new_node = new Node<T>(data);

    if (head == NULL)
    {
        head = new_node;
        new_node->next = head;
        new_node->prev = head;
    }
    else
    {
        new_node->next = head;
        head->prev = new_node;
        // Now new_node previous should point to
        // last elemet of our list
        Node<T> *temp = head;
        while (temp->next != head)
        {
            temp = temp->next;
        }
        new_node->prev = temp;
        temp->next = new_node;
        head = new_node;
    }
    size++;
}

template <class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    /* TODO */
    bool is_contain = this->containsNode(node);
    if (!is_contain)
    {
        return;
    }

    Node<T> *new_node = new Node<T>(data);
    Node<T> *curr = head;
    while (curr->next != head)
    {
        if (curr == node)
        {
            break;
        }
        curr = curr->next;
    }
    new_node->prev = curr;
    new_node->next = curr->next;
    curr->next->prev = new_node;
    curr->next = new_node;
    size++;
}

template <class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    /* TODO */
    if (size < index || index < 0)
    {
        return;
    }

    Node<T> *new_node = new Node<T>(data);
    Node<T> *curr = head;

    if (index == 0)
    {
        if (size == 0)
        {
            append(data);
            return;
        }
        new_node->next = curr;
        new_node->prev = curr->prev;
        curr->prev->next = new_node;
        curr->prev = new_node;
        head = new_node;
    }

    else
    {
        for (int i = 0; i < index; i++)
        {
            curr = curr->next;
        }
        new_node->next = curr;
        new_node->prev = curr->prev;
        curr->prev->next = new_node;
        curr->prev = new_node;
    }
    size++;
}

template <class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    /* TODO */
    int index = 0;
    Node<T> *curr = head;
    while (index < size)
    {
        if (curr == node)
        {
            return index;
        }
        index++;
        curr = curr->next;
    }
    index = -1;
    return index;
}

template <class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    /* TODO */
    if (this->isEmpty())
    {
        return;
    }
    if (currentIndex < 0)
    {
        return;
    }
    if (currentIndex > size)
    {
        return;
    }
    if (newIndex < 0)
    {
        return;
    }
    if (currentIndex == this->getSize() - 1 && newIndex >= size - 1)
    {
        return;
    }
    if (currentIndex == newIndex)
    {
        return;
    }
    if (newIndex >= this->getSize())
    {
        newIndex = this->getSize() - 1;
    }

    Node<T>* curr = head;

    for (int i = 0; i < currentIndex; i++)
    {
        curr = curr->next;
    }
    Node<T>* left = curr->prev;
    Node<T>* middle = left->next;
    Node<T>* right = middle->next;
    if (currentIndex < newIndex)
    {
        for (int i = currentIndex; i < newIndex; i++)
        {
            right = middle->next;
            left =  middle->prev;
            left->next = right;
            right->prev = left;
            middle->prev = right;
            middle->next = right->next;
            right->next->prev = middle;
            right->next = middle;
            if (i == 0)
            {
                head = right;
            }
        }
    }
    else if (currentIndex > newIndex)
    {
        for (int i = newIndex; i < currentIndex; i++)
        {
            right = middle->next;
            left = middle->prev;
            left->next = right;
            right->prev = left;
            middle->next = left;
            middle->prev = left->prev;
            left->prev->next = middle;
            left->prev = middle;
            if (i == 0)
            {
                head = middle;
            }     
        }
        
    }
    
    return;

    // Deletion
    // oldNode->prev->next = oldNode->next;
    // oldNode->next->prev = oldNode->prev;
    /*for (int i = 0; i < currentIndex; i++)
    {
        curr = curr->next;
    }
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;*/

    // Insertion
    // newNode->prev = current;
    // newNode->next = current->next;
    // newNode->prev->next = newNode;
    // newNode->next->prev = newNode
    /*Node<T>* target = head;
    for (int i = 0; i < newIndex - 1; i++)
    {
        target = target->next;
    }
    curr->prev = target;
    curr->next = target->next;
    curr->prev->next = curr;
    curr->next->prev = curr;*/
    /*Node<T>* target = head;
    for (int i = 0; i < currentIndex; i++)
    {
        curr = curr->next;
    }
    for(int i = 0; i < newIndex; i++)
    {
        target = target->next;
    }
    if (currentIndex == this->getSize() - 1)
    {
        head->prev = curr->prev;
        curr->prev->next = head;
    }
    else if (currentIndex == 0)
    {
        head = head->next;
    }
    else
    {
        Node<T>* left = curr->prev;
        Node<T>* right = curr->next;
        left->next = right;
        right->prev = left;
    }
    if (newIndex == 0)
    {
        curr->next = head;
        curr->prev = head->prev;
        head->prev->next = curr;
        head->prev = curr;
        head = curr;
    }
    else
    {
        target->prev = curr;
        target->prev->next = curr;
        curr->next = target;
        curr->prev = target->prev;
    }*/
    
    /*if (currentIndex == 0)
    {
        if (newIndex >= this->getSize() - 1)
        {
            head = head->next;
            return;
        }
        Node<T>* new_head = curr->next;
        Node<T>* last = head->prev;
        Node<T>* pos = head;
        for (int i = 0; i < newIndex; i++)
        {
            pos = pos->next;
        }
        curr->next = pos->next;
        pos->next->prev = curr;
        pos->next = curr;
        curr->prev = pos;
        new_head->prev = last;
        last->next = new_head;
        head = new_head;
        return;
    }
    
    
    else if (currentIndex == this->getSize() - 1)
    {
        for (int i = 0; i < currentIndex; i++)
        {
            curr = curr->next;
        }
        if (newIndex == 0)
        {
            head = curr;
            return;
        }
        Node<T>* pos = head;
        for (int i = 0; i < newIndex; i++)
        {
            pos = pos->next;
        }
        curr->prev->next = head;
        head->prev = curr->prev;
        curr->next = pos;
        curr->prev = pos->prev;
        pos->prev->next = curr;
        pos->prev = curr;
     }
    else
    {
        for (int i = 0; i < currentIndex; i++)
        {
            curr = curr->next;
        }
        if (newIndex == 0)
        {
            Node<T>* last = head->prev;
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            curr->next = head;
            head->prev = curr;
            curr->prev = last;
            last->next = curr;
            head = curr;
            return;
        }
        else if (newIndex == this->getSize() - 1)
        {
            Node<T>* last = head->prev;
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            last->next = curr;
            curr->prev = last;
            curr->next = head;
            head->prev = curr;
            return;
        }
        else
        {
            Node<T>* last = head->prev;
            Node<T>* pos = head;
            for (int i = 0; i < newIndex; i++)
            {
                pos = pos->next;
            }
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            pos->prev->next = curr;
            curr->next = pos;
            curr->prev = pos->prev;
            pos->prev = curr;
            return;
        }
    }*/
    /*Node<T>* left = curr->prev;
    Node<T>* middle = left->next;
    Node<T>* right = middle->next;
    left->next = right;
    right->prev = left;
    int shift = newIndex > currentIndex ? newIndex - currentIndex : currentIndex - newIndex;
    while (shift)
    {
        if (currentIndex < newIndex)
        {
            right = right->next;
            left = left->next;
        }
        else if (currentIndex > newIndex)
        {
            right = right->prev;
            left = left->prev;
        }
        shift--;
    }
    if (left == middle)
    {
        left = left->next;
    }
    middle->next = right;
    right->prev = middle;
    left->next = middle;
    middle->prev = left;
    
    if (newIndex == 0)
    {
        head = middle;
    }
    if (currentIndex == 0)
    {
        head = left;
    }*/
    // <---------------------------------------------->
    /*Node<T> *from = this->getNodeAtIndex(currentIndex);
    Node<T> *left = from->prev;

    left->next = from->next;
    from->next->prev = left;
    
    
    Node<T>* to = head;

    for (int i = 0; i < newIndex; i++)
    {
        to = to->next;
    }
    from = to->next->prev;
    from->next = to->next;
    from->prev = to;
    to->next = from;


    if (newIndex == 0)
    {
        head = from;
    }

    if (currentIndex == 0)
    {
        head = head->next;
    }*/
}

template <class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    /* TODO */
    bool is_contain = this->containsNode(node);

    if (!is_contain)
    {
        return;
    }

    Node<T> *curr = head;
    if (curr->next == head)
    {
        delete head;
        size--;
        return;
    }
    int index = this->getIndex(node);
    if (index == 0)
    {
        Node<T> *temp = head;
        Node<T> *last = head->prev;
        last->next = head->next;
        head = head->next;
        head->prev = last;
        delete temp;
        size--;
        return;
    }
    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    Node<T> *left = curr->prev;
    Node<T> *middle = left->next;
    Node<T> *right = middle->next;
    left->next = right;
    right->prev = left;
    if (left == head->prev)
    {
        head = right;
    }
    delete middle;
    size--;
    if (size == 0)
    {
        head = NULL;
    }
    return;
}

template <class T>
void LinkedList<T>::removeNode(const T &data)
{
    /* TODO */
    if (head == NULL)
    {
        return;
    }
    Node<T> *curr = head;
    int count = 0;
    int last_index = size;
    while (count < last_index)
    {
        Node<T> *left = curr->prev;
        Node<T> *middle = left->next;
        Node<T> *right = middle->next;
        if (curr->data == data)
        {
            left->next = right;
            right->prev = left;
            if (middle == head)
            {
                head = right;
            }
            delete middle;

            if (size == 1)
            {
                size--;
                head = NULL;
                return;
            }
            size--;
            curr = right;
            count++;
        }
        else
        {
            curr = curr->next;
            count++;
        }
    }
}

template <class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    /* TODO */
    if (head == NULL)
    {
        return;
    }
    if (index < 0)
    {
        return;
    }
    if (index >= size)
    {
        return;
    }
    Node<T> *curr = head;
    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    Node<T> *left = curr->prev;
    Node<T> *middle = left->next;
    Node<T> *right = middle->next;
    left->next = right;
    right->prev = left;
    if (middle == head)
    {
        head = right;
    }
    delete middle;
    size--;
    if (size == 0)
    {
        head = NULL;
    }
}

template <class T>
void LinkedList<T>::removeAllNodes()
{
    /* TODO */
    if (head == NULL)
    {
        return;
    }
    Node<T> *curr = head;
    int count = 0;
    int last_index = size;
    while (count < last_index)
    {
        Node<T> *left = curr->prev;
        Node<T> *middle = left->next;
        Node<T> *right = middle->next;
        left->next = right;
        right->prev = left;
        if (middle == head)
        {
            head = right;
        }
        delete middle;

        if (size == 1)
        {
            size--;
            head = NULL;
            return;
        }
        size--;
        curr = right;
        count++;
    }
}

template <class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty())
    {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    do
    {
        std::cout << *node << std::endl;
        node = node->next;
    } while (node != this->getFirstNode());
}

#endif // LINKEDLIST_H
