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

Node::Node(wsl::Rect rect, Node * parent) : nodeRect(rect), parent_(parent)
{
    split_ = false;
    leftChild_ = NULL;
    rightChild_ = NULL;
    sibling_ = NULL;
    connected = false;
    // splitPos_ = wsl::Vector2i(0,0);
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
        int width = nodeRect.w; // nodeRect.x2 - nodeRect.x1;
        int height = nodeRect.h; // nodeRect.y2 - nodeRect.y1;

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
                leftChild_ = new Node(wsl::Rect(nodeRect.x1, nodeRect.y1, width, split), this);
                rightChild_ = new Node(wsl::Rect(nodeRect.x1, nodeRect.y1 + split, width, height - split), this);
            }
            else
            {
                splitPos.x = split + nodeRect.x1;
                leftChild_ = new Node(wsl::Rect(nodeRect.x1, nodeRect.y1, split, height), this); 
                rightChild_ = new Node(wsl::Rect(nodeRect.x1 + split, nodeRect.y1, width - split, height), this);
            }
            leftChild_->sibling_ = rightChild_;
            rightChild_->sibling_ = leftChild_;
            horizontal_ = horizontalSplit;
            success = true;
            split_ = true;
        // std::cout << splitPos.x << "," << splitPos.y << std::endl;
        }
       
    }

    return success;
}

Tree::Tree()
{
    //
}

void Tree::populate(wsl::Rect rootRect)
{
    root_ = Node(rootRect);

    // std::vector<Node *> growth;
    // growth.push_back(&root_);
    // bool didSplit = true;
    // while(didSplit)
    // {
    //     didSplit = false;
    //     int growthSize = growth.size();
    //     for(int i = 0; i < growthSize; ++i)
    //     {
    //         // if((growth[i]->leftChild() != NULL) && (growth_[i]->rightChild() != NULL))
    //         if(!growth[i]->hasSplit())
    //         {
    //             if(growth[i]->nodeRect.w > MAX_LEAF_SIZE || growth[i]->nodeRect.h > MAX_LEAF_SIZE || wsl::randomBool(0.25))
    //             {
    //                 if(growth[i]->split())
    //                 {
    //                     growth.push_back(growth[i]->leftChild());
    //                     growth.push_back(growth[i]->rightChild());
    //                     didSplit = true;
    //                 }
    //             }
    //         }
    //     }
    // }
    // for(int i = 0; i < growth.size(); ++i)
    // {
    //     if(growth[i]->hasSplit())
    //     {
    //         continue;
    //     }
    //
    //     leaves_.push_back(growth[i]->parent());
    // }
    // growth.clear();
    /* A
     * 1 2
     * 1a 1b 2a
     */
                        
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
    
    carveRooms(4); // Temporarily here, I might want to eventually make BSP just generate a map like game_map currently does, and then have game_map read it.
    // std::cout << root_.rooms.size() << std::endl;
    
}

void Tree::carveRooms(int minRoomSize)
{
    //Make the rooms
    for(int i = 0; i < leaves_.size(); ++i)
    {
        int width = wsl::randomInt(minRoomSize, leaves_[i]->nodeRect.x2 - leaves_[i]->nodeRect.x1);
        int height = wsl::randomInt(minRoomSize, leaves_[i]->nodeRect.y2 - leaves_[i]->nodeRect.y1);
        int x = wsl::randomInt(leaves_[i]->nodeRect.x1, leaves_[i]->nodeRect.x2 - width);
        int y = wsl::randomInt(leaves_[i]->nodeRect.y1, leaves_[i]->nodeRect.y2 - height);
        wsl::Rect newRoom = wsl::Rect(x,y,width,height);
        rooms_.push_back(newRoom);
        leaves_[i]->rooms.push_back(newRoom);
        // rooms_.push_back(leaves_[i]->nodeRect);
    }

    // Tell each node what rooms it contains
    // for(int i = 0; i < leaves_.size(); ++i)
    // {
    //     addRoomsToNode_(leaves_[i]);
    // }

    //Carve the cooridors
    // for(int i = 0; i < leaves_.size(); ++i)
    // {
       // For each leaf, start by connect to sibling
       // Determine if the leaf is separated from its sibling by a horizontal or vertical split 
       // Find the closest room in that leaf to the closest room in the sibling leaf -- This might be a problem, there needs to be a routine 
       //   that loops from leaves -> root collecting and storing roomRects for each node.
       // Find random spots in closest wall (bottom/top for horizontal split, right/left for vertical split)
       // Make a cooridor from those spots to the split, and then connect them along split
       // Set connected_ to true for both node and it's sibling.
       // Move to parent node
       // Check if parent is null, if so then move to next node. 
       // If not, repeat.
        // carveCorridors(leaves_[i]);
    // }
    // std::cout << leaves_.size() << "," << corridors_.size() << std::endl;
}

