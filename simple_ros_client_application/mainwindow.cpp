#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "buttontimer.h"
#include <QDebug>
#include <QMessageBox>
#include <QWebSocket>
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    isConnected(false),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    btntimer = new buttontimer();
    connect(btntimer, SIGNAL(timeout()), this, SLOT(publishtopic()));

    socket = new QWebSocket();

    connect(socket, &QWebSocket::connected, [this](){ onConnected(); });
    connect(socket, &QWebSocket::disconnected, [this](){ closed(); });
    connect(socket, &QWebSocket::stateChanged, [this](){ stateChanged(); });
    connect(socket, &QWebSocket::textMessageReceived, [this](const QString message){ onTextMessageReceived(message); });
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), [=](QAbstractSocket::SocketError){
        qDebug() << socket->errorString();
    });

}

void MainWindow::onTextMessageReceived(QString message)
{
    qDebug() << "Message received:" << message;
}

void MainWindow::publishtopic(){

    QString btn_name = btntimer->get_buttonname();

    if (btn_name == "ForwardButton"){
        moveforward();
    }
    else if (btn_name == "BackwardsButton"){
        movebackwards();
    }
    else if (btn_name == "RotateLeftButton"){
        rotateleft();
    }
    else if (btn_name == "RotateRightButton"){
        rotateright();
    }
    else{
        qDebug() << "Unknown button pressed.";
    }

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onConnected()
{
    qDebug() << socket->state();

    isConnected = true;
    ui->connectButton->setText("Disconnect");
}

void MainWindow::closed()
{
    qDebug() << socket->state();

    isConnected = false;
    ui->connectButton->setText("Connect");
}

void MainWindow::stateChanged()
{
    qDebug() << "State changed.";
    qDebug() << socket->state();
    qDebug() << socket->error();

    if(socket->state() == QAbstractSocket::UnconnectedState && socket->error() == QAbstractSocket::RemoteHostClosedError)
    {
       QMessageBox::critical(this, tr("Failed to connect to server"),
                                   tr("Unable to a connect to server, please check your network connection."),
                                   QMessageBox::Ok);

    }
}

void MainWindow::on_connectButton_clicked()
{

    if(ui->IPaddressTextbox->toPlainText().isEmpty() || ui->portTextbox->toPlainText().isEmpty())
    {
       QMessageBox::warning(this, tr("Missing inputs"),
                                  tr("IP address and port information are needed."),
                                  QMessageBox::Ok);
    }
    else
    {

        if(ui->connectButton->text().toStdString() == "Disconnect")
        {
            socket->close();
            ui->connectButton->setText("Connect");

        }
        else
        {

            QString URL;

            URL = "ws://"+QString(ui->IPaddressTextbox->toPlainText())+":"+QString(ui->portTextbox->toPlainText());

            qDebug() << URL;
            socket->open((QUrl(URL)));

            if(socket->state() == QAbstractSocket::ConnectedState || socket->state() == QAbstractSocket::ConnectingState)
            {
                ui->connectButton->setText("Disconnect");

            }


        }
    }


}


void MainWindow::moveforward()
{

    if(isConnected){

        QJsonObject json;
        QJsonObject msgjson;
        QJsonObject linearjson;
        QJsonObject angularjson;

        json["op"] = "publish";
        json["topic"] = "/turtle1/cmd_vel";
        linearjson["x"] = 1.0;
        linearjson["y"] = 0.0;
        linearjson["z"] = 0.0;
        angularjson["x"] = 0.0;
        angularjson["y"] = 0.0;
        angularjson["z"] = 0.0;

        msgjson["linear"] = linearjson;
        msgjson["angular"] = angularjson;
        json["msg"] = msgjson;


        QJsonDocument doc(json);
        QByteArray docByteArray = doc.toJson(QJsonDocument::Compact);
        QString strJson = QLatin1String(docByteArray);

        qDebug() << strJson;

        //QString data_str = "up";
        //QByteArray data = data_str.toUtf8();
        socket->sendTextMessage(strJson);
        qDebug() << socket->errorString();
        qDebug() << socket->error();
    }

}

void MainWindow::rotateleft()
{
    if(isConnected){

        QJsonObject json;
        QJsonObject msgjson;
        QJsonObject linearjson;
        QJsonObject angularjson;

        json["op"] = "publish";
        json["topic"] = "/turtle1/cmd_vel";
        linearjson["x"] = 0.0;
        linearjson["y"] = 0.0;
        linearjson["z"] = 0.0;
        angularjson["x"] = 0.0;
        angularjson["y"] = 0.0;
        angularjson["z"] = 1.0;

        msgjson["linear"] = linearjson;
        msgjson["angular"] = angularjson;
        json["msg"] = msgjson;


        QJsonDocument doc(json);
        QByteArray docByteArray = doc.toJson(QJsonDocument::Compact);
        QString strJson = QLatin1String(docByteArray);

        qDebug() << strJson;

        socket->sendTextMessage(strJson);
        qDebug() << socket->errorString();
        qDebug() << socket->error();
    }
}

void MainWindow::rotateright()
{

    if(isConnected){
        QJsonObject json;
        QJsonObject msgjson;
        QJsonObject linearjson;
        QJsonObject angularjson;

        json["op"] = "publish";
        json["topic"] = "/turtle1/cmd_vel";
        linearjson["x"] = 0.0;
        linearjson["y"] = 0.0;
        linearjson["z"] = 0.0;
        angularjson["x"] = 0.0;
        angularjson["y"] = 0.0;
        angularjson["z"] = -1.0;

        msgjson["linear"] = linearjson;
        msgjson["angular"] = angularjson;
        json["msg"] = msgjson;


        QJsonDocument doc(json);
        QByteArray docByteArray = doc.toJson(QJsonDocument::Compact);
        QString strJson = QLatin1String(docByteArray);

        qDebug() << strJson;

        socket->sendTextMessage(strJson);
        qDebug() << socket->errorString();
        qDebug() << socket->error();
    }

}

void MainWindow::movebackwards()
{
    if(isConnected){
        QJsonObject json;
        QJsonObject msgjson;
        QJsonObject linearjson;
        QJsonObject angularjson;

        json["op"] = "publish";
        json["topic"] = "/turtle1/cmd_vel";
        linearjson["x"] = -1.0;
        linearjson["y"] = 0.0;
        linearjson["z"] = 0.0;
        angularjson["x"] = 0.0;
        angularjson["y"] = 0.0;
        angularjson["z"] = 0.0;

        msgjson["linear"] = linearjson;
        msgjson["angular"] = angularjson;
        json["msg"] = msgjson;


        QJsonDocument doc(json);
        QByteArray docByteArray = doc.toJson(QJsonDocument::Compact);
        QString strJson = QLatin1String(docByteArray);

        qDebug() << strJson;

        socket->sendTextMessage(strJson);

        qDebug() << socket->errorString();
        qDebug() << socket->error();


    }
}



void MainWindow::on_moveForwardButton_pressed()
{
    btntimer->set_buttonname("ForwardButton");
    btntimer->start(90);
}

void MainWindow::on_moveForwardButton_released()
{
    btntimer->stop();
}

void MainWindow::on_moveBackwardsButton_pressed()
{
    btntimer->set_buttonname("BackwardsButton");
    btntimer->start(90);
}

void MainWindow::on_moveBackwardsButton_released()
{
    btntimer->stop();
}

void MainWindow::on_moveRotateLeftButton_pressed()
{
    btntimer->set_buttonname("RotateLeftButton");
    btntimer->start(90);
}

void MainWindow::on_moveRotateLeftButton_released()
{
    btntimer->stop();
}

void MainWindow::on_moveRotateRightButton_pressed()
{
    btntimer->set_buttonname("RotateRightButton");
    btntimer->start(90);
}

void MainWindow::on_moveRotateRightButton_released()
{
    btntimer->stop();
}
