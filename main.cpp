// main.cpp
#include <QApplication>
#include "snakegame.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SnakeGame game;
    game.setWindowTitle("Qt贪吃蛇 - 最终版");
    game.show();
    return a.exec();
}
