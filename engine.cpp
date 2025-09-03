#include "engine.h"

void Engine::zeroInitialization()
{
    valueMatrix[0][0] = 0;
    valueMatrix[0][1] = 0;
    valueMatrix[0][2] = 0;
    valueMatrix[0][3] = 0;

    valueMatrix[1][0] = 0;
    valueMatrix[1][1] = 0;
    valueMatrix[1][2] = 0;
    valueMatrix[1][3] = 0;

    valueMatrix[2][0] = 0;
    valueMatrix[2][1] = 0;
    valueMatrix[2][2] = 0;
    valueMatrix[2][3] = 0;

    valueMatrix[3][0] = 0;
    valueMatrix[3][1] = 0;
    valueMatrix[3][2] = 0;
    valueMatrix[3][3] = 0;
}

bool Engine::loadGame()
{
    std::fstream save;
    save.open(FILE_NAME, std::ios::in | std::ios::out);

    // confirm successful file opening or create new
    if (save.is_open() == false or save.fail() == true)
    {
        std::ofstream file(FILE_NAME); // to create new file
        file.close();
        save.open(FILE_NAME, std::ios::in | std::ios::out);
    }

    // check file length: if it empty then fill it
    save.seekg(0, save.end);
    if (save.tellg() == 0)
    {
        save.seekp(0);
        save << "2|2|0|0\n"
                "0|0|0|0\n"
                "0|0|0|0\n"
                "0|0|0|0";
    }

    // fill saved game to valueMatrix
    std::string lineIter;
    int row{ 0 }, prevPipePos{ 0 }, newPipePos{ 0 };
    save.seekg(0, save.beg);
    while(std::getline(save, lineIter))
    {
        if (lineIter.size() < 7) // 7 symbols is minimum length of line from save file ("0|0|0|0")
            continue;

        // check entire line contain only digits and pipe
        for (char symbol : lineIter)
            if(!(std::isdigit(symbol) || symbol == '|'))
                return 0; // return error

        prevPipePos = 0;
        newPipePos = lineIter.find("|", 0);
        valueMatrix[row][0] = stoi(lineIter.substr(prevPipePos, newPipePos));

        prevPipePos = newPipePos + 1;
        newPipePos = lineIter.find("|", newPipePos+1);
        valueMatrix[row][1] = stoi(lineIter.substr(prevPipePos, newPipePos));

        prevPipePos = newPipePos + 1;
        newPipePos = lineIter.find("|", newPipePos+1);
        valueMatrix[row][2] = stoi(lineIter.substr(prevPipePos, newPipePos));

        prevPipePos = newPipePos + 1;
        newPipePos = lineIter.find("|", newPipePos+1);
        valueMatrix[row][3] = stoi(lineIter.substr(prevPipePos, newPipePos));

        ++row;
    }

    // confirm correct content in save
    for (int row = 0; row <= 3; ++row)
        for (int column = 0; column <= 3; ++column)
            if (valueMatrix[row][column] == 2048) // if game done
                return 0;
            else if (valueMatrix[row][column] % 2 != 0 || valueMatrix[row][column] > 2048) // if save contain unacceptable nums
                return 0;

    if (row != 4) // after successful loop we have row = 4
    {
        return 0;
    }

    save.close();
    valuesToColors();

    return 1;
}

int Engine::getValue(int row, int column)
{
    return valueMatrix[row][column];
}

QColor Engine::getColor(int row, int column)
{
    return colorMatrix[row][column];
}

