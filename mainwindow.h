#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>
#include <QPalette>
#include "engine.h"


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

    void updateGraphic();

private:
    Ui::MainWindow *ui;
    Engine game;
};
#endif // MAINWINDOW_H
