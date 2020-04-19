#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QHostAddress>
#include <QWebSocket>
#include "buttontimer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString URL;
    bool isConnected;


private slots:
    void on_connectButton_clicked();

    void onConnected();
    void closed();
    void stateChanged();
    void publishtopic();

    void on_moveForwardButton_pressed();

    void on_moveForwardButton_released();

    void on_moveBackwardsButton_pressed();

    void on_moveBackwardsButton_released();

    void on_moveRotateLeftButton_pressed();

    void on_moveRotateLeftButton_released();

    void on_moveRotateRightButton_pressed();

    void on_moveRotateRightButton_released();

    void moveforward();
    void movebackwards();
    void rotateleft();
    void rotateright();

    void onTextMessageReceived(QString message);


private:
    Ui::MainWindow *ui;
    QWebSocket *socket;
    buttontimer *btntimer;
};

#endif // MAINWINDOW_H
