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

    // std::cout << "nodes.size() = " << nodes_.size() << ", leaves.size() = " << leaves_.size() << std::endl;
    // std::cout << "isLeaf(leaves[leaves_.size() - 1]) = " << isLeaf(leaves_[leaves_.size() - 1]) << ", should be 1\n";
    // std::cout << "isLeaf(root_) = " << isLeaf(&root_) << ", should be 0\n";
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
    // for(int i = 0; i < tree_->leaves().size(); ++i)
    // {
    //     traverseNode_(tree_->leaves()[i]);
    // }

    for(int i = 0; i < tree_->nodes().size(); ++i)
    {
        // if(tree_->isLeaf(tree_->nodes()[i]))
        //     continue;
        traverseNode_(tree_->nodes()[i]);
    }

   // std::cout << "Rooms.size() = " << rooms.size() << ", should be " << tree_->leaves().size() << std::endl;

    // Other dungeon stuff?
}

void Dungeon::traverseNode_(Node * node)
{
    if(node->parent() == NULL)
    {
        return;
    }
    if(tree_->isLeaf(node))
    {
        // std::cout << "Building room: ";
        // Build room
        int xR = node->nodeRect.x1 + 1;
        int yR = node->nodeRect.y1 + 1;
        int wR = node->nodeRect.w - 1;
        int hR = node->nodeRect.h - 1;

        wR == width() ? wR = 1 : wR = node->nodeRect.w - 1;
        hR == height() ? hR = 1 : hR = node->nodeRect.h -1;
        
        wsl::Color randomColor(wsl::randomInt(50,255), wsl::randomInt(50,255), wsl::randomInt(50,255));
        if(!fullRooms_)
        {
            //Room size is random, otherwise roomsize fills the node
            wR = wsl::randomInt(minRoomSize_, node->nodeRect.w - 1);
            hR = wsl::randomInt(minRoomSize_, node->nodeRect.h - 1);
            xR = wsl::randomInt(node->nodeRect.x1 + 1, node->nodeRect.x2 - wR);
            yR = wsl::randomInt(node->nodeRect.y1 + 1, node->nodeRect.y2 - hR);

            //This is just for visualizing the nodes
            // for(int x = node->nodeRect.x1; x < node->nodeRect.x2; ++x)
            // {
            //     for(int y = node->nodeRect.y1; y < node->nodeRect.y2; ++y)
            //     {
            //         dungeonMap[index(x,y)].glyph().setColor(randomColor);
            //     }
            // }
        }

        wsl::Rect room(xR,yR,wR,hR);
        // std::cout << minX << "," << minY << "," << maxX - minX + 1 << "," << maxY - minY + 1 << std::endl;
        for(int x = room.x1; x < room.x2 - 1; ++x)
        {
            for(int y = room.y1; y < room.y2 - 1; ++y)
            {
                dungeonMap[index(x,y)] = Tile::Floor;
                // dungeonMap[index(x,y)] = Tile(0, wsl::Glyph(' ', wsl::Color::Black, randomColor));
            }
        }
        rooms.push_back(room);
    }
    else //!tree_->isLeaf(node)
    {
        // Build corridor
        wsl::Rect left = node->leftChild()->nodeRect;
        wsl::Rect right = node->rightChild()->nodeRect;

        if(node->horizontal())
        {
            // if((left.x1 + left.w - 1 <= right.x1) || (right.x1 + right.w - 1 <= left.x1))
            if(wsl::randomBool())
            {
                int x1 = wsl::randomInt(left.x1 + 1, left.x2 - 1);
                int x2 = wsl::randomInt(right.x1 + 1, right.x2 - 1);
                int y1 = wsl::randomInt(left.y2, right.y1);

                vlineUp_(x1, y1 - 1);
                hline_(x1, y1, x2);
                vlineDown_(x2, y1 + 1);
                // std::cout << "horizontal first conditional\n";
            }
            else
            {
                int minX = (left.x1 > right.x1 ? left.x1 : right.x1);
                int maxX = (left.x2 -1 < right.x2 -1 ? left.x2 : right.x2);
                int x1 = wsl::randomInt(minX + 2, maxX - 2);
                while(x1 > width() - 1)
                {
                    x1--;
                }
                vlineDown_(x1, right.y1);
                vlineUp_(x1, right.y1 - 1);
            }
        }
        else // !node->horizontal
        {
            // if((left.y2 - 1 < right.y1) || (right.y2 -1 < left.y1))
            if(wsl::randomBool())
            {
                int y1 = wsl::randomInt(left.y1, left.y2 - 1);
                int y2 = wsl::randomInt(right.y1, right.y2 - 1);
                int x1 = wsl::randomInt(left.x2, right.x1);
                hlineLeft_(x1 - 1, y1);
                vline_(x1, y1, y2);
                hlineRight_(x1 + 1, y2);
                // std::cout << "vertical first conditional\n";
            }
            else
            {
                int minY = (left.y1 > right.y1 ? left.y1 : right.y1);
                int maxY = (left.y1 < right.y1 ? left.y1 : right.y1);
                int y1 = wsl::randomInt(minY, maxY);
                while(y1 > height() - 1)
                {
                    y1--;
                }

                hlineLeft_(right.x1 - 1, y1);
                hlineRight_(right.x1, y1);

            }
        }
    }
}

