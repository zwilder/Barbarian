#include <iostream>
#include "../include/BSP.hpp"

Leaf::Leaf(wsl::Rect rect) : leafRect(rect)
{
    leftChild = NULL;
    rightChild = NULL;
}

Leaf::~Leaf()
{
    if(leftChild != NULL)
    {
        delete leftChild;
    }

    if(rightChild != NULL)
    {
        delete rightChild;
    }
}

bool Leaf::split()
{
    if(leftChild != NULL || rightChild != NULL)
    {
        std::cout << "Already split this leaf!" << std::endl;
        return false; // Already split!
    }

    bool horizontalSplit = wsl::randomBool();
    int width = leafRect.x1 + leafRect.x2;
    int height = leafRect.y1 + leafRect.y2;

    if((width > height) && (100 * (width / height) > 125)) // This funky statement is basically if width/height > 1.25. Trickin those integers.
    {
        horizontalSplit = false;
    }
    else if((height > width) && (100 * (height / width) > 125))
    {
        horizontalSplit = true;
    }

    int max = (horizontalSplit ? height : width) - MIN_LEAF_SIZE;
    if(max <= MIN_LEAF_SIZE) // Too small to split further
    {
        std::cout << "Too small to split further!" << std::endl;
        return false;
    }
    
    int split = wsl::randomInt(MIN_LEAF_SIZE, max);

    if(horizontalSplit)
    {
        // x,y,width,split
        leftChild = new Leaf(wsl::Rect(leafRect.x1, leafRect.y1, width, split));
        // x,y+split, width, height - split
        rightChild = new Leaf(wsl::Rect(leafRect.x1, leafRect.y1 + split, width, height - split));
    }
    else
    {
        // x,y,split, height
        leftChild = new Leaf(wsl::Rect(leafRect.x1, leafRect.y1, split, height)); 
        // x+split,y,width-split, height
        rightChild = new Leaf(wsl::Rect(leafRect.x1 + split, leafRect.y1, width - split, height));
    }

    
    // bool success = false;
    // success = leftChild->split();
    // success = rightChild->split();

    return true;
}
