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

/*
 * Cereal serialization of fancy wsl types (DLList, PQList, Vector)
 */

#pragma once
#ifndef WSL_CEREAL_HPP
#define WSL_CEREAL_HPP

#include "rect.hpp"
#include "vector.hpp"
#include "dllist.hpp"
#include "pqlist.hpp"

namespace wsl
{

template<typename T>
class CerealDLList
{
    public:
        
        void convert(DLList<T> * list);
        DLList<T> extract();

        std::vector<T> data;

        template<class Archive>
        void serialize(Archive & ar)
        {
            ar(data);
        }

};

template<typename T>
void CerealDLList<T>::convert(DLList<T> * list)
{
    for(DLNode<T> * node = list->head(); node != NULL; node = node->next)
    {
        T listData = node->data;
        data.push_back(listData);
    }
}

template<typename T>
DLList<T> CerealDLList<T>::extract()
{
    DLList<T> result;
    for(size_t i = 0; i < data.size(); ++i)
    {
        result.push(data[i]);
    }

    return result;
}

template<typename T, typename S>
class CerealPQList
{
    public:
        void convert(PQList<T,S> * list);
        PQList<T,S> extract();

        std::vector<T> data;
        std::vector<S> priorities;

        template<class Archive>
        void serialize(Archive & ar)
        {
            ar(data);
            ar(priorities);
        }
};

template<typename T, typename S>
void CerealPQList<T,S>::convert(PQList<T,S> * list)
{
    for(PQNode<T,S> * node = list->head(); node != NULL; node = node->next)
    {
        data.push_back(node->data);
        priorities.push_back(node->priority);
    }
}

template<typename T, typename S>
PQList<T,S> CerealPQList<T,S>::extract()
{
    PQList<T,S> result;
    for(size_t i = 0; i < data.size(); ++i)
    {
        result.push(data[i], priorities[i]);
    }
    return result;
}

template <class Archive, typename T>
void serialize(Archive & ar, Vector2<T> & vec)
{
    ar(vec.x, vec.y);
}

template <class Archive, typename T>
void serialize(Archive & ar, Rectangle<T> & rect)
{
    ar(rect.x1, rect.y1, rect.x2, rect.y2, rect.w, rect.h);
}

} //namespace wsl

#endif //WSL_CEREAL_HPP