void Engine::moveElementsToEdge(int direction)
{
    if (direction == Qt::Key_W) // move everything up
    {
        for (int column = 0; column <= 3; ++column)
        {
            if (valueMatrix[0][column] + valueMatrix[1][column] + valueMatrix[2][column] + valueMatrix[3][column] > 0) // if all rows have 0, don't continue
            {
                for (int i = 0; i < 3; ++i) // if valueMatrix[0 and 1 and 2][0] == 0 and valueMatrix[3][0] != 0 we need move last 3 times (through each row)
                {
                    if (valueMatrix[0][column] == 0)
                    {
                        valueMatrix[0][column] = valueMatrix[1][column];
                        valueMatrix[1][column] = 0;
                    }
                    if (valueMatrix[1][column] == 0)
                    {
                        valueMatrix[1][column] = valueMatrix[2][column];
                        valueMatrix[2][column] = 0;
                    }
                    if (valueMatrix[2][column] == 0)
                    {
                        valueMatrix[2][column] = valueMatrix[3][column];
                        valueMatrix[3][column] = 0;
                    }
                }
            }
        }
    }
    else if (direction == Qt::Key_S) // move everything down
    {
        for (int column = 0; column <= 3; ++column)
        {
            if (valueMatrix[0][column] + valueMatrix[1][column] + valueMatrix[2][column] + valueMatrix[3][column] > 0)
            {
                for (int i = 0; i < 3; ++i)
                {
                    if (valueMatrix[3][column] == 0)
                    {
                        valueMatrix[3][column] = valueMatrix[2][column];
                        valueMatrix[2][column] = 0;
                    }
                    if (valueMatrix[2][column] == 0)
                    {
                        valueMatrix[2][column] = valueMatrix[1][column];
                        valueMatrix[1][column] = 0;
                    }
                    if (valueMatrix[1][column] == 0)
                    {
                        valueMatrix[1][column] = valueMatrix[0][column];
                        valueMatrix[0][column] = 0;
                    }
                }
            }
        }
    }
    else if (direction == Qt::Key_A) // move everything left
    {
        for (int row = 0; row <= 3; ++row)
        {
            if (valueMatrix[row][0] + valueMatrix[row][1] + valueMatrix[row][2] + valueMatrix[row][3] + valueMatrix[row][0] > 0)
            {
                for (int i = 0; i < 3; ++i)
                {
                    if (valueMatrix[row][0] == 0)
                    {
                        valueMatrix[row][0] = valueMatrix[row][1];
                        valueMatrix[row][1] = 0;
                    }
                    if (valueMatrix[row][1] == 0)
                    {
                        valueMatrix[row][1] = valueMatrix[row][2];
                        valueMatrix[row][2] = 0;
                    }
                    if (valueMatrix[row][2] == 0)
                    {
                        valueMatrix[row][2] = valueMatrix[row][3];
                        valueMatrix[row][3] = 0;
                    }
                }
            }
        }
    }
    else if (direction == Qt::Key_D) // move everything right
    {
        for (int row = 0; row <= 3; ++row)
        {
            if (valueMatrix[row][0] + valueMatrix[row][1] + valueMatrix[row][2] + valueMatrix[row][3] + valueMatrix[row][0] > 0)
            {
                for (int i = 0; i < 3; ++i)
                {
                    if (valueMatrix[row][3] == 0)
                    {
                        valueMatrix[row][3] = valueMatrix[row][2];
                        valueMatrix[row][2] = 0;
                    }
                    if (valueMatrix[row][2] == 0)
                    {
                        valueMatrix[row][2] = valueMatrix[row][1];
                        valueMatrix[row][1] = 0;
                    }
                    if (valueMatrix[row][1] == 0)
                    {
                        valueMatrix[row][1] = valueMatrix[row][0];
                        valueMatrix[row][0] = 0;
                    }
                }
            }
        }
    }
}

void Engine::calculateElements(int direction)
{
    if (direction == Qt::Key_W) // calculate from top to bottom
    {
        for (int column = 0; column <= 3; ++column)
        {
            // example: 2|2|4|4
            if (valueMatrix[0][column] == valueMatrix[1][column])
            {
                valueMatrix[0][column] *= 2;
                valueMatrix[1][column] = 0;

                if (valueMatrix[2][column] == valueMatrix[3][column])
                {
                    valueMatrix[2][column] *= 2;
                    valueMatrix[3][column] = 0;
                }
            }

            // example: 2|4|4|2
            if (valueMatrix[1][column] == valueMatrix[2][column])
            {
                valueMatrix[1][column] *= 2;
                valueMatrix[2][column] = 0;
            }

            // example: 8|4|2|2
            if (valueMatrix[2][column] == valueMatrix[3][column])
            {
                valueMatrix[2][column] *= 2;
                valueMatrix[3][column] = 0;
            }
        }
    }
    else if (direction == Qt::Key_S) // calculate from bottom to top
    {
        for (int column = 0; column <= 3; ++column)
        {
            if (valueMatrix[3][column] == valueMatrix[2][column])
            {
                valueMatrix[3][column] *= 2;
                valueMatrix[2][column] = 0;

                if (valueMatrix[1][column] == valueMatrix[0][column])
                {
                    valueMatrix[1][column] *= 2;
                    valueMatrix[0][column] = 0;
                }
            }

            if (valueMatrix[2][column] == valueMatrix[1][column])
            {
                valueMatrix[2][column] *= 2;
                valueMatrix[1][column] = 0;
            }

            if (valueMatrix[1][column] == valueMatrix[0][column])
            {
                valueMatrix[1][column] *= 2;
                valueMatrix[0][column] = 0;
            }
        }
    }
    else if (direction == Qt::Key_A) // calculate from left to right
    {
        for (int row = 0; row <= 3; ++row)
        {
            if (valueMatrix[row][0] == valueMatrix[row][1])
            {
                valueMatrix[row][0] *= 2;
                valueMatrix[row][1] = 0;

                if (valueMatrix[row][2] == valueMatrix[row][3])
                {
                    valueMatrix[row][2] *= 2;
                    valueMatrix[row][3] = 0;
                }
            }

            if (valueMatrix[row][1] == valueMatrix[row][2])
            {
                valueMatrix[row][1] *= 2;
                valueMatrix[row][2] = 0;
            }

            if (valueMatrix[row][2] == valueMatrix[row][3])
            {
                valueMatrix[row][2] *= 2;
                valueMatrix[row][3] = 0;
            }
        }
    }
    else if (direction == Qt::Key_D) // calculate from tight to left
    {
        for (int row = 0; row <= 3; ++row)
        {
            if (valueMatrix[row][3] == valueMatrix[row][2])
            {
                valueMatrix[row][3] *= 2;
                valueMatrix[row][2] = 0;

                if (valueMatrix[row][1] == valueMatrix[row][0])
                {
                    valueMatrix[row][1] *= 2;
                    valueMatrix[row][0] = 0;
                }
            }

            if (valueMatrix[row][2] == valueMatrix[row][1])
            {
                valueMatrix[row][2] *= 2;
                valueMatrix[row][1] = 0;
            }

            if (valueMatrix[row][1] == valueMatrix[row][0])
            {
                valueMatrix[row][1] *= 2;
                valueMatrix[row][0] = 0;
            }
        }
    }
}

