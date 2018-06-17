#pragma once
#ifndef BSP_HPP
#define BSP_HPP

#include<vector>
#include "rect.hpp"
#include "random.hpp"

class Node
{
    public:
        Node(wsl::Rect rect = wsl::Rect(0,0,0,0), Node * parent = NULL);
        ~Node();
               
        bool hasSplit() { return split_; }
        bool split();
        bool horizontal() { return horizontal_; }
        Node * parent() { return parent_; }
        Node * leftChild() { return leftChild_; }
        Node * rightChild() { return rightChild_; }
        Node * sibling() { return sibling_; } // Binary tree - there's only one sibling

        wsl::Rect nodeRect;
        
    private:
        Node * parent_;
        Node * leftChild_;
        Node * rightChild_;
        Node * sibling_;
        bool split_;
        bool horizontal_;
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
