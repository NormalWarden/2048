#ifndef ENGINE_H
#define ENGINE_H

#define FILE_NAME "savedGame.txt"

#include <QRandomGenerator>
#include <QPalette>
#include <QColor>
#include <fstream>
#include <vector>


class Engine
{
public:
    void zeroInitialization();
    bool loadGame();
    int getValue(int row, int column);
    QColor getColor(int row, int column);

    void moveElementsToEdge(int direction);
    void calculateElements(int direction);
    bool checkGameOver();
    bool checkVictory();
    void createNewValue();
    void valuesToColors();
    int calculateScore();
    void saveGame();

private:
    int valueMatrix[4][4] { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} }; // Game "2048" has 4 rows and 4 columns
    QColor colorMatrix[4][4] {};
};

#endif // ENGINE_H
