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
#ifndef ACTION_HPP
#define ACTION_HPP

class ActionResult;
class Action 
{
public:
    virtual ActionResult perform() = 0;
protected:
    Action() { }
};
        
class ActionResult
{
public:
    ActionResult() { status_ = true; }
    bool success() { return status_; }
    void setFalse() { status_ = false; }
    void setTrue() { status_ = true; }
    Action * getAlternate() { return alternative_; }
    void setAlternate(Action * alternate) { alternative_ = alternate; }
private:
    Action * alternative_;
    bool status_;
};

class Entity;
class Tile;
class WalkAction : public Action
{
    public:
        WalkAction(Tile * tile, wsl::Vector2i pos);
        ActionResult perform();
    private:
        Tile * tile_;
        wsl::Vector2i pos;
};

#endif //ACTION_HPP
