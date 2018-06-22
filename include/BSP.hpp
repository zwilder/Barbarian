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
#ifndef BSP_HPP
#define BSP_HPP

#include<vector>
#include "rect.hpp"
#include "random.hpp"
#include "vector.hpp"

class Node
{
    public:
        Node(wsl::Rect rect = wsl::Rect(0,0,0,0), Node * parent = NULL);
        ~Node();
               
        bool hasSplit() { return split_; }
        bool split();
        bool horizontal() { return horizontal_; }
        bool connected() { return connected_; }
        Node * parent() { return parent_; }
        Node * leftChild() { return leftChild_; }
        Node * rightChild() { return rightChild_; }
        Node * sibling() { return sibling_; } // Binary tree - there's only one sibling

        wsl::Rect nodeRect;
        std::vector<wsl::Rect> rooms;
        
    private:
        Node * parent_;
        Node * leftChild_;
        Node * rightChild_;
        Node * sibling_;
        bool split_;
        wsl::Vector2i splitPos_;
        bool horizontal_;
        bool connected_;
};

class Tree
{
    public:
        Tree();
        // ~Tree();

        std::vector<wsl::Rect> rooms() { return rooms_; }
        std::vector<wsl::Rect> corridors() { return corridors_; }
        void populate(wsl::Rect nodeRect);

    private:
        std::vector<wsl::Rect> rooms_;
        std::vector<wsl::Rect> corridors_;
        Node root_;
        std::vector<Node *> leaves_;
};

#endif //BSP_HPP