void Tree::addRoomsToNode_(Node * node)
{
    if(node->parent() != NULL)
    {
        for(int i = 0; i < node->rooms.size(); ++i)
        {
            wsl::Rect room = node->rooms[i];
            bool roomExists = false;
            for(int j = 0; j < node->parent()->rooms.size(); ++j)
            {
                if(node->parent()->rooms[j] == room)
                {
                    roomExists = true;
                    break;
                }
            }
            if(!roomExists)
            {
                node->parent()->rooms.push_back(node->rooms[i]);
            }
        }
        addRoomsToNode_(node->parent());
    }
}


void Tree::carveCorridors(Node * node)
{
    // Connect leaf to it's sibling
    // Find which wall is closet to it's sibling wall
    if(node->connected || node->parent() == NULL)
    {
        return;
    }
    /*
    if(node->parent()->horizontal())
    {
        // Determine wall overlap
        wsl::Rect topRoom = (node->rooms[0].y1 < node->sibling()->rooms[0].y1 ? node->rooms[0] : node->sibling()->rooms[0]);
        wsl::Rect btmRoom = (node->rooms[0].y1 > node->sibling()->rooms[0].y1 ? node->rooms[0] : node->sibling()->rooms[0]); 
        // Connect them
        wsl::Rect corridor(topRoom.center().x, topRoom.center().y, 1, btmRoom.center().y - topRoom.center().y);
        corridors_.push_back(corridor);
    }
    else
    {
        // Determine wall overlap
        wsl::Rect leftRoom = (node->rooms[0].x1 < node->sibling()->rooms[0].x1 ? node->rooms[0] : node->sibling()->rooms[0]);
        wsl::Rect rightRoom = (node->rooms[0].x1 > node->sibling()->rooms[0].x1 ? node->rooms[0] : node->sibling()->rooms[0]);
        // Connect them
        wsl::Rect corridor(leftRoom.center().x, leftRoom.center().y, rightRoom.center().x - leftRoom.center().x, 1);
        corridors_.push_back(corridor);
    }
    */
    
    node->connected = true;
    node->sibling()->connected = true;
    
}

