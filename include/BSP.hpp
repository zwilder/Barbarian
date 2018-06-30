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

#include <vector>
#include <memory>

#include "rect.hpp"
#include "random.hpp"
#include "vector.hpp"
#include "tile.hpp"

namespace bsp
{
class Node
{
    public:
        Node(wsl::Rect rect = wsl::Rect(0,0,0,0), Node * parent = NULL);

        static const int MIN_NODE_SIZE = 11;
               
        bool hasSplit() { return split_; }
        bool split();
        bool horizontal() { return horizontal_; }
        Node * parent() { return parent_; }
        Node * leftChild() { return leftChild_.get(); }
        Node * rightChild() { return rightChild_.get(); }
        Node * sibling() { return sibling_; } // Binary tree - there's only one sibling

        wsl::Rect nodeRect;
        bool connected;
        wsl::Vector2i splitPos;

        int width() { return nodeRect.w; }
        int height() { return nodeRect.h; }

        std::vector<wsl::Rect> rooms;
        
    private:
        Node * parent_;
        Node * sibling_;
        std::unique_ptr<Node> leftChild_;
        std::unique_ptr<Node> rightChild_;
        bool split_;
        bool horizontal_;
};

class Tree
{
    public:
        Tree(wsl::Rect rect);

        std::vector<Node *> leaves() { return leaves_; }
        std::vector<Node *> nodes() { return nodes_; }
        
        void populate(wsl::Rect nodeRect);
        bool isLeaf(Node * node);
        int width() { return root_.width(); }
        int height() { return root_.height(); }
        Node * root() { return &root_; }
    private:
        Node root_; // The root node
        std::vector<Node *> leaves_; // The leaves of the tree
        std::vector<Node *> nodes_; // ALL nodes of a tree
};

class Dungeon
{
    public:
        Dungeon(Tree * tree, int minRoomSize = 5, bool fullRooms = true);

        int width() { return tree_->width(); }
        int height() { return tree_->height(); }

        int index(int x, int y) { return (x + (y * width())); }           
        std::vector<Tile> dungeonMap;
        std::vector<wsl::Rect> rooms;

    private:
        void build_();
        void traverseNode_(Node * node);
        void vline_(int x, int y1, int y2); // Vertical line from (x,y1) to (x,y2)
        void vlineUp_(int x, int y); // Vertical line from (x,y) to (x,0)
        void vlineDown_(int x, int y); //Vertical line from (x,y) to (x, height - 1)
        void hline_(int x1, int y, int x2); // Horizontal line from (x1, y) to (x2, y)
        void hlineLeft_(int x, int y); // Horizontal line from (x,y) to (0,y)
        void hlineRight_(int x, int y); // Horizontal line from (x,y) to (width - 1)

        Tree * tree_;
        bool fullRooms_;
        int minRoomSize_;
};

} //namespace bsp
#endif //BSP_HPP
