#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (!game.loadGame())
    {
        QMessageBox::critical(this, "Save file error", "File with saved game is corrupted. Try to delete file and open game again");
        exit(-1);
    }

    updateGraphic();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonNewGame_clicked()
{
    game.zeroInitialization();

    game.createNewValue();
    game.createNewValue();

    game.valuesToColors();
    updateGraphic();
    game.saveGame();
}

void MainWindow::on_buttonQuit_clicked()
{
    MainWindow::~MainWindow();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    // confirm pressing only WASD
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_S || event->key() == Qt::Key_A || event->key() == Qt::Key_D)
    {
        game.moveElementsToEdge(event->key());
        game.calculateElements(event->key());
        game.moveElementsToEdge(event->key());

        if (game.checkGameOver())
        {
            QMessageBox::information(this, "Game over", "Your game over. Starting new game...");
            on_buttonNewGame_clicked();
        }
        else if (game.checkVictory())
        {
            game.valuesToColors();
            updateGraphic();
            QMessageBox::information(this, "Victory", "You win! Starting new game...");
            on_buttonNewGame_clicked();
        }
        else
        {
            game.createNewValue();
            game.valuesToColors();
            updateGraphic();
            game.saveGame();
        }
    }
}

void MainWindow::updateGraphic()
{
    // change button text (number) and background color
    ui->element11->setText(QString::number(game.getValue(0, 0)));
    ui->element11->setStyleSheet(QString("background-color: %1; color: rgb(255,255,255)").arg(game.getColor(0, 0).name()));
    ui->element12->setText(QString::number(game.getValue(0, 1)));
    ui->element12->setStyleSheet(QString("background-color: %1; color: rgb(255,255,255)").arg(game.getColor(0, 1).name()));
    ui->element13->setText(QString::number(game.getValue(0, 2)));
    ui->element13->setStyleSheet(QString("background-color: %1; color: rgb(255,255,255)").arg(game.getColor(0, 2).name()));
    ui->element14->setText(QString::number(game.getValue(0, 3)));
    ui->element14->setStyleSheet(QString("background-color: %1; color: rgb(255,255,255)").arg(game.getColor(0, 3).name()));

    ui->element21->setText(QString::number(game.getValue(1, 0)));
    ui->element21->setStyleSheet(QString("background-color: %1; color: rgb(255,255,255)").arg(game.getColor(1, 0).name()));
    ui->element22->setText(QString::number(game.getValue(1, 1)));
    ui->element22->setStyleSheet(QString("background-color: %1; color: rgb(255,255,255)").arg(game.getColor(1, 1).name()));
    ui->element23->setText(QString::number(game.getValue(1, 2)));
    ui->element23->setStyleSheet(QString("background-color: %1; color: rgb(255,255,255)").arg(game.getColor(1, 2).name()));
    ui->element24->setText(QString::number(game.getValue(1, 3)));
    ui->element24->setStyleSheet(QString("background-color: %1; color: rgb(255,255,255)").arg(game.getColor(1, 3).name()));

    ui->element31->setText(QString::number(game.getValue(2, 0)));
    ui->element31->setStyleSheet(QString("background-color: %1; color: rgb(255,255,255)").arg(game.getColor(2, 0).name()));
    ui->element32->setText(QString::number(game.getValue(2, 1)));
    ui->element32->setStyleSheet(QString("background-color: %1; color: rgb(255,255,255)").arg(game.getColor(2, 1).name()));
    ui->element33->setText(QString::number(game.getValue(2, 2)));
    ui->element33->setStyleSheet(QString("background-color: %1; color: rgb(255,255,255)").arg(game.getColor(2, 2).name()));
    ui->element34->setText(QString::number(game.getValue(2, 3)));
    ui->element34->setStyleSheet(QString("background-color: %1; color: rgb(255,255,255)").arg(game.getColor(2, 3).name()));

    ui->element41->setText(QString::number(game.getValue(3, 0)));
    ui->element41->setStyleSheet(QString("background-color: %1; color: rgb(255,255,255)").arg(game.getColor(3, 0).name()));
    ui->element42->setText(QString::number(game.getValue(3, 1)));
    ui->element42->setStyleSheet(QString("background-color: %1; color: rgb(255,255,255)").arg(game.getColor(3, 1).name()));
    ui->element43->setText(QString::number(game.getValue(3, 2)));
    ui->element43->setStyleSheet(QString("background-color: %1; color: rgb(255,255,255)").arg(game.getColor(3, 2).name()));
    ui->element44->setText(QString::number(game.getValue(3, 3)));
    ui->element44->setStyleSheet(QString("background-color: %1; color: rgb(255,255,255)").arg(game.getColor(3, 3).name()));

    ui->element11->update();
    ui->element12->update();
    ui->element13->update();
    ui->element14->update();

    ui->element21->update();
    ui->element22->update();
    ui->element23->update();
    ui->element24->update();

    ui->element31->update();
    ui->element32->update();
    ui->element33->update();
    ui->element34->update();

    ui->element41->update();
    ui->element42->update();
    ui->element43->update();
    ui->element44->update();

    ui->labelScorePoints->setText(QString::number(game.calculateScore()));
}
