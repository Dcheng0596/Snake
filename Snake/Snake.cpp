#include "Snake.h"

void Snake::setDir(int dir)
{
    direction = dir;
}
int Snake::getDir()
{
    return direction;
}
void Snake::setPosition(std::list<std::pair<int, int>> pos)
{
    position = pos;
}
/*
* Creates and adds a new position to the front of the snake
* x - the x coordinate
* y - the y coordinate
*/
void Snake::addPos(int y, int x)
{
    std::pair<int, int> pos(y, x);
    position.push_front(pos);
}
std::pair<int, int> Snake::getPos(int index)
{
    if(index < position.size())
    {
        std::list<std::pair<int, int>>::iterator it = position.begin();
        for(int i = 0; i < index; i++)
            it++;
        return *it;
    }
}
/* Removes the tail position of the snake */
void Snake::delPos()
{
    position.pop_back();
}
int Snake::posSize()
{
    return position.size();
}
void Snake::setModel(std::string str)
{
    model = str;
}
void Snake::setChar(char ch, int index)
{
    model[index] = ch;
}
/*
* Adds char at the index, pushing back elements after the index
* Does nothing if index is out of bounds
* ch - char to be inserted
* index - index the char will be inserted
*/
void Snake::addChar(char ch, int index)
{
    std::string::iterator it = model.begin();
    for(int i = 0; i <= index; i++)
        it++;
    if(index < model.size() + 2)
        model.insert(it, ch);
}
char Snake::getChar(int index)
{
    if(index < model.size())
        return model[index];
}
/*
* Removes char at the index, pushing back elements after the index
* Does nothing if index is out of bounds
* index - index the char will be inserted
*/
void Snake::delChar(int index)
{
    std::string::iterator it = model.begin();
    for(int i = 0; i < index; i++)
        it++;
    if(index < model.size())
        model.erase(it);
}



