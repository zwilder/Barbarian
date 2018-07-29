/*
* Barbarian!
* Copyright (C) Zach Wilder 2018
* 
* This file is a part of Barbarian!
*
* Barbarian! is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Barbarian! is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Barbarian!.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef DLLIST_HPP
#define DLLIST_HPP

#include <iostream>
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
        DLList();
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
        bool contains(T data);
        void clear();

        T popFront();
        T popBack();
        DLNode<T> * at(int index);
        int size();

        bool isEmpty() { return (head_ == NULL); }

        DLNode<T> * tail();
        void print();

    private:
        DLNode<T> * head_;
        
};

template <typename T>
DLList<T>::DLList()
{
    head_ = NULL;
}

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
    if(head_ != NULL)
    {
        newNode->next = head_;
        head_->prev = newNode;
    }
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
bool DLList<T>::contains(T data)
{
    bool success = false;

    DLNode<T> * last = head_;

    while(last->next != NULL)
    {
        if(last->data == data)
        {
            success = true;
            break;
        }
        last = last->next;
    }
    return success;
}

template <typename T>
void DLList<T>::clear()
{
    while(!isEmpty())
    {
        popFront();
    }
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
DLNode<T> * DLList<T>::at(int index)
{
    DLNode<T> * resultNode = head_;
    int count = 0;
    while(resultNode != NULL)
    {
        if(count == index)
        {
            break;
        }
        ++count;
        resultNode = resultNode->next;
    }
    
    // std::cout << "Looking for node in DLList out of bounds!\n";
    // assert(0);
    return resultNode;
}

template <typename T>
DLNode<T> * DLList<T>::tail()
{
    if(head_ == NULL)
    {
        return NULL;
    }

    DLNode<T> * tail = head_;
    while(tail->next != NULL)
    {
        tail = tail->next;
    }
    return tail;
}

template <typename T>
int DLList<T>::size()
{
    DLNode<T> * sentinal = head_;
    int result = 0;
    while(sentinal != NULL)
    {
        ++result;
        sentinal = sentinal->next;
    }
    return result;
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
