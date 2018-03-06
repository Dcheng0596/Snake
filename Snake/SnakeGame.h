#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "Snake.h"
#include "curses.h"
#include <windows.h>

class SnakeGame
{
  private:
    Snake snake;
  public:
    bool isRunning();
    void createScreen();
    void createSnake();
    std::pair<int ,int> createPellet();
    bool moveHead(int dir);
    void moveTail();
    void updateMove();
    void updateLength(int len);
    void updateScore();
    void gameOver();
    void startGame();
    void playSound();
};
#endif // SNAKEGAME_H
