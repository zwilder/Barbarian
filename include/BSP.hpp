#pragma once
#ifndef BSP_HPP
#define BSP_HPP

#include<vector>
#include "rect.hpp"
#include "random.hpp"

class Leaf
{
    public:
        Leaf(wsl::Rect rect);
        ~Leaf();

        wsl::Rect leafRect; // position/size of leaf
        wsl::Rect roomRect; // position/size of room inside leaf
    
        Leaf * leftChild;
        Leaf * rightChild;

        bool split();

    private:
        const int MIN_LEAF_SIZE = 6;

};

#endif //BSP_HPP
