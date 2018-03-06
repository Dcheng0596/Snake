#ifndef SNAKE_H
#define SNAKE_H

#include <list>
#include <utility>
#include <string>

/*
* The Snake class
* Contains the characteristic of the snake for the game of "Snake"
* @author Darien Cheng
*/
class Snake
{
  private:
    std::list<std::pair<int, int>> position; // position of all parts of the snake
    std::string model;                       // the characters of the snake
    int direction;                           // the current direction the snake is moving
  public:
    void setPosition(std::list<std::pair<int, int>> pos);
    void setDir(int dir);
    int getDir();
    void addPos(int y, int x);
    void delPos();
    int posSize();
    std::pair<int, int> getPos(int index);
    void setModel(std::string str);
    void addChar(char ch, int index);
    void setChar(char ch, int index);
    char getChar(int index);
    void delChar(int index);

};
#endif // SNAKE_H
