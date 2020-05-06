#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QVBoxLayout"
#include "gomokuqgraphicsview.h"
#include "gomokuqgraphicsscene.h"
#include <QGraphicsScene>
#include <QRect>
#include "config.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    view = new GomokuQGraphicsView();
    ui->verticalLayout->addWidget(view);
    connect((GomokuQGraphicsScene*)view->scene(), &GomokuQGraphicsScene::infoChanged,
            this, &MainWindow::changeInfo);
    ((GomokuQGraphicsScene*)view->scene())->init();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConfig_triggered()
{
    auto scene = ((GomokuQGraphicsScene*)view->scene());
    auto dialog = new Config(scene->getWhiteNick(), scene->getBlackNick());
    if(dialog->exec() == QDialog::Accepted)
    {
        scene->setWhiteNick(dialog->whiteNick());
        scene->setBlackNick(dialog->blackNick());
    }
}
void MainWindow::changeInfo(QString text)
{
    ui->label->setText(text);
}


