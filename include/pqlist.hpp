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
#ifndef PQLIST_HPP
#define PQLIST_HPP

namespace wsl
{

template<typename T, typename S>
class PQNode
{
    public:
        PQNode(T a, S p) : data(a), priority(p) { next = NULL; }

        T data;
        S priority;
        PQNode<T,S> * next;
};

template<typename T, typename S>
class PQList
{
    public:
        PQList();
        PQList(T data, S priority = S());
        PQList(const PQList<T,S> & other); // Copy constructor 
        PQList<T,S> operator =(PQList<T,S> other) // Copy assignment  
        {
            swap(*this, other);
            return *this;
        }
        friend void swap(PQList<T,S> & first, PQList<T,S> & other)
        {
            PQNode<T,S> * temp = first.head_;
            first.head_ = other.head_;
            other.head_ = temp;
        }

        ~PQList();
        
        PQNode<T,S> * head() { return head_; }
        PQNode<T,S> * tail() { return tail_; }

        void push(T data, S priority);
        T pop();
        T peek();
        PQNode<T, S> * at(int index);
        // void remove(T data);
        void remove(PQNode<T,S> * node);
        int size();

        bool isEmpty() { return head_ == NULL; }
    private:
        PQNode<T,S> * head_;
        PQNode<T,S> * tail_;
};

template<typename T, typename S>
PQList<T,S>::PQList()
{
    head_ = NULL;
    tail_ = NULL;
}

template<typename T, typename S>
PQList<T,S>::PQList(T data, S priority)
{
    head_ = NULL;
    tail_ = NULL;
    push(data, priority);
}

template<typename T, typename S>
PQList<T,S>::PQList(const PQList<T,S> & other)
{
    for(PQNode<T,S> * node = other.head_; node != NULL; node = node->next)
    {
        push(node->data, node->priority);
    }
}

template<typename T, typename S>
PQList<T,S>::~PQList()
{
    PQNode<T,S> * current = head_;
    PQNode<T,S> * next;

    while(current != NULL)
    {
        next = current->next;
        delete(current);
        current = next;
    }
}

template<typename T, typename S>
void PQList<T,S>::push(T data, S priority)
{
    PQNode<T,S> * newNode = new PQNode<T,S>(data, priority);
    if(head_ == NULL)
    {
        head_ = newNode;
        tail_ = newNode;
    }
    else if(head_->priority > newNode->priority)
    {
        newNode->next = head_;
        head_ = newNode;
    }
    else
    {
       PQNode<T,S> * temp = head_;
       while((temp->next != NULL) && (temp->next->priority < priority))
       {
           temp = temp->next;
       }
       newNode->next = temp->next;
       temp->next = newNode;
    }
}

template<typename T, typename S>
T PQList<T,S>::peek()
{
    T result;
    if(head_ == NULL)
    {
        result = T();
    }
    else
    {
        result = (head_->data);
    }
    return result;
}

template<typename T, typename S>
T PQList<T,S>::pop()
{
    if(head_ == NULL)
    {
        return T();
    }
    T result = head_->data;
    PQNode<T,S> * temp = head_;
    head_ = head_->next;
    delete(temp);
    return result;
}

template <typename T, typename S>
PQNode<T,S> * PQList<T,S>::at(int index)
{
    PQNode<T,S> * resultNode = head_;
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
    return resultNode;
}

template <typename T, typename S>
void PQList<T,S>::remove(PQNode<T,S> * node)
{
    if(head_ == NULL || node == NULL)
    {
        return;
    }
    
    PQNode<T,S> * prevNode = head_;
    for(PQNode<T,S> * temp = head_; temp != NULL; temp = temp->next)
    {
        if(temp == node) break;
        prevNode = temp;
    }

    if(head_ == node)
    {
        head_ = node->next;
    }

    if(prevNode != NULL)
    {
        prevNode->next = node->next;
    }

    // if(node->next != NULL)
    // {
    //     node->next->prev = node->prev;
    // }
    //
    // if(node->prev != NULL)
    // {
    //     node->prev->next = node->next;
    // }

    delete(node);
}

template <typename T, typename S>
int PQList<T,S>::size()
{
    PQNode<T,S> * sentinal = head_;
    int result = 0;
    while(sentinal != NULL)
    {
        ++result;
        sentinal = sentinal->next;
    }
    return result;
}
} //namespace wsl

#endif //PQLIST_HPP
