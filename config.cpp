#include "config.h"
#include "ui_config.h"

Config::Config(QString player1, QString player2, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config)
{
    ui->setupUi(this);
    ui->whiteNickInput->setText(player1);
    ui->blackNickInput->setText(player2);
}

Config::~Config()
{
    delete ui;
}


QString Config::whiteNick() {
    return ui->whiteNickInput->text();
}
QString Config::blackNick(){
    return ui->blackNickInput->text();
}