/*
void Tree::carveCorridors(Node * node)
{
    if(node->parent() == NULL)
    {
        return;
    }
    if(node->connected)
    {
        return;
    }
    wsl::Rect siblingRoom = node->sibling()->rooms[0];
    wsl::Rect nodeRoom = node->rooms[0];
    // std::cout << "siblingRoom == nodeRoom: " << (siblingRoom == nodeRoom) << std::endl;
    //Determine split
    if(node->parent()->horizontal())
    {
        //Find closest wall (bottom wall of top room, top wall of bottom room)
        wsl::Rect topRoom = (nodeRoom.y1 < siblingRoom.y1 ? nodeRoom : siblingRoom );
        wsl::Rect btmRoom = (nodeRoom.y1 > siblingRoom.y1 ? nodeRoom : siblingRoom );
        // std::cout << "topRoom == btmRoom: " << (topRoom == btmRoom) << std::endl;
        // std::cout << node->parent()->splitPos.x << "," << node->parent()->splitPos.y << std::endl;

        //Choose spot in wall
        int topSpot = (wsl::randomInt(topRoom.x1 + 1,topRoom.x2));
        int btmSpot = (wsl::randomInt(btmRoom.x1 + 1,btmRoom.x2));
        //Line to split from each room
        wsl::Rect topRect(topSpot, topRoom.y2, 1, node->parent()->splitPos.y - topRoom.y2); // h of 1 temporarily
        wsl::Rect btmRect(btmSpot, btmRoom.y1, 1, btmRoom.y1 - node->parent()->splitPos.y);
        //connect lines
        wsl::Rect hRect(topSpot, node->parent()->splitPos.y, btmSpot - topSpot, 1);
        corridors_.push_back(topRect);
        // corridors_.push_back(btmRect);
        corridors_.push_back(hRect);
    }
    else
    {
        //Find closest wall (right wall of left room, left wall of right room)
        //Choose spot in wall
        //Line to split from each room
        //connect lines
    }
    node->connected = true;
}
*/
/*
void Tree::carveCorridors(Node * node)
{
    if(node->connected)
    {
        return;
    }
    // Choose a room in the node
    wsl::Rect nodeRoom = node->rooms[wsl::randomInt(0, node->rooms.size() - 1)];

    // Find closest room in sibling->rooms;
    wsl::Rect closestRoom;
    int closestDistance;
    for(int i = 0; i < node->sibling()->rooms.size(); ++i)
    {
        if(0 == i)
        {
            closestRoom = node->sibling()->rooms[i];
            // closestDistance = sqrt(pow(closestRoom.x1 - nodeRoom.x1, 2) + pow(closestRoom.y1 - nodeRoom.y2, 2));
            closestDistance = nodeRoom.distanceTo(closestRoom);
            continue;
        }
        wsl::Rect testRoom = node->sibling()->rooms[i];
        int distance = nodeRoom.distanceTo(testRoom);
        // int distance = sqrt(pow(testRoom.x1 - nodeRoom.x1, 2) + pow(testRoom.y1 - nodeRoom.y2, 2));
        if(distance < closestDistance)
        {
            closestRoom = testRoom;
        }
    }

    // If closest distance is like 1, we might need to add a little logic here to just pick a spot and make a hole, otherwise this could get weird.
    std::cout << closestDistance << std::endl;
    if(closestDistance < 2)
    {
        return;
    }
    if(node->horizontal())
    {
        // Figure out which room is on top and which is on bottom
        wsl::Rect & topRoom = (nodeRoom.y1 < closestRoom.y1 ? nodeRoom : closestRoom);
        wsl::Rect & btmRoom = (nodeRoom.y1 > closestRoom.y1 ? nodeRoom : closestRoom); 

        // Choose a random spot on the bottom wall of top room, and the top wall of bottom room
        wsl::Vector2i topPos(wsl::randomInt(topRoom.x1,topRoom.x2), topRoom.y2);
        wsl::Vector2i btmPos(wsl::randomInt(btmRoom.x1,btmRoom.x2), btmRoom.y1);

        // Make a rectangle of width 1 from topPos to split, and from btmPos to split
        wsl::Rect topRect(topPos.x, topPos.y, 1, topPos.y - node->splitPos().y);
        corridors_.push_back(topRect);
        wsl::Rect btmRect(btmPos.x, node->splitPos().y, 1, node->splitPos().y - btmPos.y);
        corridors_.push_back(btmRect);

        // Connect the two with another rect
        wsl::Rect & leftRect = (topRect.x1 < btmRect.x1 ? topRect : btmRect);
        wsl::Rect & rightRect = (topRect.x1 >= btmRect.x1 ? topRect : btmRect);
        corridors_.push_back(wsl::Rect(leftRect.x1, node->splitPos().y, rightRect.x1 - leftRect.x1, 1));
    }
    else // !node->horizontal()
    {
        // same as above, but with left/right
        wsl::Rect & leftRoom = (nodeRoom.x1 < closestRoom.x2 ? nodeRoom : closestRoom);
        wsl::Rect & rightRoom = (nodeRoom.x1 > closestRoom.x2 ? nodeRoom : closestRoom);

        wsl::Vector2i leftPos(leftRoom.x2, wsl::randomInt(leftRoom.y1,leftRoom.y2));
        wsl::Vector2i rightPos(rightRoom.x1, wsl::randomInt(rightRoom.y1,rightRoom.y2));
        
        wsl::Rect leftRect(leftPos.x,leftPos.y,node->splitPos().x - leftPos.x, 1);
        corridors_.push_back(leftRect);
        wsl::Rect rightRect(rightPos.x,rightPos.y, rightPos.x - node->splitPos().x, 1);
        corridors_.push_back(rightRect);

        wsl::Rect & topRect = (leftRect.y1 < rightRect.y1 ? leftRect : rightRect);
        wsl::Rect & btmRect = (leftRect.y1 > rightRect.y1 ? leftRect : rightRect);
        corridors_.push_back(wsl::Rect(leftRect.x1, leftRect.y2, 1, btmRect.y1 - topRect.y2));
    }
    
    node->connected = true;
}    
*/