void Engine::createNewValue()
{
    std::vector<int> availablePositions {}; // first values are available rows

    // check rows for availability
    for (int row = 0; row <= 3; ++row)
        for (int column = 0; column <= 3; ++column)
            if (valueMatrix[row][column] == 0)
            {
                availablePositions.push_back(row);
                break;
            }

    int chosenRow {availablePositions[QRandomGenerator::global()->generate() % availablePositions.size()]}; // choosing random row to create new value in it
    availablePositions.clear(); // prepare vector for saving available columns

    // check columns for availability
    for (int column = 0; column <= 3; ++column)
        if (valueMatrix[chosenRow][column] == 0)
            availablePositions.push_back(column);

    valueMatrix[chosenRow][ availablePositions[ QRandomGenerator::global()->generate() % availablePositions.size() ] ] = 2; // 2 is new standard value in 2048
}

void Engine::saveGame()
{
    std::ofstream save;
    save.open(FILE_NAME, std::ios::out | std::ios::trunc); // create new empty file
    save.seekp(0);
    save << valueMatrix[0][0] << "|" <<  valueMatrix[0][1] << "|" << valueMatrix[0][2] << "|" <<valueMatrix[0][3] << "\n" <<
        valueMatrix[1][0] << "|" <<  valueMatrix[1][1] << "|" << valueMatrix[1][2] << "|" <<valueMatrix[1][3] << "\n" <<
        valueMatrix[2][0] << "|" <<  valueMatrix[2][1] << "|" << valueMatrix[2][2] << "|" <<valueMatrix[2][3] << "\n" <<
        valueMatrix[3][0] << "|" <<  valueMatrix[3][1] << "|" << valueMatrix[3][2] << "|" <<valueMatrix[3][3];
    save.close();
}

int Engine::calculateScore()
{
    int score { 0 };
    for (int row = 0; row <= 3; ++row)
        for (int column = 0; column <= 3; ++column)
            score += valueMatrix[row][column];

    return score;
}

bool Engine::checkGameOver()
{
    for (int row = 0; row <= 3; ++row)
        for (int column = 0; column <= 3; ++column)
            if (valueMatrix[row][column] == 0)
                return false;

    return true;
}

bool Engine::checkVictory()
{
    for (int row = 0; row <= 3; ++row)
        for (int column = 0; column <= 3; ++column)
            if (valueMatrix[row][column] == 2048)
                return true;

    return false;
}

void Engine::valuesToColors()
{
    for (int row = 0; row <= 3; ++row)
    {
        for (int column = 0; column <= 3; ++column)
        {
            switch (valueMatrix[row][column])
            {
            case 0:
                colorMatrix[row][column] = 0xffffffff;
                break;
            case 2:
                colorMatrix[row][column] = 0x13a87f5b;
                break;
            case 4:
                colorMatrix[row][column] = 0x17d39d6f;
                break;
            case 8:
                colorMatrix[row][column] = 0x20f2b179;
                break;
            case 16:
                colorMatrix[row][column] = 0x34f59563;
                break;
            case 32:
                colorMatrix[row][column] = 0x46f67c60;
                break;
            case 64:
                colorMatrix[row][column] = 0x58f65e3b;
                break;
            case 128:
                colorMatrix[row][column] = 0x03edcf73;
                break;
            case 256:
                colorMatrix[row][column] = 0x03edcc62;
                break;
            case 512:
                colorMatrix[row][column] = 0x04edc850;
                break;
            case 1024:
                colorMatrix[row][column] = 0x05edc53f;
                break;
            case 2048:
                colorMatrix[row][column] = 0x06edc22d;
                break;
            default:
                break;
            }
        }
    }
}
