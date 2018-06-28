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


#include <iostream>
#include "../include/BSP.hpp"

namespace bsp
{

Node::Node(wsl::Rect rect, Node * parent) : nodeRect(rect), parent_(parent)
{
    split_ = false;
    leftChild_ = NULL;
    rightChild_ = NULL;
    sibling_ = NULL;
    connected = false;
}

bool Node::split()
{
    bool success = false;
    if(!hasSplit())
    {
        bool horizontalSplit = wsl::randomBool();
        int width = nodeRect.w;
        int height = nodeRect.h;

        if((width > height) && (100 * (width / height) > 125)) // This funky statement is basically if width/height > 1.25. Trickin those integers.
        {
            horizontalSplit = false;
        }
        else if((height > width) && (100 * (height / width) > 125))
        {
            horizontalSplit = true;
        }

        int max = (horizontalSplit ? height : width) - MIN_NODE_SIZE;
        if(max <= MIN_NODE_SIZE) 
        {
            // Too small to split further
            success = false;
        }
        else // max > MIN_NODE_SIZE
        {
            int split = wsl::randomInt(MIN_NODE_SIZE, max);

            if(horizontalSplit)
            {
                splitPos.y = split + nodeRect.y1;
                leftChild_ = std::make_unique<Node>(wsl::Rect(nodeRect.x1, nodeRect.y1, width, split), this);
                rightChild_ = std::make_unique<Node>(wsl::Rect(nodeRect.x1, nodeRect.y1 + split, width, height - split), this);
            }
            else
            {
                splitPos.x = split + nodeRect.x1;
                leftChild_ = std::make_unique<Node>(wsl::Rect(nodeRect.x1, nodeRect.y1, split, height), this); 
                rightChild_ = std::make_unique<Node>(wsl::Rect(nodeRect.x1 + split, nodeRect.y1, width - split, height), this);
            }
            leftChild_->sibling_ = rightChild_.get();
            rightChild_->sibling_ = leftChild_.get();
            horizontal_ = horizontalSplit;
            success = true;
            split_ = true;
        }
       
    }
    return success;
}

Tree::Tree(wsl::Rect rect)
{
    populate(rect);
}

void Tree::populate(wsl::Rect rootRect)
{
    root_ = Node(rootRect);
                       
    std::vector<Node *> growth;
    growth.push_back(&root_);

    while(!growth.empty())
    {
        Node * currentNode = growth.back();
        nodes_.push_back(currentNode);
        if(!currentNode->hasSplit())
        {
            // Check if node can split, if so split it and add children to growth
            if(currentNode->split())
            {
                growth.push_back(currentNode->leftChild());
                growth.push_back(currentNode->rightChild());
            }
            else // if it can't split, add it to leaves
            {
                leaves_.push_back(currentNode);
                growth.pop_back();
            }
        }
        else // currentNode.hasSplit() == true
        {
            growth.pop_back();
        }
    }

    std::cout << "nodes.size() = " << nodes_.size() << ", leaves.size() = " << leaves_.size() << std::endl;
    std::cout << "isLeaf(leaves[leaves_.size() - 1]) = " << isLeaf(leaves_[leaves_.size() - 1]) << ", should be 1\n";
    std::cout << "isLeaf(root_) = " << isLeaf(&root_) << ", should be 0\n";
}

bool Tree::isLeaf(Node * node)
{
    for(int i = 0; i < leaves_.size(); ++i)
    {
        if(leaves_[i] == node)
        {
            return true;
        }
    }
    return false;
}

Dungeon::Dungeon(Tree * tree, int minRoomSize, bool fullRooms) : tree_(tree), minRoomSize_(minRoomSize), fullRooms_(fullRooms)
{
    dungeonMap.assign(width() * height(), Tile::Wall);
    build_();
}

void Dungeon::build_()
{
    for(int i = 0; i < tree_->nodes().size(); ++i)
    {
        traverseNode_(tree_->nodes()[i]);
    }
    std::cout << "Rooms.size() = " << rooms.size() << ", should be " << tree_->leaves().size() << std::endl;

    // Other dungeon stuff?
}

void Dungeon::traverseNode_(Node * node)
{
    if(tree_->isLeaf(node))
    {
        // std::cout << "Building room: ";
        // Build room
        int minX = node->nodeRect.x1 + 1;
        int maxX = node->nodeRect.x1 + node->nodeRect.w - 1;
        int minY = node->nodeRect.y1 + 1;
        int maxY = node->nodeRect.y1 + node->nodeRect.h - 1;

        maxX == width() ? maxX = 1 : maxX = node->nodeRect.x2 - 1;
        maxY == height() ? maxY = 1 : maxY = node->nodeRect.y2 -1;

        // if(false == fullRooms_)
        // {
        //     //Room size is random, otherwise roomsize fills the node
        //     minX = wsl::randomInt(minX, maxX - minRoomSize_ + 1);
        //     minY = wsl::randomInt(minY, maxY - minRoomSize_ + 1);
        //     maxX = wsl::randomInt(minX + minRoomSize_ - 2, maxX);
        //     maxY = wsl::randomInt(maxY + minRoomSize_ - 2, maxY);
        // }

        wsl::Rect room(minX, minY, maxX - minX + 1, maxY - minY + 1);
        // std::cout << minX << "," << minY << "," << maxX - minX + 1 << "," << maxY - minY + 1 << std::endl;
        wsl::Color randomColor(wsl::randomInt(150,255), wsl::randomInt(150,255), wsl::randomInt(150,255));
        for(int x = minX; x < maxX; ++x)
        {
            for(int y = minY; y < maxY; ++y)
            {
                // dungeonMap[index(x,y)] = Tile::Floor;
                dungeonMap[index(x,y)] = Tile(0, wsl::Glyph(' ', wsl::Color::Black, randomColor));
            }
        }
        rooms.push_back(room);
    }
    else //!tree_->isNode(node)
    {
        // Build corridor
    }
}

void Dungeon::vline_(int x, int y1, int y2)
{
// Vertical line from (x,y1) to (x,y2)
}
void Dungeon::vlineUp_(int x, int y)
{
// Vertical line from (x,y) to (x,0)
}
void Dungeon::vlineDown_(int x, int y)
{
//Vertical line from (x,y) to (x, height - 1)
}
void Dungeon::hline_(int x1, int y, int x2)
{
// Horizontal line from (x1, y) to (x2, y)
}
void Dungeon::hlineLeft_(int x, int y)
{
// Horizontal line from (x,y) to (0,y)
}
void Dungeon::hlineRight_(int x, int y)
{
// Horizontal line from (x,y) to (width - 1)
}

} //namespace bsp
