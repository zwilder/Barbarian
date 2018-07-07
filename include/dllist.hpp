#pragma once
#ifndef DLLIST_HPP
#define DLLIST_HPP

/*
 * A lot of this is adapted from https://www.geeksforgeeks.org/data-structures/linked-list/#doublyLinkedList
 * I made it a fancy template class, since there is a lot of different things I could use this structure for - such as
 * a time management system or pathfinding. 
 */
namespace wsl
{

template <typename T>
class DLNode
{
    public:
        DLNode(T a) : data(a) { next = NULL; prev = NULL; }
        T data;
        DLNode<T> * next;
        DLNode<T> * prev;
};

template <typename T>
class DLList
{
    public:
        DLList(T data);
        ~DLList();

        DLNode<T> * head() { return head_; };

        void reverse();
        void push(T data);
        void insertAfter(DLNode<T> * prevNode, T data);
        void insertBefore(DLNode<T> * nextNode, T data) { insertAfter(nextNode->prev, data); }
        void append(T data);
        void remove(T data);
        void remove(DLNode<T> * node);
        T popFront();
        T popBack();

        DLNode<T> * tail();
        void print();
        
    private:
        DLNode<T> * head_;
        
};

template <typename T>
DLList<T>::DLList(T data)
{
    DLNode<T> * newNode = new DLNode<T>(data);
    head_ = newNode;
}

template <typename T>
DLList<T>::~DLList()
{
    DLNode<T> * current = head_;
    DLNode<T> * next;

    while(current != NULL)
    {
        next = current->next;
        delete(current);
        current = next;
    }
}

template <typename T>
void DLList<T>::reverse()
{
    DLNode<T> * temp = NULL;
    DLNode<T> * current = head_;

    while(current != NULL)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if(temp != NULL)
    {
        head_ = temp->prev;
    }
}

template <typename T>
void DLList<T>::push(T data)
{
    DLNode<T> * newNode = new DLNode<T>(data);
    newNode->next = head_;
    head_->prev = newNode;
    head_ = newNode;
}

template <typename T>
void DLList<T>::insertAfter(DLNode<T> * prevNode, T data)
{
    if(prevNode == NULL)
    {
        return;
    }

    DLNode<T> * newNode = new DLNode<T>(data);
    newNode->next = prevNode->next;
    prevNode->next = newNode;
    newNode->prev = prevNode;

    if(newNode->next != NULL)
    {
        newNode->next->prev = newNode;
    }
}

template <typename T>
void DLList<T>::append(T data)
{
    DLNode<T> * newNode = new DLNode<T>(data);
    if(head_ == NULL)
    {
        head_ = newNode;
    }
    DLNode<T> * last = head_;

    while(last->next != NULL)
    {
        last = last->next;
    }

    last->next = newNode;
    newNode->prev = last;
}

template <typename T>
void DLList<T>::remove(DLNode<T> * node)
{
    if(head_ == NULL || node == NULL)
    {
        return;
    }
    
    if(head_ == node)
    {
        head_ = node->next;
    }

    if(node->next != NULL)
    {
        node->next->prev = node->prev;
    }

    if(node->prev != NULL)
    {
        node->prev->next = node->next;
    }

    delete(node);
}

template <typename T>
T DLList<T>::popFront()
{
    T result = head_->data;
    remove(head_);
    return result;
}

template <typename T>
T DLList<T>::popBack()
{
    T result = tail()->data;
    remove(tail());
    return result;
}

template <typename T>
DLNode<T> * DLList<T>::tail()
{
    DLNode<T> * tail = head_;
    while(tail->next != NULL)
    {
        tail = tail->next;
    }
    return tail;
}

template <typename T>
void DLList<T>::print()
{
    DLNode<T> * sentinal = head_;
    std::cout << "\t";
    while(sentinal != NULL)
    {
        std::cout << sentinal->data << "->";
        sentinal = sentinal->next;
    }
    std::cout << "\\\n";
}

}// namespace wsl

#endif //DLLIST_HPP
