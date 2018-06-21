/*
* Barbarian!
* Copyright (C) 2018
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

Node::Node(wsl::Rect rect, Node * parent) : nodeRect(rect), parent_(parent)
{
    split_ = false;
    leftChild_ = NULL;
    rightChild_ = NULL;
    sibling_ = NULL;
}

Node::~Node()
{
    if(hasSplit())
    {
        delete leftChild_;
        delete rightChild_;
    }
}

bool Node::split()
{
    bool success = false;
    if(!hasSplit())
    {
        bool horizontalSplit = wsl::randomBool();
        int width = nodeRect.x2 - nodeRect.x1;
        int height = nodeRect.y2 - nodeRect.y1;

        if((width > height) && (100 * (width / height) > 125)) // This funky statement is basically if width/height > 1.25. Trickin those integers.
        {
            horizontalSplit = false;
        }
        else if((height > width) && (100 * (height / width) > 125))
        {
            horizontalSplit = true;
        }

        const int MIN_NODE_SIZE = 8; // This should be somewhere else - seems silly to declare a constant in the middle of this function.
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
                leftChild_ = new Node(wsl::Rect(nodeRect.x1, nodeRect.y1, width, split), this);
                rightChild_ = new Node(wsl::Rect(nodeRect.x1, nodeRect.y1 + split, width, height - split), this);
            }
            else
            {
                leftChild_ = new Node(wsl::Rect(nodeRect.x1, nodeRect.y1, split, height), this); 
                rightChild_ = new Node(wsl::Rect(nodeRect.x1 + split, nodeRect.y1, width - split, height), this);
            }
            leftChild_->sibling_ = rightChild_;
            rightChild_->sibling_ = leftChild_;
            horizontal_ = horizontalSplit;
            success = true;
            split_ = true;
        }
       
    }

    return success;
}

Tree::Tree()
{
    //
}
/*
Tree::~Tree()
{
    for(int i = 0; i < leaves_.size(); ++i)
    {
        if(leaves_[i] != NULL)
        {
            delete leaves_[i];
        }
    }
}*/

void Tree::populate(wsl::Rect rootRect)
{
    root_ = Node(rootRect);

    std::vector<Node *> growth;
    growth.push_back(&root_);
    
    while(!growth.empty())
    {
        Node * currentNode = growth.back();
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
    
    //Make the rooms
    for(int i = 0; i < leaves_.size(); ++i)
    {
        // Changing the first number here in width/height will (obviously) affect the room size. This should possibly be passed into the class
        // creation function.
        int width = wsl::randomInt(4, leaves_[i]->nodeRect.x2 - leaves_[i]->nodeRect.x1);
        int height = wsl::randomInt(4, leaves_[i]->nodeRect.y2 - leaves_[i]->nodeRect.y1);
        int x = wsl::randomInt(leaves_[i]->nodeRect.x1, leaves_[i]->nodeRect.x2 - width);
        int y = wsl::randomInt(leaves_[i]->nodeRect.y1, leaves_[i]->nodeRect.y2 - height);
        rooms_.push_back(wsl::Rect(x,y,width,height));
        // rooms_.push_back(leaves_[i]->nodeRect);
    }
}
