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
#ifndef WLIST_HPP
#define WLIST_HPP

#include "random.hpp"

namespace wsl
{
template <typename T>
class WNode
{
    public:
        WNode(T a, int wt = 1) : data(a), weight(wt) { next = NULL; }
        T data;
        int weight; 
        WNode<T> * next;
};

template <typename T>
class WList
{
    public:
        WList();
        WList(T data, int wt);
        WList(const WList<T> & other); // Copy constructor 
        ~WList();
        WList<T> operator =(WList<T> other) // Copy assignment  
        {
            swap(*this, other);
            return *this;
        }
        friend void swap(WList<T> & first, WList<T> & other)
        {
            WNode<T> * temp = first.head_;
            first.head_ = other.head_;
            other.head_ = temp;
        }
        void push(T data, int wt);
        void clear();
        WNode<T> * at(int index);
        T pop();
        T pick(RNGState * rng);

        bool isEmpty() { return (head_ == NULL); }
        WNode<T> * head() { return head_; };

    private:
        WNode<T> * head_;

};

template <typename T>
WList<T>::WList()
{
    head_ = NULL;
}

template <typename T>
WList<T>::WList(T data, int wt)
{
    push(data, wt);
}

template <typename T>
WList<T>::WList(const WList<T> & other) // Copy constructor
{
    for(WNode<T> * node = other.head_; node != NULL; node = node->next)
    {
        push(node->data, node->weight);
    }

}

template <typename T>
WList<T>::~WList()
{
    WNode<T> * current = head_;
    WNode<T> * next;

    while(current != NULL)
    {
        next = current->next;
        delete(current);
        current = next;
    }
}

template <typename T>
void WList<T>::push(T data, int wt)
{
    if(wt <= 0)
    {
        return;
    }
    WNode<T> * newNode = new WNode<T>(data);
    if(head_ != NULL)
    {
        newNode->next = head_;
    }
    head_ = newNode;
}

template <typename T>
void WList<T>::clear()
{
    while(!isEmpty())
    {
        pop();
    }
}

template <typename T>
WNode<T> * WList<T>::at(int index)
{
    WNode<T> * resultNode = head_;
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

template <typename T>
T WList<T>::pick(RNGState * rng)
{
    T result = T();
    int totalWt = 0;
    for(WNode<T> * node = head_; node != NULL; node = node->next)
    {
        totalWt += node->weight;
    }

    int choiceWt = randomInt(0, totalWt, rng);
    int runningWt = 0;

    for(WNode<T> * node = head_; node != NULL; node = node->next)
    {
        if(runningWt + node->weight >= choiceWt)
        {
            result = node->data;
            break;
        }
        runningWt += node->weight;
    }
    return result;
}

template <typename T>
T WList<T>::pop()
{
    if(head_ == NULL)
    {
        return T();
    }
    T result = head_->data;
    WNode<T> * temp = head_;
    head_ = head_->next;
    delete(temp);
    return result;
}

} // namespace wsl

#endif //WLIST_HPP
