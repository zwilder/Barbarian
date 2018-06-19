#include <iostream>
#include "../include/BSP.hpp"

Node::Node(wsl::Rect rect, Node * parent) : nodeRect(rect), parent_(parent)
{
    split_ = false;
    leftChild_ = NULL;
    rightChild_ = NULL;
    sibling_ = NULL;
    connected_ = false;
    splitPos_ = wsl::Vector2i(0,0);
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
                splitPos_.y = split;
                leftChild_ = new Node(wsl::Rect(nodeRect.x1, nodeRect.y1, width, split), this);
                rightChild_ = new Node(wsl::Rect(nodeRect.x1, nodeRect.y1 + split, width, height - split), this);
            }
            else
            {
                splitPos_.x = split;
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

    //Carve the cooridors
    for(int i = 0; i < leaves_.size(); ++i)
    {
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
    }
}

void Tree::carveCorridor(Node * node)
{
    if(node->connected())
    {
        return;
    }
    // Choose a room in the node
    wsl::Rect nodeRoom = node->rooms[wsl::randomInt(0, node->rooms.Size() - 1)];
    // Find closest room in sibling->rooms;
    wsl::Rect closestRoom;
    int closestDistance;
    for(int i = 0; i < node->sibling()->rooms.size(); ++i)
    {
        if(0 == i)
        {
            closestRoom = node->sibling()->rooms[i];
            closestDistance = sqrt(pow(closestRoom.x1 - nodeRoom.x1, 2) + pow(closestRoom.y1 - nodeRoom.y2));
            continue;
        }
        wsl::Rect testRoom = node->sibling()->rooms[i];
        int distance = sqrt(pow(testRoom.x1 - nodeRoom.x1, 2) + pow(testRoom.y1 - nodeRoom.y2));
        if(distance < closestDistance)
        {
            closestRoom = testRoom;
        }
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
        corridors_.push_back(wsl::Rect(topPos.x, topPos.y, 1, topPos.y - split.y));
        corridors_.push_back(wsl::Rect(btmPos.x, split.y, 1, split.y - btmPos.y));

        // Connect the two with another rect
        
