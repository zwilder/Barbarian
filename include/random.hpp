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
#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cstdint>

#include "dllist.hpp"

namespace wsl
{

class RNGState
{
    public:
        RNGState(uint32_t a = 123456789, uint32_t b = 362436069, uint32_t c = 521288629, uint32_t d = 88675123) : x(a), y(b), z(c), w(d) { }
        uint32_t x;
        uint32_t y;
        uint32_t z;
        uint32_t w;
        template <class Archive>
        void serialize(Archive & ar)
        {
            ar(x,y,z,w);
        }
};
/*
template <typename T>
class WeightedList
{
    public:
        WeightedList() { }
        WeightedList(const WeightedList<T> & other) // Copy constructor 
        {
            list_ = other.list_; 
        }
        WeightedList<T> operator =(WeightedList<T> other) // Copy assignment  
        {
            swap(*this, other);
            return *this;
        }
        friend void swap(WeightedList<T> & first, WeightedList<T> & other)
        {
            // using std::swap;
            // swap(first.list_, other.list_);
            DLNode<T> * temp = first.list_.head();
            first.list_.head() = other.list_.head();
            other.list_.head() = temp;
        }
        void add(T obj, int wt);
        void clear() { list_.clear(); }
        int size() { return list_.size(); }
        T pick(RNGState * rng);

    private:
        DLList<T> list_;
};

template <typename T>
void WeightedList<T>::add(T obj, int wt)
{
    if(wt <=0)
    {
        return;
    }
    for(int i = 0; i < wt; ++i)
    {
        list_.push(obj);
    }
}

template <typename T>
T WeightedList<T>::pick(RNGState * rng)
{
    if(list_.isEmpty()) return T();
    int index = randomInt(0, list_.size() - 1, rng);
    return list_.at(index)->data;
}
*/

uint32_t xor128(RNGState * rng);
int randomInt(int min, int max, RNGState * rng);
int randomInt(int max, RNGState * rng);
bool randomBool(RNGState * rng);

} // namespace wsl

#endif // RANDOM_HPP
