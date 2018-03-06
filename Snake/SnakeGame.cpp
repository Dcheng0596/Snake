#include "SnakeGame.h"
#include <chrono>
#include <random>
#include <thread>
#include "resource.h"

void SnakeGame::createScreen()
{
    move(1, 3);
    for(int i = 1; i < 115; i++)
        addch(ACS_BLOCK);
    for(int i = 1; i < 29; i++)
    {
        move(i, 3);
        addch(ACS_BLOCK);
        move(i, 30);
        addch(ACS_BLOCK);;
        move(i, 116);
        addch(ACS_BLOCK);
    }
    move(28, 3);
    for(int i = 1; i < 115; i++)
        addch(ACS_BLOCK);
    move(5, 12);
    printw("SCORE : 0");
    move(9, 12);
    printw("LENGTH : 5");
    move(23, 7);
    printw("CONTROLS: ARROW KEYS");
    move(26, 10);
    printw("SNAKE BY LOCKON");
    refresh();

}
void SnakeGame::createSnake()
{
    std::string sModel = "O0000";
    //std::string sModel = "SNAKE";
    std::list<std::pair<int, int>> empty;

    snake.setPosition(empty);
    snake.setModel(sModel);

    int x = 73, y = 13;
    for(int i = 4; i >= 0; i--)
    {
        move(y, x);
        std::pair<int, int> pos(y, x);
        snake.addPos(y, x);
        addch(snake.getChar(i));
        x--;
    }
    refresh();
}
std::pair<int, int> SnakeGame::createPellet()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> disX(31, 115);
    std::uniform_int_distribution<int> disY(2, 27);
    int x = disX(generator);
    int y = disY(generator);
    bool posTaken = true;
    while(posTaken)
    {
        posTaken = false;
        for(int i = 0; i < snake.posSize(); i++)
        {
            std::pair<int, int> pelPos(y, x);
            if(pelPos == snake.getPos(i))
            {
                x = disX(generator);
                y = disY(generator);
                posTaken = true;
                break;
            }
        }
    }
    move(y, x);
    printw("@");
    refresh();
    std::pair<int, int> rtnval(y, x);
    return rtnval;
}
bool SnakeGame::moveHead(int dir)
{
    std::pair<int, int> curHeadPos(snake.getPos(0));
    std::pair<int, int> newHeadPos;
    switch(dir)
    {
        case KEY_UP:
                snake.addPos(curHeadPos.first - 1, curHeadPos.second);
                newHeadPos.first = snake.getPos(0).first;
                newHeadPos.second = snake.getPos(0).second;
                if(newHeadPos.first == 1 || newHeadPos.first == 28 || newHeadPos.second == 30 || newHeadPos.second == 116)
                {
                  gameOver();
                  return false;
                }
                for(int i = 1; i < snake.posSize(); i++)
                    if(newHeadPos.first == snake.getPos(i).first && newHeadPos.second == snake.getPos(i).second)
                    {
                      gameOver();
                      return false;
                    }
                snake.addChar('0', 2);
                //snake.addChar('A', 2);
                updateMove();
                return true;
        case KEY_DOWN:
                snake.addPos(curHeadPos.first + 1, curHeadPos.second);
                newHeadPos.first = snake.getPos(0).first;
                newHeadPos.second = snake.getPos(0).second;
                if(newHeadPos.first == 1 || newHeadPos.first == 28 || newHeadPos.second == 30 || newHeadPos.second == 116)
                {
                  gameOver();
                  return false;
                }
                for(int i = 1; i < snake.posSize(); i++)
                    if(newHeadPos.first == snake.getPos(i).first && newHeadPos.second == snake.getPos(i).second)
                    {
                      gameOver();
                      return false;
                    }
                snake.addChar('0', 2);
                //snake.addChar('A', 2);
                updateMove();
                return true;
        case KEY_LEFT:
                snake.addPos(curHeadPos.first, curHeadPos.second - 1);
                newHeadPos.first = snake.getPos(0).first;
                newHeadPos.second = snake.getPos(0).second;
                if(newHeadPos.first == 1 || newHeadPos.first == 28 || newHeadPos.second == 30 || newHeadPos.second == 116)
                {
                  gameOver();
                  return false;
                }
                for(int i = 1; i < snake.posSize(); i++)
                    if(newHeadPos.first == snake.getPos(i).first && newHeadPos.second == snake.getPos(i).second)
                    {
                      gameOver();
                      return false;
                    }
                snake.addChar('0', 2);
                //snake.addChar('A', 2);
                updateMove();
                return true;
        case KEY_RIGHT:
                snake.addPos(curHeadPos.first, curHeadPos.second + 1);
                newHeadPos.first = snake.getPos(0).first;
                newHeadPos.second = snake.getPos(0).second;
                if(newHeadPos.first == 1 || newHeadPos.first == 28 || newHeadPos.second == 30 || newHeadPos.second == 116)
                {
                  gameOver();
                  return false;
                }
                for(int i = 1; i < snake.posSize(); i++)
                    if(newHeadPos.first == snake.getPos(i).first && newHeadPos.second == snake.getPos(i).second)
                    {
                      gameOver();
                      return false;
                    }
                snake.addChar('0', 2);
                //snake.addChar('A', 2);
                updateMove();
                return true;
        default:
            break;
    }

}
void SnakeGame::moveTail()
{
    std::pair<int, int> curTailPos(snake.getPos(snake.posSize() - 1));
    move(curTailPos.first, curTailPos.second);
    addch(' ');
    snake.delPos();
    snake.delChar(snake.posSize());
    //snake.setChar('E', snake.posSize() - 1);
    //snake.setChar('K', snake.posSize() - 2);
    updateMove();
}
void SnakeGame::updateMove()
{
    for(int i = snake.posSize() - 1; i >= 0; i--)
    {
        int y = snake.getPos(i).first;
        int x = snake.getPos(i).second;
        move(y, x);
        addch(snake.getChar(i));
    }
    refresh();
}
void SnakeGame::playSound()
{
    while(true)
        PlaySound(MAKEINTRESOURCE(IDR_SOUND), GetModuleHandle(NULL), SND_RESOURCE);
}
void SnakeGame::gameOver()
{
    move(13, 12);
    attron(A_BOLD);
    printw("GAME OVER");
    attroff(A_BOLD);
    move(15, 12);
    printw("CONTINUE?");
    move(16, 14);
    printw("(Y/N)");
}
void SnakeGame::startGame()
{
    bool retry = true;
    do
    {
        std::thread soundT(playSound, this);
        initscr();
        noecho();
        keypad(stdscr, TRUE);
        cbreak();
        nodelay(stdscr, TRUE);
        curs_set(0);

        soundT.detach();
        clear();
        createScreen();
        createSnake();
        std::pair<int, int> pelPos = createPellet();
        snake.setDir(KEY_LEFT);
        int score = 0;
        std::pair<int, int> scorePos(5, 20);
        int length = snake.posSize();
        std::pair<int, int> lenPos(9, 21);
        bool notGameOver = true;
        int direction = ERR;
        int growTime = 4;
        while(notGameOver)
        {
            int input = getch();
            if(input != KEY_DOWN && input != KEY_UP && input != KEY_LEFT && input != KEY_RIGHT)
                input = direction;

            switch(input)
            {
                case KEY_RIGHT:
                    if(snake.getDir() == KEY_LEFT)
                        break;
                    if(!moveHead(input))
                    {
                        notGameOver = false;
                        break;
                    }
                    if(pelPos == snake.getPos(0))
                    {
                        score += 10;
                        move(scorePos.first, scorePos.second);
                        printw(std::to_string(score).c_str());
                        length += 4;
                        move(lenPos.first, lenPos.second);
                        printw(std::to_string(length).c_str());
                        pelPos = createPellet();
                        growTime = 0;
                    }
                    else if(growTime >= 4)
                        moveTail();
                    direction = input;
                    snake.setDir(input);
                    Sleep(60);
                    break;
                case KEY_LEFT:
                    if(snake.getDir() == KEY_RIGHT)
                        break;
                    if(!moveHead(input))
                    {
                        notGameOver = false;
                        break;
                    }
                    if(pelPos == snake.getPos(0))
                    {
                        score += 10;
                        move(scorePos.first, scorePos.second);
                        printw(std::to_string(score).c_str());
                        length += 4;
                        move(lenPos.first, lenPos.second);
                        printw(std::to_string(length).c_str());
                        pelPos = createPellet();
                        growTime = 0;
                    }
                    else if(growTime >= 4)
                        moveTail();
                    direction = input;
                    snake.setDir(input);
                    Sleep(60);
                    break;
                case KEY_UP:
                    if(snake.getDir() == KEY_DOWN)
                        break;
                    if(!moveHead(input))
                    {
                        notGameOver = false;
                        break;
                    }
                    if(pelPos == snake.getPos(0))
                    {
                        score += 10;
                        move(scorePos.first, scorePos.second);
                        printw(std::to_string(score).c_str());
                        length += 4;
                        move(lenPos.first, lenPos.second);
                        printw(std::to_string(length).c_str());
                        pelPos = createPellet();
                        growTime = 0;
                    }
                    else if(growTime >= 4)
                        moveTail();
                    direction = input;
                    snake.setDir(input);
                    Sleep(110);
                    break;
                case KEY_DOWN:
                    if(snake.getDir() == KEY_UP)
                        break;
                    if(!moveHead(input))
                    {
                        notGameOver = false;
                        break;
                    }
                    if(pelPos == snake.getPos(0))
                    {
                        score += 10;
                        move(scorePos.first, scorePos.second);
                        printw(std::to_string(score).c_str());
                        length += 4;
                        move(lenPos.first, lenPos.second);
                        printw(std::to_string(length).c_str());
                        pelPos = createPellet();
                        growTime = 0;
                    }
                    else if(growTime >= 4)
                        moveTail();
                    direction = input;
                    snake.setDir(input);
                    Sleep(110);
                    break;
                default:
                    break;
            }
            if(growTime < 4)
                growTime++;
        }
        bool noAns = true;
        while(noAns)
        {
            int ans = getch();
            switch(ans)
            {
                case 'Y':
                case 'y':
                    noAns = false;
                    break;
                case 'N':
                case 'n':
                    retry = false;
                    noAns = false;
                default:
                    break;
            }
        }
    }while(retry);
    endwin();
}


