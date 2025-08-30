#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QPalette>
#include <QColor>
#include <fstream>
#include <vector>

#define FILE_NAME "savedGame.txt"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonNewGame_clicked();
    void on_buttonQuit_clicked();
    void keyPressEvent(QKeyEvent* event);

    void moveElementsToEdge(int direction);
    void calculateElements(int direction);
    bool checkGameOver();
    void createNewValue();
    void valuesToColors();
    int calculateScore();
    void showNewResult(int score);
    void saveGame();

private:
    Ui::MainWindow *ui;
    int valueMatrix[4][4] { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} }; // Game "2048" has 4 rows and 4 columns
    QColor colorMatrix[4][4] {};
};
#endif // MAINWINDOW_H