void Dungeon::vline_(int x, int y1, int y2)
{
    // Vertical line from (x,y1) to (x,y2)
    int minY = y1;
    int maxY = y2;
    if(y1 > y2)
    {
        minY = y2;
        maxY = y1;
    }
    for(int y = minY; y <= maxY; ++y)
    {
        dungeonMap[index(x,y)] = Tile::Floor;
    }
}
void Dungeon::vlineUp_(int x, int y)
{
    // Vertical line from (x,y) to (x,0)
    while(y > 0)
    {
        if(!dungeonMap[index(x,y)].blocksMovement())
        {
            break;
        }
        dungeonMap[index(x,y)] = Tile::Floor;
        // dungeonMap[index(x,y)].glyph().setBgColor(wsl::Color::Green);
        y--;
    }
}
void Dungeon::vlineDown_(int x, int y)
{
    //Vertical line from (x,y) to (x, height - 1)
    while(y < height())
    {
        if(!dungeonMap[index(x,y)].blocksMovement())
        {
            break;
        }
        dungeonMap[index(x,y)] = Tile::Floor;
        // dungeonMap[index(x,y)].glyph().setBgColor(wsl::Color::Red);
        y++;
    }
}
void Dungeon::hline_(int x1, int y, int x2)
{
    // Horizontal line from (x1, y) to (x2, y)
    int minX = x1;
    int maxX = x2;
    if(x1 > x2)
    {
        minX = x2;
        maxX = x1;
    }
    for(int x = minX; x <= maxX; ++x)
    {
        dungeonMap[index(x,y)] = Tile::Floor;
    }
}
void Dungeon::hlineLeft_(int x, int y)
{
    // Horizontal line from (x,y) to (0,y)
    if(y == 0)
        return;
    while(x > 0)
    {
        if(!dungeonMap[index(x,y)].blocksMovement())
        {
            break;
        }
        dungeonMap[index(x,y)] = Tile::Floor;
        // dungeonMap[index(x,y)].glyph().setBgColor(wsl::Color::Blue);
        x--;
    }
}
void Dungeon::hlineRight_(int x, int y)
{
    // Horizontal line from (x,y) to (width - 1)
    if(y == 0)
        return;
    while(x < width() - 1)
    {
        if(!dungeonMap[index(x,y)].blocksMovement())
        {
            break;
        }
        dungeonMap[index(x,y)] = Tile::Floor;
        // dungeonMap[index(x,y)].glyph().setBgColor(wsl::Color::Yellow);
        x++;
    }
}

} //namespace bsp
